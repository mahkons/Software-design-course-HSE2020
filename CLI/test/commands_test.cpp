#include <sstream>
#include <memory>
#include <filesystem>

#include "gtest/gtest.h"

#include "commands/command.h"
#include "commands/assignment_command.h"
#include "commands/cat_command.h"
#include "commands/echo_command.h"
#include "commands/exit_command.h"
#include "commands/external_command.h"
#include "commands/pwd_command.h"
#include "commands/wc_command.h"
#include "commands/grep_command.h"

namespace {
    using namespace NCLI;
    using namespace NCLI::NCommand;

    TEST(Commands, AssignmentCommand) {
        std::stringstream input("Input"), output;
        Environment env;
        env.set_variable("simple", "not");
        AssignmentCommand command = AssignmentCommand(env, "simple", "yup");

        auto result = command.execute(input, output);
        EXPECT_EQ("yup", env.get_variable("simple"));
        EXPECT_EQ("", output.str());
        EXPECT_EQ(ExecutionStatus::success, result.status);
        EXPECT_EQ("", result.message);
    }

    TEST(Commands, CatCommandStream) {
        std::stringstream input("Input"), output;
        CatCommand command = CatCommand();

        auto result = command.execute(input, output);
        EXPECT_EQ("Input", output.str());
        EXPECT_EQ(ExecutionStatus::success, result.status);
        EXPECT_EQ("", result.message);
    }

    TEST(Commands, CatCommandFile) {
        std::stringstream input("Input"), output;
        CatCommand command = CatCommand("../test/resources/test.txt");
        std::stringstream expected;
        expected << "Example text!\nHi\n";

        auto result = command.execute(input, output);
        EXPECT_EQ(expected.str(), output.str());
        EXPECT_EQ(ExecutionStatus::success, result.status);
        EXPECT_EQ("", result.message);
    }

    TEST(Commands, CatCommandUnknownFile) {
        std::stringstream input("Input"), output;
        CatCommand command = CatCommand("../test/resources/unknown.txt");

        auto result = command.execute(input, output);
        EXPECT_EQ("", output.str());
        EXPECT_EQ(ExecutionStatus::error, result.status);
        EXPECT_EQ("Can't open file: " +
                std::string(std::filesystem::absolute("../test/resources/unknown.txt")) + "\n",
                result.message);
    }

    TEST(Commands, EchoCommand) {
        std::stringstream input("Input"), output;
        EchoCommand command = EchoCommand("text text");

        auto result = command.execute(input, output);
        EXPECT_EQ("text text", output.str());
        EXPECT_EQ(ExecutionStatus::success, result.status);
        EXPECT_EQ("", result.message);
    }

    TEST(Commands, ExitCommand) {
        std::stringstream input("Input"), output;
        ExitCommand command = ExitCommand();

        auto result = command.execute(input, output);
        EXPECT_EQ("", output.str());
        EXPECT_EQ(ExecutionStatus::exit, result.status);
        EXPECT_EQ("", result.message);
    }

    TEST(Commands, PwdCommand) {
        std::stringstream input("Input"), output;
        PwdCommand command = PwdCommand();

        auto result = command.execute(input, output);
        EXPECT_EQ(std::string(std::filesystem::current_path()) + "\n", output.str());
        EXPECT_EQ(ExecutionStatus::success, result.status);
        EXPECT_EQ("", result.message);
    }

    TEST(Commands, WcCommandStream) {
        std::stringstream input("Input"), output;
        WcCommand command = WcCommand();

        auto result = command.execute(input, output);
        EXPECT_EQ("0 1 5\n", output.str());
        EXPECT_EQ(ExecutionStatus::success, result.status);
        EXPECT_EQ("", result.message);
    }

    TEST(Commands, WcCommandFile) {
        std::stringstream input("Input"), output;
        WcCommand command = WcCommand("../test/resources/test.txt");

        auto result = command.execute(input, output);
        EXPECT_EQ("2 3 17\n", output.str());
        EXPECT_EQ(ExecutionStatus::success, result.status);
        EXPECT_EQ("", result.message);
    }

    TEST(Commands, WcCommandUnknownFile) {
        std::stringstream input("Input"), output;
        WcCommand command = WcCommand("../test/resources/unknown.txt");

        auto result = command.execute(input, output);
        EXPECT_EQ("", output.str());
        EXPECT_EQ(ExecutionStatus::error, result.status);
        EXPECT_EQ("Can't open file: " +
                std::string(std::filesystem::absolute("../test/resources/unknown.txt")) + "\n",
                result.message);
    }

    TEST(Commands, GrepCommandStream) {
        std::stringstream input("Input\nSome"), output;
        auto ptr = GrepCommand::create_command({"grep", "put"}).get_ok();
        GrepCommand command = *dynamic_cast<GrepCommand*>(ptr.get());

        auto result = command.execute(input, output);
        EXPECT_EQ("Input\n", output.str());
        EXPECT_EQ(ExecutionStatus::success, result.status);
        EXPECT_EQ("", result.message);
    }

    TEST(Commands, GrepCommandFile) {
        std::stringstream input("Input"), output;
        auto ptr = GrepCommand::create_command({"grep", "text", "../test/resources/test.txt"}).get_ok();
        GrepCommand command = *dynamic_cast<GrepCommand*>(ptr.get());

        auto result = command.execute(input, output);
        EXPECT_EQ("Example text!\n", output.str());
        EXPECT_EQ(ExecutionStatus::success, result.status);
        EXPECT_EQ("", result.message);
    }

    TEST(Commands, GrepCommandUnknownFile) {
        std::stringstream input("Input"), output;
        auto ptr = GrepCommand::create_command({"grep", "text", "../test/resources/unknown.txt"}).get_ok();
        GrepCommand command = *dynamic_cast<GrepCommand*>(ptr.get());

        auto result = command.execute(input, output);
        EXPECT_EQ("", output.str());
        EXPECT_EQ(ExecutionStatus::error, result.status);
        EXPECT_EQ("Can't open file: " +
                std::string(std::filesystem::absolute("../test/resources/unknown.txt")) + "\n",
                result.message);
    }


    TEST(Commands, GrepCommandMultipleFiles) {
        std::stringstream input("Input"), output;
        auto message = GrepCommand::create_command(
                {"grep", "text", "../test/resources/unknown.txt", "../test/resources/test.txt"}).get_error();
        EXPECT_EQ("Multiple files are not supported", message);
    }

    TEST(Commands, GrepCommandNoPattern) {
        std::stringstream input("Input"), output;
        auto message = GrepCommand::create_command(
                {"grep", "-i"}).get_error();
        EXPECT_EQ("Pattern is not specified", message);
    }

    TEST(Commands, GrepCommandUnknownFlag) {
        std::stringstream input("Input"), output;
        auto message = GrepCommand::create_command(
                {"grep", "-B"}).get_error();
        EXPECT_EQ("unrecognised option '-B'", message);
    }

    TEST(Commands, GrepCommandStreamIgnoreCase) {
        std::stringstream input("some\nnice\n\nTEXt\n\nis pretty  is\n\nnice\nbye"), output;
        auto ptr = GrepCommand::create_command({"grep", "-i", "text"}).get_ok();
        GrepCommand command = *dynamic_cast<GrepCommand*>(ptr.get());

        auto result = command.execute(input, output);
        EXPECT_EQ("TEXt\n", output.str());
        EXPECT_EQ(ExecutionStatus::success, result.status);
        EXPECT_EQ("", result.message);
    }

    TEST(Commands, GrepCommandStreamWholeWords) {
        std::stringstream input("some\nnice\n\nTEXt\n\nis pretty  is\n\nnice\nbye"), output;
        auto ptr = GrepCommand::create_command({"grep", "-w", "pretty|bye|TEX"}).get_ok();
        GrepCommand command = *dynamic_cast<GrepCommand*>(ptr.get());

        auto result = command.execute(input, output);
        EXPECT_EQ("is pretty  is\nbye\n", output.str());
        EXPECT_EQ(ExecutionStatus::success, result.status);
        EXPECT_EQ("", result.message);
    }

    TEST(Commands, GrepCommandStreamTrailingContext) {
        std::stringstream input("some\nnice\n\nTEXt\n\nis pretty  is\n\nnice\nbye"), output;
        auto ptr = GrepCommand::create_command({"grep", "-A", "3", "nice"}).get_ok();
        GrepCommand command = *dynamic_cast<GrepCommand*>(ptr.get());

        auto result = command.execute(input, output);
        EXPECT_EQ("nice\n\nTEXt\n\nnice\nbye\n", output.str());
        EXPECT_EQ(ExecutionStatus::success, result.status);
        EXPECT_EQ("", result.message);
    }

} // namespace
