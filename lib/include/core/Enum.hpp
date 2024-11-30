#pragma once

#include <core/Common.hpp>


template<class T>
class Enum {
protected:
    T _id;
public:


    ///
    /// Constructors
    ///


    constexpr
    explicit
    Enum(T id) noexcept : _id(id) {}


    ///
    /// Type Casts
    ///


    constexpr
    operator T() const noexcept {
        return _id;
    }


    ///
    /// Properties
    ///


    constexpr
    T id() const noexcept {
        return _id;
    }


    ///
    /// Operators
    ///


    constexpr T operator++() noexcept { return ++_id; }
    constexpr T operator++(int) noexcept { return _id++; }


    constexpr void operator+=(T value) noexcept { _id += value; }
    constexpr void operator-=(T value) noexcept { _id -= value; }
    constexpr void operator*=(T value) noexcept { _id *= value; }
    constexpr void operator/=(T value) noexcept { _id /= value; }
    constexpr void operator%=(T value) noexcept { _id %= value; }
    constexpr void operator&=(T value) noexcept { _id &= value; }
    constexpr void operator|=(T value) noexcept { _id |= value; }
    constexpr void operator^=(T value) noexcept { _id ^= value; }
    constexpr void operator<<=(u32 offset) noexcept { _id <<= offset; }
    constexpr void operator>>=(u32 offset) noexcept { _id >>= offset; }
};
