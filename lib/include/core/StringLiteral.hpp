#pragma once

#include <core/Common.hpp>


/*
template<u32 SIZE>
struct FixedString {
private:
    u8 _data[SIZE]{};
public:


    constexpr
    FixedString(const char *str) noexcept {
        for (u32 i = 0; i < SIZE; ++i) {
            _data[i] = str[i];
        }
    }


    constexpr
    operator const u8 *() const noexcept {
        return _data;
    }
};


template<u32 SIZE>
FixedString(const char (&)[SIZE]) -> FixedString<SIZE - 1>;


template<FixedString STR>
class Foo {
    static
    constexpr
    const u8 *_data = STR;
public:


    constexpr
    operator const u8 *() const noexcept {
        return _data;
    }
};
*/


/*
template<const char *STR>
class StringLiteral;

template<u32 SIZE>
class StringLiteral<const char (&STR)[SIZE]> {
private:
    static
    constexpr
    u8[SIZE] DATA{};
public:


    ///
    /// Constructors
    ///


    constexpr
    StringLiteral() noexcept {
        for (u32 i = 0; i < SIZE; ++i) {
            DATA[i] = STR[i];
        }
    }


    ///
    /// Properties
    ///


    constexpr
    const u8 *data() const noexcept {
        return DATA;
    }


    constexpr
    u32 size() const noexcept {
        return SIZE;
    }
};
*/

template<const char *STR>
class StringLiteral {
private:

    static
    constexpr
    u32 str_size() noexcept {
        u32 size = 0;
        while (STR[size]) {
            ++size;
        }
        return size;
    }


    static
    constexpr
    u8 *DATA[str_size()]{};
public:


    ///
    /// Constructors
    ///


    constexpr
    StringLiteral() noexcept {
        for (u32 i = 0; i < str_size(); ++i) {
            DATA[i] = STR[i];
        }
    }


    ///
    /// Properties
    ///


    constexpr
    const u8 *data() const noexcept {
        return DATA;
    }


    constexpr
    u32 size() const noexcept {
        return str_size();
    }
};


template<class T>
struct IsStringLiteral : std::false_type {};

template<auto STR>
struct IsStringLiteral<StringLiteral<STR>> : std::true_type {};

template<typename T>
concept AnyStringLiteral = requires { typename std::decay_t<T>; } && IsStringLiteral<T>::value;
