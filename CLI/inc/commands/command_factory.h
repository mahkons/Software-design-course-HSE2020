#pragma once

#include <string>
#include <vector>
#include <functional>
#include <regex>

#include "environment.h"
#include "result.h"
#include "commands/command.h"

namespace NCLI::NCommand {

    using factoryResult = Result<std::shared_ptr<Command>, std::string>;
    using commandGenerator = std::function<factoryResult(std::vector<std::string>)>;

    class CommandFactory {
    public:
        factoryResult parse_command(std::vector<std::string> args) const;
        void register_command(std::regex name_regex,
                commandGenerator command_generator);
        void register_default_command(
                commandGenerator command_generator);


    private:
        std::vector<std::pair<std::regex, commandGenerator>> registered_commands_;
        std::optional<commandGenerator> default_command_;

    };

} // namespace NCLI::NCommand
