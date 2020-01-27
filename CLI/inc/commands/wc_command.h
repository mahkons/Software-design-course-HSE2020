#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <filesystem>
#include <memory>

#include "commands/command.h"
#include "commands/execution_result.h"
#include "result.h"

namespace NCLI::NCommand {

    /* Command that counts lines, bytes and words
     * in given file or input stream
     * and writes result to output stream */
    class WcCommand : public Command {
    public:
        /* Command will use content of input stream */
        WcCommand() {};
        /* Command will use content of specified file */
        WcCommand(std::string filename) : filename_(std::filesystem::absolute(filename)) {};
        /* Counts lines, bytes and words in specified file or input stream
         * If file is specified but cannot be open, returns result with ExecutionStatus::error */
        virtual ExecutionResult execute(std::istream& is, std::ostream& os) override;

        /* If args[1] given, uses it as file to get content from
         * otherwise creates command that copies input stream to output stream */
        static Result<std::shared_ptr<Command>, std::string> create_command(std::vector<std::string> args);
    private:
        ExecutionResult execute_helper(std::istream& is, std::ostream& os);
    private:
        std::optional<std::string> filename_;
    };

} // namespace NCLI::NCommand

