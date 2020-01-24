#pragma once

#include <vector>
#include <string>

#include "environment.h"
#include "result.h"
#include "parser/tokenizer.h"
#include "parser/variables_substitutor.h"
#include "commands/command.h"

namespace NCLI::NParser {

    using parserResult = Result<std::vector<std::string>, std::string>;

    class Parser {
    public:
        explicit Parser(Environment& env)
            : tokenizer_(), variables_substitutor_(env) {};
        ~Parser() = default;
        Parser(const Parser&) = delete;
        Parser& operator=(const Parser&) = delete;

        parserResult parse(std::string user_command);

    private:
        Tokenizer tokenizer_;
        VariablesSubstitutor variables_substitutor_;
    };

} // namespace NCLI::NParser
