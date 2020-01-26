#include <iostream>
#include <string>
#include <regex>
#include <functional>

#include "application.h"
#include "commands/execution_result.h"
#include "commands/command.h"
#include "commands/wc_command.h"
#include "commands/echo_command.h"
#include "commands/exit_command.h"
#include "commands/pwd_command.h"
#include "commands/cat_command.h"
#include "commands/assignment_command.h"
#include "commands/external_command.h"

namespace NCLI {

    namespace {
        NCommand::CommandFactory create_command_factory(Environment& env) {
            NCommand::CommandFactory factory;
            factory.register_command(std::regex("wc"), NCommand::WcCommand::create_command);
            factory.register_command(std::regex("cat"), NCommand::CatCommand::create_command);
            factory.register_command(std::regex("echo"), NCommand::EchoCommand::create_command);
            factory.register_command(std::regex("pwd"), NCommand::PwdCommand::create_command);
            factory.register_command(std::regex("exit"), NCommand::ExitCommand::create_command);
            factory.register_command(std::regex(".*=.*"),
                    std::bind(NCommand::AssignmentCommand::create_command, env, std::placeholders::_1));

            factory.register_default_command(NCommand::ExternalCommand::create_command);
            return factory;
        }
    }

    Application::Application() :
        env_(), command_factory_(create_command_factory(env_)), parser_(env_, command_factory_) { }

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
