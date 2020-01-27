#pragma once

#include <vector>
#include <iostream>
#include <memory>

#include "commands/execution_result.h"
#include "commands/command.h"

namespace NCLI {
    
    /* Class for commands execution */
    class Executor {
    public:
        /* Executes commands in order of input
         * First command input stream {param} is
         * Last command output stream {param} os
         * Not first command uses previous command output as input
         * If some command executes with result status that differs from ExecutionStatus::success
         *  execution terminates instantly and that result returned */ 
        NCommand::ExecutionResult execute(const std::vector<std::shared_ptr<NCommand::Command>>& commands,
                std::istream& is, std::ostream& os);
    };

} // namespace NCLI
