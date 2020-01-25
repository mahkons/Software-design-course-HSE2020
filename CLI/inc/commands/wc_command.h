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

    class WcCommand : public Command {
    public:
        WcCommand() {};
        WcCommand(std::string filename) : filename_(std::filesystem::absolute(filename)) {};
        virtual ExecutionResult execute(std::istream& is, std::ostream& os) override;

        static Result<std::shared_ptr<Command>, std::string> create_command(std::vector<std::string> args);
    private:
        ExecutionResult execute_helper(std::istream& is, std::ostream& os);
    private:
        std::optional<std::string> filename_;
    };

} // namespace NCLI::NCommand

