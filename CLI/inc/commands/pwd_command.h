#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "commands/command.h"
#include "commands/execution_result.h"

namespace NCLI::NCommand {

    class PwdCommand : public Command {
    public:
        PwdCommand();
        virtual ExecutionResult execute(std::istream& is, std::ostream& os) override;
    };

} // namespace NCLI::NCommand

