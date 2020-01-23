#include <vector>
#include <string>

#include "parser/substitutor.h"

namespace NCLI::NParser {

    Token substitute(const Token& token) {


        return token;
    }

    std::vector<Token> VariablesSubstitutor::substitute(const std::vector<Token>& tokens) {
        std::vector<Token> tokens_after_substitution;
        for (const Token& token : tokens) {
            if (token.surrounding_quotes == TypeOfQuotation::strong) {
                tokens_after_substitution.push_back(token);
            } else {
                tokens_after_substitution.push_back(substitute(token));
            }
        }

        return tokens_after_substitution;
    }

} // namespace NCLI::NParser
