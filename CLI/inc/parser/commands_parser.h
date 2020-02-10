#pragma once

#include <vector>
#include <memory>

#include "parser/token.h"
#include "commands/command_factory.h"

namespace NCLI::NParser {

    using CommandsParserResult = Result<std::vector<std::shared_ptr<NCommand::Command>>, std::string>;
    
    /* Class for parsing commands from tokens list */
    class CommandsParser {
    public:
        CommandsParser(const NCommand::CommandFactory& command_factory)
            : command_factory_(command_factory) {}

        /* Divides token lists in groups by pipes
         *  and creates command by applying commandFactory parseCommand method to those groups
         * If one of the groups is empty or commandFactory returnes an error
         *  during command construction, returnes an error,
         *  otherwise returns list of pointers to commands in order of
         *  corresponding tokens in input */
        CommandsParserResult parse_commands(const std::vector<Token>& tokens) const;

    private:
        const NCommand::CommandFactory& command_factory_;
    };

} // namespace NCLI::NParser
