#pragma once

#include <vector>
#include <string>

#include "parser/token.h"

namespace NCLI::NParser {

    class Tokenizer {
    public:
        std::tuple<std::vector<Token>, bool, std::string> tokenize(std::string text);

    private:
        class TokenizerHelper {
        public:
            void add_char(char c);
            std::vector<Token> get_tokens();
            TypeOfQuotation current_quote();

        private:
            void add_cur_word();

        private:
            std::string cur_word_;
            std::vector<Token> tokens_;
            TypeOfQuotation cur_quote_ = TypeOfQuotation::none;
        };
    };

} // namespace NCLI::NParser
