#pragma once

#include <core/Common.hpp>

template<class T>
class RangeIterator {
private:
    T _value;
    u32 _step;
public:
    using iterator_category = std::contiguous_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = T;
    using pointer = T *;


    ///
    /// Constructors
    ///


    constexpr
    explicit
    RangeIterator(int value, int step, bool inclusive) noexcept : _value(value), _step(step) {}


    ///
    /// Operators
    ///


    constexpr
    value_type operator*() const noexcept {
        return _value;
    }


    constexpr
    value_type operator[](difference_type n) const noexcept {
        return *(this + n);
    }


    constexpr
    RangeIterator& operator++() noexcept {
        _value += _step;
        return *this;
    }


    constexpr
    RangeIterator operator++(int) noexcept {
        RangeIterator tmp(*this);
        _value += _step;
        return tmp;
    }


    constexpr
    RangeIterator &operator--() noexcept {
        _value -= _step;
        return *this;
    }


    constexpr
    RangeIterator operator--(int) noexcept {
        RangeIterator tmp(*this);
        _value -= _step;
        return tmp;
    }


    constexpr
    RangeIterator &operator+=(difference_type n) noexcept {
        _value += n * _step;
        return *this;
    }


    constexpr
    RangeIterator &operator-=(difference_type n) noexcept {
        _value -= n * _step;
        return *this;
    }


    constexpr
    difference_type operator-(const RangeIterator &other) const noexcept {
        return (_value - other._value) / _step;
    }


    constexpr
    bool operator!=(const RangeIterator &other) const noexcept {
        return _value != other._value;
    }


    constexpr
    bool operator==(const RangeIterator &other) const noexcept {
        return _value == other._value;
    }
};


/// @brief A value range
/// @tparam T The value type
template<class T>
class Range {
private:
    const T _start;
    const T _end;
    const u32 _step;
public:


    ///
    /// Constructors
    ///


    constexpr
    explicit
    Range(T start, T end) noexcept : _start(start), _end(end), _step(1) {}


    constexpr
    explicit
    Range(T start, T end, u32 step) noexcept : _start(start), _end(end), _step(step) {}


    ///
    /// Properties
    ///


    constexpr
    T start() const noexcept {
        return _start;
    }


    constexpr
    T end() const noexcept {
        return _end;
    }


    constexpr
    u32 step() const noexcept {
        return _step;
    }


    constexpr
    u32 size() const noexcept {
        return (_end - _start) / _step;
    }


    ///
    /// Iterator
    ///


    constexpr
    RangeIterator begin() const noexcept {
        return RangeIterator(_start, _step);
    }


    constexpr
    RangeIterator end() const noexcept {
        return RangeIterator(_end, _step);
    }
};
