#pragma once

#include <core/Function.hpp>
#include <core/Result.hpp>


/// @brief A slice is a non-owning contiguous array of elements represented by a pointer to data
/// and a size.
template<class T>
class Slice {
private:
    T *_data;
    u32 _size;
public:


    ///
    /// Constructors
    ///


    /// @brief Create an empty slice.
    constexpr
    Slice() noexcept : _data(nullptr), _size(0) {}


    /// @brief Create an empty slice from a nullptr.
    constexpr
    Slice(std::nullptr_t) noexcept : _data(nullptr), _size(0) {}


    /// @brief Create a slice from the given elements.
    /// @param data The elements
    /// @param size The size of the slice
    constexpr
    Slice(T *data, u32 size) noexcept : _data(data), _size(size) {}


    /// @brief Create a slice from an array.
    /// @tparam SIZE The size of the array.
    /// @param data The array to reference.
    template<u32 SIZE>
    constexpr
    Slice(T (&data)[SIZE]) noexcept : _data(data), _size(SIZE) {}


    /// @brief Create a slice from an initializer list.
    /// @param data The initializer list to reference.
    //template<class U = T, class = Where::is_const<U>>
    //constexpr
    //Slice(std::initializer_list<typename std::remove_const_t<T>> data) noexcept :
    //    _data(data.begin()), _size(data.size())
    //{}


    ///
    /// Type Casts
    ///


    constexpr
    operator Slice<const T>() const noexcept {
        return Slice<const T>(_data, _size);
    }


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


    /// @brief Return a reference to the first element of the slice.
    /// @note Undefined if the slice is empty.
    constexpr
    const T &operator*() const noexcept {
        return *_data;
    }


    /// @brief Return a reference to the first element of the slice.
    /// @note Undefined if the slice is empty.
    constexpr
    T &operator*() noexcept {
        return *_data;
    }


    /// @brief Return a reference to the element at the given index within the slice.
    /// @param index The index of the element
    /// @note Undefined if the given index is outside the bounds of the slice.
    constexpr
    const T &operator[](u32 index) const noexcept {
        return _data[index];
    }


    /// @brief Return a reference to the element at the given index within the slice.
    /// @param index The index of the element
    /// @note Undefined if the given index is outside the bounds of the slice.
    constexpr
    T &operator[](u32 index) noexcept {
        return _data[index];
    }


    /// @brief Increment the data pointer and decrement the size of the slice.
    /// @return A reference to the slice
    constexpr
    Slice<T> &operator++() noexcept {
        _data += 1;
        _size -= 1;
        return *this;
    }


    /// @brief Decrement the data pointer and increment the size of the slice.
    /// @return A reference to the slice
    constexpr
    Slice<T> &operator--() noexcept {
        _data -= 1;
        _size += 1;
        return *this;
    }


    /// @brief Increment the data pointer and decrement the size of the slice.
    /// @return A copy of the original value
    constexpr
    Slice<T> operator++(int) noexcept {
        Slice<T> copy = *this;
        ++*this;
        return copy;
    }


    /// @brief Decrement the data pointer and increment the size of the slice.
    /// @return A copy of the original value
    constexpr
    Slice<T> operator--(int) noexcept {
        Slice<T> copy = *this;
        --*this;
        return copy;
    }


    /// @brief Increment the data pointer and decrement the size of the slice by the given amount.
    /// @param size The amount by which to increment
    constexpr
    void operator+=(u32 offset) noexcept {
        _data += offset;
        _size -= offset;
    }


    /// @brief Decrement the data pointer and increment the size of the slice by the given amount.
    /// @param size The amount by which to decrement
    constexpr
    void operator-=(u32 offset) noexcept {
        _data -= offset;
        _size += offset;
    }


    /// @brief Shift the slice to the right by the given number of elements.
    /// @param size The amount by which to increment
    constexpr
    void operator>>=(u32 offset) noexcept {
        _data += offset;
    }


    /// @brief Shift the slice to the left by the given number of elements.
    /// @param size The amount by which to decrement
    constexpr
    void operator<<=(u32 offset) noexcept {
        _data -= offset;
    }


    ///
    /// Properties
    ///


    /// @brief Return a pointer to the first element in the slice.
    constexpr
    const T *data() const noexcept {
        return _data;
    }


    /// @brief Return a pointer to the first element in the slice.
    constexpr
    T *data() noexcept {
        return _data;
    }


    /// @brief Return the number of elements in the slice.
    constexpr
    u32 size() const noexcept {
        return _size;
    }


    /// @brief Return true if the slice is empty.
    constexpr
    bool is_empty() const noexcept {
        return _size == 0;
    }


    /// @brief Shift the slice to the left by the given number of elements.
    /// @param offset The number of elements by which to shift the slice
    constexpr
    Slice<const T> shift_left(u32 offset) noexcept {
        _data -= offset;
        return *this;
    }


    /// @brief Shift the slice to the right by the given number of elements.
    /// @param offset The number of elements by which to shift the slice
    constexpr
    Slice<const T> shift_right(u32 offset) noexcept {
        _data += offset;
        return *this;
    }


    /// @brief Return a reference to the elements from the given start index through the given end
    /// index.
    /// @param start The index of the first element
    /// @param end The index after the last element
    constexpr
    Slice<const T> slice(u32 start, u32 end) const noexcept {
        return Slice<const T>(_data + start, end - start);
    }


    /// @brief Return a reference to the elements from the given start index through the given end
    /// index.
    /// @param start The index of the first element
    /// @param end The index after the last element
    constexpr
    Slice<T> slice(u32 start, u32 end) noexcept {
        return Slice<T>(_data + start, end - start);
    }


    /// @brief Return a reference to the elements from the given start index through the given end
    /// index.
    /// @param start The index of the first element
    constexpr
    Slice<const T> slice(u32 start) const noexcept {
        return Slice<const T>(_data + start, _size - start);
    }


    /// @brief Return a reference to the elements from the given start index through the given end
    /// index.
    /// @param start The index of the first element
    constexpr
    Slice<T> slice(u32 start) noexcept {
        return Slice<T>(_data + start, _size - start);
    }


    /// @brief Return a reference to the elements from the given start index through the end of the
    /// slice.
    /// @param start The index of the first element
    constexpr
    Slice<const T> head(u32 end) const noexcept {
        return slice(0, end);
    }


    /// @brief Return a reference to the elements from the given start index through the end of the
    /// slice.
    /// @param start The index of the first element
    constexpr
    Slice<T> head(u32 end) noexcept {
        return slice(0, end);
    }


    /// @brief Return a reference to the elements from the given start index through the end of the
    /// slice.
    /// @param start The index of the first element
    constexpr
    Slice<const T> tail(u32 start) const noexcept {
        return slice(start, _size);
    }


    /// @brief Return a reference to the elements from the given start index through the end of the
    /// slice.
    /// @param start The index of the first element
    constexpr
    Slice<T> tail(u32 start) noexcept {
        return slice(start, _size);
    }


    ///
    /// Comparison Methods
    ///


    /// @brief Return the lexicographical order between the slice and the given sequence of values.
    /// @param sequence The sequence of values with which to compare
    /// @return Less than zero if the slice is ordered before the given sequence; Greater than zero
    /// if the slice is ordered after the given sequence; Zero if they are equal
    constexpr
    i32 compare(Slice<const T> sequence) const noexcept {
        for (u32 i = 0; i < std::min(_size, sequence._size); ++i) {
            if (_data[i] < sequence[i]) {
                return -1;
            }

            if (sequence[i] < _data[i]) {
                return 1;
            }
        }

        return _size - sequence._size;
    }


    /// @brief Return the lexicographical order between the slice and the given sequence of values.
    /// @param sequence The sequence of values with which to compare
    /// @param size The size of the sequence
    /// @return Less than zero if the slice is ordered before the given sequence; Greater than zero
    /// if the slice is ordered after the given sequence; Zero if they are equal
    constexpr
    i32 compare(const T *sequence, u32 size) const noexcept {
        return compare(Slice<const T>(sequence, size));
    }


    /// @brief Return true if the slice is equal to the given sequence of values.
    /// @param sequence The sequence of values with which to compare
    constexpr
    bool is_equal(Slice<const T> sequence) const noexcept {
        if (_size != sequence._size) {
            return false;
        }

        for (u32 i = 0; i < _size; ++i) {
            if (_data[i] != sequence[i]) {
                return false;
            }
        }

        return true;
    }


    /// @brief Return true if the slice is equal to the given sequence of values.
    /// @param sequence The sequence of values with which to compare
    /// @param size The size of the sequence
    constexpr
    bool is_equal(const T *sequence, u32 size) const noexcept {
        return is_equal(Slice<const T>(sequence, size));
    }


    /// @brief Return true if the slice starts with the given value.
    /// @param value The value with which to compare
    constexpr
    bool starts_with(const T &value) const noexcept {
        return !is_empty() && *_data == value;
    }


    /// @brief Return true if the slice starts with the given sequence of values.
    /// @param sequence The sequence of values with which to compare
    constexpr
    bool starts_with(Slice<const T> sequence) const noexcept {
        return !sequence.is_empty() && sequence._size <= _size && slice(0, sequence._size) == sequence;
    }


    /// @brief Return true if the slice starts with the given sequence of values.
    /// @param sequence The sequence of values with which to compare
    /// @param size The size of the sequence
    constexpr
    bool starts_with(const T *sequence, u32 size) const noexcept {
        return starts_with(Slice<const T>(sequence, size));
    }


    /// @brief Return true if the slice ends with the given value.
    /// @param value The value with which to compare
    constexpr
    bool ends_with(const T &value) const noexcept {
        return !is_empty() && _data[_size - 1] == value;
    }


    /// @brief Return true if the slice ends with the given sequence of values.
    /// @param sequence The sequence of values with which to compare
    constexpr
    bool ends_with(Slice<const T> sequence) const noexcept {
        return !sequence.is_empty() && sequence._size <= _size && slice(_size - sequence._size) == sequence;
    }


    /// @brief Return true if the slice ends with the given sequence of values.
    /// @param sequence The sequence of values with which to compare
    /// @param size The size of the sequence
    constexpr
    bool ends_with(const T *sequence, u32 size) const noexcept {
        return ends_with(Slice<const T>(sequence, size));
    }


    /// @brief Return true if the slice contains the given value.
    /// @param values The value for which to search
    constexpr
    bool contains(const T &value) const noexcept {
        return index_of_first(value).has_value();
    }


    /// @brief Return true if the slice contains the given sequence of values.
    /// @param sequence The sequence of values for which to search
    constexpr
    bool contains(Slice<const T> sequence) const noexcept {
        return index_of_first(sequence).has_value();
    }


    /// @brief Return true if the slice contains the given sequence of values.
    /// @param sequence The sequence of values for which to search
    /// @param size The size of the sequence
    constexpr
    bool contains(const T *sequence, u32 size) const noexcept {
        return contains(Slice<const T>(sequence, size));
    }


    /// @brief Return true if the slice contains an element which satisfies the given predicate.
    /// @param is_equal The predicate with which to compare
    constexpr
    bool contains(Function<bool(const T &)> is_equal) const noexcept {
        return index_of_first(is_equal).has_value();
    }


    /// @brief Return true if the slice contains any of the given values.
    /// @param set The set of values for which to search
    constexpr
    bool contains_any_of(Slice<const T> set) const noexcept {
        return index_of_first_of(set).has_value();
    }


    /// @brief Return true if the slice contains any of the given values.
    /// @param set The set of values for which to search
    /// @param size The size of the set of values
    constexpr
    bool contains_any_of(const T *set, u32 size) const noexcept {
        return contains_any_of(Slice<const T>(set, size));
    }


    ///
    /// Counting Methods
    ///


    /// @brief Return the number of elements in the slice which match the given value.
    /// @param value The value for which to search
    constexpr
    u32 count(const T &value) const noexcept {
        u32 count = 0;

        for (u32 index = 0; index < _size; ++index) {
            if (_data[index] == value) {
                count += 1;
            }
        }

        return count;
    }


    /// @brief Return the number of non-overlapping occurrences of the given sequence of values
    /// contained in the slice.
    /// @param sequence The sequence of values for which to search
    constexpr
    u32 count(Slice<const T> sequence) const noexcept {
        if (sequence.is_empty() || sequence._size > _size) {
            return 0;
        }

        u32 count = 0;

        for (u32 index = 0; index < _size - sequence._size;) {
            if (sequence.is_equal(&_data[index], sequence._size)) {
                index += sequence._size;
                count += 1;
            } else {
                index += 1;
            }
        }

        return count;
    }


    /// @brief Return the number of non-overlapping occurrences of the given sequence of values in
    /// the slice.
    /// @param sequence The sequence of values for which to search
    /// @param size The size of the sequence
    constexpr
    u32 count(const T *sequence, u32 size) const noexcept {
        return count(Slice<const T>(sequence, size));
    }


    /// @brief Return the number of elements which satisfy the given predicate.
    /// @param is_equal The predicate with which to compare
    constexpr
    u32 count(Function<bool(const T &)> is_equal) const noexcept {
        u32 count = 0;

        for (const T &value : *this) {
            if (is_equal(value)) {
                count += 1;
            }
        }

        return count;
    }


    /// @brief Return the number of occurrences of any of the given set of values contained in this
    /// slice.
    /// @param set The set of values for which to search
    constexpr
    u32 count_all_of(Slice<const T> set) const noexcept {
        u32 count = 0;

        for (const T &value : *this) {
            if (set.contains(value)) {
                count += 1;
            }
        }

        return count;
    }


    /// @brief Return the number of occurrences of any of the given set of values contained in this
    /// slice.
    /// @param set The set of values for which to search
    /// @param size The size of the set
    constexpr
    u32 count_all_of(const T *set, u32 size) const noexcept {
        return count_all_of(Slice<const T>(set, size));
    }


    ///
    /// Index Of
    ///


    /// @brief Return a pointer to the first element in the slice which matches the given value or
    /// nullptr if none were found.
    /// @param values The value for which to search
    constexpr
    Result<u32> index_of_first(const T &value) const noexcept {
        for (u32 index = 0; index < _size; ++index) {
            if (_data[index] == value) {
                return index;
            }
        }

        return Error::FAILURE;
    }


    /// @brief Return a slice of the first sequence in the slice which matches the given sequence
    /// or an empty slice if none were found.
    /// @param sequence The sequence of values for which to search
    constexpr
    Result<u32> index_of_first(Slice<const T> sequence) const noexcept {
        if (sequence.is_empty() || sequence._size > _size) {
            return Error::FAILURE;
        }

        for (
            Slice<const T> seq(_data, sequence._size);
            seq._data < &_data[_size - sequence._size];
            seq >>= 1
        ) {
            if (seq == sequence) {
                return u32(seq.data() - sequence.data());
            }
        }

        return Error::FAILURE;
    }


    /// @brief Return a slice of the first sequence in the slice which matches the given sequence
    /// or an empty slice if none were found.
    /// @param sequence The sequence of values for which to search
    /// @param size The size of the sequence
    constexpr
    Result<u32> index_of_first(const T *sequence, u32 size) const noexcept {
        return index_of_first(Slice<const T>(sequence, size));
    }


    /// @brief Return a pointer to the first element in the slice which satisfies the given
    /// predicate or nullptr if none were found.
    /// @param is_equal The predicate with which to compare
    constexpr
    Result<u32> index_of_first(Function<bool(const T &)> is_equal) const noexcept {
        for (u32 index = 0; index < _size; ++index) {
            if (is_equal(_data[index])) {
                return index;
            }
        }

        return Error::FAILURE;
    }


    /// @brief Return a pointer to the first element in the slice which satisfies the given
    /// predicate or nullptr if none were found.
    /// @param is_equal The predicate with which to compare
    constexpr
    Result<u32> index_of_first(Function<bool(const T &)> is_equal) noexcept {
        for (u32 index = 0; index < _size; ++index) {
            if (is_equal(_data[index])) {
                return index;
            }
        }

        return Error::FAILURE;
    }


    /// @brief Return a pointer to the first element in the slice which matches any of the given
    /// set of values.
    /// @param set The set of values for which to search
    constexpr
    Result<u32> index_of_first_of(Slice<const T> set) const noexcept {
        for (u32 index = 0; index < _size; ++index) {
            if (set.contains(_data[index])) {
                return index;
            }
        }

        return Error::FAILURE;
    }


    /// @brief Return a pointer to the first element in the slice which matches any of the given
    /// set of values.
    /// @param set The set of values for which to search
    /// @param size The size of the set
    constexpr
    Result<u32> index_of_first_of(const T *set, u32 size) const noexcept {
        return index_of_first_of(set, size);
    }


    ///
    /// Reverse Searching Methods
    ///


    constexpr
    Result<u32> index_of_last(const T &value) const noexcept {
        for (u32 index = _size; index-- > 0;) {
            if (_data[index] == value) {
                return index;
            }
        }

        return Error::FAILURE;
    }


    /// @brief Return the number of occurrences of elements which are not contained in the given
    /// set of values.
    /// @param set The set of values of which to exclude
    constexpr
    Result<u32> index_of_last(Function<bool(const T &)> is_equal) const noexcept {
        for (u32 index = _size; index-- > 0;) {
            if (is_equal(_data[index])) {
                return index;
            }
        }

        return Error::FAILURE;
    }


    constexpr
    Result<u32> index_of_last(Slice<const T> sequence) const noexcept {
        if (sequence.is_empty() || sequence._size > _size) {
            return 0;
        }

        for (
            Slice<const T> seq(&_data[_size - sequence._size - 1], sequence._size);
            seq._data >= _data;
            seq <<= 1
        ) {
            if (seq == sequence) {
                return u32(seq.data() - sequence.data());
            }
        }

        return Error::FAILURE;
    }


    constexpr
    Result<u32> index_of_last(const T *sequence, u32 size) const noexcept {
        return index_of_last(Slice<const T>(sequence, size));
    }


    constexpr
    Result<u32> index_of_last_of(Slice<const T> set) const noexcept {
        for (u32 index = _size; index-- > 0;) {
            if (set.contains(&_data[index])) {
                return index;
            }
        }

        return Error::FAILURE;
    }


    constexpr
    Result<u32> index_of_last_of(const u8 *set, u32 size) const noexcept {
        return index_of_last_of(set, size);
    }


    ///
    /// Searching Methods
    ///


    /// @brief Return a pointer to the first element in the slice which matches the given value or
    /// nullptr if none were found.
    /// @param values The value for which to search
    constexpr
    const T *find_first(const T &value) const noexcept {
        Result<u32> index = index_of_first(value);
        return index.has_value() ? &_data[index.value()] : nullptr;
    }


    /// @brief Return a slice of the first sequence in the slice which matches the given sequence
    /// or an empty slice if none were found.
    /// @param sequence The sequence of values for which to search
    constexpr
    Slice<const T> find_first(Slice<const T> sequence) const noexcept {
        if (sequence.is_empty() || sequence._size > _size) {
            return 0;
        }

        for (
            Slice<const T> seq(_data, sequence._size);
            seq._data < &_data[_size - sequence._size];
            seq >>= 1
        ) {
            if (seq == sequence) {
                return seq;
            }
        }

        return nullptr;
    }


    /// @brief Return a slice of the first sequence in the slice which matches the given sequence
    /// or an empty slice if none were found.
    /// @param sequence The sequence of values for which to search
    /// @param size The size of the sequence
    constexpr
    Slice<const T> find_first(const T *sequence, u32 size) const noexcept {
        return find_first(Slice<const T>(sequence, size));
    }


    /// @brief Return a pointer to the first element in the slice which satisfies the given
    /// predicate or nullptr if none were found.
    /// @param is_equal The predicate with which to compare
    constexpr
    const T *find_first(Function<bool(const T &)> is_equal) const noexcept {
        Result<u32> index = index_of_first(is_equal);
        return index.has_value() ? &_data[index.value()] : nullptr;
    }


    /// @brief Return a pointer to the first element in the slice which satisfies the given
    /// predicate or nullptr if none were found.
    /// @param is_equal The predicate with which to compare
    constexpr
    T *find_first(Function<bool(const T &)> is_equal) noexcept {
        Result<u32> index = index_of_first(is_equal);
        return index.has_value() ? &_data[index.value()] : nullptr;
    }


    /// @brief Return a pointer to the first element in the slice which matches any of the given
    /// set of values.
    /// @param set The set of values for which to search
    constexpr
    const T *find_first_of(Slice<const T> set) const noexcept {
        Result<u32> index = index_of_first_of(set);
        return index.has_value() ? &_data[index.value()] : nullptr;
    }


    /// @brief Return a pointer to the first element in the slice which matches any of the given
    /// set of values.
    /// @param set The set of values for which to search
    /// @param size The size of the set
    constexpr
    const T *find_first_of(const T *set, u32 size) const noexcept {
        return find_first_of(set, size);
    }


    ///
    /// Reverse Searching Methods
    ///


    constexpr
    const T *find_last(const T &value) const noexcept {
        Result<u32> index = index_of_last(value);
        return index.has_value() ? &_data[index.value()] : nullptr;
    }


    /// @brief Return the number of occurrences of elements which are not contained in the given
    /// set of values.
    /// @param set The set of values of which to exclude
    constexpr
    const T *find_last(Function<bool(const T &)> is_equal) const noexcept {
        Result<u32> index = index_of_last(is_equal);
        return index.has_value() ? &_data[index.value()] : nullptr;
    }


    constexpr
    Slice<const T> find_last(Slice<const T> sequence) const noexcept {
        if (sequence.is_empty() || sequence._size > _size) {
            return 0;
        }

        for (
            Slice<const T> seq(&_data[_size - sequence._size - 1], sequence._size);
            seq._data >= _data;
            seq <<= 1
        ) {
            if (seq == sequence) {
                return seq;
            }
        }

        return nullptr;
    }


    constexpr
    Slice<const T> find_last(const T *sequence, u32 size) const noexcept {
        return find_last(Slice<const T>(sequence, size));
    }


    constexpr
    const T *find_last_of(Slice<const T> set) const noexcept {
        Result<u32> index = index_of_last_of(set);
        return index.has_value() ? &_data[index.value()] : nullptr;
    }


    /// @brief 
    /// @param set The set of values
    constexpr
    const T *find_last_of(const u8 *set, u32 size) const noexcept {
        return find_last_of(Slice<const T>(set, size));
    }


    ///
    /// Iterator
    ///


    /// @brief Return an iterator to the beginning of the slice.
    constexpr
    const T *begin() const noexcept {
        return _data;
    }


    /// @brief Return an iterator to the beginning of the slice.
    constexpr
    T *begin() noexcept {
        return _data;
    }


    /// @brief Return an iterator to the end of the slice.
    constexpr
    const T *end() const noexcept {
        return &_data[_size];
    }


    /// @brief Return an iterator to the end of the slice.
    constexpr
    T *end() noexcept {
        return &_data[_size];
    }
};


///
/// Operators
///


/// @brief Return true if the contents of the slices are equal.
template<class T>
constexpr
bool operator==(Slice<const T> lhs, Slice<const T> rhs) noexcept {
    return lhs.is_equal(rhs);
}


/// @brief Return true if the contents of the slices are not equal.
template<class T>
constexpr
bool operator!=(Slice<const T> lhs, Slice<const T> rhs) noexcept {
    return !lhs.is_equal(rhs);
}


/// @brief Return true if the contents of lhs are lexigraphically less than the contents of rhs.
template<class T>
constexpr
bool operator<(Slice<const T> lhs, Slice<const T> rhs) noexcept {
    return lhs.compare(rhs) < 0;
}


/// @brief Return true if the contents of lhs are lexigraphically less than or equal to the
/// contents of rhs.
template<class T>
constexpr
bool operator<=(Slice<const T> lhs, Slice<const T> rhs) noexcept {
    return lhs.compare(rhs) <= 0;
}


/// @brief Return true if the contents of lhs are lexigraphically greater than the contents of rhs.
template<class T>
constexpr
bool operator>(Slice<const T> lhs, Slice<const T> rhs) noexcept {
    return lhs.compare(rhs) > 0;
}


/// @brief Return true if the contents of lhs are lexigraphically greater than or equal to the
/// contents of rhs.
template<class T>
constexpr
bool operator>=(Slice<const T> lhs, Slice<const T> rhs) noexcept {
    return lhs.compare(rhs) >= 0;
}


/// @brief Increment the data pointer and decrement the size of the given slice by the given amount.
/// @param size The amount by which to increment
template<class T>
constexpr
Slice<T> operator+(Slice<T> slice, u32 offset) noexcept {
    slice += offset;
    return slice;
}


/// @brief Decrement the data pointer and increment the size of the given slice by the given amount.
/// @param size The amount by which to decrement
template<class T>
constexpr
Slice<T> operator-(Slice<T> slice, u32 offset) noexcept {
    slice -= offset;
    return slice;
}


/// @brief Shift the data of the given slice to the right by the given amount.
/// @param size The amount by which to shift
template<class T>
constexpr
Slice<T> operator>>(Slice<T> slice, u32 offset) noexcept {
    slice >>= offset;
    return slice;
}


/// @brief Shift the data of the given slice to the left by the given amount.
/// @param size The amount by which to shift
template<class T>
constexpr
Slice<T> operator<<(Slice<T> slice, u32 offset) noexcept {
    slice <<= offset;
    return slice;
}
