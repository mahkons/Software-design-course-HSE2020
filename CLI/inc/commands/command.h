#pragma once

#include <iostream>
#include <string>

#include "commands/execution_outcome.h"

namespace NCLI::NCommand {

    class Command {
    public:
        virtual ExecutionStatus execute(std::iostream& is, std::ostream& os) = delete;
    };

} // namespace NCLI::NCommand
