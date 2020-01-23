#pragma once

#include "environment.h"
#include "parser/parser.h"

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
        NParser::Parser parser_;

    };

} // namespace NCLI
