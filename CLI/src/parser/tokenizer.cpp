#include <cctype>
#include <tuple>

#include "parser/tokenizer.h"
#include "parser/token.h"

namespace NCLI::NParser {

    std::tuple<std::vector<Token>, bool, std::string> Tokenizer::tokenize(std::string text) {
        TokenizerHelper helper;
        for (char c : text) {
            helper.add_char(c);
        }
        helper.add_char(' ');
        if (helper.current_quote() != TypeOfQuotation::none) {
            std::string error_message = "unmatched_quote: ";
            error_message += static_cast<char>(helper.current_quote());
            return std::make_tuple(std::vector<Token>(), 1, error_message);
        }

        return std::make_tuple(helper.get_tokens(), 0, "");
    };

    void Tokenizer::TokenizerHelper::add_cur_word() {
        if (cur_word_.empty())
            return;
        tokens_.push_back(Token(std::move(cur_word_), cur_quote_));
        cur_word_.clear();
    }

    TypeOfQuotation Tokenizer::TokenizerHelper::current_quote() {
        return cur_quote_;
    }

    void Tokenizer::TokenizerHelper::add_char(char c) {
        if (isspace(c)) {
            add_cur_word();
            return;
        }

        if (c == '|' && cur_quote_ == TypeOfQuotation::none) {
            add_cur_word();
            cur_word_ = "|";
            add_cur_word();
            return;
        }

        if ((c == '\'' || c == '\"') && cur_quote_ == TypeOfQuotation::none) {
            cur_quote_ = static_cast<TypeOfQuotation>(c);
            return;
        }

        if ((c == '\'' || c == '\"') && cur_quote_ == static_cast<TypeOfQuotation>(c)) {
            add_cur_word();
            cur_quote_ = TypeOfQuotation::none;
            return;
        }

        cur_word_ += c;
    }

    std::vector<Token> Tokenizer::TokenizerHelper::get_tokens() {
        return tokens_;
    }

} // namespace NCLI::NParser
