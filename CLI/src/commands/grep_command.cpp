#include <fstream>

#include "boost/program_options.hpp"

#include "commands/grep_command.h"

namespace NCLI::NCommand {

    namespace po = boost::program_options;

    namespace {
    }

    Result<std::shared_ptr<Command>, std::string> GrepCommand::create_command(
             const std::vector<std::string>& args) {

        // Declare the supported options.
        po::options_description desc("Allowed options");
        desc.add_options()
            ("i,i", "case insensitivity")
            ("w,w", "force pattern to match only whole words")
            ("A,A", po::value<int>()->default_value(0), "print NUM lines of trailing context")
            ("pattern", po::value<std::string>(), "pattern")
            ("input-file", po::value<std::vector<std::string>>(), "input file");
        ;

        po::positional_options_description pd;
        pd.add("pattern", 1);
        pd.add("input-file", -1);

        try {
            auto parsed = po::command_line_parser(std::vector<std::string>(args.begin() + 1, args.end()))
                .options(desc)
                .positional(pd)
                .run();

            po::variables_map vm;
            po::store(parsed, vm);
            po::notify(vm);

            if (!vm.count("pattern")) {
                return Result<std::shared_ptr<Command>, std::string>(
                        Error(std::string("Pattern is not specified")));
            }

            std::string pattern_str = vm["pattern"].as<std::string>();
            // Add whole words matching
            if (vm.count("w")) {
                pattern_str = "(\\W|^)" + pattern_str + "(\\W|$)";
            }

            // Add case-insensitivity to pattern
            std::regex pattern;
            if (vm.count("i")) {
                pattern = std::regex(pattern_str, std::regex_constants::icase);
            } else {
                pattern = std::regex(pattern_str);
            }

            if (vm.count("input-file")) {
                std::vector<std::string> some = vm["input-file"].as<std::vector<std::string>>();
                assert(some.size());

                if (some.size() > 1) {
                    return Result<std::shared_ptr<Command>, std::string>(
                            Error(std::string("Multiple files are not supported")));
                }
                return Result<std::shared_ptr<Command>, std::string>(
                        Ok(std::shared_ptr<Command>(new GrepCommand(some[0], pattern, vm["A"].as<int>()))));
            } else {
                return Result<std::shared_ptr<Command>, std::string>(
                        Ok(std::shared_ptr<Command>(new GrepCommand(pattern, vm["A"].as<int>()))));
            }


        } catch (po::error& e) {
            return Result<std::shared_ptr<Command>, std::string>(
                    Error(std::string(e.what())));
        }
    }

    ExecutionResult GrepCommand::execute_helper(std::istream& is, std::ostream& os) {
        std::string line;
        int print_count = 0;

        while (std::getline(is, line)) {
            if (std::regex_search(line, pattern_)) {
                print_count = trailing_context_lines_ + 1;
            }
            if (print_count) {
                os << line << '\n';
            }
            print_count = std::max(0, print_count - 1);
        }

        return ExecutionResult(ExecutionStatus::success, "");
    }

    ExecutionResult GrepCommand::execute(std::istream& is, std::ostream& os) {
        if (filename_.has_value()) {
            std::ifstream file(filename_.value());
            if (!file.is_open()) {
                return ExecutionResult(NCommand::ExecutionStatus::error,
                        "Can't open file: " + filename_.value() + '\n');
            }
            return execute_helper(file, os);
        } else {
            return execute_helper(is, os);
        }
    }

} // namespace NCLI::NCommand


