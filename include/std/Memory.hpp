#pragma once

#include <std/Common.hpp>


class Memory {
public:


    template<class T>
    static
    void allocate(T *&ptr, u32 size) {
        ptr = new T[size]();
    }


    template<class T>
    static
    void deallocate(T *&ptr) {
        delete[] ptr;
    }


    static
    void move(void *dst, const void *src, u32 size) noexcept {
        std::memmove(dst, src, size);
    }


    static
    void copy(void *dst, const void *src, u32 size) noexcept {
        std::memcpy(dst, src, size);
    }


    static
    void swap(void *a, const void *b, u32 size) noexcept {
        std::swap(a, b, size);
    }
};
