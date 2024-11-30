#pragma once

#include <core/Function.hpp>
#include <io/internal/Parsable.hpp>
#include <io/internal/StringParserFormatOptions.hpp>


/// @brief A context object for sequentially parsing a string.
class StringParser {
private:
    StringParserFormatOptions _format;
    StringView _format_string;
    StringView _string;
    Slice<Parsable> _args;
    u32 _next_index = 0;
public:


    ///
    /// Constructors
    ///


    constexpr
    StringParser(StringView format_string, Slice<Parsable> args) noexcept :
        _format_string(format_string),
        _args(args)
    {}


    ///
    /// Properties
    ///


    Parsable &arg();


    const StringView &string() const noexcept {
        return _string;
    }


    StringView &string() noexcept {
        return _string;
    }


    const StringParserFormatOptions &format() const noexcept {
        return _format;
    }


    StringParserFormatOptions &format() noexcept {
        return _format;
    }


    ///
    /// Methods
    ///


    Error parse(StringView string) noexcept;


    /// @brief Return the format argument value given the expected value of the type.
    /// @tparam T The type of argument.
    template<class T>
    T &value() const noexcept {
        return *reinterpret_cast<T *>(_args[_parse_format.index]._value);
    }


    /// @brief Return the format argument value given the expected value of the type.
    /// @tparam T The type of argument.
    template<class T>
    void set_value(T value) const noexcept {
        this.value() = value;
    }
private:


    Error parse_format() noexcept;
};
