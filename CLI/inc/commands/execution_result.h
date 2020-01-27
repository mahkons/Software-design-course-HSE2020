#pragma once

#include <string>

namespace NCLI::NCommand {

    /* Status of command executions 
     * success: execution completed successfully
     * error: error occured during execution
     * exit: command asks shell to close */
    enum class ExecutionStatus { success, error, exit };
    
    /* Result of execution,
     * consists of execution status and additional message */
    class ExecutionResult {
    public:
        ExecutionResult(const ExecutionStatus& status, const std::string& message)
            : status(status), message(message) {};

        const ExecutionStatus status;
        const std::string message;
    };

} // namespace NCLI::NCommand
