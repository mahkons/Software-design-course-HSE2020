#pragma once

#include <variant>

namespace NCLI {
    template<typename T>
    class Ok {
    public:
        explicit Ok(T value) : value(value) {}
        T value;
    };

    template<typename E>
    class Error {
    public:
        explicit Error(E value) : value(value) {}
        E value;
    };

    template<typename T, typename E>
    class Result {
    public:
        explicit Result(Ok<T> ok_value) : value_(ok_value) {};
        explicit Result(Error<E> error_value) : value_(error_value) {};

        operator bool() const {
            return std::holds_alternative<Ok<T>>(value_);
        }

        T get_ok() const {
            return std::get<Ok<T>>(value_).value;
        }

        E get_error() const {
            return std::get<Error<E>>(value_).value;
        }

    private:
        std::variant<Ok<T>, Error<E>> value_;
    };

} // namespace NCLI
