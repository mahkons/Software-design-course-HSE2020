#include <fstream>

#include "commands/cat_command.h"

namespace NCLI::NCommand {

    Result<std::shared_ptr<Command>, std::string> CatCommand::create_command(
            std::vector<std::string> args) {
        if (args.size() <= 1) {
            return Result<std::shared_ptr<Command>, std::string>(
                    Ok(std::shared_ptr<Command>(new CatCommand())));
        } else {
            return Result<std::shared_ptr<Command>, std::string>(
                    Ok(std::shared_ptr<Command>(new CatCommand(args[1]))));
        }
    }

    ExecutionResult CatCommand::execute_helper(std::istream& is, std::ostream& os) {
        char c;
        while (is.get(c)) {
            os << c;
        }
        return ExecutionResult(ExecutionStatus::success, "");
    }

    ExecutionResult CatCommand::execute(std::istream& is, std::ostream& os) {
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

