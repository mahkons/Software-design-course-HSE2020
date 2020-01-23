#pragma once

#include <string>

namespace NCLI::NCommand {

    enum class ExecutionStatus { success, error, exit };
    
    class ExecutionResult {
    public:
        ExecutionResult(const ExecutionStatus& status, const std::string& message)
            : status(status), message(message) {};

        const ExecutionStatus status;
        const std::string message;
    };

} // namespace NCLI::NCommand
