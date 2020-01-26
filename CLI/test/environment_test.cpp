#include "gtest/gtest.h"

#include "environment.h"

namespace {
    TEST(Environment, emptyEnv) {
        NCLI::Environment env;
        EXPECT_EQ("", env.get_variable("var"));
    }

    TEST(Environment, singleVar) {
        NCLI::Environment env;
        env.set_variable("var", "a");
        EXPECT_EQ("a", env.get_variable("var"));
        env.set_variable("var", "bb");
        EXPECT_EQ("bb", env.get_variable("var"));
    }

    TEST(Environment, twoVar) {
        NCLI::Environment env;
        env.set_variable("var", "a");
        env.set_variable("var_second", "b");
        EXPECT_EQ("a", env.get_variable("var"));
        EXPECT_EQ("b", env.get_variable("var_second"));
    }

} // namespace
