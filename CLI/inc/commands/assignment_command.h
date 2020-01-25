#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "commands/command.h"
#include "commands/execution_result.h"

namespace NCLI::NCommand {

    class AssignmentCommand : public Command {
    public:
        AssignmentCommand(std::string variable_name, std::string variable_value);
        virtual ExecutionResult execute(std::istream& is, std::ostream& os) override;
    };

} // namespace NCLI::NCommand
