#pragma once

#include <c/ast/CBasicType.hpp>


class CEnumerationType : public CBasicType {
private:

    Vector<CMember *> members_;
    const CToken *name_; // The type identifier sequence (TODO)
    const CComment *comment_; // The type documentation comment

    const CBasicType &index_type_;
    const Vector<CVariable> values_;
public:


    CEnumerationType(
        u32 size,
        u32 alignment,
        bool is_const,
        bool is_volatile,
        const CToken &name,
        const CComment *comment,
        CBasicType &index_type
    ) :
        index_type_(index_type)
    {}


    ~CEnumerationType() {}


    /// \brief Return the size of the type in bytes.
    u32 size() const {
        return index_type_.size();
    }


    /// \brief Return the alignment of the type in bytes.
    u32 alignment() const {
        return index_type_.alignment();
    }


    /// \brief Return true if the type is 'const' qualified.
    bool is_const() const {
        return true;
    }


    /// \brief Return true if the type is 'volatile' qualified.
    bool is_volatile() const {
        return false;
    }


    const Vector<CMember *> &members() const {
        return members_;
    }


    /// \brief Return the list of operators defined by the type.
    const Vector<COperator *> &operators() const {
        return OPERATORS;
    }


    /// \brief Return the 'const' qualified derivation of the type.
    const CType &const_qualified_derivation() const {
        return;
    }


    /// \brief Return the 'volatile' qualified derivation of the type.
    const CType &volatile_qualified_derivation() const {
        return;
    }

    bool is_anonymous() {
        return name_ == nullptr;
    }


    const CBasicType &index_type() const {
        return index_type_;
    }


    const Vector<CVariable> values() const {
        return values_;
    }
};
