#pragma once

#include <unit/Unit.hpp>

namespace unit {


template<class T, class U>
class Value {
private:
    T _value;
public:


    constexpr
    Value(T value) noexcept : _value(value) {}


    template<class V>
    constexpr
    Value(Value<T, V> value) noexcept : _value(U::from(value).value()) {}


    constexpr
    T value() const noexcept {
        return _value;
    }
};










using g = Unit<dimension::Mass, "g", "gram", "grams">;
using kg = k<g>;


struct m : public Unit<m, quantity::Length> {


    template<class T, class U>
    static
    constexpr
    Value<T, m> from(Value<T, U> value) noexcept {
        return value.value() / 1000;
    }


    template<class T, class U>
    static
    constexpr
    Value<T, U> to(Value<T, m> value) noexcept {
        return value.value() * 1000;
    }
};


using km = k<m>;


template<class T, class U, class V>
auto operator+(Value<T, U> lhs, Value<T, V> rhs) noexcept {
    return Value<T, U>(lhs.value() + V::to(rhs));
}


template<class T, class U, template<class> class P>
auto operator*(Value<T, U> lhs, Value<T, P<U>> rhs) noexcept {
    return Value<T, U>(lhs.value() * P<U>::to(rhs.value()));
}



constexpr
auto operator""_u32(const char *data, std::size_t size) noexcept {
    u32 value = 0;

    if (data[0] == 'g') {
        return Value<u32, g>(value);
    } else {
        return Value<u32, m>(value);
    }
}


void test() {
    auto ms = "m"_u32;

    auto val = Value<u32, g>(3) + Value<u32, m>(5);
    Value<u32, g> v = Value<u32, kg>(3);
}


}
