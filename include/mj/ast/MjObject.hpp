#pragma once

#include <mj/ast/MjType.hpp>
#include <mj/ast/MjStorage.hpp>


/// An object is an association of a type with storage.
/// This is used for compile time emulation and execution.
class MjObject {
private:
    MjType *_type;
    MjStorage _storage;
public:


    ///
    /// Properties
    ///


    /// Return true if this object has relative offset.
    bool is_relative() const noexcept {
        return false;
    }


    /// Return true if this object has internal linkage.
    bool is_internal() const noexcept {
        return false;
    }


    /// Return true if this object has external linkage.
    bool is_external() const noexcept {
        return false;
    }


    /// Return true if this object has local storage.
    bool is_local() const noexcept {
        return false;
    }


    /// Return true if this object has global storage.
    bool is_global() const noexcept {
        return false;
    }


    // Return the type information.
    const MjType *type() const noexcept {
        return _type;
    }


    // Return the type information.
    u32 size() const noexcept {
        return _type->size();
    }


    // Return the type information.
    u32 alignment() const noexcept {
        return _type->alignment();
    }


    // Return the object address.
    u32 address() const noexcept {
        return _storage.address();
    }


    // Return the object offset.
    u32 offset() const noexcept {
        return _storage.offset();
    }


    // Return the storage
    const MjStorage &storage() const noexcept {
        return _storage;
    }


    // Return the storage
    MjStorage &storage() noexcept {
        return _storage;
    }
};
