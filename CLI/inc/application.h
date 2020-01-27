#pragma once

#include "environment.h"
#include "parser/parser.h"
#include "commands/command_factory.h"
#include "executor.h"

namespace NCLI {

    /* Command line interface
     * Gets input from stdin and writes output to stdout */
    class Application {
    public:
        /* Initialises application */
        Application();
        ~Application() = default;
        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        /* Runs command line interface */
        void run();

    private:
        Environment env_;
        NCommand::CommandFactory command_factory_;
        NParser::Parser parser_;
        Executor executor_;
    };

} // namespace NCLI
