#pragma once

#include <vector>

#include "environment.h"
#include "parser/token.h"

namespace NCLI::NParser {
        
    class VariablesSubstitutor {
    public:
        explicit VariablesSubstitutor(Environment& env) : env_(env) {};

        Token substitute(const Token& token);
        std::vector<Token> substitute(const std::vector<Token>& tokens);
        
    private:
        Environment& env_;
    };

} // namespace NCLI::NParser
