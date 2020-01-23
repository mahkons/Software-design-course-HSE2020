#pragma once

#include <vector>
#include <string>

#include "commands/command.h"

namespace NCLI::NParser {

    class ParseResult {
    public:
        explicit ParseResult(std::vector<NCommand::Command>&& result)
            : result(result), error_occured(0) {}
        explicit ParseResult(std::string&& error_message)
            : error_occured(1), error_message(error_message) {}

        std::vector<NCommand::Command> result;
        bool error_occured;
        std::string error_message;
    };

} // namespace NCLI::NParser
