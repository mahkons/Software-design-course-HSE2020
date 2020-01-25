#include "commands/echo_command.h"

namespace NCLI::NCommand {

    Result<std::shared_ptr<Command>, std::string> EchoCommand::create_command(
            std::vector<std::string> args) {

        std::string acc = "";
        for (size_t i = 1; i < args.size(); i++) {
            if (i != 1) {
                acc += " ";
            }
            acc += args[i];
        }
        acc += '\n';
        return Result<std::shared_ptr<Command>, std::string>(
                Ok(std::shared_ptr<Command>(new EchoCommand(acc))));
    }

    ExecutionResult EchoCommand::execute(std::istream&, std::ostream& os) {
        os << text_;
        return ExecutionResult(ExecutionStatus::success, "");
    }

} // namespace NCLI::NCommand

