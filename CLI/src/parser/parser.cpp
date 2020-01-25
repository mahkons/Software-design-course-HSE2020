#include <vector>
#include <string>

#include "parser/parser.h"

namespace NCLI::NParser {

    parserResult Parser::parse(std::string user_command) {
        Result<std::vector<Token>, std::string> tokens = tokenizer_.tokenize(user_command);
        if (!tokens) {
            return parserResult(Error(tokens.get_error()));
        }
        std::vector<Token> substituted = variables_substitutor_.substitute(tokens.get_ok());
        return commands_parser_.parse_commands(substituted);
    }

} // namespace NCLI::NParser
