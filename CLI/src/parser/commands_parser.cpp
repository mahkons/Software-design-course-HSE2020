#include "parser/commands_parser.h"

namespace NCLI::NParser {

    commandsParserResult CommandsParser::parse_commands(const std::vector<Token>& tokens) {
        std::vector<std::shared_ptr<NCommand::Command>> parsed_commands;
        std::vector<std::string> args;

        for (size_t i = 0; i <= tokens.size(); i++) {
            if (i == tokens.size() || tokens[i].value == "|") {
                if (args.empty()) {
                    return commandsParserResult(Error(std::string("Parser Error: empty command")));
                }
                NCommand::factoryResult command = command_factory_.parse_command(args);
                args.clear();

                if (!command) {
                    return commandsParserResult(Error(command.get_error()));
                }
                parsed_commands.push_back(command.get_ok());
            } else {
                args.push_back(tokens[i].value);
            }
        }
        return commandsParserResult(Ok(parsed_commands));
    }

} // namespace NCLI::NParser
