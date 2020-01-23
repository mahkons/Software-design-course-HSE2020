#pragma once

#include <iostream>

namespace NCLI {
    class Command {
    public:
        Command() = delete;
        virtual ~Command() = default;

        void execute(std::iostream& is, std::ostream& os);
    };

} // namespace NCLI
