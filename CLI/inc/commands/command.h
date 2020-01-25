#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "commands/execution_result.h"

namespace NCLI::NCommand {

    class Command {
    public:
        Command() {}
        virtual ExecutionResult execute(std::istream&, std::ostream&) { 
            return ExecutionResult(ExecutionStatus::success, "");
        };
    };

} // namespace NCLI::NCommand
