#include <iostream>
#include <string>

#include "application.h"
#include "commands/execution_result.h"
#include "commands/command.h"

namespace NCLI {

    Application::Application() : env_(), parser_(env_) {}

    void Application::run() {
        NCommand::ExecutionStatus lastExecutionStatus = NCommand::ExecutionStatus::success;
        do {
            std::cout << "-> ";
            std::string user_command;
            getline(std::cin, user_command);

            auto res = parser_.parse(user_command);
            if (res) {
                for (auto x : res.get_ok()) {
                    std::cout << x << std::endl;
                }
            } else {
                std::cout << res.get_error() << std::endl;
            }

            if (user_command == "exit") {
                lastExecutionStatus = NCommand::ExecutionStatus::exit;
            }
        } while (lastExecutionStatus != NCommand::ExecutionStatus::exit);
    }

} // namespace NCLI
