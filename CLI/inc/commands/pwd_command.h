#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "result.h"
#include "commands/command.h"
#include "commands/execution_result.h"

namespace NCLI::NCommand {

    /* Command that writes current directory absolute path to output stream */
    class PwdCommand : public Command {
    public:
        PwdCommand() = default;
        /* Writes current directory absolute path to output stream
         * Always terminates with status ExecutionStatus::success */
        virtual ExecutionResult execute(std::istream& is, std::ostream& os) override;

        /* Creates new PwdCommand and returns pointer to it
         * Always terminated successfully */
        static Result<std::shared_ptr<Command>, std::string> create_command(std::vector<std::string> args);
    };

} // namespace NCLI::NCommand

