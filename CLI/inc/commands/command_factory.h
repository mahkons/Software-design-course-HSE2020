#pragma once

#include <string>

#include "environment.h"
#include "result.h"
#include "commands/command.h"

namespace NCLI::NCommand {

    using factoryResult = Result<Command, std::string>;

    class CommandFactory {
    public:
        CommandFactory(Environment& env) : env_(env) {}

        factoryResult create_command(std::vector<std::string> args);

    private:
        Environment& env_;

    };

} // namespace NCLI::NCommand
