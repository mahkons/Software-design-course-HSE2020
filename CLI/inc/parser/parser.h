#pragma once

#include <vector>
#include <string>

#include "environment.h"
#include "parser/parse_result.h"

namespace NCLI::NParser {

    class Parser {
    public:
        explicit Parser(const Environment& env) : env_(env) {};
        ~Parser() = default;
        Parser(const Parser&) = delete;
        Parser& operator=(const Parser&) = delete;

        ParseResult parse(std::string user_command);

    private:
        const Environment& env_;
    };

} // namespace NCLI::NParser
