#include <cassert>
#include <string>
#include <regex>

#include "commands/command_factory.h"
#include "commands/cat_command.h"
#include "commands/echo_command.h"
#include "commands/wc_command.h"
#include "commands/pwd_command.h"
#include "commands/exit_command.h"

namespace NCLI::NCommand {

    using factoryResult = Result<std::shared_ptr<Command>, std::string>;

    factoryResult CommandFactory::parse_command(std::vector<std::string> args) const {
        assert(((void)"First argument must correspond to command name", args.size() != 0));

        for (const auto& command_generator : registered_commands_) {
            if (std::regex_match(args[0], command_generator.first)) {
                return command_generator.second(args);
            }
        }

        if (default_command_.has_value()) {
            return default_command_.value()(args);
        }
        return factoryResult(Error(std::string("Unknown command: ") + args[0]));
    }

    void CommandFactory::register_command(const std::regex& name_regex,
            const CommandGenerator& command_generator) {
        registered_commands_.push_back(make_pair(name_regex, command_generator));
    }

    void CommandFactory::register_default_command(const CommandGenerator& command_generator) {
        default_command_ = command_generator;
    }

} // namespace NCLI::NCommand
