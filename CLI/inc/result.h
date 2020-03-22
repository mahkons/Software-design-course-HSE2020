#pragma once

#include <variant>

namespace NCLI {
    template<typename T>
    class Ok {
    public:
        explicit Ok(const T& value) : value(value) {}
        explicit Ok(T&& value) : value(value) {}
        T value;
    };

    template<typename E>
    class Error {
    public:
        explicit Error(const E& value) : value(value) {}
        explicit Error(E&& value) : value(value) {}
        E value;
    };

    /**
     * Stores variable of one of types T or E
     */ 
    template<typename T, typename E>
    class Result {
    public:
        explicit Result(const Ok<T>& ok_value) : value_(ok_value) {};
        explicit Result(const Error<E>& error_value) : value_(error_value) {};
        explicit Result(Ok<T>&& ok_value) : value_(ok_value) {};
        explicit Result(Error<E>&& error_value) : value_(error_value) {};

        operator bool() const {
            return std::holds_alternative<Ok<T>>(value_);
        }

        T get_ok() {
            return std::move(std::get<Ok<T>>(value_).value);
        }

        E get_error() {
            return std::move(std::get<Error<E>>(value_).value);
        }

    private:
        std::variant<Ok<T>, Error<E>> value_;
    };

} // namespace NCLI
