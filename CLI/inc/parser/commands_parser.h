#pragma once

#include <vector>
#include <memory>

#include "parser/token.h"
#include "commands/command_factory.h"

namespace NCLI::NParser {

    using commandsParserResult = Result<std::vector<std::shared_ptr<NCommand::Command>>, std::string>;
    
    class CommandsParser {
    public:
        CommandsParser(const NCommand::CommandFactory& command_factory)
            : command_factory_(command_factory) {}

        commandsParserResult parse_commands(const std::vector<Token>& tokens);

    private:
        const NCommand::CommandFactory& command_factory_;
    };

} // namespace NCLI::NParser
