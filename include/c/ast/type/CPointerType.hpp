#pragma once

#include <c/ast/CDerivedType.hpp>


class CPointerType : public CDerivedType {
private:
    const CType &base_type_;
    bool is_const_;
    bool is_volatile_;
public:


    CPointerType(
        const CType &base_type,
        bool is_const,
        bool is_volatile
    ) :
        base_type_(base_type),
        is_const_(is_const),
        is_volatile_(is_volatile)
    {}


    ~CPointerType() = default;


    /// \brief Return the size of the type in bytes.
    u32 size() const {
        return size_;
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


    /// \brief Return the 'const' qualified derivation of the type.
    const CType &const_qualified_derivation() const {
        return;
    }


    /// \brief Return the 'volatile' qualified derivation of the type.
    const CType &volatile_qualified_derivation() const {
        return;
    }
};
