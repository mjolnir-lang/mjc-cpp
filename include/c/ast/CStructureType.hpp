#pragma once

#include <c/ast/CBasicType.hpp>


// Not a class. A data container only. no methods, no properties, no shared.
class CStructureType : public CBasicType {
private:
    Vector<CType> derivations_; // The derived types
    Vector<CMember *> members_; // Members
    const CTypeName &name_;     // The type identifier sequence (TODO)
    const CComment &comment_;   // The type documentation comment
    u32 size_;             // The type size in bytes
    u32 alignment_;        // The type alignment in bytes
    const bool is_const_;        // The type mutability. Memory may not be modified through this type
    const bool is_volatile_;     // The type volatility. Memory may be modified outside of the program
public:


    CStructureType(
        const CTypeName &name,
        const CComment &comment,
        bool is_const,
        bool is_volatile
    ) :
        name_(name),
        comment_(comment),
        is_const_(is_const),
        is_volatile_(is_volatile)
    {
        size_ = 0;
        alignment_ = 0;

        for (CMember *member : members_) {
            size_ = std::max(size_, member->size());
            alignment_ = std::max(alignment_, member->size());
        }
    }


    const CTypeName &name() const {
        return name_;
    }


    const CComment &comment() const {
        return comment_;
    }


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


    const Vector<CMember *> &members() const {
        return members_;
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
