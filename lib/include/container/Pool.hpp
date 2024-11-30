#pragma once

#include <system/Memory.hpp>


template<class T>
class Pool {
private:

public:


    template<class... Args>
    T &insert(Args &&... args) {
        return new T(std::forward<Args>(args)...);
    }


    void remove(T &object) {
        delete object;
    }
};
