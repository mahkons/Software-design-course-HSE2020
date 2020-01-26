#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "boost/process.hpp"

#include "result.h"
#include "commands/command.h"
#include "commands/execution_result.h"


namespace NCLI::NCommand {
    
    namespace bp = boost::process;
    namespace bf = boost::filesystem;

    class ExternalCommand : public Command {
    public:
        ExternalCommand(const bf::path& path, std::vector<std::string> args) : path_(path), args_(args) {};
        virtual ExecutionResult execute(std::istream& is, std::ostream& os) override;

        static Result<std::shared_ptr<Command>, std::string> create_command(std::vector<std::string> args);
    private:
        bf::path path_;
        std::vector<std::string> args_;
    };

} // namespace NCLI::NCommand

