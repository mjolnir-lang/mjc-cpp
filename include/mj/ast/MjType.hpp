#pragma once

#include <mj/ast/MjItem.hpp>
#include <mj/ast/MjDeclaration.hpp>
#include <mj/ast/MjAnnotation.hpp>
#include <mj/ast/MjComment.hpp>
#include <mj/ast/MjOperatorKind.hpp>
#include <mj/ast/MjTypeQualifiers.hpp>


class MjTypeName;


class MjType : public MjDeclaration {
protected:
    u32 _size;
    u32 _alignment;


    ///
    /// Constructors
    ///


    constexpr
    MjType(MjItemInfo item_info) noexcept : MjDeclaration(item_info) {}


public:


    ///
    /// Properties
    ///


    /// Return true if the type is 'const' qualified.
    constexpr
    bool is_const_qualified() const noexcept {
        return is<MjConstantType>();
    }


    constexpr
    bool is_safe_qualified() const noexcept {
        return is<MjSafeType>();
    }


    ///
    /// Type Properties
    ///


    bool is_value_type() const noexcept;
    bool is_reference_type() const noexcept;

    bool is_constructable() const noexcept;
    bool is_default_constructable() const noexcept;
    bool is_copy_constructable() const noexcept;
    bool is_move_constructable() const noexcept;

    bool is_assignable() const noexcept;
    bool is_default_assignable() const noexcept;
    bool is_move_assignable() const noexcept;
    bool is_copy_assignable() const noexcept;

    bool is_destructible() const noexcept;
    bool is_trivially_destructible() const noexcept;
    bool is_default_destructible() const noexcept;

    bool has_destructor() const noexcept;
    bool has_default_destructor() const noexcept;
    bool has_virtual_destructor() const noexcept;




    bool is_movable() const noexcept;
    bool is_trivially_movable() const noexcept;

    bool is_copyable() const noexcept;
    bool is_trivially_copyable() const noexcept;

    bool has_default_constructor() const noexcept;

    /// A class type that has all the following properties:
    ///
    /// - it has a constexpr destructor
    /// - all of its non-static non-variant data members and base classes are of non-volatile literal types, and it:
    ///     is a closure type
    ///     is an aggregate union type that has either no variant members or at least one variant member of non-volatile literal type
    ///     is a non-union aggregate type for which each of its anonymous union members satisfies the above requirements for an aggregate union type, or
    ///     has at least one constexpr constructor or constructor template that is not a copy or move constructor.
    bool is_literal() const noexcept;

    /// A trivial type is a type that has a trivial default constructor and is trivially copyable.
    bool is_trivial() const noexcept;




    ///
    /// Properties
    ///


    /// Return true if the type has a comment.
    constexpr
    bool has_comment() const noexcept {
        return has_item<MjComment>();
    }


    /// Return the comment or `nullptr`.
    constexpr
    MjComment *comment() const noexcept {
        Slice<MjComment *const> comments = items<MjComment>();
        return !comments.is_empty() ? *comments : nullptr;
    }


    constexpr
    bool has_annotations() const noexcept {
        return has_item<MjAnnotation>();
    }


    Slice<MjAnnotation *const> annotations() const noexcept {
        return items<MjAnnotation>();
    }


    constexpr
    bool has_name() const noexcept {
        return has_item<MjTypeName>();
    }


    const MjTypeName *name() const noexcept {
        return items<MjTypeName>();
    }


    constexpr
    bool is_anonymous() const noexcept {
        return !has_name();
    }


    /// Return true if the type has a comment.
    constexpr
    bool has_template() const noexcept {
        return has_item<MjTemplate>();
    }


    /// Return the comment or `nullptr`.
    constexpr
    MjComment *base_template() const noexcept {
        Slice<MjComment *const> comments = items<MjComment>();
        return !comments.is_empty() ? *comments : nullptr;
    }


    constexpr
    bool is_template_specialization() const noexcept {
        return has_template_argument_list();
    }


    constexpr
    bool has_template_argument_list() const noexcept {
        return has_item<MjTemplateArgumentList>();
    }


    MjTemplateArgumentList *template_argument_list() const noexcept {
        return items<MjTemplateArgumentList>();
    }


    MjTemplateArgumentList *template_argument_list() noexcept {
        return items<MjTemplateArgumentList>();
    }


    constexpr
    bool has_constructors() const noexcept {
        return _constructors_size > 0;
    }





    Slice<MjConstructor *const> constructors() const noexcept {
        return items<MjConstructor>();
    }


    Slice<MjConstructor *> constructors() noexcept {
        return items<MjConstructor>();
    }


    constexpr
    bool has_destructor() const noexcept {
        return has_item<MjDestructor>();
    }


    MjFunction *destructor() const noexcept {
        return items<MjDestructor>();
    }


    Slice<MjVariable *const> members() const noexcept {
        return items<MjMember>();
    }


    Slice<MjMethod *const> methods() const noexcept {
        return items<MjMethod>();
    }


    Slice<MjVariable *const> variables() const noexcept {
        return items<MjVariable>();
    }


    Slice<MjFunction *const> functions() const noexcept {
        return items<MjFunction>();
    }


    Slice<MjFunction *const> operators() const noexcept {
        return items<MjFunction>();
    }


    constexpr
    bool has_types() const noexcept {
        return has_item<MjType>();
    }


    Slice<MjType *const> types() const noexcept {
        return items<MjType>();
    }


    constexpr
    bool has_type_templates() const noexcept {
        return has_item<MjTypeTemplate>();
    }


    Slice<MjTypeTemplate *const> type_templates() const noexcept {
        return items<MjTypeTemplate>();
    }


    constexpr
    MjTypeQualifiers type_qualifiers() const noexcept {
        return MjTypeQualifiers::NONE;
    }


    /// @brief Return the size of the type in bytes.
    constexpr
    u32 size() const noexcept {
        return _size;
    }


    /// @brief Return the alignment of the type in bytes.
    constexpr
    u32 alignment() const noexcept {
        return _alignment;
    }


    ///
    /// Methods
    ///





    const MjType *find_type(MjToken name) const noexcept;


    const MjType *find_type_template(MjToken name, const MjTemplateArgumentList &argument_list) const noexcept;


    /// A variable may be a member or a shared member. It may be a constant as well.
    const MjVariable *find_variable(MjToken name) const noexcept;


    const MjVariable *find_member(MjToken name) const noexcept;


    /// A function may be a method or a shared function.
    const MjFunction *find_function(MjToken name, const MjFunctionArgumentList &argument_list) const noexcept;


    const MjMethod *find_method(MjToken name, const MjFunctionArgumentList &argument_list) const noexcept;


    /// A method or a function.
    const MjFunction *find_operator(MjOperatorKind kind, const MjFunctionArgumentList &argument_list) const noexcept;
};
