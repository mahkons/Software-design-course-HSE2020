#include <sstream>
#include <memory>

#include "gtest/gtest.h"

#include "result.h"
#include "commands/command.h"
#include "commands/command_factory.h"

namespace {
    using namespace NCLI;
    using namespace NCLI::NCommand;

    class SimpleCommand : public Command {
    public:
        SimpleCommand(std::vector<std::string> args) : args(args) {}
        static Result<std::shared_ptr<Command>, std::string> create_command(
                std::vector<std::string> args) {

            return Result<std::shared_ptr<Command>, std::string>(
                    Ok(std::shared_ptr<Command>(new SimpleCommand(args))));
        };
        std::vector<std::string> args;
    };

    class SimpleErrorCommand : public Command {
    public:
        static Result<std::shared_ptr<Command>, std::string> create_command(
                std::vector<std::string>) {

            return Result<std::shared_ptr<Command>, std::string>(
                    Error(std::string("construction error")));
        };
    };

    TEST(CommandFactory, noCommand) {
        CommandFactory command_factory;
        std::vector<std::string> args = {"simple", "a", "b"};

        FactoryResult result = command_factory.parse_command(args);
        EXPECT_FALSE((bool)result);
        EXPECT_EQ("Unknown command: simple", result.get_error());
    }

    TEST(CommandFactory, oneCommand) {
        CommandFactory command_factory;
        std::vector<std::string> args = {"simple", "a", "b"};

        command_factory.register_command(std::regex(".*imp.*"), SimpleCommand::create_command);

        FactoryResult result = command_factory.parse_command(args);
        EXPECT_TRUE((bool)result);
        auto ptr = result.get_ok();
        SimpleCommand* command = dynamic_cast<SimpleCommand*>(ptr.get());
        EXPECT_TRUE(command);
        EXPECT_EQ(args, command->args);
    }

    TEST(CommandFactory, twoCommandsFirstMatch) {
        CommandFactory command_factory;
        std::vector<std::string> args = {"simple", "a", "b"};

        command_factory.register_command(std::regex(".*imp.*"), SimpleCommand::create_command);
        command_factory.register_command(std::regex(".*simple"), SimpleErrorCommand::create_command);

        FactoryResult result = command_factory.parse_command(args);
        EXPECT_TRUE((bool)result);
        auto ptr = result.get_ok();
        SimpleCommand* command = dynamic_cast<SimpleCommand*>(ptr.get());
        EXPECT_TRUE(command);
        EXPECT_EQ(args, command->args);
    }

    TEST(CommandFactory, twoCommandsSecondMatch) {
        CommandFactory command_factory;
        std::vector<std::string> args = {"simple", "a", "b"};

        command_factory.register_command(std::regex("impossible"), SimpleErrorCommand::create_command);
        command_factory.register_command(std::regex(".*simple"), SimpleCommand::create_command);

        FactoryResult result = command_factory.parse_command(args);
        EXPECT_TRUE((bool)result);
        auto ptr = result.get_ok();
        SimpleCommand* command = dynamic_cast<SimpleCommand*>(ptr.get());
        EXPECT_TRUE(command);
        EXPECT_EQ(args, command->args);
    }

    TEST(CommandFactory, defaultCommand) {
        CommandFactory command_factory;
        std::vector<std::string> args = {"simple", "a", "b"};

        command_factory.register_command(std::regex("impossible"), SimpleErrorCommand::create_command);
        command_factory.register_default_command(SimpleCommand::create_command);

        FactoryResult result = command_factory.parse_command(args);
        EXPECT_TRUE((bool)result);
        auto ptr = result.get_ok();
        SimpleCommand* command = dynamic_cast<SimpleCommand*>(ptr.get());
        EXPECT_TRUE(command);
        EXPECT_EQ(args, command->args);
    }

    TEST(CommandFactory, errorCommand) {
        CommandFactory command_factory;
        std::vector<std::string> args = {"simple", "a", "b"};

        command_factory.register_command(std::regex(".*imp.*"), SimpleErrorCommand::create_command);

        FactoryResult result = command_factory.parse_command(args);
        EXPECT_FALSE((bool)result);
        EXPECT_EQ("construction error", result.get_error());
    }



} // namespace

