#include <iostream>
#include <string>
#include <regex>

#include "application.h"
#include "commands/execution_result.h"
#include "commands/command.h"
#include "commands/wc_command.h"

namespace NCLI {

    namespace {
        NCommand::CommandFactory create_command_factory() {
            NCommand::CommandFactory factory;
            factory.register_command(std::regex("wc"), NCommand::WcCommand::create_command);
            return factory;
        }
    }

    Application::Application() :
        env_(), command_factory_(create_command_factory()), parser_(env_, command_factory_) { }

    void Application::run() {
        while (true) {
            std::cout << "-> ";
            std::string user_command;
            getline(std::cin, user_command);

            NParser::parserResult parse_result = parser_.parse(user_command);
            if (!parse_result) {
                std::cout << parse_result.get_error() << std::endl;
                continue;
            }
            NCommand::ExecutionResult execution_result =
                executor_.execute(parse_result.get_ok(), std::cin, std::cout);

            std::cout << execution_result.message;

            if (execution_result.status == NCommand::ExecutionStatus::exit) {
                break;
            }
        }
    }

} // namespace NCLI
