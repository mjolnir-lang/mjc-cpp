#pragma once

#include <core/Error.hpp>
//#include <core/Where.hpp>


#include <expected>

template<class T, class E = Error>
using Result = std::expected<T, E>;


/*
/// @brief A wrapped object which is either a value or an error. This is used as a way of returning
/// a value from a fallible function, method, lambda, or other callable.
/// @tparam T The expected value type
/// @tparam E The error type
template<class T, class E = Error>
class Result {
private:
    union {
        T _value;
    };
    E _error;
public:


    constexpr
    Result(T &&value) noexcept : _value(value), _error(Error::SUCCESS) {}


    constexpr
    Result(E error) noexcept : _error(error) {}


    ///
    /// Destructor
    ///


    ~Result() {
        if constexpr (!std::is_trivially_destructible_v<T>) {
            if (has_value()) {
                _value.~T();
            }
        }
    }


    ///
    /// Properties
    ///


    /// @brief Return true if the result has a value.
    constexpr
    bool has_value() const noexcept {
        return _error == Error::SUCCESS;
    }


    /// @brief Return true if the result has an error.
    constexpr
    bool has_error() const noexcept {
        return _error != Error::SUCCESS;
    }


    /// @brief Return the value.
    constexpr
    const T &value() const & noexcept {
        return _value;
    }


    /// @brief Return the value.
    constexpr
    T &value() & noexcept {
        return _value;
    }


    /// @brief Return the value.
    constexpr
    const T &&value() const && noexcept {
        return _value;
    }


    /// @brief Return the value.
    constexpr
    T &&value() && noexcept {
        return std::move(_value);
    }


    /// @brief Return the value if this result has one or the given value.
    constexpr
    T value_or(T default_value) noexcept {
        return has_value() ? _value : default_value;
    }


    /// @brief Return the error.
    constexpr
    E error() const noexcept {
        return _error;
    }
};
*/
