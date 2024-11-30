#pragma once

#include <unit/Unit.hpp>
#include <core/Where.hpp>

namespace unit {


template<class T, class U>
class Quantity {
private:
    T _value;
public:


    constexpr
    explicit
    Quantity(T value) noexcept : _value(value) {}


    constexpr
    Quantity(const Quantity<T, U> &other) noexcept : _value(other._value) {}


    template<class T2>
    constexpr
    Quantity(Quantity<T2, U> other) noexcept : _value(static_cast<T>(other._value)) {}


    template<class T2, class U2, class = Where::is_same<typename U::Dimension, typename U2::Dimension>>
    constexpr
    Quantity(Quantity<T2, U2> other) noexcept {
        //using ratio = typename U::Per<typename U2::Ratio>;
        //_value = static_cast<T>(other._value) * ratio::num / ratio::den;
    }


    constexpr
    T value() const noexcept {
        return _value;
    }


    Quantity<T, U> operator+(Quantity<T, U> rhs) const noexcept {
        return Quantity<T, U>(_value + rhs._value);
    }


    Quantity<T, U> operator-(Quantity<T, U> rhs) const noexcept {
        return Quantity<T, U>(_value - rhs._value);
    }


    Quantity<T, U> operator+=(Quantity<T, U> rhs) noexcept {
        return _value += rhs._value;
    }


    Quantity<T, U> operator-=(Quantity<T, U> rhs) noexcept {
        return _value -= rhs._value;
    }
};


template<class U>
using u8 = unit::Quantity<core::u8, U>;

template<class U>
using u16 = unit::Quantity<core::u16, U>;

template<class U>
using u32 = unit::Quantity<core::u32, U>;

template<class U>
using u64 = unit::Quantity<core::u64, U>;


}
