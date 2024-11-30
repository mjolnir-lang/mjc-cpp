#pragma once

#include <core/Common.hpp>


namespace Memory {


    template<class T>
    inline
    constexpr
    T *allocate(u32 size) {
        return new T[size]();
    }


    template<class T>
    inline
    constexpr
    void allocate(T *&ptr, u32 size) {
        ptr = Memory::allocate<T>(size);
    }


    template<class T>
    inline
    constexpr
    void deallocate(T *&ptr) {
        delete[] ptr;
    }


    template<class T>
    inline
    constexpr
    void trim(T *&ptr) {
    }


    template<class T>
    inline
    constexpr
    void resize(T *&ptr, u32 size) {
        ptr = Memory::allocate<T>(size);
    }


    template<class T>
    inline
    constexpr
    void reallocate(T *&ptr, u32 size) {
        ptr = Memory::allocate<T>(size);
    }
};
