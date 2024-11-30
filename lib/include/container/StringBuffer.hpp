#pragma once

#include <core/String.hpp>


class StringBuffer {
public:


    class Iterator {
    public:
        StringBuffer &_buffer;
        u32 _count = 0;
        u32 _ptr;


        constexpr
        Iterator(
            StringBuffer &buffer
        ) noexcept :
            _buffer(buffer),
            _ptr(buffer._front)
        {}


        bool has_next() const noexcept {
            return _count < _buffer._size;
        }


        /// @brief Return the next string from the buffer iterator.
        /// @param string The string to return
        /// @param length The length of the string
        /// @return true if the iterator had a string to return
        StringView next() noexcept {
            const u8 *data = &_buffer._data[_ptr + 1];
            u32 size = _buffer._data[_ptr];
            _ptr += size + 2;

            if (_buffer._data[_ptr] == 0) {
                _ptr = 0;
            }

            _count += 1;
            return StringView(data, size);
        }
    };


private:
    u8 *_data;
    u32 _capacity;
    u32 _size = 0; // The number of strings in the buffer.
    u32 _front = 0;
    u32 _back = 0;
    u32 _space_used = 0;
public:


    ///
    /// Constructors
    ///


    /// @brief Create a buffer.
    /// @param data The character buffer backend
    /// @param capacity The size of the backend buffer
    constexpr
    StringBuffer(u32 capacity) noexcept : _data(new u8[capacity]), _capacity(capacity) {}


    ///
    /// Destructor
    ///


    ~StringBuffer() {
        delete[] _data;
    }


    ///
    /// Properties
    ///


    /// @brief Return true if the buffer is empty.
    /// @return true if the buffer is empty
    bool is_empty() const noexcept {
        return _size == 0;
    }


    /// @brief Return the number of strings in the buffer.
    /// @return The number of strings in the buffer.
    u32 capacity() const noexcept {
        return _capacity;
    }


    /// @brief Return the number of strings in the buffer.
    /// @return The number of strings in the buffer.
    u32 used() const noexcept {
        return _space_used;
    }


    /// @brief Return the number of strings in the buffer.
    /// @return The number of strings in the buffer.
    u32 free() const noexcept {
        return _capacity - _space_used;
    }


    /// @brief Return the number of strings in the buffer.
    /// @return The number of strings in the buffer.
    u32 size() const noexcept {
        return _size;
    }


    ///
    /// Methods
    ///


    /// @brief Clear the buffer.
    void clear() {
        _size = 0;
        _front = 0;
        _back = 0;
    }


    /// @brief Push a string onto the buffer.
    /// @param string The string to push
    void push(StringView string) noexcept;


    /// @brief Push a string onto the buffer.
    /// @param string The string to push
    /// @param size The length of the string
    void push(const u8 *string, u32 size) noexcept {
        push(StringView(string, size));
    }


    /// @brief Return a pointer to the next string.
    /// @return The string pointer
    StringView peek() const noexcept {
        return StringView(&_data[_front + 1], _data[_front]);
    }


    /// @brief Pop a null terminated string off of the buffer.
    void pop() noexcept;


    Iterator iter() noexcept {
        return Iterator(*this);
    }
};
