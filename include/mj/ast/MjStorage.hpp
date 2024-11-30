#pragma once

#include <core/Common.hpp>


/// An `MjStorage` object is a memory backing for compile time emulation and execution as well as
/// for storing raw data. It provides methods for detecting overlap and modification or exclusive
/// access to data. This allows assumptions to be made about the data.
class MjStorage {
private:
    u64 _address;
    u32 _offset;
    bool _is_volatile;
    bool _is_aliased;
    bool _is_relative;
    bool _is_owned;
public:


    MjStorage(u32 size) noexcept {}


    MjStorage(MjStorage &owner, u32 offset) noexcept {}


    bool is_owned() const noexcept {
        return _is_owned;
    }


    // Return the object address.
    u32 address() const noexcept {
        return _address;
    }


    // Return the object offset.
    u32 offset() const noexcept {
        return _offset;
    }
};
