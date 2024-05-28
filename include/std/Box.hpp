#pragma once

#include <std/Memory.hpp>
#include <std/Object.hpp>


template<class T>
class Box {
private:
    T *_ptr;
public:


    ///
    /// Constructors
    ///


    constexpr
    Box() noexcept : _ptr(nullptr) {}


    constexpr
    Box(std::nullptr_t) noexcept : _ptr(nullptr) {}


    template<class... Args>
    constexpr
    Box(Args &&... args) noexcept : _ptr(Memory::allocate(sizeof(T))) {
        Object::construct(_ptr, std::forward<Args>(args)...));
    }


    constexpr
    Box(Box<T> &&other) noexcept : _ptr(other._ptr) {
        other._ptr = nullptr;
    }


    Box(const Box<T> &other) = delete;


    ///
    /// Constructors
    ///


    ~Box() {
        if (_ptr == nullptr) {
            return;
        }

        Object::destroy(_ptr);
        Memory::free(_ptr);
    }


    ///
    /// Type Casts
    ///


    constexpr
    operator const T *() const noexcept {
        return _ptr;
    }


    constexpr
    operator T *() noexcept {
        return _ptr;
    }


    ///
    /// Operators
    ///


    constexpr
    Box<T> &operator=(Box<T> &&other) noexcept {
        Object::swap(_ptr, other._ptr);
    }


    Box<T> &operator=(const Box<T> &other) = delete;


    ///
    /// Properties
    ///


    constexpr
    const T *data() const noexcept {
        return _ptr;
    }


    constexpr
    T *data() noexcept {
        return _ptr;
    }


    ///
    /// Methods
    ///


};

