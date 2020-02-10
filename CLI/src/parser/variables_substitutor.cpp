#include <vector>
#include <string>

#include "parser/variables_substitutor.h"

namespace NCLI::NParser {

    namespace {
        std::vector<std::string> split(std::string text, const std::string& delims) {
            std::vector<std::string> splitted_text;

            size_t cur_pos = -1;
            do {
                size_t new_pos = text.find_first_of(delims, cur_pos + 1);
                splitted_text.push_back(text.substr(cur_pos + 1, new_pos - cur_pos - 1));
                cur_pos = new_pos;
            } while (cur_pos != std::string::npos);
            return splitted_text;
        }
    }

    Token VariablesSubstitutor::substitute(const Token& token) const {
        if (token.surrounding_quotes == TypeOfQuotation::strong) {
            return token;
        }
        std::vector<std::string> splitted_text = split(token.value, "$");
        std::string substituted_text = splitted_text[0];
        for (size_t i = 1; i < splitted_text.size(); i++) {
            substituted_text += env_.get_variable(splitted_text[i]);
        }

        return Token(substituted_text, token.surrounding_quotes);
    }

    std::vector<Token> VariablesSubstitutor::substitute(const std::vector<Token>& tokens) const {
        std::vector<Token> tokens_after_substitution;
        for (const Token& token : tokens) {
            tokens_after_substitution.push_back(substitute(token));
        }
        return tokens_after_substitution;
    }

} // namespace NCLI::NParser
