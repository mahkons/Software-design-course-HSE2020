#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "commands/execution_result.h"

namespace NCLI::NCommand {

    /**
     * Interface for objects that supports execution
     * with input and output streams as arguments
     * and ExecutionResult as result
     */ 
    class Command {
    public:
        Command() = default;
        virtual ~Command() = default;
        virtual ExecutionResult execute(std::istream&, std::ostream&) { 
            return ExecutionResult(ExecutionStatus::success, "");
        };
    };

} // namespace NCLI::NCommand
