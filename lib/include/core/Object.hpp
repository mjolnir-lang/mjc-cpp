#pragma once

#include <core/Slice.hpp>

#include <algorithm>


namespace Object {


    ///
    /// Cast
    ///


    template<class T, class U>
    constexpr
    T &&bit_cast(T &&object, U &&) noexcept {
        std::bit_cast(object);
    }


    ///
    /// In-place Construct/Destroy
    ///


    template<class T, class... Args>
    constexpr
    void construct(T *ptr, Args &&... args) noexcept {
        new (static_cast<void *>(ptr)) T(std::forward<Args>(args)...);
    }


    template<class T>
    constexpr
    void destroy(T &object) noexcept {
        object.~T();
    }


    template<class T, u32 SIZE>
    constexpr
    void destroy(T (&array)[SIZE]) noexcept {
        for (T &object : array) {
            Object::destroy(object);
        }
    }


    ///
    /// Move
    ///


    template<class T>
    constexpr
    Type::remove_reference<T> &&move(T &&object) noexcept {
        return std::move(object);
    }


    template<class T>
    constexpr
    void move(T *dst, Slice<const T> values) noexcept {
        for (u32 i = 0; i < values.size(); ++i) {
            dst[i] = Object::move(values[i]);
        }
    }


    template<class T>
    constexpr
    void move(T *dst, const T *values, u32 size) noexcept {
        Object::move(dst, Slice<const T>(values, size));
    }


    ///
    /// Copy
    ///


    template<class T>
    constexpr
    void copy(T *dst, Slice<const T> values) noexcept {
        std::copy(values.data(), &values[values.size()], dst);
    }


    template<class T>
    constexpr
    void copy(T *dst, const T *values, u32 size) noexcept {
        Object::copy(dst, Slice<const T>(values, size));
    }


    ///
    /// Swap
    ///


    template<class T>
    constexpr
    void swap(T &a, T &b) noexcept {
        std::swap(a, b);
        T tmp(Object::move(a));
        a = Object::move(b);
        b = Object::move(tmp);
    }


    template<class T, u32 SIZE>
    constexpr
    void swap(T (&a)[SIZE], T (&b)[SIZE]) noexcept {
        Object::swap<Slice<T>>(a, b);
    }


    ///
    /// Fill
    ///


    template<class T, class... Args>
    constexpr
    void fill(Slice<T> &data, Args &&... args) noexcept {
        for (T &ptr : data) {
            Object::construct(&ptr, Type::forward<Args>(args)...);
        }
    }
}
