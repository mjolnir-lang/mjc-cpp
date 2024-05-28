#pragma once

#include <std/Slice.hpp>


namespace Object {


    template<class T, class... Args>
    constexpr
    void construct(T *ptr, Args &&... args) noexcept {
        new (ptr) (std::forward<Args>(args)...);
    }


    template<class T>
    constexpr
    void destroy(T *ptr) noexcept {
        if constexpr (std::is_array_v<T>) {
            for (T &p : *ptr) {
                destroy(&p);
            }
        } else {
            ptr->~T(); 
        }
    }


    template<class T>
    constexpr
    void move(T &dst, T &src) noexcept {
        std::move(dst, src);
    }


    template<class T>
    constexpr
    void move(T *dst, Slice<T> &src) noexcept {
        std::move(dst, src);
    }


    template<class T>
    constexpr
    void copy(T &dst, const T &src) noexcept {
        std::move(dst, src);
    }


    template<class T>
    constexpr
    void copy(T *dst, Slice<const T> &src) noexcept {
        std::move(dst, src);
    }


    template<class T>
    constexpr
    void swap(T &a, T &b) noexcept {
        T tmp(a);
        a = Object::move(b);
        b = Object::move(tmp);
    }


    template<class T>
    constexpr
    void swap(Slice<T> a, Slice<T> b) noexcept {
        for (u32 i = 0; i < a.size(); ++i) {
            swap(a[i], b[i]);
        }
    }


    template<class T, class... Args>
    constexpr
    void fill(Slice<T> &data, Args &&... args) noexcept {
        for (T &ptr : data) {
            new (&ptr) (std::forward<Args>(args)...);
        }
    }
}
