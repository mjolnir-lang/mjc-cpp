#pragma once

#include <core/Enum.hpp>


template<class MjItemKind>
struct MjItemKindValues {
    static constexpr MjItemKind UNKNOWN{};

    static constexpr MjItemKind FILE{};
    static constexpr MjItemKind MODULE{};
    static constexpr MjItemKind VARIABLE{};
    static constexpr MjItemKind CONSTANT{};

    static constexpr MjItemKind METHOD{};
    static constexpr MjItemKind FUNCTION{};


    ///
    /// Comment
    ///

    static constexpr MjItemKind BLOCK_COMMENT{};
    static constexpr MjItemKind FORMATTED_BLOCK_COMMENT{};
    static constexpr MjItemKind FORMATTED_LINE_COMMENT{};
    static constexpr MjItemKind LINE_COMMENT{};


    ///
    /// Annotation
    ///

    static constexpr MjItemKind ALIGNMENT_ANNOTATION{};
    static constexpr MjItemKind API_ANNOTATION{};
    static constexpr MjItemKind INTERNAL_ANNOTATION{};
    static constexpr MjItemKind OFFSET_ANNOTATION{};
    static constexpr MjItemKind PURE_ANNOTATION{};
    static constexpr MjItemKind SHARED_ANNOTATION{};
    static constexpr MjItemKind SIZE_ANNOTATION{};


    ///
    /// Directive
    ///

    static constexpr MjItemKind IMPORT_DIRECTIVE{};


    ///
    /// Statement
    ///

    static constexpr MjItemKind BLOCK_STATEMENT{};
    static constexpr MjItemKind BREAK_STATEMENT{};
    static constexpr MjItemKind CONTINUE_STATEMENT{};
    static constexpr MjItemKind DO_LOOP{};
    static constexpr MjItemKind DO_UNTIL_LOOP{};
    static constexpr MjItemKind DO_WHILE_LOOP{};
    static constexpr MjItemKind FOR_LOOP{};
    static constexpr MjItemKind IF_STATEMENT{};
    static constexpr MjItemKind ELSE_STATEMENT{};
    static constexpr MjItemKind CASE_STATEMENT{};
    static constexpr MjItemKind THEN_STATEMENT{};
    static constexpr MjItemKind MATCH_STATEMENT{};
    static constexpr MjItemKind RETURN_STATEMENT{};
    static constexpr MjItemKind TRY_STATEMENT{};
    static constexpr MjItemKind UNTIL_LOOP{};
    static constexpr MjItemKind WHILE_LOOP{};
    static constexpr MjItemKind YIELD_STATEMENT{};


    ///
    /// Expression
    ///

    static constexpr MjItemKind BINARY_EXPRESSION{};
    static constexpr MjItemKind BLOCK_EXPRESSION{};
    static constexpr MjItemKind CASE_EXPRESSION{};
    static constexpr MjItemKind CATCH_EXPRESSION{};
    static constexpr MjItemKind ELSE_EXPRESSION{};
    static constexpr MjItemKind FUNCTION_CALL_EXPRESSION{};
    static constexpr MjItemKind IF_EXPRESSION{};
    static constexpr MjItemKind LAMBDA_EXPRESSION{};
    static constexpr MjItemKind MATCH_EXPRESSION{};
    static constexpr MjItemKind METHOD_CALL_EXPRESSION{};
    static constexpr MjItemKind NULL_EXPRESSION{};
    static constexpr MjItemKind OPERATOR_CALL_EXPRESSION{};
    static constexpr MjItemKind UNINITIALIZED_EXPRESSION{};
    static constexpr MjItemKind THEN_EXPRESSION{};
    static constexpr MjItemKind TRY_EXPRESSION{};
    static constexpr MjItemKind TYPE_CAST_EXPRESSION{};
    static constexpr MjItemKind USE_EXPRESSION{};
    static constexpr MjItemKind UNARY_EXPRESSION{};


    ///
    /// Types
    ///


    ///
    /// Built-in Type
    ///

    static constexpr MjItemKind VOID_TYPE{};

    static constexpr MjItemKind TYPE_ALIAS{};

    static constexpr MjItemKind TYPE_NAME{};

    static constexpr MjItemKind TYPE_EXPRESSION{};

    static constexpr MjItemKind CONSTANT_TYPE{};
    static constexpr MjItemKind ARRAY_TYPE{};
    static constexpr MjItemKind POINTER_TYPE{};
    static constexpr MjItemKind SLICE_TYPE{};
    static constexpr MjItemKind FUNCTION_TYPE{};
    static constexpr MjItemKind METHOD_TYPE{};

    static constexpr MjItemKind BITFIELD_TYPE{};
    static constexpr MjItemKind CLASS_TYPE{};
    static constexpr MjItemKind ENUMERATION_TYPE{};
    static constexpr MjItemKind INTERFACE_TYPE{};
    static constexpr MjItemKind REFERENCE_TYPE{};
    static constexpr MjItemKind SAFE_TYPE{};
    static constexpr MjItemKind STRUCTURE_TYPE{};
    static constexpr MjItemKind UNION_TYPE{};

    static constexpr MjItemKind CONSTRUCTOR_TYPE{};
    static constexpr MjItemKind DESTRUCTOR_TYPE{};
    static constexpr MjItemKind OPERATOR_TYPE{};


    ///
    /// Type Template Specialization
    ///

    static constexpr MjItemKind TYPE_ALIAS_TEMPLATE_SPECIALIZATION{};

    static constexpr MjItemKind TYPE_EXPRESSION_TEMPLATE_SPECIALIZATION{};
    static constexpr MjItemKind ARRAY_TYPE_TEMPLATE_SPECIALIZATION{};
    static constexpr MjItemKind FUNCTION_TYPE_TEMPLATE_SPECIALIZATION{};
    static constexpr MjItemKind METHOD_TYPE_TEMPLATE_SPECIALIZATION{};
    static constexpr MjItemKind POINTER_TYPE_TEMPLATE_SPECIALIZATION{};
    static constexpr MjItemKind SLICE_TYPE_TEMPLATE_SPECIALIZATION{};

    static constexpr MjItemKind BITFIELD_TYPE_TEMPLATE_SPECIALIZATION{};
    static constexpr MjItemKind CLASS_TYPE_TEMPLATE_SPECIALIZATION{};
    static constexpr MjItemKind ENUMERATION_TYPE_TEMPLATE_SPECIALIZATION{};
    static constexpr MjItemKind INTERFACE_TYPE_TEMPLATE_SPECIALIZATION{};
    static constexpr MjItemKind REFERENCE_TYPE_TEMPLATE_SPECIALIZATION{};
    static constexpr MjItemKind STRUCTURE_TYPE_TEMPLATE_SPECIALIZATION{};
    static constexpr MjItemKind UNION_TYPE_TEMPLATE_SPECIALIZATION{};

    static constexpr MjItemKind CONSTRUCTOR_TYPE_TEMPLATE_SPECIALIZATION{};
    static constexpr MjItemKind DESTRUCTOR_TYPE_TEMPLATE_SPECIALIZATION{};
    static constexpr MjItemKind OPERATOR_TYPE_TEMPLATE_SPECIALIZATION{};


    ///
    /// Template
    ///


    ///
    /// Type Template
    ///


    static constexpr MjItemKind TYPE_ALIAS_TEMPLATE{};

    static constexpr MjItemKind TYPE_EXPRESSION_TEMPLATE{};
    static constexpr MjItemKind ARRAY_TYPE_TEMPLATE{};
    static constexpr MjItemKind FUNCTION_TYPE_TEMPLATE{};
    static constexpr MjItemKind METHOD_TYPE_TEMPLATE{};
    static constexpr MjItemKind POINTER_TYPE_TEMPLATE{};
    static constexpr MjItemKind SLICE_TYPE_TEMPLATE{};

    static constexpr MjItemKind BITFIELD_TYPE_TEMPLATE{};
    static constexpr MjItemKind CLASS_TYPE_TEMPLATE{};
    static constexpr MjItemKind ENUMERATION_TYPE_TEMPLATE{1};
    static constexpr MjItemKind INTERFACE_TYPE_TEMPLATE{};
    static constexpr MjItemKind REFERENCE_TYPE_TEMPLATE{};
    static constexpr MjItemKind STRUCTURE_TYPE_TEMPLATE{};
    static constexpr MjItemKind UNION_TYPE_TEMPLATE{};

    static constexpr MjItemKind CONSTRUCTOR_TYPE_TEMPLATE{};
    static constexpr MjItemKind DESTRUCTOR_TYPE_TEMPLATE{};
    static constexpr MjItemKind OPERATOR_TYPE_TEMPLATE{};

};


struct MjItemKind : public Enum<u8>, public MjItemKindValues<MjItemKind> {


    constexpr
    explicit
    MjItemKind(u8 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    constexpr
    bool is_basic() noexcept {
        return _id;
    }


    constexpr
    bool is_derived() noexcept {
        return _id;
    }


    constexpr
    bool is_builtin() noexcept {
        return _id;
    }


    ///
    ///
    ///


    bool is_type_alias() const noexcept {
        return _id == MjItemKind::TYPE_ALIAS;
    }


    constexpr
    bool is_void_type() const noexcept {
        return _id == MjItemKind::VOID_TYPE;
    }


    constexpr
    bool is_array_type() const noexcept {
        return _id == MjItemKind::ARRAY_TYPE;
    }


    constexpr
    bool is_bitfield_type() const noexcept {
        return _id == MjItemKind::BITFIELD_TYPE;
    }


    constexpr
    bool is_class_type() const noexcept {
        return _id == MjItemKind::CLASS_TYPE;
    }


    constexpr
    bool is_enumeration_type() const noexcept {
        return _id == MjItemKind::ENUMERATION_TYPE;
    }


    constexpr
    bool is_structure_type() const noexcept {
        return _id == MjItemKind::STRUCTURE_TYPE;
    }


    constexpr
    bool is_union_type() const noexcept {
        return _id == MjItemKind::UNION_TYPE;
    }


    constexpr
    bool is_interface_type() const noexcept {
        return _id == MjItemKind::INTERFACE_TYPE;
    }


    constexpr
    bool is_slice_type() const noexcept {
        return _id == MjItemKind::SLICE_TYPE;
    }


    constexpr
    bool is_pointer_type() const noexcept {
        return _id == MjItemKind::POINTER_TYPE;
    }


    constexpr
    bool is_method_type() const noexcept {
        return _id == MjItemKind::METHOD_TYPE;
    }


    constexpr
    bool is_function_type() const noexcept {
        return _id == MjItemKind::FUNCTION_TYPE;
    }


    constexpr
    bool is_operator_type() const noexcept {
        return _id == MjItemKind::OPERATOR_TYPE;
    }


    constexpr
    bool is_constructor_type() const noexcept {
        return _id == MjItemKind::CONSTRUCTOR_TYPE;
    }


    constexpr
    bool is_destructor_type() const noexcept {
        return _id == MjItemKind::DESTRUCTOR_TYPE;
    }

};
