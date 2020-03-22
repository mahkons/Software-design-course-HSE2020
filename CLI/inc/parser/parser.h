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

    using ParserResult = Result<std::vector<std::shared_ptr<NCommand::Command>>, std::string>;

    /**
     * Class for parsing commands from input string
     */ 
    class Parser {
    public:
        explicit Parser(Environment& env, const NCommand::CommandFactory& command_factory)
            : tokenizer_(), variables_substitutor_(env), commands_parser_(command_factory) {};
        ~Parser() = default;
        Parser(const Parser&) = delete;
        Parser& operator=(const Parser&) = delete;

        /**
         * Returns parsed commands list or an error if one occured during parsing
         */ 
        ParserResult parse(const std::string& user_command) const;

    private:
        const Tokenizer tokenizer_;
        const VariablesSubstitutor variables_substitutor_;
        const CommandsParser commands_parser_;
    };

} // namespace NCLI::NParser
