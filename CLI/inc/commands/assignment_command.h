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

    /* Command that modifies Environment
     * by setting variable value */
    class AssignmentCommand : public Command {
    public:
        /* After execution, in given {param}env
         * variable {param}variable_name will be set to {param}variable_value */
        AssignmentCommand(Environment& env,
                const std::string& variable_name,
                const std::string& variable_value)
            : env_(env), variable_name_(variable_name), variable_value_(variable_value) {};
        virtual ExecutionResult execute(std::istream& is, std::ostream& os) override;

        /* Parses variable_name and variable_value from args[0]
         * supports only one assignment in args[0] */
        static Result<std::shared_ptr<Command>, std::string> create_command(
                Environment& env, const std::vector<std::string>& args);
    private:
        Environment& env_;
        const std::string variable_name_;
        const std::string variable_value_;
    };

} // namespace NCLI::NCommand
