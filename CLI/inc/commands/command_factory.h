#pragma once

#include <string>
#include <vector>
#include <functional>
#include <regex>

#include "environment.h"
#include "result.h"
#include "commands/command.h"

namespace NCLI::NCommand {

    using FactoryResult = Result<std::shared_ptr<Command>, std::string>;
    using CommandGenerator = std::function<FactoryResult(const std::vector<std::string>&)>;

    /* Factory class that creates command by given arguments */
    class CommandFactory {
    public:
        /* Returns pointer to command by it's argument or an error message
         *  if construction failes or no command matches
         * {param} args should not be empty and it's first element used as command name
         * Compares command name with registered commands regex in order of registration
         *  until finds a match. Uses default command if no match found
         * Returns result of applying matched command generator to given arguments or
         *  an error message of fitted command wasn't found */
        FactoryResult parse_command(std::vector<std::string> args) const;
        /* Adds command generator */
        void register_command(const std::regex& name_regex,
                const CommandGenerator& command_generator);
        /* Adds default command generator
         * If one already was registered, new one replaces it */
        void register_default_command(
                const CommandGenerator& command_generator);


    private:
        std::vector<std::pair<std::regex, CommandGenerator>> registered_commands_;
        std::optional<CommandGenerator> default_command_;

    };

} // namespace NCLI::NCommand
