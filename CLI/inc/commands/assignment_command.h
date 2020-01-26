#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "result.h"
#include "environment.h"
#include "commands/command.h"
#include "commands/execution_result.h"

namespace NCLI::NCommand {

    class AssignmentCommand : public Command {
    public:
        AssignmentCommand(Environment& env, std::string variable_name, std::string variable_value)
            : env_(env), variable_name_(variable_name), variable_value_(variable_value) {};
        virtual ExecutionResult execute(std::istream& is, std::ostream& os) override;

        static Result<std::shared_ptr<Command>, std::string> create_command(
                Environment& env, std::vector<std::string> args);
    private:
        Environment& env_;
        std::string variable_name_;
        std::string variable_value_;
    };

} // namespace NCLI::NCommand
