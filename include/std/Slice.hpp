#pragma once

#include <std/Common.hpp>


/// @brief A non-owning array of contiguous elements
/// @tparam T 
template<class T>
class Slice {
private:
    T *_data;
    u32 _size;
public:


    ///
    /// Constructors
    ///


    constexpr
    Slice(std::nullptr_t) noexcept : _data(nullptr), _size(0) {}


    constexpr
    Slice(T *data, u32 size) noexcept : _data(data), _size(size) {}


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


    ///
    /// Properties
    ///


    // Return true if the Vector contains no elements.
    constexpr
    bool is_empty() const noexcept {
        return _size == 0;
    }


    // Return the number of elements in the Vector.
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


    bool starts_with(Slice<const T> other) const noexcept {
        if (other._size > _size) {
            return false;
        }

        return slice(0, other._size) == other;
    }


    bool starts_with(T value) const noexcept {
        return _size > 0 && *_data == value;
    }


    bool contains(Slice<const T> other) const noexcept {
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


    ///
    /// Methods
    ///


    constexpr
    Slice<const T> slice(u32 start, u32 end) const noexcept {
        return Slice<const T>(&_data[start], end - start);
    }


    constexpr
    Slice<T> slice(u32 start, u32 end) noexcept {
        return Slice<T>(&_data[start], end - start);
    }


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
