#pragma once

#include "environment.h"
#include "parser/parser.h"
#include "commands/command_factory.h"
#include "executor.h"

namespace NCLI {

    class Application {
    public:
        Application();
        ~Application() = default;
        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        void run();

    private:
        Environment env_;
        NCommand::CommandFactory command_factory_;
        NParser::Parser parser_;
        Executor executor_;
    };

} // namespace NCLI
