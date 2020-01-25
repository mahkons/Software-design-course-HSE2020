#pragma once

#include <vector>
#include <iostream>
#include <memory>

#include "commands/execution_result.h"
#include "commands/command.h"

namespace NCLI {
    
    class Executor {
    public:
        NCommand::ExecutionResult execute(const std::vector<std::shared_ptr<NCommand::Command>>& commands,
                std::istream& is, std::ostream& os);
    };

} // namespace NCLI
