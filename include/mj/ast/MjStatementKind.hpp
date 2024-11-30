#pragma once

#include <core/Enum.hpp>


template<class MjStatementKind>
struct MjStatementKindValues {
    static constexpr MjStatementKind BLOCK{0};
    static constexpr MjStatementKind BREAK{1};
    static constexpr MjStatementKind CONTINUE{2};
    static constexpr MjStatementKind CLASS_DEFINITION{3};
    static constexpr MjStatementKind DO{4};
    static constexpr MjStatementKind DO_UNTIL{5};
    static constexpr MjStatementKind DO_WHILE{6};
    static constexpr MjStatementKind ENUMERATION_DEFINITION{7};
    static constexpr MjStatementKind EXPRESSION{8};
    static constexpr MjStatementKind FAIL{9};
    static constexpr MjStatementKind FOR{10};
    static constexpr MjStatementKind FOR_EACH{11};
    static constexpr MjStatementKind IF{12};
    static constexpr MjStatementKind IF_ELSE{12};
    static constexpr MjStatementKind IMPORT{13};
    static constexpr MjStatementKind INTERFACE_DEFINITION{14};
    static constexpr MjStatementKind MATCH{15};
    static constexpr MjStatementKind RETURN{16};
    static constexpr MjStatementKind STRUCTURE_DEFINITION{17};
    static constexpr MjStatementKind UNTIL{18};
    static constexpr MjStatementKind UNION_DEFINITION{19};
    static constexpr MjStatementKind VARIABLE_DECLARATION{20};
    static constexpr MjStatementKind VARIANT_DEFINITION{21};
    static constexpr MjStatementKind WHILE{22};
    static constexpr MjStatementKind YIELD{23};
};


struct MjStatementKind : public Enum<u8>, public MjStatementKindValues<MjStatementKind> {

    constexpr
    explicit
    MjStatementKind(u8 id) noexcept : Enum(id) {}
};
