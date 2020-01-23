#pragma once

#include <vector>

#include "environment.h"
#include "parser/token.h"

namespace NCLI::NParser {
        
    class VariablesSubstitutor {
    public:
        explicit VariablesSubstitutor(const Environment& env) : env_(env) {};

        std::vector<Token> substitute(const std::vector<Token>& tokens);

    private:
        Token substitute(const Token& token);
        
    private:
        const Environment& env_;
    };

} // namespace NCLI::NParser
