#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "result.h"
#include "commands/command.h"
#include "commands/execution_result.h"

namespace NCLI::NCommand {

    /**
     * Command that writes given arguments to output stream
     */ 
    class EchoCommand : public Command {
    public:
        EchoCommand(const std::string& text) : text_(text) {};
        /**
         * Writes text to output stream
         */ 
        virtual ExecutionResult execute(std::istream& is, std::ostream& os) override;

        /**
         * Concats given arguments, except of first one. Adds lineseparator to end of the string.
         * Uses result as text, which will be written during execution
         */ 
        static Result<std::shared_ptr<Command>, std::string> create_command(
                const std::vector<std::string>& args);
    private:
        const std::string text_;
    };

} // namespace NCLI::NCommand
