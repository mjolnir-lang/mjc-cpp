#pragma once

#include "mj/ast/MjBasicType.hpp"


class MjClassType : public MjBasicType {
private:

    // Type System Hierarchy
    Vector<MjType> derived_; // The derived types

    // Members
    MjShared shared_; // The list of shared type scopes
    Vector<MjOperator *> operators_;
    MjMethod destructor_;
    Vector<MjMethod *> constructors_;
    Vector<MjMethod *> methods_;
    Vector<MjMember *> members_;
    Vector<MjProperty *> properties_;
    Vector<MjInterfaceType *> interfaces_;

    // Storage
    u32 size_;        // The type size in bytes
    u32 alignment_;   // The type alignment in bytes

    // Storage Modifiers
    const bool is_const_;    // The type mutability. Memory may not be modified through this type
    const bool is_volatile_; // The type volatility. Memory may be modified outside of the program




    const MjToken *name_; // The type identifier sequence (TODO)
    const MjComment *comment_; // The type documentation comment
    Vector<MjType *> template_parameters_;
public:


    MjClassType(
        const MjToken *name,
        Vector<MjType *> template_parameters
    ) :
        name_(name),
        template_parameters_(template_parameters)
    {}


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


    const Vector<MjProperty *> &properties() {
        return properties_;
    }


    const Vector<MjMethod *> &constructors() const {
        return constructors_;
    }


    const MjMethod &destructor() const {
        return destructor_;
    }


    /// \brief Return the list of methods defined by the type.
    const Vector<MjMethod *> &methods() const {
        return methods_;
    }


    const Vector<MjMember *> &members() const {
        return members_;
    }


    /// \brief Return the list of operators defined by the type.
    const Vector<MjOperator *> &operators() const {
        return operators_;
    }


    /// \brief Return the list of operators defined by the type.
    const Vector<MjOperator *> &operators() const {
        return operators_;
    }


    /// \brief Return the 'const' qualified derivation of the type.
    const MjType &const_qualified_derivation() const {
        return;
    }


    /// \brief Return the 'volatile' qualified derivation of the type.
    const MjType &volatile_qualified_derivation() const {
        return;
    }

    bool is_anonymous() {
        return name_ == nullptr;
    }


    bool is_generic() {
        return !template_parameters_.is_empty();
    }
};
