#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <filesystem>
#include <regex>

#include "result.h"
#include "commands/command.h"
#include "commands/execution_result.h"

namespace NCLI::NCommand {

    /**
     * Command that finds pattern in file if file is specified
     *  or in input stream otherwise
     */ 
    class GrepCommand : public Command {
    public:
        /**
         */
        GrepCommand(const std::regex& pattern, int trailing_context_lines)
            : pattern_(pattern), trailing_context_lines_(trailing_context_lines) {};
        /**
         */
        // TODO think about adding builder
        GrepCommand(const std::string& filename, const std::regex& pattern, int trailing_context_lines)
            : filename_(std::filesystem::absolute(filename)), pattern_(pattern),
            trailing_context_lines_(trailing_context_lines) {};
        /**
         */ 
        virtual ExecutionResult execute(std::istream& is, std::ostream& os) override;

        /**
         */ 
        static Result<std::shared_ptr<Command>, std::string> create_command(
                const std::vector<std::string>& args);
    private:
        ExecutionResult execute_helper(std::istream& is, std::ostream& os);

    private:
        const std::optional<std::string> filename_;
        const std::regex pattern_;

        const int trailing_context_lines_;
    };

} // namespace NCLI::NCommand

