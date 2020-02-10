#pragma once

#include <vector>

#include "environment.h"
#include "parser/token.h"

namespace NCLI::NParser {
        
    /* Class for substitution of varables */
    class VariablesSubstitutor {
    public:
        explicit VariablesSubstitutor(Environment& env) : env_(env) {};

        /* Substitute variables in token string
         *  in form of {$[^$]*}(greedy) using environment
         * If token TypeOfQuotation is strong, no substitution applied */
        Token substitute(const Token& token) const;
        /* Substitutes variables in list of given tokens */
        std::vector<Token> substitute(const std::vector<Token>& tokens) const;
        
    private:
        Environment& env_;
    };

} // namespace NCLI::NParser
