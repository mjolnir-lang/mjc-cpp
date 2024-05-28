#pragma once

#include <mj/ast/MjType.hpp>


class MjTypeEnumeration {
private:
    Vector<MjVariable *> _members;
    const MjToken *_name; // The type identifier sequence (TODO)
    MjComment *_comment; // The type documentation comment
    MjType *_index_type;
    Vector<MjVariable> _values;
public:


    MjTypeEnumeration(
        u32 size,
        u32 alignment,
        bool is_const,
        bool is_volatile,
        const MjToken *name,
        Vector<MjType *> template_parameters,
        MjComment *comment,
        MjType *index_type
    ) :
        _index_type(index_type)
    {}


    ~MjTypeEnumeration() {}


    /// \brief Return the size of the type in bytes.
    u32 size() const {
        return _index_type->size();
    }


    /// \brief Return the alignment of the type in bytes.
    u32 alignment() const {
        return _index_type->alignment();
    }


    /// \brief Return true if the type is 'const' qualified.
    bool is_const() const {
        return true;
    }


    /// \brief Return true if the type is 'volatile' qualified.
    bool is_volatile() const {
        return false;
    }


    const Vector<MjFunction> &constructors() const {
        return nullptr;
    }


    const MjFunction *destructor() const {
        return nullptr;
    }


    /// \brief Return the list of methods defined by the type.
    const Vector<MjFunction *> &methods() const {
        return METHODS;
    }


    const Vector<MjVariable *> &members() const {
        return _members;
    }


    /// \brief Return the list of operators defined by the type.
    const Vector<MjFunction *> &operators() const {
        return OPERATORS;
    }


    /// \brief Return the 'const' qualified derivation of the type.
    const MjType *const_qualified_derivation() const {
        return;
    }


    /// \brief Return the 'volatile' qualified derivation of the type.
    const MjType *volatile_qualified_derivation() const {
        return;
    }

    bool is_anonymous() {
        return _name == nullptr;
    }


    bool is_generic() {
        return !_template_parameters.is_empty();
    }


    const MjType &index_type() const {
        return _index_type;
    }


    const Vector<MjVariable> values() const {
        return _values;
    }
};
