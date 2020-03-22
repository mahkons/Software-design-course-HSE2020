#include "commands/exit_command.h"

namespace NCLI::NCommand {

    Result<std::shared_ptr<Command>, std::string> ExitCommand::create_command(
            const std::vector<std::string>&) {
        return Result<std::shared_ptr<Command>, std::string>(
                Ok(std::shared_ptr<Command>(new ExitCommand())));
    }

    ExecutionResult ExitCommand::execute(std::istream&, std::ostream&) {
        return ExecutionResult(ExecutionStatus::exit, "");
    }

} // namespace NCLI::NCommand


