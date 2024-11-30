#pragma once

#include <core/Common.hpp>


/// @brief An assignable reference type wrapper.
/// @tparam T The underlying type
template<class T>
class Ref {
private:
    T *_ptr;
public:


    ///
    /// Constructors
    ///


    constexpr
    Ref(T &value) noexcept : _ptr(&value) {}


    ///
    /// Type Casts
    ///


    constexpr
    operator const T &() const noexcept {
        return *_ptr;
    }


    constexpr
    operator T &() noexcept {
        return *_ptr;
    }
};
