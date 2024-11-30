#pragma once

#include <core/Object.hpp>


template<class T, size_t SIZE>
class Array {
private:
    T _data[SIZE];
public:


    ///
    /// Constructors
    ///


    constexpr
    Array() {
        for (u32 i = 0; i < SIZE ; ++i) {
            new(&_data[i]) T();
        }
    }


    /// @brief Create an array from an initializer list.
    /// @param data The initializer list
    constexpr
    Array(std::initializer_list<T> data) {
        for (u32 i = 0; i < SIZE; ++i) {
            if (i < data.size()) {
                new(&_data[i]) T(data.begin()[i]);
            } else {
                new(&_data[i]) T();
            }
        }
    }


    /// @brief Create an array from a slice by copying as many values from from the slice as are
    /// present and will fit in the array.
    /// @param data The slice from which to copy elements
    constexpr
    Array(Slice<const T> data) {
        for (u32 i = 0; i < SIZE ; ++i) {
            if (i < data.size()) {
                new(&_data[i]) T(data[i]);
            } else {
                new(&_data[i]) T();
            }
        }
    }


    /// @brief Create an array from a slice by copying as many values from from the slice as are
    /// present and will fit in the array.
    /// @param data The slice from which to copy elements
    constexpr
    Array(const T *data, u32 size) {
        for (u32 i = 0; i < SIZE ; ++i) {
            if (i < size) {
                new(&_data[i]) T(data[i]);
            } else {
                new(&_data[i]) T();
            }
        }
    }


    /// @brief Create a slice from a built-in array.
    /// @param data The array
    template<size_t SIZE2>
    constexpr
    Array(T (&data)[SIZE2]) {
        for (u32 i = 0; i < SIZE; ++i) {
            if (i < SIZE2) {
                new(&_data[i]) T(data[i]);
            } else {
                new(&_data[i]) T();
            }
        }
    }


    /// @brief Create a vector with the given inital size and fill it with copies of the given
    /// default value.
    /// @param size The initial size of the vector
    /// @param value The default value with which to fill the vector
    explicit
    Array(const T &value, u32 size) {
        for (u32 i = 0; i < std::min<u32>(SIZE, size); ++i) {
            if (i < size) {
                new(&_data[i]) T(value);
            } else {
                new(&_data[i]) T();
            }
        }
    }


    ///
    /// Destructor
    ///


    ~Array() {
        Object::destroy(_data);
    }


    ///
    /// Type Casts
    ///


    /// @brief Implicit cast.
    constexpr
    operator Slice<const T>() const {
        return Slice<const T>(_data, SIZE);
    }


    /// @brief Implicit cast.
    constexpr
    operator Slice<T>() {
        return Slice<T>(_data, SIZE);
    }


    /// @brief Implicit cast.
    constexpr
    operator const T *() const {
        return _data;
    }


    /// @brief Implicit cast.
    constexpr
    operator T *() {
        return _data;
    }


    ///
    /// Assignment Operators
    ///



    ///
    /// Properties
    ///


    constexpr
    const T *data() const {
        return _data;
    }


    constexpr
    T *data() {
        return _data;
    }


    constexpr
    u32 size() const {
        return SIZE;
    }


    /// @brief Return true if the string is empty.
    /// @return true if the string is empty
    constexpr
    bool is_empty() const {
        return SIZE == 0;
    }


    ///
    /// Methods
    ///


    constexpr
    void fill(const T &value) {
        Slice<T>(*this).fill(value);
    }


    /// @brief Return a slice of the array.
    /// @param start The index of the first element
    /// @param end The index just past the last element
    constexpr
    Slice<const T> slice(u32 start, u32 end) const {
        return Slice<const T>(&_data[start], end - start);
    }


    /// @brief Return a slice of the array.
    /// @param start The index of the first element
    /// @param end The index just past the last element
    constexpr
    Slice<T> slice(u32 start, u32 end) {
        return Slice<T>(&_data[start], end - start);
    }


    /// @brief Return a slice of the array from the index through the end of the array.
    /// @param start The index of the first element
    constexpr
    Slice<const T> slice(u32 start) const {
        return slice(start, (SIZE - 1) - start);
    }


    /// @brief Return a slice of the array from the given index through the end of the array.
    /// @param start The index of the first element
    constexpr
    Slice<T> slice(u32 start) {
        return slice(start, (SIZE - 1) - start);
    }


    ///
    /// Operators
    ///


    /// @brief Return a reference to the first element of the array.
    constexpr
    const T &operator*() const {
        return *_data;
    }


    /// @brief Return a reference to the first element of the array.
    constexpr
    T &operator*() {
        return *_data;
    }


    /// @brief Return a reference to the element of the array by index.
    /// @param index The index of the element
    constexpr
    const T &operator[](u32 index) const {
        return _data[index];
    }


    /// @brief Return a reference to the element of the array by index.
    /// @param index The index of the element
    constexpr
    T &operator[](u32 index) {
        return _data[index];
    }


    ///
    /// Iterator
    ///


    const T *begin() const {
        return Slice<const T>(*this).begin();
    }


    T *begin() {
        return Slice<T>(*this).begin();
    }


    const T *end() const {
        return Slice<const T>(*this).end();
    }


    T *end() {
        return Slice<T>(*this).end();
    }
};
