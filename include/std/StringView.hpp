#pragma once

#include <std/Slice.hpp>


/// @brief A non-owning string.
class StringView {
private:
    Slice<const u8> _data;
public:


    constexpr
    StringView(std::nullptr_t) noexcept : _data(nullptr) {}


    constexpr
    StringView(const u8 *data, u32 size) noexcept : _data(data, size) {}


    constexpr
    StringView(Slice<const u8> other) noexcept : _data(other) {}


    template<u32 SIZE>
    constexpr
    StringView(const char (&data)[SIZE]) noexcept :
        _data(static_cast<const u8 *>(static_cast<const void *>(data)), SIZE - 1)
    {}


    constexpr
    StringView(const char *data, u32 size) noexcept :
        _data(static_cast<const u8 *>(static_cast<const void *>(data)), size)
    {}


    ///
    /// Type Casts
    ///


    constexpr
    operator Slice<const u8>() const noexcept {
        return _data;
    }


    constexpr
    operator const u8 *() const noexcept {
        return _data;
    }


    ///
    /// Operators
    ///


    /// Return true if this object is equal to the other object.
    constexpr
    bool operator==(StringView other) const noexcept {
        return is_equal(other);
    }


    /// Return true if this object is not equal to the other object.
    constexpr
    bool operator!=(StringView other) const noexcept {
        return !is_equal(other);
    }


    /// Return true if this object is less than the other object.
    constexpr
    bool operator<(StringView other) const noexcept {
        return compare(other) < 0;
    }


    /// Return true if this object is greater than the other object.
    constexpr
    bool operator>(StringView other) const noexcept {
        return compare(other) > 0;
    }


    /// Return true if this object is less than or equal to the other object.
    constexpr
    bool operator<=(StringView other) const noexcept {
        return compare(other) <= 0;
    }


    /// Return true if this object is greater than or equal to the other object.
    constexpr
    bool operator>=(StringView other) const noexcept {
        return compare(other) >= 0;
    }


    constexpr
    const u8 &operator*() const {
        return *_data;
    }


    constexpr
    const u8 &operator[](u32 index) const {
        return _data[index];
    }


    constexpr
    StringView operator++(int) {
        StringView tmp(*this);
        _data += 1;
        _size -= 1;
        return tmp;
    }


    constexpr
    StringView &operator++() {
        _data += 1;
        _size -= 1;
        return *this;
    }


    constexpr
    StringView operator+(u32 size) const {
        return StringView(_data + size, _size - size);
    }


    constexpr
    StringView &operator+=(u32 size) {
        _data += size;
        _size -= size;
        return *this;
    }


    constexpr
    StringView operator--(int) {
        StringView tmp(*this);
        _data -= 1;
        _size += 1;
        return tmp;
    }


    constexpr
    StringView &operator--() {
        _data -= 1;
        _size += 1;
        return *this;
    }


    constexpr
    StringView &operator-=(u32 size) {
        _data -= size;
        _size += size;
        return *this;
    }


    constexpr
    StringView operator-(u32 size) const noexcept {
        return StringView(_data - size, _size + size);
    }


    ///
    /// Properties
    ///


    // Return true if the String contains no elements.
    constexpr
    bool is_empty() const noexcept {
        return _data.is_empty();
    }


    // Return the number of elements in the String.
    constexpr
    u32 size() const noexcept {
        return _data.size();
    }


    constexpr
    const u8 *data() const noexcept {
        return _data.data();
    }


    constexpr
    StringView slice(u32 start) const noexcept {
        return _data.slice(start);
    }


    constexpr
    StringView slice(u32 start, u32 end) const noexcept {
        return _data.slice(start, end);
    }


    constexpr
    bool starts_with(StringView other) const noexcept {
        return _data.starts_with(other);
    }


    constexpr
    bool starts_with(u8 ch) const noexcept {
        return _data.starts_with(ch);
    }


    constexpr
    bool contains(StringView other) const noexcept {
        return _data.contains(other);
    }


    constexpr
    bool contains(u8 ch) const noexcept {
        return _data.contains(ch);
    }


    ///
    /// Equatable<StringView>
    ///


    constexpr
    bool is_equal(const u8 *data, u32 size) const {
        if (_size != size) {
            return false;
        }

        return memcmp(_data, data, size) == 0;
    }


    constexpr
    bool is_equal(StringView other) const {
        return is_equal(other._data, other._size);
    }


    constexpr
    bool is_equal(StringView other, u32 size) const {
        return is_equal(other._data, size);
    }


    ///
    /// Comparable<StringView>
    ///


    constexpr
    i32 compare(const u8 *data, u32 size) const {
        i32 result = memcmp(_data, data, std::min(_size, size));

        if (result) {
            return result;
        }

        return _size - size;
    }


    constexpr
    i32 compare(StringView other) const {
        return compare(other._data, other._size);
    }


    constexpr
    i32 compare(StringView other, u32 size) const {
        return compare(other._data, size);
    }
};
