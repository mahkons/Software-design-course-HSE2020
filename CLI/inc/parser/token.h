#pragma once

#include <string>

namespace NCLI::NParser {

    enum class TypeOfQuotation : char {
        none = '\0',
        strong = '\'',
        weak = '\"'
    };

    class Token {
    public:
        Token(const std::string& value, const TypeOfQuotation& surrounding_quotes)
            : value(value), surrounding_quotes(surrounding_quotes) {}

        bool operator==(const Token& o) const {
            return value == o.value && surrounding_quotes == o.surrounding_quotes;
        };

        std::string value;
        TypeOfQuotation surrounding_quotes;
        
    };

} // namespace NCLI::NParser
