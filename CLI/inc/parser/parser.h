#pragma once

#include <vector>
#include <string>
#include <memory>

#include "environment.h"
#include "result.h"
#include "parser/tokenizer.h"
#include "parser/variables_substitutor.h"
#include "parser/commands_parser.h"
#include "commands/command.h"

namespace NCLI::NParser {

    using parserResult = Result<std::vector<std::shared_ptr<NCommand::Command>>, std::string>;

    class Parser {
    public:
        explicit Parser(Environment& env, NCommand::CommandFactory& command_factory)
            : tokenizer_(), variables_substitutor_(env), commands_parser_(command_factory) {};
        ~Parser() = default;
        Parser(const Parser&) = delete;
        Parser& operator=(const Parser&) = delete;

        parserResult parse(std::string user_command);

    private:
        Tokenizer tokenizer_;
        VariablesSubstitutor variables_substitutor_;
        CommandsParser commands_parser_;
    };

} // namespace NCLI::NParser
