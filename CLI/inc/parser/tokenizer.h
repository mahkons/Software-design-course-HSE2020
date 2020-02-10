#pragma once

#include <vector>
#include <string>

#include "parser/token.h"
#include "result.h"

namespace NCLI::NParser {

    using TokenizerResult = Result<std::vector<Token>, std::string>;

    /* Class for dividing text into tokens */
    class Tokenizer {
    public:
        /* Splits text into tokens by space characters(defines as in std::isspace) and pipes
         *  Deletes outer quotes and uses them as TypeOf quotation information in Tokens */
        TokenizerResult tokenize(const std::string& text) const;

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
