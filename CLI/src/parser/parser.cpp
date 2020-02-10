#include <vector>
#include <string>

#include "parser/parser.h"

namespace NCLI::NParser {

    ParserResult Parser::parse(const std::string& user_command) const {
        Result<std::vector<Token>, std::string> tokens = tokenizer_.tokenize(user_command);
        if (!tokens) {
            return ParserResult(Error(tokens.get_error()));
        }
        std::vector<Token> substituted = variables_substitutor_.substitute(tokens.get_ok());
        return commands_parser_.parse_commands(substituted);
    }

} // namespace NCLI::NParser
