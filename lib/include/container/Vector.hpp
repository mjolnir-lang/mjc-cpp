#pragma once

#include <core/Common.hpp>
#include <vector>

template<class T>
using Vector = std::vector<T>;


/*
#include <core/UnmanagedBox.hpp>
#include <io/OutputStream.hpp>

#include <algorithm>


/// @brief A dynamically allocated, contiguous array of elements.
/// @tparam T The element type
template<class T>
class Vector {
private:
    UnmanagedBox<T> _data;
    u32 _capacity;
    u32 _size;
public:


    ///
    /// Constructors
    ///


    /// @brief Create an empty vector. (Default Constructor)
    constexpr
    Vector() noexcept : _data(nullptr), _capacity(0), _size(0) {}


    /// @brief Create an empty vector. (Default Constructor)
    constexpr
    Vector(nullptr_t) noexcept : _data(nullptr), _capacity(0), _size(0) {}


    /// @brief Move constructor.
    constexpr
    Vector(Vector<T> &&other) noexcept : _data(other._data), _capacity(other._capacity), _size(other._size) {
        other._data = nullptr;
        other._capacity = 0;
        other._size = 0;
    }


    /// @brief Copy constructor.
    constexpr
    Vector(const Vector<T> &other) noexcept {
        append(other);
    }


    /// @brief Create a vector from an initializer list.
    /// @param values The initializer list
    Vector(std::initializer_list<T> values) noexcept : _data(nullptr), _capacity(0), _size(0) {
        append(values);
    }


    /// @brief Create a vector from a slice. (Copy Constructor)
    /// @param values The values to copy
    Vector(Slice<const T> values) noexcept : _data(nullptr), _capacity(0), _size(0) {
        append(values);
    }


    /// @brief Create a vector from a sequence of values.
    /// @param values The values to copy
    /// @param size The number of values to copy
    Vector(const T *values, u32 size) noexcept : _data(nullptr), _capacity(0), _size(0) {
        append(values, size);
    }


    /// @brief Create a vector with the given inital size and fill it with copies of the given
    /// default value.
    /// @param size The initial size of the vector
    /// @param value The default value with which to fill the vector
    explicit
    Vector(const T &value, u32 size) noexcept : _data(nullptr), _capacity(0), _size(0) {
        for (u32 i = 0; i < size; ++i) {
            append(value);
        }
    }


    explicit
    Vector(u32 size, T value = T()) noexcept : _data(size), _capacity(size), _size(size) {
        for (u32 i = 0; i < size; ++i) {
            append(value);
        }
    }


    ///
    /// Destructor
    ///


    ~Vector() {
        clear();
    }


    ///
    /// Type Casts
    ///


    /// @brief Implicit cast to interface OutputStream<T>.
    constexpr
    operator const OutputStream<T>() const noexcept {
        return OutputStream<T>(const_cast<Vector<T> *>(this), _vtable);
    }


    /// @brief Implicit cast to interface OutputStream<T>.
    constexpr
    operator OutputStream<T>() noexcept {
        return OutputStream<T>(this, _vtable);
    }


    /// @brief Implicit cast.
    constexpr
    operator Slice<const T>() const noexcept {
        return Slice<const T>(_data, _size);
    }


    /// @brief Implicit cast.
    constexpr
    operator Slice<T>() noexcept {
        return Slice<T>(_data, _size);
    }


    /// @brief Implicit cast.
    constexpr
    operator const T *() const noexcept {
        return _data;
    }


    /// @brief Implicit cast.
    constexpr
    operator T *() noexcept {
        return _data;
    }


    ///
    /// Assignment Operators
    ///


    /// @brief Move assignment operator.
    constexpr
    void operator=(Vector<T> &&other) noexcept {
        Object::swap(_data, other._data);
    }


    /// @brief Copy assignment operator.
    constexpr
    void operator=(const Vector<T> &other) noexcept {
        clear();
        append(other);
    }


    /// @brief Copy assignment operator.
    constexpr
    void operator=(Slice<const T> other) noexcept {
        clear();
        append(other);
    }


    ///
    /// Operators
    ///


    /// @brief Access the first character of the vector.
    /// @note Undefined if the vector is empty.
    constexpr
    const T &operator*() const noexcept {
        return *_data;
    }


    /// @brief Access the first character of the vector.
    /// @note Undefined if the vector is empty.
    constexpr
    T &operator*() noexcept {
        return *_data;
    }


    /// @brief Access a character of the vector by index.
    /// @param index The index of the character
    /// @note Undefined if the given index is outside the bounds of the vector.
    constexpr
    const T &operator[](u32 index) const noexcept {
        return _data[index];
    }


    /// @brief Access a character of the vector by index.
    /// @param index The index of the character
    /// @note Undefined if the given index is outside the bounds of the vector.
    constexpr
    T &operator[](u32 index) noexcept {
        return _data[index];
    }


    ///
    /// Properties
    ///


    /// @brief Return a pointer to the vector data.
    constexpr
    const T *data() const noexcept {
        return _data;
    }


    /// @brief Return a pointer to the vector data.
    constexpr
    T *data() noexcept {
        return _data;
    }


    /// @brief Return the size of the allocated space for the vector data.
    constexpr
    u32 capacity() const noexcept {
        return _capacity;
    }


    /// @brief Return the size of the vector data.
    constexpr
    u32 size() const noexcept {
        return _size;
    }


    /// @brief Return the available space in the vector data.
    constexpr
    u32 space() const noexcept {
        return _capacity - _size;
    }


    /// @brief Return true if the vector is empty.
    constexpr
    bool is_empty() const noexcept {
        return _size == 0;
    }


    ///
    /// Constant Methods
    ///


    /// @brief Return a slice of the vector.
    /// @param start The index of the first character
    /// @param size The number of characters
    constexpr
    Slice<const T> slice(u32 start, u32 end) const noexcept {
        return slice().slice(start, end);
    }


    /// @brief Return a slice of the vector.
    /// @param index The index of the first character
    /// @param size The number of characters
    constexpr
    Slice<const T> slice(u32 start) const noexcept {
        return slice().slice(start);
    }


    /// @brief Return a slice of the string from an index through the end of the string.
    /// @param index The index of the first element
    constexpr
    Slice<const T> slice() const noexcept {
        return Slice<const T>(0, _size);
    }


    /// @brief Return a slice of the string from an index through the end of the string.
    /// @param index The index of the first element
    constexpr
    Slice<T> slice() noexcept {
        return Slice<T>(0, _size);
    }


    /// @brief Test if the vectors are equal.
    /// @param other The second vector
    /// @return true if the vectors are equal
    constexpr
    bool is_equal(Slice<const T> other) const noexcept {
        return slice().is_equal(other);
    }


    /// @brief Test if the vectors are equal up to the maximum number of
    /// characters.
    /// @param other The second vector
    /// @return true if the vectors are equal
    constexpr
    bool is_equal(const T *data, u32 size) const noexcept {
        return slice().is_equal(data, size);
    }


    /// @brief Compare the first vector with the second vector.
    /// @param other The second vector
    /// @return 0 if the vectors are equal, positive if the first vector is
    /// greater than the second vector, and negative if the first vector is
    /// less than the second vector
    constexpr
    i32 compare(Slice<const T> other) const noexcept {
        return slice().compare(other);
    }


    /// @brief Compare the first vector with the second vector up to the
    /// maximum number of characters.
    /// @param other The second vector
    /// @return 0 if the vectors are equal, positive if the first vector is
    /// greater than the second vector, and negative if the first vector is
    /// less than the second vector
    constexpr
    i32 compare(const T *data, u32 size) const noexcept {
        return slice().compare(data, size);
    }


    /// @brief Count the characters from the beginning of the vector which are
    /// contained in the character set.
    /// @param set The character set
    /// @return The number of characters
    constexpr
    u32 count(Slice<const T> set) const noexcept {
        return slice().count(set);
    }


    /// @brief Count the characters from the beginning of the vector which are
    /// not contained in the character set.
    /// @param set The character set
    /// @return The number of characters
    constexpr
    u32 count_not_of(Slice<const T> set) const noexcept {
        return slice().count_not_of(set);
    }


    ///
    /// Index Of
    ///



    /// @brief Return the index of the first matching character in the string
    /// or the size of the string if no matching character was found.
    /// @param ch The character for which to search
    constexpr
    Result<u32> index_of_first(T value) const noexcept {
        return slice().index_of_first(value);
    }


    /// @brief Return the index of the first matching substring in the string
    /// or nullptr if one could not be found.
    /// @param substring The substring for which to search
    /// @return The index of the first matching substring or just past the end of this string.
    constexpr
    Result<u32> index_of_first(Slice<const T> data) const noexcept {
        return slice().index_of_first(data);
    }


    /// @brief Return the index of the first matching substring in the string
    /// or nullptr if one could not be found.
    /// @param substring The substring for which to search
    /// @return The index of the first matching substring or just past the end of this string.
    constexpr
    Result<u32> index_of_first(const T *data, u32 size) const noexcept {
        return index_of_first(Slice<const T>(data, size));
    }


    /// @brief Return the index of the last matching character in the string
    /// or U32_MAX if one could not be found.
    /// @param ch The character for which to search
    /// @return The pointer to the last matching character or nullptr
    constexpr
    Result<u32> index_of_last(T value) const noexcept {
        return slice().index_of_last(value);
    }


    /// @brief Return the index of the last matching substring in the string
    /// or U32_MAX if one could not be found.
    /// @param substring The substring for which to search
    /// @return The pointer to the last matching substring or nullptr
    constexpr
    Result<u32> index_of_last(Slice<const T> data) const noexcept {
        return slice().index_of_last(data);
    }


    /// @brief Return the index of the last matching substring in the string
    /// or U32_MAX if one could not be found.
    /// @param substring The substring for which to search
    /// @return The pointer to the last matching substring or nullptr
    constexpr
    Result<u32> index_of_last(const T *data, u32 size) const noexcept {
        return slice().index_of_last(data, size);
    }


    ///
    /// Find
    ///


    /// @brief Return the index of the first matching character in the string
    /// or the size of the string if no matching character was found.
    /// @param ch The character for which to search
    constexpr
    const T *find_first(T ch) const noexcept {
        return slice().find_first(ch);
    }


    /// @brief Return the index of the first matching substring in the string
    /// or nullptr if one could not be found.
    /// @param substring The substring for which to search
    /// @return The index of the first matching substring or just past the end of this string.
    constexpr
    Slice<const T> find_first(Slice<const T> data) const noexcept {
        return slice().find_first(data);
    }


    /// @brief Return the index of the first matching substring in the string
    /// or nullptr if one could not be found.
    /// @param substring The substring for which to search
    /// @return The index of the first matching substring or just past the end of this string.
    constexpr
    Slice<const T> find_first(const T *data, u32 size) const noexcept {
        return find_first(Slice<const T>(data, size));
    }


    /// @brief Return the index of the last matching character in the string
    /// or U32_MAX if one could not be found.
    /// @param ch The character for which to search
    /// @return The pointer to the last matching character or nullptr
    constexpr
    const T *find_last(T value) const noexcept {
        return slice().find_last(value);
    }


    /// @brief Return the index of the last matching substring in the string
    /// or U32_MAX if one could not be found.
    /// @param substring The substring for which to search
    /// @return The pointer to the last matching substring or nullptr
    constexpr
    Slice<const T> find_last(Slice<const T> substring) const noexcept {
        return slice().find_last(substring);
    }


    /// @brief Return the index of the last matching substring in the string
    /// or U32_MAX if one could not be found.
    /// @param substring The substring for which to search
    /// @return The pointer to the last matching substring or nullptr
    constexpr
    Slice<const T> find_last(const T *substring, u32 size) const noexcept {
        return slice().find_last(substring, size);
    }








    ///
    /// Mutable Methods
    ///


    /// @brief Remove all elements from the vector.
    void clear() noexcept {
        for (u32 i = 0; i < _size; ++i) {
            Object::destroy(_data[i]);
        }

        _size = 0;
    }


    /// @brief Resize the vector. If the new size is greater than the current size, the new
    /// elements will be default initialized. If the new size is less than the current size, the
    /// trailing elements will be removed. If the new size is equal to the current size, nothing
    /// happens.
    ///
    /// If the size is increased and the underlying storage is reallocated, all references to the
    /// elements in the vector data will be invalidated.
    /// @param size The new size of the vector
    void resize(u32 size) noexcept {
        if (size == _size) {
            return;
        }

        if (size < _size) {
            remove(size, _size - _size);
            return;
        }

        append(T(), size - _size);
    }


    /// @brief Resize the vector. If the new size is greater than the current size, the new
    /// elements will be copy initialized using the given value. If the new size is less than the
    /// current size, the trailing elements will be removed. If the new size is equal to the
    /// current size, nothing happens.
    ///
    /// If the size is increased and the underlying storage is reallocated, all references to the
    /// elements in the vector data will be invalidated.
    /// @param size The new size of the vector
    void resize(u32 size, const T &value) noexcept {
        if (size == _size) {
            return;
        }

        if (size < _size) {
            remove(size, _size - _size);
            return;
        }

        append(value, size - _size);
    }


    /// @brief Adjust the capacity of the vector.
    ///
    /// If the capacity is increased and the underlying storage is reallocated, all references to
    /// the elements in the vector data will be invalidated.
    /// @param size The requested allocated capacity
    void reserve(u32 size) noexcept {
        _data.resize(size);
    }


    /// @brief Reduce the allocated capacity to the vector size.
    void trim() noexcept {
        _data.trim(_size);
    }


    /// @brief Swap the underlying elements of two vectors.
    /// @param other The other vector
    constexpr
    void fill(Slice<const T> other) noexcept {
        Object::fill(_data, other);
    }


    ///
    /// Element Insertion Methods
    ///


    /// @brief Insert a vector into the vector at an arbitrary index.
    /// @param index The index at which to insert
    /// @param other The vector to insert
    void insert(u32 index, Slice<const T> values) noexcept {
        u32 size = _size + values.size();
        reserve(size);

        if (index < _size) {
            Object::move(&_data[index], &_data[index + values.size()], _size - (index + values.size()));
        }

        Object::copy(&_data[index], values);
        _size = size;
    }


    /// @brief Insert a byte sequence into the vector at an arbitrary index.
    /// @param index The index at which to insert
    /// @param data The byte sequence to insert
    /// @param size The number of characters to insert
    void insert(u32 index, const T *values, u32 size) noexcept {
        insert(index, Slice<const T>(values, size));
    }


    /// @brief Insert a character into the vector at an arbitrary index.
    /// @param index The index at which to insert
    /// @param ch The character to insert
    /// @param count The number of characters to insert
    void insert(u32 index, const T &value) noexcept {
        insert(index, Slice<const T>(&value, 1));
    }


    /// @brief Insert a copy of the given value into the vector at the given index a given number
    /// of times.
    /// @param index The index at which to insert the values
    /// @param value The value to copy into vector
    /// @param count The number of copies to insert
    void insert(u32 index, const T &value, u32 count) noexcept {
        u32 size = _size + count;
        reserve(size);
        //Object::move(new_data, _data, index);

        if (index < _size) {
            //Object::move(&new_data[index + count], &_data[index], _size - (index + count));
        }

        Object::copy(&_data[index], &value, count);
        _size = size;
    }


    /// @brief Append the given values to the end of the vector.
    /// @param values The values to append
    void append(Slice<const T> values) noexcept {
        insert(_size, values);
    }


    /// @brief Append a byte sequence to the end of the vector.
    /// @param values The byte sequence to append
    /// @param size The number of bytes to append
    void append(const T *values, u32 size) noexcept {
        insert(_size, Slice<const T>(values, size));
    }


    /// @brief Append the given value to the end of the vector the given number of times.
    /// @param value The value to append
    /// @param count The number of times to append the value
    void append(const T &value, u32 count) noexcept {
        insert(_size, value, count);
    }


    /// @brief Append the given value to the end of the vector the given number of times.
    /// @param value The value to append
    /// @param count The number of times to append the value
    void append(T value) noexcept {
        insert(_size, value, 1);
    }


    ///
    /// Element Removal Methods
    ///


    /// @brief Remove a sequence of elements from the vector.
    /// @param index The index of the first element to remove
    /// @param count The number of elements to remove
    constexpr
    void remove(u32 index, u32 count = 1) noexcept {
        for (u32 i = index; i < index + count; ++i) {
            Object::destroy(_data[i]);
        }

        Object::move(&_data[index], &_data[index + count], _size - (index + count));
        _size -= count;
    }


    ///
    /// Iterator
    ///


    /// @brief Return an iterator to the beginning of the vector.
    constexpr
    const T *begin() const noexcept {
        return _data;
    }


    /// @brief Return an iterator to the beginning of the vector.
    constexpr
    T *begin() noexcept {
        return _data;
    }


    /// @brief Return an iterator to the end of the vector.
    constexpr
    const T *end() const noexcept {
        return &_data[_size];
    }


    /// @brief Return an iterator to the end of the vector.
    constexpr
    T *end() noexcept {
        return &_data[_size];
    }


    ///
    /// OutputStream
    ///
private:
    static
    const typename OutputStream<T>::VTable _vtable;
};


template<class T>
inline
const typename OutputStream<T>::VTable Vector<T>::_vtable{
    .space{&Vector<T>::space},
    .is_full{[](const void *) { return false; }},
    .flush{[](void *) {}},
    .write{[](void *inst, Slice<const T> data) {
        reinterpret_cast<Vector<T> *>(inst)->append(data);
        return data.size();
    }},
};


template<class T>
struct Printer<Vector<T>> {

    static
    Error print(StringPrinter &out) noexcept {
        return Printer<Slice<T>>::print(out);
    }
};
*/
