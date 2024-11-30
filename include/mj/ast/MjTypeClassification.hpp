#pragma once

#include <core/Enum.hpp>


template<class MjTypeClassification>
struct MjTypeClassificationValues {
    static constexpr MjTypeClassification FUNDAMENTAL{0};
    static constexpr MjTypeClassification VOID{1};
    static constexpr MjTypeClassification NULL_POINTER{2};
    static constexpr MjTypeClassification ARITHMETIC{3};
    static constexpr MjTypeClassification BOOL{};
    static constexpr MjTypeClassification BITFIELD{};
    static constexpr MjTypeClassification CLASS{};
    static constexpr MjTypeClassification UNION{};
    static constexpr MjTypeClassification ENUMERATION{};
    static constexpr MjTypeClassification INTERFACE{};
    static constexpr MjTypeClassification POINTER{};
    static constexpr MjTypeClassification ARRAY{};
    static constexpr MjTypeClassification SLICE{};
    static constexpr MjTypeClassification COMPOSITE{};
    static constexpr MjTypeClassification COMPOUND{};
    static constexpr MjTypeClassification INTEGER{};
    static constexpr MjTypeClassification FLOATING_POINT{};
    static constexpr MjTypeClassification SIGNED{};
    static constexpr MjTypeClassification UNSIGNED{};
    static constexpr MjTypeClassification INTEGRAL{};
    static constexpr MjTypeClassification REFERENCE{};
    static constexpr MjTypeClassification FUNCTION{};
    static constexpr MjTypeClassification STRUCTURE{};
    static constexpr MjTypeClassification VARIANT{};
    static constexpr MjTypeClassification OBJECT{};
    static constexpr MjTypeClassification SCALAR{};
    static constexpr MjTypeClassification VALUE{};
    static constexpr MjTypeClassification DERIVED{};
};


class MjTypeClassification : public Enum<u8>, public MjTypeClassificationValues<MjTypeClassification> {
public:


    constexpr
    explicit
    MjTypeClassification(u8 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    /// Return true if the type is .
    constexpr
    bool is_fundamental() const noexcept {
        return _id & MjTypeClassification::FUNDAMENTAL;
    }


    constexpr
    bool is_compound() const noexcept {
        return _id & MjTypeClassification::COMPOUND;
    }


    constexpr
    bool is_void() const noexcept {
        return _id & MjTypeClassification::VOID;
    }


    constexpr
    bool is_null_pointer() const noexcept {
        return _id & MjTypeClassification::NULL_POINTER;
    }


    constexpr
    bool is_pointer() const noexcept {
        return _id & MjTypeClassification::POINTER;
    }


    constexpr
    bool is_arithmetic() const noexcept {
        return _id & MjTypeClassification::ARITHMETIC;
    }


    constexpr
    bool is_integral() const noexcept {
        return _id & MjTypeClassification::INTEGRAL;
    }


    constexpr
    bool is_floating_point() const noexcept {
        return _id & MjTypeClassification::FLOATING_POINT;
    }


    constexpr
    bool is_function() const noexcept {
        return _id & MjTypeClassification::FUNCTION;
    }


    constexpr
    bool is_reference() const noexcept {
        return _id & MjTypeClassification::REFERENCE;
    }


    constexpr
    bool is_array() const noexcept {
        return _id & MjTypeClassification::ARRAY;
    }


    constexpr
    bool is_slice() const noexcept {
        return _id & MjTypeClassification::SLICE;
    }


    constexpr
    bool is_class() const noexcept {
        return _id & MjTypeClassification::CLASS;
    }


    constexpr
    bool is_union() const noexcept {
        return _id & MjTypeClassification::UNION;
    }


    constexpr
    bool is_structure() const noexcept {
        return _id & MjTypeClassification::STRUCTURE;
    }


    constexpr
    bool is_enumeration() const noexcept {
        return _id & MjTypeClassification::ENUMERATION;
    }


    constexpr
    bool is_variant() const noexcept {
        return _id & MjTypeClassification::VARIANT;
    }


    constexpr
    bool is_interface() const noexcept {
        return _id & MjTypeClassification::INTERFACE;
    }
};
