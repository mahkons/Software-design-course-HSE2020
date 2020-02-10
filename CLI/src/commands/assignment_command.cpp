#include "commands/assignment_command.h"

namespace NCLI::NCommand {

    Result<std::shared_ptr<Command>, std::string> AssignmentCommand::create_command(
            Environment& env, const std::vector<std::string>& args) {

        size_t assignment_pos = args[0].find_first_of("=");
        if (args[0].find_first_of("=", assignment_pos + 1) != std::string::npos) {
            return Result<std::shared_ptr<Command>, std::string>(
                    Error("Multiple assignment are not supported: " + args[0]));
        }
        if (assignment_pos == 0) {
            return Result<std::shared_ptr<Command>, std::string>(
                    Error("Variable name should not be empty: " + args[0]));
        }

        return Result<std::shared_ptr<Command>, std::string>(
                Ok(std::shared_ptr<Command>(new AssignmentCommand(env,
                            args[0].substr(0, assignment_pos), args[0].substr(assignment_pos + 1)))));
    }

    ExecutionResult AssignmentCommand::execute(std::istream&, std::ostream&) {
        env_.set_variable(variable_name_, variable_value_);
        return ExecutionResult(ExecutionStatus::success, "");
    }

} // namespace NCLI::NCommand

