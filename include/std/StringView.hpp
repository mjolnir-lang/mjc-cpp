#pragma once

#include "std/String.hpp"

#include <cstring>


/// @brief A non-owning string.
class StringView {
private:
    const u8 *data_ = nullptr;
    u32 size_ = 0;
public:


    StringView(const u8 *data, u32 size) :
        data_(data),
        size_(size)
    {}


    StringView(StringView other, u32 size) :
        data_(other.data_),
        size_(size)
    {}


    StringView(const String &other) :
        data_(other.data()),
        size_(other.size())
    {}


    StringView(String other, u32 size) :
        data_(other.data()),
        size_(size)
    {}


    template<size_t SIZE>
    StringView(const char (&data)[SIZE]) :
        data_(reinterpret_cast<const u8 *>(data)),
        size_(SIZE)
    {}


    StringView(const char *data, u32 size) :
        data_(reinterpret_cast<const u8 *>(data)),
        size_(size)
    {}


    StringView(std::nullptr_t) {}


    StringView() {}


    ~StringView() {}


    // Return true if the String contains no elements.
    bool is_empty() const {
        return size_ != 0;
    }


    // Return the number of elements in the String.
    u32 size() const {
        return size_;
    }


    const u8 *data() const {
        return data_;
    }


    StringView slice(u32 start, u32 end) {
        return StringView(&data_[start], end - start);
    }


    const StringView slice(u32 start, u32 end) const {
        return StringView(&data_[start], end - start);
    }


    ///
    /// Equatable<StringView>
    ///


    bool is_equal(const u8 *data, u32 size) const {
        if (size_ != size) {
            return false;
        }

        return memcmp(data_, data, size) == 0;
    }


    bool is_equal(StringView other) const {
        return is_equal(other.data_, other.size_);
    }


    bool is_equal(StringView other, u32 size) const {
        return is_equal(other.data_, size);
    }


    /// Return true if this object is equal to the other object.
    bool operator==(StringView other) const {
        return is_equal(other);
    }


    /// Return true if this object is not equal to the other object.
    bool operator!=(StringView other) const {
        return !is_equal(other);
    }


    ///
    /// Comparable<StringView>
    ///


    i32 compare(const u8 *data, u32 size) const {
        i32 result = memcmp(data_, data, std::min(size_, size));

        if (result) {
            return result;
        }

        return size_ - size;
    }


    i32 compare(StringView other) const {
        return compare(other.data_, other.size_);
    }


    i32 compare(StringView other, u32 size) const {
        return compare(other.data_, size);
    }

    /// Return true if this object is less than the other object.
    bool operator<(StringView other) const {
        return compare(other) < 0;
    }


    /// Return true if this object is greater than the other object.
    bool operator>(StringView other) const {
        return compare(other) > 0;
    }


    /// Return true if this object is less than or equal to the other object.
    bool operator<=(StringView other) const {
        return compare(other) <= 0;
    }


    /// Return true if this object is greater than or equal to the other object.
    bool operator>=(StringView other) const {
        return compare(other) >= 0;
    }


    ///
    /// Indexable<const u8>
    ///


    const u8 &operator[](u32 index) {
        return data_[index];
    }


    const u8 &operator[](u32 index) const {
        return data_[index];
    }


    StringView &operator++(int) {
        StringView tmp(*this);
        data_ += 1;
        size_ -= 1;
        return tmp;
    }


    StringView &operator++() {
        data_ += 1;
        size_ -= 1;
        return *this;
    }


    StringView &operator+=(u32 size) {
        data_ += size;
        size_ -= size;
        return *this;
    }


    StringView &operator--(int) {
        StringView tmp(*this);
        data_ -= 1;
        size_ += 1;
        return tmp;
    }


    StringView &operator--() {
        data_ -= 1;
        size_ += 1;
        return *this;
    }


    StringView &operator-=(u32 size) {
        data_ -= size;
        size_ += size;
        return *this;
    }
};
