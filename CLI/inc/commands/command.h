#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "commands/execution_result.h"

namespace NCLI::NCommand {

    class Command {
    public:
        Command(std::vector<std::string>) {}
        virtual ExecutionStatus execute(std::iostream& is, std::ostream& os) = delete;
    };

} // namespace NCLI::NCommand
