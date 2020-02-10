#include <sstream>
#include <future>

#include "boost/asio.hpp"

#include "commands/external_command.h"

namespace NCLI::NCommand {

    namespace {
        std::string copy_stream(std::istream& is) {
            std::string line;
            std::string out = "";
            while (std::getline(is, line)) {
                out += line + '\n';
            }
            return out;
        }
    } // namespace

    Result<std::shared_ptr<Command>, std::string> ExternalCommand::create_command(
            std::vector<std::string> args) {

        bf::path path = bp::search_path(args[0]);

        if (path.empty()) {
            return Result<std::shared_ptr<Command>, std::string>(
                    Error("Unknown command: " + args[0]));
        }
        args = std::vector<std::string>(args.begin() + 1, args.end());
        return Result<std::shared_ptr<Command>, std::string>(
                Ok(std::shared_ptr<Command>(new ExternalCommand(path, args))));
    }

    ExecutionResult ExternalCommand::execute(std::istream& is, std::ostream& os) {
        boost::asio::io_service ios;

        bp::async_pipe input(ios);
        std::future<std::string> output;
        std::future<std::string> error;

        bp::child c;
        if (is.rdbuf() == std::cin.rdbuf()) {
            c = bp::child(path_, bp::args(args_),
                    bp::std_in < stdin, bp::std_out > output, bp::std_err > error, ios);
        } else {
            boost::asio::async_write(input, bp::buffer(copy_stream(is)),
                    [&input](auto, auto){ input.close(); });

            c = bp::child(path_, bp::args(args_),
                    bp::std_in < input, bp::std_out > output, bp::std_err > error, ios);
        }
        ios.run();
        c.wait();

        int exit_code = c.exit_code();

        if (exit_code == 0) {
            os << output.get();
            return ExecutionResult(ExecutionStatus::success, error.get());
        } else {
            return ExecutionResult(ExecutionStatus::error, error.get());
        }
    }

} // namespace NCLI::NCommand

