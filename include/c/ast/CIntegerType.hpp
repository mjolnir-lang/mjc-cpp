#pragma once

#include <c/ast/CBasicType.hpp>


// An 'Array Type' is a contiguous array of the base type whose size is the
// product of the base type size and the array size.
class CIntegerType : public CBasicType {
private:
    u32 size_;
    u32 alignment_;
    bool is_const_;
    bool is_volatile_;
public:


    CIntegerType(
        const CType &base_type,
        CExpression array_size,
        u32 size,
        u32 alignment,
        bool is_const,
        bool is_volatile
    ) :
        size_(size),
        alignment_(alignment),
        is_const_(is_const),
        is_volatile_(is_volatile)
    {
        // create constructor and destructor
    }


    ~CIntegerType() {}


    /// \brief Return the size of the type in bytes.
    u32 size() const {
        return size_;
    }


    ///
    /// CBasicType
    ///


    const CTypeName &name() const {

    }


    const CComment &comment() const {

    }


    ///
    /// CType
    ///


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


    /// \brief Return the 'const' qualified derivation of the type.
    const CType &const_qualified_derivation() const {
        return;
    }


    /// \brief Return the 'volatile' qualified derivation of the type.
    const CType &volatile_qualified_derivation() const {
        return;
    }
};
