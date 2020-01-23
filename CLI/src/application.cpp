#include <iostream>
#include <string>

#include "application.h"
#include "commands/command.h"
#include "commands/execution_outcome.h"

namespace NCLI {

    Application::Application() : env_(), parser_(env_) {}

    void Application::run() {
        NCommand::ExecutionStatus lastExecutedStatus = NCommand::ExecutionStatus::success;
        do {
            std::cout << "-> ";
            std::string user_command;
            getline(std::cin, user_command);
        } while (lastExecutedStatus != NCommand::ExecutionStatus::exit);
    }

} // namespace NCLI
