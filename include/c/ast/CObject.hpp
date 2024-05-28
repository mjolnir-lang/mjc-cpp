#pragma once

#include <c/ast/CType.hpp>
#include <c/ast/CStorage.hpp>


/// An CObject is an association of a type with storage.
/// This is used for compile time emulation and execution.
class CObject {
public:


    // Return the type information.
    virtual const CType &type() const = 0;


    // Return the type information.
    u32 size() const {
        return type().size();
    }


    // Return the type information.
    u32 alignment() const {
        return type().alignment();
    }


    // Return the storage
    virtual CStorage &storage() = 0;


    // Return the storage
    virtual const CStorage &storage() const = 0;
};
