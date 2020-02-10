#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <memory>
#include <filesystem>

#include "result.h"
#include "commands/command.h"
#include "commands/execution_result.h"

namespace NCLI::NCommand {

    /**
     * Command that writes file content to output stream if file is specified
     * or copies input stream to output stream otherwise
     */
    class CatCommand : public Command {
    public:
        /**
         * Command will copy input stream to output stream
         */
        CatCommand() {};
        /**
         * Command will write file content to output stream
         */
        CatCommand(const std::string& filename) : filename_(std::filesystem::absolute(filename)) {};
        /**
         * Writes file content to output stream if file is specified
         * or copies input stream to output stream otherwise
         * If file is specified but cannot be open, returns result with ExecutionStatus::error
         */
        virtual ExecutionResult execute(std::istream& is, std::ostream& os) override;

        /**
         * If args[1] given, uses it as file to get content from
         * otherwise creates command that copies input stream to output stream
         */
        static Result<std::shared_ptr<Command>, std::string> create_command(
                const std::vector<std::string>& args);
    private:
        ExecutionResult execute_helper(std::istream& is, std::ostream& os);
    private:
        const std::optional<std::string> filename_;
    };

} // namespace NCLI::NCommand
