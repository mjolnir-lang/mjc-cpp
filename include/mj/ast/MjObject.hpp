#pragma once

#include <mj/ast/MjType.hpp>
#include <mj/ast/MjStorage.hpp>


/// An MjObject is an association of a type with storage.
/// This is used for compile time emulation and execution.
class MjObject {
public:


    // Return the type information.
    const MjType *type() const {
        return nullptr;
    }


    // Return the type information.
    u32 size() const {
        return type()->size();
    }


    // Return the type information.
    u32 alignment() const {
        return type()->alignment();
    }


    // Return the storage
    MjStorage *storage() {
        return nullptr;
    }


    // Return the storage
    const MjStorage *storage() const {
        return nullptr;
    }
};
