#pragma once

#include <core/Common.hpp>


/// @brief A non-owning array of contiguous elements
/// @tparam T 
template<class T>
class Range {
private:
    T *_data;
    u32 _size;
public:


    ///
    /// Constructors
    ///


    constexpr
    Range() noexcept : _data(nullptr), _size(0) {}


    constexpr
    Range(std::nullptr_t) noexcept : _data(nullptr), _size(0) {}


    constexpr
    Range(T *data, u32 size) noexcept : _data(data), _size(size) {}


    ///
    /// Type Casts
    ///


    constexpr
    operator const T *() const noexcept {
        return _data;
    }


    constexpr
    operator T *() noexcept {
        return _data;
    }


    ///
    /// Operators
    ///


    constexpr
    const T &operator[](u32 index) const noexcept {
        return _data[index];
    }


    constexpr
    T &operator[](u32 index) noexcept {
        return _data[index];
    }


    constexpr
    Range<T> operator++(int) {
        Range<T> tmp(*this);
        _data++;
        return tmp;
    }


    constexpr
    Range<T> &operator++() {
        _data += 1;
        _size -= 1;
        return *this;
    }


    constexpr
    Range<T> operator+(u32 size) const {
        return Range<T>(_data + size, _size - size);
    }


    constexpr
    Range<T> operator-(u32 size) const noexcept {
        return Range<T>(_data - size, _size + size);
    }


    constexpr
    Range<T> operator--(int) {
        Range<T> tmp(*this);
        _data -= 1;
        _size += 1;
        return tmp;
    }


    constexpr
    Range<T> &operator--() {
        _data -= 1;
        _size += 1;
        return *this;
    }


    constexpr
    void operator+=(u32 offset) noexcept {
        _data += offset;
        _size -= offset;
    }


    constexpr
    void operator-=(u32 offset) noexcept {
        _data -= offset;
        _size += offset;
    }


    constexpr
    void operator>>=(u32 offset) noexcept {
        _data += offset;
    }


    constexpr
    void operator<<=(u32 offset) noexcept {
        _data -= offset;
    }


    friend
    constexpr
    bool operator==(Range<T> a, Range<T> b) noexcept {
        if (a.size() != b.size()) {
            return false;
        }

        for (u32 i = 0; i < a.size(); ++i) {
            if (a[i] != b[i]) {
                return false;
            }
        }

        return true;
    }


    friend
    constexpr
    std::three_way_comparable operator<=>(Range<T> a, Range<T> b) noexcept {
        return a.compare(b);
    }


    ///
    /// Properties
    ///


    /// True if the slice contains no elements.
    constexpr
    bool is_empty() const noexcept {
        return _size == 0;
    }


    /// The number of elements in the slice.
    constexpr
    u32 size() const noexcept {
        return _size;
    }


    constexpr
    const T *data() const noexcept {
        return _data;
    }


    constexpr
    T *data() noexcept {
        return _data;
    }


    ///
    /// Methods
    ///



    constexpr
    bool is_equal(Range<const T> other) const noexcept {
        if (other._size != _size) {
            return false;
        }

        for (u32 i = 0; i < _size; ++i) {
            if (_data[i] != other[i]) {
                return false;
            }
        }

        return true;
    }


    constexpr
    bool is_equal(const T *data, u32 size) const noexcept {
        return is_equal({data, size});
    }



    constexpr
    i32 compare(const T *data, u32 size) const noexcept {
        return _data.compare({data, size});
    }


    constexpr
    i32 compare(Range<const T> other) const noexcept {
        u32 size = std::min(other._size, _size);

        for (u32 i = 0; i < size; ++i) {
            if (i32 result = _data[i] <=> other[i]) {
                return result;
            }
        }

        return i32(other._size - _size);
    }





    bool starts_with(Range<const T> other) const noexcept {
        if (other._size > _size) {
            return false;
        }

        return slice(0, other._size) == other;
    }


    bool starts_with(T value) const noexcept {
        return _size > 0 && *_data == value;
    }


    bool ends_with(Range<const T> other) const noexcept {
        if (other._size > _size) {
            return false;
        }

        return slice(0, other._size) == other;
    }


    bool ends_with(T value) const noexcept {
        return _size > 0 && *_data == value;
    }


    bool contains(Range<const T> other) const noexcept {
        for (u32 i = 0; i < _size - other._size; i++) {
            if (other.is_equal(&_data[i], other._size)) {
                return true;
            }
        }

        return false;
    }


    bool contains(T value) const noexcept {
        for (u32 i = 0; i < _size; i++) {
            if (_data[i] == value) {
                return true;
            }
        }

        return false;
    }


    constexpr
    Range<const T> slice(u32 start) const noexcept {
        return Range<const T>(_data + start, _size - start);
    }


    constexpr
    Range<T> slice(u32 start) noexcept {
        return Range<T>(_data + start, _size - start);
    }


    constexpr
    Range<const T> slice(u32 start, u32 end) const noexcept {
        return Range<const T>(_data + start, end - start);
    }


    constexpr
    Range<T> slice(u32 start, u32 end) noexcept {
        return Range<T>(_data + start, end - start);
    }


    ///
    /// Iterator
    ///


    constexpr
    const T *begin() const noexcept {
        return _data;
    }


    T *begin() noexcept {
        return _data;
    }


    const T *end() const noexcept {
        return _data + _size;
    }


    T *end() noexcept {
        return _data + _size;
    }
};
