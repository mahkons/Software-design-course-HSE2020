#include <cassert>

#include "commands/command_factory.h"

namespace NCLI::NCommand {

    using factoryResult = Result<Command, std::string>;

    factoryResult create_command(std::vector<std::string> args) {
        assert(("First argument must correspond to command name", args.size() != 0));

        return factoryResult(Error(args[0]));
    };

} // namespace NCLI::NCommand
