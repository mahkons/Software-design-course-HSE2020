#include <sstream>
#include <string>

#include "executor.h"

namespace NCLI {

    NCommand::ExecutionResult Executor::execute(const std::vector<std::shared_ptr<NCommand::Command>>& commands, std::istream& is, std::ostream& os) const {

        std::stringstream buf_in, buf_out;
        for (size_t i = 0; i < commands.size(); i++) {
            std::istream& in = (i == 0 ? is : buf_in);
            std::ostream& out = (i + 1 == commands.size() ? os : buf_out);

            if (auto execution_result = commands[i]->execute(in, out);
                    execution_result.status != NCommand::ExecutionStatus::success) {
                return execution_result;
            }
            buf_in.clear();
            swap(buf_in, buf_out);
        }
        return NCommand::ExecutionResult(NCommand::ExecutionStatus::success, "");
    }

} // namespace NCLI
