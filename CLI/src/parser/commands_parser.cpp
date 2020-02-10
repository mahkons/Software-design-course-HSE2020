#include "parser/commands_parser.h"

namespace NCLI::NParser {

    CommandsParserResult CommandsParser::parse_commands(const std::vector<Token>& tokens) const {
        std::vector<std::shared_ptr<NCommand::Command>> parsed_commands;
        std::vector<std::string> args;

        for (size_t i = 0; i <= tokens.size(); i++) {
            if (i == tokens.size() || tokens[i].value == "|") {
                if (args.empty()) {
                    return CommandsParserResult(Error(std::string("Parser Error: empty command")));
                }
                NCommand::FactoryResult command = command_factory_.parse_command(args);
                args.clear();

                if (!command) {
                    return CommandsParserResult(Error(command.get_error()));
                }
                parsed_commands.push_back(command.get_ok());
            } else {
                args.push_back(tokens[i].value);
            }
        }
        return CommandsParserResult(Ok(parsed_commands));
    }

} // namespace NCLI::NParser
