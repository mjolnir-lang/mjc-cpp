#pragma once

#include <core/Box.hpp>


template<class T, size_t BLOCK_SIZE = 64>
class Stack {
private:
    struct Block {
        T data[BLOCK_SIZE];
        Box<Block> next = nullptr;
        Box<Block> last;


        constexpr
        Block(Box<Block> &last) noexcept : last(last) {}
    };

    static constexpr u32 INDEX() noexcept { return (_size - 1) & (BLOCK_SIZE - 1); }


    Box<Block> _block;
    u32 _capacity = 0;
    u32 _size = 0;
public:


    ///
    /// Constructors
    ///


    constexpr
    Stack() noexcept {}


    Stack(u32 capacity) noexcept {
        reserve(capacity);
    }


    Stack(Slice<const T> data) noexcept {
        push(data);
    }


    Stack(const T *data, u32 size) noexcept {
        push(data, size);
    }


    /// @brief Create an array from an initializer list.
    /// @param data The initializer list
    Stack(std::initializer_list<T> data) noexcept {
        push(data);
    }


    ///
    /// Properties
    ///


    /// @brief Return a reference to the element at the top of the stack.
    constexpr
    const T &top() const noexcept {
        return _block[INDEX()];
    }


    /// @brief Return a reference to the element at the top of the stack.
    constexpr
    T &top() noexcept {
        return _block[INDEX()];
    }


    /// @brief Return the total number of elements the stack can store before the it must be grown.
    constexpr
    u32 capacity() const noexcept {
        return _capacity;
    }


    /// @brief Return the number of elements stored in the stack.
    constexpr
    u32 size() const noexcept {
        return _size;
    }


    /// @brief Return the number of elements which can be stored before the stack must be grown.
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
    /// Methods
    ///


    /// @brief Swap the underlying elements of two stacks.
    /// @param other The other stack
    constexpr
    void swap(Stack<T> &other) noexcept {
        std::swap(this->_block, other._block);
        std::swap(this->_capacity, other._capacity);
        std::swap(this->_size, other._size);
    }


    /// @brief Adjust the capacity of the vector.
    ///
    /// If the capacity is increased and the underlying storage is reallocated, all references to
    /// the elements in the vector data will be invalidated.
    /// @param size The requested allocated capacity
    void reserve(u32 size) noexcept {
    }


    /// @brief Reduce the allocated capacity to the vector size.
    void trim() noexcept {
        _data.trim(_size);
    }


    ///
    /// Element Insertion Methods
    ///


    void push(Slice<const T> values) noexcept {
        for (const T &value : values) {
            u32 index = INDEX();

            if (index == BLOCK_SIZE) {
                if (_block->next == nullptr) {
                    _block->next = Box<Block>(_block);
                    _block = _block->next;
                }
            }

            _block[index] = value;
            _size += 1;
        }
    }


    void push(const T *values, u32 size) noexcept {
        push(Slice<const T>(values, size));
    }


    /// @brief Push the given value onto the top of stack.
    /// @param value The value to push.
    /// @return The error code
    /// @note Fails if memory cannot be allocated.
    void push(const T &value) noexcept {
        push(&value, 1);
    }


    void push(T &&value) {
        u32 index = INDEX();

        if (index == BLOCK_SIZE) {
            if (_block->next == nullptr) {
                _block->next = Box<Block>(_block);
                _block = _block->next;
            }
        }

        _block[index] = value;
        _size += 1;
    }


    template<class... Args>
    void push_new(Args &&... args) noexcept {
        u32 index = INDEX();

        if (index == BLOCK_SIZE) {
            if (_block->next == nullptr) {
                _block->next = Box<Block>(_block);
                _block = _block->next;
            }
        }

        new(_block[index]) T(std::forward<Args>(args)...);
        _size += 1;
    }


    /// @brief Push a value onto the stack a given number of times.
    /// @param value The value to push
    /// @param count The number of copies to push
    void fill(const T &value, u32 count) noexcept {
        for (u32 i = 0; i < count; ++i) {
            u32 index = INDEX();

            if (index == BLOCK_SIZE) {
                if (_block->next == nullptr) {
                    _block->next = Box<Block>(_block);
                    _block = _block->next;
                }
            }

            _block[index] = value;
            _size += 1;
        }
    }


    ///
    /// Element Removal Methods
    ///


    /// @brief Clear the stack.
    void clear() noexcept {
        pop(size_);
    }


    /// @brief Pop multiple elements off the top of the stack.
    /// @param values The location to store the values
    /// @return The number of elements popped
    u32 pop(Slice<T> values) noexcept {
        for (T &value : values) {
            if (is_empty()) {
                return n;
            }

            u32 index = INDEX();
            value = std::move(_block[index]);
            _block[index].~T();
            _size -= 1;

            if (index == 0 && _size > 0) {
                _block = _block->last;
            }
        }

        return n;
    }


    /// @brief Pop multiple elements off the top of the stack.
    /// @param values The location to store the values
    /// @param size The number of elements to pop
    /// @return The number of elements popped
    u32 pop(T *values, u32 size) noexcept {
        return pop(Slice<const T>(values, size));
    }


    /// @brief Pop the top element off of the stack.
    /// @param value The location to store the value
    /// @return The number of elements popped
    u32 pop(T &value) noexcept {
        return pop(&value, 1);
    }


    /// @brief Pop multiple elements off the top of the stack without storing their values.
    /// @param size The number of elements to pop (default: 1)
    void pop(u32 size = 1) noexcept {
        if (size > _size) {
            size = _size;
        }

        for (; size; --size) {
            u32 index = INDEX();
            Memory::destroy(_block[index]);
            _size -= 1;

            if (index == 0 && _size > 0) {
                _block = _block->last;
            }
        }
    }
};
