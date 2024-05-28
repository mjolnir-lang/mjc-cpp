#pragma once

#include <std/Common.hpp>


namespace Ascii {


    constexpr
    inline
    bool is_space(u8 ch) noexcept {
        return ch == ' ' || u8(ch - '\t') < 5u;
    }


    constexpr
    inline
    bool is_lower(u8 ch) noexcept {
        return u8(ch - 'a') < 26u;
    }


    constexpr
    inline
    bool is_upper(u8 ch) noexcept {
        return u8(ch - 'A') < 26u;
    }


    constexpr
    inline
    bool is_alpha(u8 ch) noexcept {
        return u8((ch | 0x20u) - 'A') < 26u;
    }


    constexpr
    inline
    bool is_digit(u8 ch) noexcept {
        return u8(ch - '0') < 10u;
    }


    constexpr
    inline
    bool is_digit(u8 ch, u8 base) noexcept {
        return u8(ch - '0') < base || u8((ch | 0x20u) - 'a') < base - 10u;
    }


    constexpr
    inline
    bool is_digit_upper(u8 ch, u8 base) noexcept {
        return u8(ch - '0') < base || u8(ch - 'A') < base - 10u;
    }


    constexpr
    inline
    bool is_digit_lower(u8 ch, u8 base) noexcept {
        return u8(ch - '0') < base || u8(ch - 'a') < base - 10u;
    }


    constexpr
    inline
    bool is_alnum(u8 ch) noexcept {
        return is_alpha(ch) || is_digit(ch);
    }
}
