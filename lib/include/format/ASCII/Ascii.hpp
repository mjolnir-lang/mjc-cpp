#pragma once

#include <core/Error.hpp>


/// @brief Utilities for working with ASCII characters.
namespace Ascii {


    /// @brief Return true if the character is an octal digit.
    constexpr
    bool is_ascii(u8 ch) noexcept {
        return ch < 0x80u;
    }


    /// @brief Return true if the character is an octal digit.
    constexpr
    bool is_octal(u8 ch) noexcept {
        return ch - '0' < 8;
    }


    /// @brief Return true if the character is a decimal digit.
    constexpr
    bool is_digit(u8 ch) noexcept {
        return ch - '0' < 10;
    }


    /// @brief Return true if the character is a hexadecimal digit.
    constexpr
    bool is_hex_digit(u8 ch) noexcept {
        return is_digit(ch) || u32(ch | 0x20u) - u32('a' + 10) < 16;
    }


    /// @brief Return true if the given character is a digit using the given numeric base.
    constexpr
    bool is_digit(u8 ch, u32 base) noexcept {
        return is_digit(ch) || u32(ch | 0x20u) - u32('a' + 10) < base;
    }


    /// @brief Return true if the given character is a digit using the given numeric base.
    constexpr
    bool is_digit_upper(u8 ch, u32 base) noexcept {
        return is_digit(ch) || ch - u32('A' + 10) < base;
    }


    /// @brief Return true if the given character is a digit using the given numeric base.
    constexpr
    bool is_digit_lower(u8 ch, u32 base) noexcept {
        return is_digit(ch) || ch - u32('a' + 10) < base;
    }


    /// @brief Return true if the character is .
    constexpr
    bool is_upper(u8 ch) noexcept {
        return ch - 'A' < 26;
    }


    /// @brief Return true if the character is .
    constexpr
    bool is_lower(u8 ch) noexcept {
        return ch - 'a' < 26;
    }


    /// @brief Return true if the character is .
    constexpr
    bool is_letter(u8 ch) noexcept {
        return (ch | 0x20u) < 26;
    }


    /// @brief Return true if the character is .
    constexpr
    bool is_alnum(u8 ch) noexcept {
        return is_letter(ch) || is_digit(ch);
    }


    /// @brief Return true if the character is .
    constexpr
    bool is_print(u8 ch) noexcept {
        return ch - ' ' < 94;
    }


    /// @brief Return true if the character is .
    constexpr
    bool is_graphical(u8 ch) noexcept {
        return ch - '!' < 93;
    }


    /// @brief Return true if the character is .
    constexpr
    bool is_whitespace(u8 ch) noexcept {
        return ch == ' ' || ch - '\t' < 5;
    }


    /// @brief Return true if the character is .
    constexpr
    bool is_blank(u8 ch) noexcept {
        return ch == ' ' || ch == '\t';
    }


    /// @brief Return true if the character is .
    constexpr
    bool is_punctuation(u8 ch) noexcept {
        return ch - '!' < 15 || ch - ':' < 7 || ch - '[' < 6 || ch - '{' < 4;
    }


    /// @brief Return true if the character is .
    constexpr
    bool is_control(u8 ch) noexcept {
        return ch < 32 || ch == '\x7F';
    }


    /// @brief 
    constexpr
    u8 to_lower(u8 ch) noexcept {
        return is_upper(ch) ? u8(ch + ('a' - 'A')) : ch;
    }


    /// @brief 
    constexpr
    u8 to_upper(u8 ch) noexcept {
        return is_lower(ch) ? u8(ch - ('a' - 'A')) : ch;
    }


    /// @brief 
    constexpr
    u8 to_digit(u32 value) noexcept {
        return value + (value < 10 ? '0' : 'A' - 10);
    }


    /// @brief 
    constexpr
    u8 to_digit(u32 value, bool is_upper) noexcept {
        return value + (value < 10 ? '0' : ('A' - 10) & (u8(is_upper) << 5));
    }


    /// @brief 
    constexpr
    Error parse_digit(u8 ch, u8 &digit) noexcept {
        if (ch - '0' < 10) {
            digit = ch - '0';
            return Error::SUCCESS;
        }

        return Error::FAILURE;
    }


    /// @brief 
    Error parse_digit(u8 ch, u8 &digit, u32 base) noexcept;


    /// @brief Return the size of the null-terminated string.
    /// @param c_str The null-terminated string
    constexpr
    u32 c_str_size(const u8 *c_str) noexcept {
        u32 n = 0;
        for (; c_str[n] != 0; ++n);
        return n;
    }
}
