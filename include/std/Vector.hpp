#pragma once

#include <std/Slice.hpp>

#include <vector>


template<class T>
class Vector {
private:
    std::vector<T> _data;
public:


    ///
    /// Constructors
    ///


    constexpr
    Vector() noexcept : _data() {}


    constexpr
    Vector(std::nullptr_t) noexcept : _data(nullptr) {}


    constexpr
    Vector(Slice<const T> other) noexcept : _data(other) {}


    ///
    /// Type Casts
    ///


    constexpr
    operator Slice<const T>() const noexcept {
        return _data;
    }


    constexpr
    operator const T *() const noexcept {
        return _data;
    }


    ///
    /// Operators
    ///


    /// Return true if this object is equal to the other object.
    constexpr
    bool operator==(Slice<const T> other) const noexcept {
        return is_equal(other);
    }


    /// Return true if this object is not equal to the other object.
    constexpr
    bool operator!=(Slice<const T> other) const noexcept {
        return !is_equal(other);
    }


    /// Return true if this object is less than the other object.
    constexpr
    bool operator<(Slice<const T> other) const noexcept {
        return compare(other) < 0;
    }


    /// Return true if this object is greater than the other object.
    constexpr
    bool operator>(Slice<const T> other) const noexcept {
        return compare(other) > 0;
    }


    /// Return true if this object is less than or equal to the other object.
    constexpr
    bool operator<=(Slice<const T> other) const noexcept {
        return compare(other) <= 0;
    }


    /// Return true if this object is greater than or equal to the other object.
    constexpr
    bool operator>=(Slice<const T> other) const noexcept {
        return compare(other) >= 0;
    }


    constexpr
    const T &operator*() const noexcept {
        return *_data;
    }


    constexpr
    T &operator*() noexcept {
        return *_data;
    }


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
    const T *data() const noexcept {
        return _data.data();
    }


    constexpr
    T *data() noexcept {
        return _data.data();
    }


    constexpr
    Slice<const T> slice(u32 start) const noexcept {
        return _data.slice(start);
    }


    constexpr
    Slice<const T> slice(u32 start, u32 end) const noexcept {
        return _data.slice(start, end);
    }


    ///
    /// Methods
    ///


    //template<class... Args>
    //void append(Args... args) noexcept {
    //    _data.append(std::forward<Args>(args)...);
    //}


    void append(T &&other) noexcept {
        _data.append(std::move(other));
    }


    void append(const T *other, u32 size = 1) noexcept {
        _data.append(other);
    }


    void append(Slice<const T> other) noexcept {
        _data.append(other);
    }


    void insert(Slice<const T> other) noexcept {
        _data.insert(other);
    }


    void remove(u32 index) noexcept {
        _data.remove(index);
    }




    const T *begin() const noexcept {
        return _data.begin();
    }


    T *begin() noexcept {
        return _data.begin();
    }


    const T *end() const noexcept {
        return _data.end();
    }


    T *end() noexcept {
        return _data.end();
    }
};
