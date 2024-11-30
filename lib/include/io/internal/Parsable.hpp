#pragma once

#include <core/Function.hpp>
#include <io/internal/Parser.hpp>


class StringParser;


/// @brief A PrintArg object contains a reference to the object to be
/// formatted/printed and the parser function associated with that object's
/// type.
class Parsable {
private:
    mutable void *_value;
    const Function<Error(StringParser &)> _parse;
public:


    ///
    /// Constructors
    ///


    template<class T>
    constexpr Parsable(const T &value) noexcept : _value(&value), _parse(&Parser<T>::parse) {}


    ///
    /// Properties
    ///


    /// @brief Return the format argument value given the expected value of the type.
    /// @tparam T The type of argument.
    template<class T>
    T &value() const noexcept {
        return *reinterpret_cast<T *>(_value);
    }


    Error parse(StringParser &in) const noexcept {
        return _parse(in);
    }
};
