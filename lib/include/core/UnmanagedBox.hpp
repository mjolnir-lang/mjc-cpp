#pragma once

#include <system/Memory.hpp>
#include <core/Object.hpp>


/// @brief A unique pointer. A single memory allocation. Does not manage initialization or destruction.
/// @tparam T 
template<class T>
class UnmanagedBox {
private:
    T *_data;
public:


    ///
    /// Constructors
    ///


    constexpr
    UnmanagedBox() noexcept : _data(nullptr) {}


    constexpr
    UnmanagedBox(std::nullptr_t) noexcept : _data(nullptr) {}


    template<class... Args>
    UnmanagedBox(u32 size) noexcept :_data(Memory::allocate<T>(size)) {}


    ///
    /// Destructor
    ///


    ~UnmanagedBox() {
        Memory::deallocate(_data);
    }


    ///
    /// Type Casts
    ///


    /// @brief Return a reference to the first element of the data.
    constexpr
    operator const T *() const noexcept {
        return _data;
    }


    /// @brief Return a reference to the first element of the data.
    constexpr
    operator T *() noexcept {
        return _data;
    }


    ///
    /// Methods
    ///


    void resize(u32 size) noexcept {
        Memory::resize(_data, size);
        //Memory::reallocate(_data, size);
    }


    void trim(u32 size) noexcept {
        Memory::trim(_data);
    }


    ///
    /// Operators
    ///


    /// @brief Return a reference to the first element of the data.
    constexpr
    const T &operator*() const noexcept {
        return *_data;
    }


    /// @brief Return a reference to the first element of the data.
    constexpr
    T &operator*() noexcept {
        return *_data;
    }


    /// @brief Return a reference to the first element of the data.
    constexpr
    const T *operator->() const noexcept {
        return _data;
    }


    /// @brief Return a reference to the first element of the data.
    constexpr
    T *operator->() noexcept {
        return _data;
    }


    /// @brief Return a reference to the element at the given index within the data.
    /// @param index The index of the element
    constexpr
    const T &operator[](u32 index) const noexcept {
        return _data[index];
    }


    /// @brief Return a reference to the element at the given index within the data.
    /// @param index The index of the element
    constexpr
    T &operator[](u32 index) noexcept {
        return _data[index];
    }
};
