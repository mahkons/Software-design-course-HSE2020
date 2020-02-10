#include <fstream>

#include "commands/wc_command.h"

namespace NCLI::NCommand {

    Result<std::shared_ptr<Command>, std::string> WcCommand::create_command(
            const std::vector<std::string>& args) {
        if (args.size() <= 1) {
            return Result<std::shared_ptr<Command>, std::string>(
                    Ok(std::shared_ptr<Command>(new WcCommand())));
        } else {
            return Result<std::shared_ptr<Command>, std::string>(
                    Ok(std::shared_ptr<Command>(new WcCommand(args[1]))));
        }
    }

    ExecutionResult WcCommand::execute_helper(std::istream& is, std::ostream& os) {
        int line_count = 0;
        int word_count = 0;
        int char_count = 0;
        enum class State { whitespace, word };
        State cur_state = State::whitespace;

        char c;
        while (is.get(c)) {
            char_count++;
            if (c == '\n') {
                line_count++;
            }

            if (isspace(c)) {
                cur_state = State::whitespace;
            } else {
                if (cur_state == State::whitespace) {
                    word_count++;
                }
                cur_state = State::word;
            }
        }
        os << line_count << ' ' << word_count << ' ' << char_count << '\n';
        return ExecutionResult(ExecutionStatus::success, "");
    }

    ExecutionResult WcCommand::execute(std::istream& is, std::ostream& os) {
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
