#pragma once

#include <mj/ast/MjTemplate.hpp>


/// @brief An `MjType` is defines the properties of an `MjObject`.
class MjTypeTemplate {
protected:
    static
    const Vector<MjMethod *> CONSTRUCTORS;

    static
    const Vector<MjMethod *> METHODS;

    static
    const Vector<MjMember *> MEMBERS;

    static
    const Vector<MjOperator *> OPERATORS;
public:


    virtual
    ~MjTypeTemplate() = default;


    ///
    /// Properties
    ///


    /// @brief Return true if the type is 'const' qualified.
    virtual
    bool is_const() const = 0;


    /// \brief Return true if the type is 'volatile' qualified.
    virtual
    bool is_volatile() const = 0;


    /// @brief Return the list of named constructors for the type.
    /// This does not include any anonymous initializers.
    virtual
    const Vector<MjMethod *> &constructors() const = 0;


    /// @brief Return the destructor for the type.
    virtual
    const MjMethod &destructor() const = 0;


    /// @brief Return the list of member variables defined by the type.
    virtual
    const Vector<MjMember *> &members() const = 0;


    /// @brief Return the list of methods defined by the type.
    virtual
    const Vector<MjMethod *> &methods() const = 0;


    /// @brief Return the list of operators defined by the type.
    virtual
    const Vector<MjOperator *> &operators() const = 0;


    virtual
    const MjScope &shared() const = 0;


    /// @brief Return the 'const' qualified derivation of the type.
    virtual
    const MjType &const_qualified_derivation() const = 0;


    /// @brief Return the 'volatile' qualified derivation of the type.
    virtual
    const MjType &volatile_qualified_derivation() const = 0;


    ///
    /// Template Properties
    ///


    virtual
    const MjTemplateArgumentList *template_argument_list() const = 0;


    virtual
    MjTemplateArgumentList *template_argument_list() = 0;


    virtual
    const MjTemplateParameterList *template_parameter_list() const = 0;


    virtual
    MjTemplateParameterList *template_parameter_list() = 0;


    /// @brief Return true if the type is a template.
    bool is_generic() const {
        return template_argument_list() != nullptr;
    }


    /// @brief Return true if the type is a template.
    bool is_generic() {
        return template_argument_list() != nullptr;
    }


    ///
    /// Derived Properties
    ///


    /// @brief Return the size of the type in bytes.
    virtual
    u32 size() const = 0;


    /// @brief Return the alignment of the type in bytes.
    virtual
    u32 alignment() const = 0;
};


#include <mj/ast/MjBasicTypeTemplate.hpp>
#include <mj/ast/MjDerivedTypeTemplate.hpp>
