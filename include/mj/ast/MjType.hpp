#pragma once

#include <mj/ast/MjItem.hpp>
#include <mj/ast/MjAnnotation.hpp>
#include <mj/ast/MjComment.hpp>
#include <mj/ast/MjOperatorKind.hpp>
#include <mj/ast/MjTypeKind.hpp>
#include <mj/ast/MjTypeQualifiers.hpp>


class MjTypeName;


class MjType : public MjItem {
private:
    Vector<MjItem *> _items;
public:


    ///
    /// Constructors
    ///


    MjType(MjTypeKind kind) noexcept : MjItem(MjItemKind::TYPE) {}


    ///
    /// Properties
    ///


    constexpr
    bool is_basic_type() noexcept {
        return _type_kind.is_basic();
    }


    constexpr
    bool is_derived_type() noexcept {
        return _type_kind.is_derived();
    }


    constexpr
    bool is_builtin_type() noexcept {
        return _type_kind.is_builtin();
    }


    constexpr
    bool is_type_alias() const noexcept {
        return _type_kind == MjTypeKind::ALIAS;
    }


    constexpr
    bool is_void_type() const noexcept {
        return _type_kind == MjTypeKind::VOID;
    }


    constexpr
    bool is_array_type() const noexcept {
        return _type_kind == MjTypeKind::ARRAY;
    }


    constexpr
    bool is_bitfield_type() const noexcept {
        return _type_kind == MjTypeKind::BITFIELD;
    }


    constexpr
    bool is_class_type() const noexcept {
        return _type_kind == MjTypeKind::CLASS;
    }


    constexpr
    bool is_enumeration_type() const noexcept {
        return _type_kind == MjTypeKind::ENUMERATION;
    }


    constexpr
    bool is_structure_type() const noexcept {
        return _type_kind == MjTypeKind::STRUCTURE;
    }


    constexpr
    bool is_union_type() const noexcept {
        return _type_kind == MjTypeKind::UNION;
    }


    constexpr
    bool is_variant_type() const noexcept {
        return _type_kind == MjTypeKind::VARIANT;
    }


    constexpr
    bool is_interface_type() const noexcept {
        return _type_kind == MjTypeKind::INTERFACE;
    }


    constexpr
    bool is_slice_type() const noexcept {
        return _type_kind == MjTypeKind::SLICE;
    }


    constexpr
    bool is_pointer_type() const noexcept {
        return _type_kind == MjTypeKind::POINTER;
    }


    constexpr
    bool is_method_type() const noexcept {
        return _type_kind == MjTypeKind::METHOD;
    }


    constexpr
    bool is_function_type() const noexcept {
        return _type_kind == MjTypeKind::FUNCTION;
    }


    constexpr
    bool is_operator_type() const noexcept {
        return _type_kind == MjTypeKind::OPERATOR;
    }


    constexpr
    bool is_constructor_type() const noexcept {
        return _type_kind == MjTypeKind::CONSTRUCTOR;
    }


    constexpr
    bool is_destructor_type() const noexcept {
        return _type_kind == MjTypeKind::DESTRUCTOR;
    }


    /// Return true if the type is 'const' qualified.
    constexpr
    bool is_const() const noexcept {
        return _type_qualifiers & MjTypeQualifiers::CONST;
    }


    /// Return true if the type is 'volatile' qualified.
    constexpr
    bool is_volatile() const noexcept {
        return _type_qualifiers & MjTypeQualifiers::VOLATILE;
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


    constexpr
    bool has_item(MjItemKind item_kind) const noexcept {
        for (MjItem *item : _items) {
            if (item->item_kind() == item_kind) {
                return true;
            }
        }

        return false;
    }


    constexpr
    Slice<MjItem *const> items(MjItemKind item_kind) const noexcept {
        MjItem *const *data = _items.begin();
        MjItem *const *end = _items.end();

        for (; data < end; ++data) {
            if ((*data)->item_kind() == item_kind) {
                u32 size = 0;

                while (data + size < end && data[size]->item_kind()) {
                    size += 1;
                }

                return {data, size};
            }
        }

        return nullptr;
    }


    constexpr
    Slice<MjItem *> items(MjItemKind item_kind) noexcept {
        MjItem **data = _items.begin();
        MjItem **end = _items.end();

        for (; data < end; ++data) {
            if ((*data)->item_kind() == item_kind) {
                u32 size = 0;

                while (data + size < end && data[size]->item_kind()) {
                    size += 1;
                }

                return {data, size};
            }
        }

        return nullptr;
    }


    template<class T, class = Where::is_derived_from<MjItem, T>>
    constexpr
    bool has_item() const noexcept {
        return has_item(T::item_kind());
    }


    template<class T, class = Where::is_derived_from<MjItem, T>>
    constexpr
    Slice<T *const> items() const noexcept {
        Slice<MjItem *const> it = items(T::item_kind());
        return {reinterpret_cast<T *const*>(it.data()), it.size()};
    }


    template<class T, class = Where::is_derived_from<MjItem, T>>
    constexpr
    Slice<T *> items() noexcept {
        Slice<MjItem *> items = this->items(T::item_kind());
        return {reinterpret_cast<T **>(items.data()), items.size()};
    }


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


    const MjToken *name() const noexcept {
        return reinterpret_cast<const MjToken *>(_items[_name_index]);
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
        return _template_argument_list_index > 0;
    }


    MjTemplateArgumentList *template_argument_list() const noexcept {
        return *reinterpret_cast<MjTemplateArgumentList *const *>(&_items[_template_argument_list_index]);
    }


    MjTemplateArgumentList *template_argument_list() noexcept {
        return *reinterpret_cast<MjTemplateArgumentList **>(&_items[_template_argument_list_index]);
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
    virtual
    u32 size() const noexcept = 0;


    /// @brief Return the alignment of the type in bytes.
    virtual
    u32 alignment() const noexcept = 0;


    ///
    /// Methods
    ///





    const MjType *find_type(const MjToken *name) const noexcept;


    const MjType *find_type_template(const MjToken *name, const MjTemplateArgumentList &argument_list) const noexcept;


    /// A variable may be a member or a shared member. It may be a constant as well.
    const MjVariable *find_variable(const MjToken *name) const noexcept;


    const MjVariable *find_member(const MjToken *name) const noexcept;


    /// A function may be a method or a shared function.
    const MjFunction *find_function(const MjToken *name, const MjFunctionArgumentList &argument_list) const noexcept;


    const MjMethod *find_method(const MjToken *name, const MjFunctionArgumentList &argument_list) const noexcept;


    /// A method or a function.
    const MjFunction *find_operator(MjOperatorKind kind, const MjFunctionArgumentList &argument_list) const noexcept;
};
