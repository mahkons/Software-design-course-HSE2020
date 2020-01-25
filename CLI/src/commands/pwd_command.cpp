#include <filesystem>

#include "commands/pwd_command.h"

namespace NCLI::NCommand {

    Result<std::shared_ptr<Command>, std::string> PwdCommand::create_command(
            std::vector<std::string>) {
        return Result<std::shared_ptr<Command>, std::string>(
                Ok(std::shared_ptr<Command>(new PwdCommand())));
    }

    ExecutionResult PwdCommand::execute(std::istream&, std::ostream& os) {
        os << std::filesystem::current_path() << '\n';
        return ExecutionResult(ExecutionStatus::success, "");
    }

} // namespace NCLI::NCommand



