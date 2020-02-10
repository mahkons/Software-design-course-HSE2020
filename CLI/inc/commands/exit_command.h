#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "result.h"
#include "commands/command.h"
#include "commands/execution_result.h"

namespace NCLI::NCommand {

    /* Commans that returns exit status */
    class ExitCommand : public Command {
    public:
        ExitCommand() = default;
        /* Returns result with ExecutionStatus::exit */
        virtual ExecutionResult execute(std::istream& is, std::ostream& os) override;

        /* Creates pointer to new exit command. Ignores given arguments */
        static Result<std::shared_ptr<Command>, std::string> create_command(
                const std::vector<std::string>& args);
    };

} // namespace NCLI::NCommand

