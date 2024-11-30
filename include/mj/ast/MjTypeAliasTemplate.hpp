#pragma once

#include <mj/ast/MjType.hpp>


class MjTypeAlias : public MjType {
private:
    MjType *_target;
public:


    MjTypeAlias(MjType *target) noexcept : MjType(), _target(target) {}


    ///
    /// Properties
    ///


    constexpr
    bool is_basic() noexcept {
        return _target.is_basic();
    }


    constexpr
    bool is_derived() noexcept {
        return _target.is_derived();
    }


    constexpr
    bool is_builtin() noexcept {
        return _target.is_builtin();
    }


    constexpr
    bool is_alias() const noexcept {
        return true;
    }


    constexpr
    bool is_void() const noexcept {
        return false;
    }


    constexpr
    bool is_array() const noexcept {
        return _type == MjTypeType::ARRAY;
    }


    constexpr
    bool is_bitfield() const noexcept {
        return _type == MjTypeType::BITFIELD;
    }


    constexpr
    bool is_class() const noexcept {
        return _type == MjTypeType::CLASS;
    }


    constexpr
    bool is_enum() const noexcept {
        return _type == MjTypeType::ENUMERATION;
    }


    constexpr
    bool is_structure() const noexcept {
        return _type == MjTypeType::STRUCTURE;
    }


    constexpr
    bool is_union() const noexcept {
        return _type == MjTypeType::UNION;
    }


    constexpr
    bool is_variant() const noexcept {
        return _type == MjTypeType::VARIANT;
    }


    constexpr
    bool is_interface() const noexcept {
        return _type == MjTypeType::INTERFACE;
    }


    constexpr
    bool is_slice() const noexcept {
        return _type == MjTypeType::SLICE;
    }


    constexpr
    bool is_pointer() const noexcept {
        return _type == MjTypeType::POINTER;
    }


    constexpr
    bool is_method() const noexcept {
        return _type == MjTypeType::METHOD;
    }


    constexpr
    bool is_function() const noexcept {
        return _type == MjTypeType::FUNCTION;
    }


    constexpr
    bool is_operator() const noexcept {
        return _type == MjTypeType::METHOD;
    }


    constexpr
    bool is_lambda() const noexcept {
        return _type == MjTypeType::METHOD;
    }


    constexpr
    bool is_constructor() const noexcept {
        return _type == MjTypeType::METHOD;
    }


    constexpr
    bool is_destructor() const noexcept {
        return _type == MjTypeType::METHOD;
    }


    constexpr
    bool is_module() const noexcept {
        return _type == MjTypeType::MODULE;
    }


    /// @brief Return true if the type is 'const' qualified.
    constexpr
    bool is_const() const noexcept {
        return _is_const;
    }


    /// \brief Return true if the type is 'volatile' qualified.
    constexpr
    bool is_volatile() const noexcept {
        return _is_volatile;
    }


    /// \brief Return true if the type is 'volatile' qualified.
    constexpr
    bool has_template_argument_list() const noexcept {
        return !_template_argument_list.is_empty();
    }


    const MjTemplateArgumentList &template_argument_list() const noexcept {
        return _template_argument_list;
    }


    MjTemplateArgumentList &template_argument_list() noexcept {
        return _template_argument_list;
    }


    /// @brief Return true if the type has no comment.
    constexpr
    bool has_comment() const noexcept {
        return _comment != nullptr;
    }


    /// @brief Return true if the type has no name.
    constexpr
    bool is_anonymous() const noexcept {
        return _name != nullptr;
    }


    constexpr
    MjType *return_type() const noexcept {
        return nullptr;
    }


    constexpr
    const MjToken *name() const noexcept {
        return _name;
    }


    constexpr
    const MjComment *comment() const noexcept {
        return _comment;
    }


    /// @brief Return the list of named constructors for the type.
    /// This does not include any anonymous initializers.
    constexpr
    const Vector<MjFunction *> &constructors() const noexcept {
        return _constructors;
    }


    /// @brief Return the list of named constructors for the type.
    /// This does not include any anonymous initializers.
    constexpr
    Vector<MjFunction *> &constructors() noexcept {
        return _constructors;
    }


    /// @brief Return the destructor for the type.
    constexpr
    const MjFunction *destructor() const noexcept {
        return _destructor;
    }


    /// @brief Return the destructor for the type.
    constexpr
    MjFunction *destructor() noexcept {
        return _destructor;
    }


    /// @brief Return the list of member variables defined by the type.
    constexpr
    const Vector<MjVariable *> &members() const noexcept {
        return _members;
    }


    /// @brief Return the list of member variables defined by the type.
    constexpr
    Vector<MjVariable *> &members() noexcept {
        return _members;
    }


    /// @brief Return the list of methods defined by the type.
    constexpr
    const Vector<MjFunction *> &methods() const noexcept {
        return _methods;
    }


    /// @brief Return the list of methods defined by the type.
    constexpr
    Vector<MjFunction *> &methods() noexcept {
        return _methods;
    }


    /// @brief Return the list of operators defined by the type.
    constexpr
    const Vector<MjFunction *> &operators() const noexcept {
        return _operators;
    }


    /// @brief Return the list of operators defined by the type.
    constexpr
    Vector<MjFunction *> &operators() noexcept {
        return _operators;
    }


    constexpr
    const Vector<MjAnnotation *> &annotations() const noexcept {
        return _annotations;
    }


    constexpr
    Vector<MjAnnotation *> &annotations() noexcept {
        return _annotations;
    }


    constexpr
    const Vector<MjFunction *> &shared_methods() const noexcept {
        return _shared_methods;
    }


    constexpr
    Vector<MjFunction *> &shared_methods() noexcept {
        return _shared_methods;
    }


    constexpr
    const Vector<MjVariable *> &shared_members() const noexcept {
        return _shared_members;
    }


    /// @brief Return the 'const' qualified derivation of the type.
    constexpr
    const MjType *const_qualified_derivation() const noexcept {
        return _const_qualified_derivation;
    }


    /// @brief Return the 'const' qualified derivation of the type.
    constexpr
    MjType *const_qualified_derivation() noexcept {
        return _const_qualified_derivation;
    }


    /// @brief Return the 'volatile' qualified derivation of the type.
    constexpr
    const MjType *volatile_qualified_derivation() const noexcept {
        return _volatile_qualified_derivation;
    }


    /// @brief Return the 'volatile' qualified derivation of the type.
    constexpr
    MjType *volatile_qualified_derivation() noexcept {
        return _volatile_qualified_derivation;
    }


    constexpr
    const MjTemplateArgumentList &template_argument_list() const noexcept {
        return _template_argument_list;
    }


    constexpr
    MjTemplateArgumentList &template_argument_list() noexcept {
        return _template_argument_list;
    }


    /// @brief Return the size of the type in bytes.
    constexpr
    u32 size() const noexcept {
        switch (_type) {
        case MjTypeType::ARRAY: return _type_specific.as_array.size->evaluate() * _type_specific.as_array.size->evaluate();
        }
    }


    /// @brief Return the alignment of the type in bytes.
    constexpr
    u32 alignment() const noexcept {
        switch (_type) {
        case MjTypeType::ARRAY: return _type_specific.as_array.base_type.alignment();
        }
    }


    ///
    /// Methods
    ///


    constexpr
    void set_name(const MjToken *name) noexcept {
        _name = name;
    }


    constexpr
    void set_comment(MjComment *comment) noexcept {
        _comment = comment;
    }
};
