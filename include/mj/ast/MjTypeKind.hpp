#pragma once

#include <core/Enum.hpp>


template<class MjTypeKind>
struct MjTypeKindValues {
    static constexpr MjTypeKind UNKNOWN{0};
    static constexpr MjTypeKind VOID{1};
    static constexpr MjTypeKind ALIAS{2};
    static constexpr MjTypeKind ARRAY{3};
    static constexpr MjTypeKind BITFIELD{4};
    static constexpr MjTypeKind CLASS{5};
    static constexpr MjTypeKind FUNCTION{6};
    static constexpr MjTypeKind INTERFACE{7};
    static constexpr MjTypeKind METHOD{8};
    static constexpr MjTypeKind POINTER{9};
    static constexpr MjTypeKind SLICE{10};
    static constexpr MjTypeKind STRUCTURE{11};
    static constexpr MjTypeKind UNION{12};
    static constexpr MjTypeKind VARIANT{13};
    static constexpr MjTypeKind ENUMERATION{14};
    static constexpr MjTypeKind MODULE{16};
    static constexpr MjTypeKind CONSTRUCTOR{17};
    static constexpr MjTypeKind DESTRUCTOR{18};
    static constexpr MjTypeKind OPERATOR{19};
    static constexpr MjTypeKind QUALIFIED{20};
};


class MjTypeKind : public Enum<u8>, public MjTypeKindValues<MjTypeKind> {
public:


    constexpr
    explicit
    MjTypeKind(u8 id) noexcept : Enum(id) {}


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
