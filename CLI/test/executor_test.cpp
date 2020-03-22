#include <sstream>
#include <memory>

#include "gtest/gtest.h"

#include "executor.h"
#include "commands/command.h"

namespace {
    using namespace NCLI;
    using namespace NCLI::NCommand;

    class SimpleRedirectCommand : public Command {
        ExecutionResult execute(std::istream& is, std::ostream& os) override {
            char c;
            while (is.get(c)) {
                os << c;
            }
            return ExecutionResult(ExecutionStatus::success, "");
        }
    };

    class SimpleErrorCommand : public Command {
        ExecutionResult execute(std::istream&, std::ostream&) override {
            return ExecutionResult(ExecutionStatus::error, "error_message");
        }
    };

    class SimpleExitCommand : public Command {
        ExecutionResult execute(std::istream&, std::ostream&) override {
            return ExecutionResult(ExecutionStatus::exit, "exit_message");
        }
    };

    TEST(Executor, emptyCommandList) {
        Executor executor;
        std::stringstream in("Input"), out;

        ExecutionResult result = executor.execute({}, in, out);
        EXPECT_EQ(ExecutionStatus::success, result.status);
        EXPECT_EQ("", result.message);
        EXPECT_EQ("", out.str());
    }

    TEST(Executor, singleCommand) {
        Executor executor;
        std::stringstream in("Input"), out;

        ExecutionResult result = executor.execute({
                std::shared_ptr<Command>(new SimpleRedirectCommand())}, in, out);
        EXPECT_EQ(ExecutionStatus::success, result.status);
        EXPECT_EQ("", result.message);
        EXPECT_EQ("Input", out.str());
    }

    TEST(Executor, TwoCommands) {
        Executor executor;
        std::stringstream in("Input"), out;

        ExecutionResult result = executor.execute({
                std::shared_ptr<Command>(new SimpleRedirectCommand()),
                std::shared_ptr<Command>(new SimpleRedirectCommand())}, in, out);
        EXPECT_EQ(ExecutionStatus::success, result.status);
        EXPECT_EQ("", result.message);
        EXPECT_EQ("Input", out.str());
    }

    TEST(Executor, ErrorCommand) {
        Executor executor;
        std::stringstream in("Input"), out;

        ExecutionResult result = executor.execute({
                std::shared_ptr<Command>(new SimpleErrorCommand())}, in, out);
        EXPECT_EQ(ExecutionStatus::error, result.status);
        EXPECT_EQ("error_message", result.message);
        EXPECT_EQ("", out.str());
    }

    TEST(Executor, ExitCommand) {
        Executor executor;
        std::stringstream in("Input"), out;

        ExecutionResult result = executor.execute({
                std::shared_ptr<Command>(new SimpleExitCommand())}, in, out);
        EXPECT_EQ(ExecutionStatus::exit, result.status);
        EXPECT_EQ("exit_message", result.message);
        EXPECT_EQ("", out.str());
    }



} // namespace
