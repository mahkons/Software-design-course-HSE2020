#include <vector>
#include <string>

#include "parser/parser.h"

namespace NCLI::NParser {

    using parserResult = Result<std::vector<std::string>, std::string>;

    parserResult Parser::parse(std::string user_command) {
        Result<std::vector<Token>, std::string> tokens = tokenizer_.tokenize(user_command);
        if (!tokens) {
            return parserResult(Error(tokens.get_error()));
        }
        std::vector<Token> substituted = variables_substitutor_.substitute(tokens.get_ok());

        std::vector<std::string> out;
        for (const Token& token : substituted) {
            out.push_back(token.value);
        }
        return parserResult(Ok(out));
    }

} // namespace NCLI::NParser
