#pragma once

#include <core/Enum.hpp>


template<class MjItemKind>
struct MjItemKindValues {
    static constexpr MjItemKind UNKNOWN{0};
    static constexpr MjItemKind TYPE{1};
    static constexpr MjItemKind FUNCTION{2};
    static constexpr MjItemKind VARIABLE{3};


    static constexpr MjItemKind COMMENT{4};
    static constexpr MjItemKind ANNOTATION{5};

    static constexpr MjItemKind DIRECTIVE{6};
    static constexpr MjItemKind IMPORT_DIRECTIVE{6};

    static constexpr MjItemKind STATEMENT{6};
    static constexpr MjItemKind BLOCK_STATEMENT{6};



    ///
    /// Built-in Types
    ///


    static constexpr MjItemKind VOID_TYPE{1};
    static constexpr MjItemKind TYPE_ALIAS{2};
    static constexpr MjItemKind ARRAY_TYPE{3};
    static constexpr MjItemKind BITFIELD_TYPE{4};
    static constexpr MjItemKind CLASS_TYPE{5};
    static constexpr MjItemKind FUNCTION_TYPE{6};
    static constexpr MjItemKind INTERFACE_TYPE{7};
    static constexpr MjItemKind METHOD_TYPE{8};
    static constexpr MjItemKind POINTER_TYPE{9};
    static constexpr MjItemKind SLICE_TYPE{10};
    static constexpr MjItemKind STRUCTURE_TYPE{11};
    static constexpr MjItemKind UNION_TYPE{12};
    static constexpr MjItemKind VARIANT_TYPE{13};
    static constexpr MjItemKind ENUMERATION_TYPE{14};
    static constexpr MjItemKind MODULE{16};
    static constexpr MjItemKind CONSTRUCTOR_TYPE{17};
    static constexpr MjItemKind DESTRUCTOR_TYPE{18};
    static constexpr MjItemKind OPERATOR_TYPE{19};
};


struct MjItemKind : public Enum<u8>, public MjItemKindValues<MjItemKind> {


    constexpr
    explicit
    MjItemKind(u8 id) noexcept : Enum(id) {}


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
};
