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
         * Command will output lines from input which contains pattern
         * and @param trailing_context_lines after each of them
         */
        GrepCommand(const std::regex& pattern, int trailing_context_lines)
            : pattern_(pattern), trailing_context_lines_(trailing_context_lines) {};
        /**
         * Command will output lines from input file which contains pattern
         * and @param trailing_context_lines after each of them
         */
        GrepCommand(const std::string& filename, const std::regex& pattern, int trailing_context_lines)
            : filename_(std::filesystem::absolute(filename)), pattern_(pattern),
            trailing_context_lines_(trailing_context_lines) {};

        /**
         * Search pattern in file if file is specified
         * or in input stream otherwise
         * If file is specified but cannot be open, returns result with ExecutionStatus::error
         */ 
        virtual ExecutionResult execute(std::istream& is, std::ostream& os) override;

        /**
         * Parses commands args
         * First argument should used as command name
         * If flag -i is given, pattern will ignore case
         * If flag -w if given, pattern will match only whole words
         * If argument -A NUM is given, NUM trailing lines would be printed after each line
         * First not named parameter will be used as pattern
         * All other not named parameters will be used as input files
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

