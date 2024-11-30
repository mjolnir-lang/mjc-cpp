#pragma once

#include <system/Memory.hpp>
#include <core/Object.hpp>


/// @brief A unique pointer. A single memory allocation.
/// @tparam T 
template<class T>
class Box {
private:
    T *_data;
public:


    ///
    /// Constructors
    ///


    constexpr
    Box() noexcept : _data(nullptr) {}


    constexpr
    Box(std::nullptr_t) noexcept : _data(nullptr) {}


    /// @brief Move constructor.
    constexpr
    Box(Box<T> &&other) noexcept : _data(other._data) {
        other._data = nullptr;
    }


    /// @brief Copy constructor.
    Box(const Box<T> &other) = delete;


    constexpr
    Box(std::nullptr_t) noexcept : _data(nullptr) {}


    template<class... Args>
    Box(Args &&... args) noexcept {
        _data = static_cast<T *>(Memory::allocate(sizeof(T)));
        Object::construct(_data, std::forward<Args>(args)...);
    }


    ///
    /// Destructor
    ///


    ~Box() {
        Object::destroy(*_data);
        Memory::deallocate(_data);
    }


    ///
    /// Type Casts
    ///


    /// @brief Return a reference to the underlying element.
    constexpr
    operator const T *() const noexcept {
        return _data;
    }


    /// @brief Return a reference to the underlying element.
    constexpr
    operator T *() noexcept {
        return _data;
    }


    ///
    /// Operators
    ///


    /// @brief Move assignment.
    constexpr
    void operator=(Box<T> &&other) noexcept {
        if (_data == other._data) {
            return;
        }

        swap(other);
    }


    /// @brief Copy assignment.
    Box<T> &operator=(const Box<T> &other) = delete;


    /// @brief Return a reference to the underlying element.
    constexpr
    const T &operator*() const noexcept {
        return *_data;
    }


    /// @brief Return a reference to the underlying element.
    constexpr
    T &operator*() noexcept {
        return *_data;
    }


    /// @brief Return a reference to the underlying element.
    constexpr
    const T *operator->() const noexcept {
        return _data;
    }


    /// @brief Return a reference to the underlying element.
    constexpr
    T *operator->() noexcept {
        return _data;
    }


    ///
    /// Properties
    ///


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
    const T *data() const noexcept {
        return _data;
    }


    constexpr
    void swap(Box<T> &other) noexcept {
        Object::swap(_data, other._data);
    }
};
