#pragma once

#include <system/ProgramArgument.hpp>


/// @brief A program option.
class ProgramOption {
private:
    ProgramArgument _argument; // The argument
    StringView _long_name;
    u8 _short_name;
public:


    /// @brief Create an optional argument with both short and long names.
    /// @param short_name The short option name
    /// @param long_name The long option name
    template<class... Args>
    constexpr
    ProgramOption(u8 short_name, StringView long_name, Args... args) noexcept :
        _argument(std::forward<Args>(args)...),
        _long_name(long_name),
        _short_name(short_name)
    {}


    /// @brief Create an optional argument with a short name.
    /// @param short_name The short option name
    template<class... Args>
    constexpr
    ProgramOption(u8 short_name, Args... args) noexcept :
        _argument(std::forward<Args>(args)...),
        _long_name(nullptr),
        _short_name(short_name)
    {}


    /// @brief Create an optional argument with a long name.
    /// @param long_name The long option name
    template<class... Args>
    constexpr
    ProgramOption(StringView long_name, Args... args) noexcept :
        _argument(std::forward<Args>(args)...),
        _long_name(long_name),
        _short_name(0)
    {}


    ///
    /// Properties
    ///


    const ProgramArgument &arg() const noexcept {
        return _argument;
    }


    ProgramArgument &arg() noexcept {
        return _argument;
    }


    constexpr
    StringView long_name() const noexcept {
        return _long_name;
    }


    constexpr
    u8 short_name() const noexcept {
        return _short_name;
    }
};
