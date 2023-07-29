#pragma once

#include "mj/ast/MjDerivedType.hpp"


// An 'Array Type' is a contiguous array of the base type whose size is the
// product of the base type size and the array size.
class MjArrayType : public MjDerivedType {
private:
    MjExpression array_size_;
    const MjType &base_type_;
    u32 size_;
    u32 alignment_;
    bool is_const_;
    bool is_volatile_;
public:


    MjArrayType(
        const MjType &base_type,
        MjExpression array_size,
        u32 size,
        u32 alignment,
        bool is_const,
        bool is_volatile
    ) :
        array_size_(array_size),
        base_type_(base_type),
        size_(size),
        alignment_(alignment),
        is_const_(is_const),
        is_volatile_(is_volatile)
    {
        // create constructor and destructor
    }


    ~MjArrayType() {}


    /// \brief Return the size of the type in bytes.
    u32 size() const {
        return size_;
    }


    /// \brief Return the size of the type in bytes.
    const MjExpression &array_size() const {
        return array_size_;
    }


    /// \brief Return the alignment of the type in bytes.
    u32 alignment() const {
        return alignment_;
    }


    /// \brief Return true if the type is 'const' qualified.
    bool is_const() const {
        return is_const_;
    }


    /// \brief Return true if the type is 'volatile' qualified.
    bool is_volatile() const {
        return is_volatile_;
    }


    const MjMethod &destructor() const {
        return ;
    }


    /// \brief Return the 'const' qualified derivation of the type.
    const MjType &const_qualified_derivation() const {
        return;
    }


    /// \brief Return the 'volatile' qualified derivation of the type.
    const MjType &volatile_qualified_derivation() const {
        return;
    }
};
