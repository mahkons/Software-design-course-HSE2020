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

    /* Command that launches external command in separate process */
    class ExternalCommand : public Command {
    public:
        ExternalCommand(const bf::path& path, 
                const std::vector<std::string>& args) : path_(path), args_(args) {};
        /* Executes external command specifies by path in separate process
         *  with {param}is as stdin and {param}os as stdout
         * Waits until end of its execution
         * If error occured returns ExecutionResult with ExecutionStatus::error status
         * and command stderr as message */
        virtual ExecutionResult execute(std::istream& is, std::ostream& os) override;

        /* Creates ExternalCommand by given args
         * args should no be empty
         * first arg used as command name
         * Search command in $PATH by it's name
         * if non was found, returns error
         * otherwise returns pointer to command */
        static Result<std::shared_ptr<Command>, std::string> create_command(
                const std::vector<std::string>& args);
    private:
        const bf::path path_;
        const std::vector<std::string> args_;
    };

} // namespace NCLI::NCommand

