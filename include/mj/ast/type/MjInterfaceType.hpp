#pragma once

#include "mj/ast/MjBasicType.hpp"


/// @brief An MjInterfaceType is an MjBasicType which associates an MjClass with a virtual method table.
class MjInterfaceType : public MjBasicType {
private:
    static constexpr u32 SIZE = 2 * PTR_SIZE;
    static constexpr u32 ALIGNMENT = PTR_ALIGNMENT;

    // Type System Hierarchy
    Vector<MjType> derived_; // The derived types

    // Members
    MjScope shared_; // The list of shared type scopes
    Vector<MjOperator *> operators_;
    MjMethod &destructor_;
    Vector<MjMethod *> constructors_;
    Vector<MjMethod *> methods_;
    Vector<MjMember *> members_;
    Vector<MjProperty *> properties_;
    Vector<MjInterfaceType *> interfaces_;

    // Storage Modifiers
    const bool is_const_;    // The type mutability. Memory may not be modified through this type
    const bool is_volatile_; // The type volatility. Memory may be modified outside of the program




    const MjToken &name_; // The type identifier sequence (TODO)
    const MjComment &comment_; // The type documentation comment
    Vector<MjType *> template_parameters_;
    MjInterfaceType *const_qualified_derivation_ = nullptr;
    MjInterfaceType *volatile_qualified_derivation_ = nullptr;
    MjInterfaceType *const_volatile_qualified_derivation_ = nullptr;
public:


    MjInterfaceType(
        const MjToken &name,
        Vector<MjType *> template_parameters,
        const MjComment &comment,
        bool is_const,
        bool is_volatile
    ) :
        is_const_(is_const),
        is_volatile_(is_volatile),
        name_(name),
        comment_(comment),
        template_parameters_(template_parameters)
    {}


    /// \brief Return the size of the type in bytes.
    u32 size() const {
        return SIZE;
    }


    /// \brief Return the alignment of the type in bytes.
    u32 alignment() const {
        return ALIGNMENT;
    }


    /// \brief Return true if the type is 'const' qualified.
    bool is_const() const {
        return is_const_;
    }


    /// \brief Return true if the type is 'volatile' qualified.
    bool is_volatile() const {
        return is_volatile_;
    }


    const MjScope &shared() const {
        return shared_;
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


    /// \brief Return the 'const' qualified derivation of the type.
    const MjType &const_qualified_derivation() const {
        return;
    }


    /// \brief Return the 'volatile' qualified derivation of the type.
    const MjType &volatile_qualified_derivation() const {
        return;
    }
};
