#include <sstream>
#include <memory>

#include "gtest/gtest.h"

#include "commands/command.h"
#include "commands/command_factory.h"
#include "parser/parser.h"
#include "parser/tokenizer.h"
#include "parser/variables_substitutor.h"
#include "parser/commands_parser.h"

namespace {
    using namespace NCLI;
    using namespace NCLI::NCommand;
    using namespace NCLI::NParser;

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

    TEST(Tokenizer, empty) {
        Tokenizer tokenizer;
        std::string text = "";

        auto result = tokenizer.tokenize(text);
        EXPECT_TRUE(result);
        EXPECT_EQ(std::vector<Token>(), result.get_ok());
    }

    TEST(Tokenizer, singleCommand) {
        Tokenizer tokenizer;
        std::string text = "some";

        auto result = tokenizer.tokenize(text);
        EXPECT_TRUE(result);
        EXPECT_EQ(std::vector<Token>({Token("some", TypeOfQuotation::none)}),
                result.get_ok());
    }

    TEST(Tokenizer, weakQuoting) {
        Tokenizer tokenizer;
        std::string text = "\"some\"";

        auto result = tokenizer.tokenize(text);
        EXPECT_TRUE(result);
        EXPECT_EQ(std::vector<Token>({Token("some", TypeOfQuotation::weak)}),
                result.get_ok());
    }

    TEST(Tokenizer, strongQuoting) {
        Tokenizer tokenizer;
        std::string text = "\'some\'";

        auto result = tokenizer.tokenize(text);
        EXPECT_TRUE(result);
        EXPECT_EQ(std::vector<Token>({Token("some", TypeOfQuotation::strong)}),
                result.get_ok());
    }

    TEST(Tokenizer, pipe) {
        Tokenizer tokenizer;
        std::string text = "some|help";

        auto result = tokenizer.tokenize(text);
        EXPECT_TRUE(result);
        EXPECT_EQ(std::vector<Token>({
                    Token("some", TypeOfQuotation::none), Token("|", TypeOfQuotation::none),
                    Token("help", TypeOfQuotation::none)}),
                result.get_ok());
    }

    TEST(Tokenizer, quoteInQuotes) {
        Tokenizer tokenizer;
        std::string text = "\"oh,quote\'oh\"";

        auto result = tokenizer.tokenize(text);
        EXPECT_TRUE(result);
        EXPECT_EQ(std::vector<Token>({ Token("oh,quote\'oh", TypeOfQuotation::weak)}),
                result.get_ok());
    }

    TEST(Tokenizer, mismatchedQuote) {
        Tokenizer tokenizer;
        std::string text = "\"oh,quote";

        auto result = tokenizer.tokenize(text);
        EXPECT_FALSE(result);
        EXPECT_EQ("unmatched quote: \"", result.get_error());
    }

    TEST(VariablesSubstitutor, noSubstitution) {
        Environment env;
        env.set_variable("simple", "TooDifficult");
        VariablesSubstitutor substitutor(env);
        std::vector<Token> text {
            Token("simple", TypeOfQuotation::none),
            Token("|", TypeOfQuotation::none)
        };

        auto result = substitutor.substitute(text);

        EXPECT_EQ(std::vector<Token>({
                    Token("simple", TypeOfQuotation::none),
                    Token("|", TypeOfQuotation::none)
                }), result);
    }

    TEST(VariablesSubstitutor, oneSubstitution) {
        Environment env;
        env.set_variable("simple", "TooDifficult");
        VariablesSubstitutor substitutor(env);
        std::vector<Token> text {
            Token("$simple", TypeOfQuotation::none),
            Token("pretty$simple", TypeOfQuotation::none)
        };

        auto result = substitutor.substitute(text);

        EXPECT_EQ(std::vector<Token>({
                    Token("TooDifficult", TypeOfQuotation::none),
                    Token("prettyTooDifficult", TypeOfQuotation::none)
                }), result);
    }

    TEST(VariablesSubstitutor, multipleSubstitutions) {
        Environment env;
        env.set_variable("simple", "TooDifficult");
        env.set_variable("super", "not");
        VariablesSubstitutor substitutor(env);
        std::vector<Token> text {
            Token("$super$simple", TypeOfQuotation::none),
            Token("pretty$super$simple", TypeOfQuotation::none)
        };

        auto result = substitutor.substitute(text);

        EXPECT_EQ(std::vector<Token>({
                    Token("notTooDifficult", TypeOfQuotation::none),
                    Token("prettynotTooDifficult", TypeOfQuotation::none)
                }), result);
    }

    TEST(VariablesSubstitutor, weakQuoting) {
        Environment env;
        env.set_variable("simple", "TooDifficult");
        VariablesSubstitutor substitutor(env);
        std::vector<Token> text {
            Token("$simple", TypeOfQuotation::weak),
            Token("pretty$simple", TypeOfQuotation::weak)
        };

        auto result = substitutor.substitute(text);

        EXPECT_EQ(std::vector<Token>({
                    Token("TooDifficult", TypeOfQuotation::weak),
                    Token("prettyTooDifficult", TypeOfQuotation::weak)
                }), result);
    }

    TEST(VariablesSubstitutor, strongQuoting) {
        Environment env;
        env.set_variable("simple", "TooDifficult");
        VariablesSubstitutor substitutor(env);
        std::vector<Token> text {
            Token("$simple", TypeOfQuotation::strong),
            Token("pretty$simple", TypeOfQuotation::strong)
        };

        auto result = substitutor.substitute(text);

        EXPECT_EQ(std::vector<Token>({
                    Token("$simple", TypeOfQuotation::strong),
                    Token("pretty$simple", TypeOfQuotation::strong)
                }), result);
    }

    TEST(CommandsParser, singleCommand) {
        CommandFactory command_factory;
        command_factory.register_command(std::regex("simple"), SimpleCommand::create_command);
        CommandsParser commandParser(command_factory);
        std::vector<Token> text {
            Token("simple", TypeOfQuotation::none), Token("a", TypeOfQuotation::none)
        };

        auto result = commandParser.parse_commands(text);
        EXPECT_TRUE((bool)result);
        auto ptr = result.get_ok();
        EXPECT_EQ(1, ptr.size());
        SimpleCommand* command = dynamic_cast<SimpleCommand*>(ptr[0].get());
        EXPECT_TRUE(command);
        EXPECT_EQ(std::vector<std::string>({"simple", "a"}), command->args);
    }

    TEST(CommandsParser, multipleCommands) {
        CommandFactory command_factory;
        command_factory.register_command(std::regex("simple"), SimpleCommand::create_command);
        CommandsParser commandParser(command_factory);
        std::vector<Token> text {
            Token("simple", TypeOfQuotation::none), Token("a", TypeOfQuotation::none),
            Token("|", TypeOfQuotation::none),
            Token("simple", TypeOfQuotation::none), Token("a", TypeOfQuotation::none),
        };

        auto result = commandParser.parse_commands(text);
        EXPECT_TRUE((bool)result);
        auto ptr = result.get_ok();
        EXPECT_EQ(2, ptr.size());
        SimpleCommand* command = dynamic_cast<SimpleCommand*>(ptr[0].get());
        EXPECT_TRUE(command);
        EXPECT_EQ(std::vector<std::string>({"simple", "a"}), command->args);

        command = dynamic_cast<SimpleCommand*>(ptr[1].get());
        EXPECT_TRUE(command);
        EXPECT_EQ(std::vector<std::string>({"simple", "a"}), command->args);
    }

    TEST(CommandsParser, commandFactoryError) {
        CommandFactory command_factory;
        command_factory.register_command(std::regex("simple"), SimpleErrorCommand::create_command);
        CommandsParser commandParser(command_factory);
        std::vector<Token> text {
            Token("simple", TypeOfQuotation::none), Token("a", TypeOfQuotation::none)
        };

        auto result = commandParser.parse_commands(text);
        EXPECT_FALSE((bool)result);
        EXPECT_EQ("construction error", result.get_error());
    }

    TEST(CommandsParser, emptyCommand) {
        CommandFactory command_factory;
        command_factory.register_command(std::regex("simple"), SimpleCommand::create_command);
        CommandsParser commandParser(command_factory);
        std::vector<Token> text {
        };

        auto result = commandParser.parse_commands(text);
        EXPECT_FALSE((bool)result);
        EXPECT_EQ("Parser Error: empty command", result.get_error());
    }


} // namespace

