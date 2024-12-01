#pragma once

#include <mj/ast/MjToken.hpp>


template<class MjLexerState>
struct MjLexerStateValues {
    static constexpr MjLexerState NONE{0};
    static constexpr MjLexerState IN_ANNOTATION{5 << 1};
    static constexpr MjLexerState IN_TYPE_EXPRESSION{6 << 1};
    static constexpr MjLexerState IN_TYPE_CAST{7 << 1};
    static constexpr MjLexerState IN_PARENTHESES{8 << 1};
    static constexpr MjLexerState IN_SQUARE_BRACKETS{9 << 1};
    static constexpr MjLexerState IN_ANGLE_BRACKETS{10 << 1};
    static constexpr MjLexerState IN_CURLY_BRACES{11 << 1};
    static constexpr MjLexerState IN_SUBSHELL{12 << 1};
    static constexpr MjLexerState IN_SHELL{13 << 1};
};


struct MjLexerState : public Enum<u16>, public MjLexerStateValues<MjLexerState> {

    constexpr
    explicit
    MjLexerState(u16 id) noexcept : Enum(id) {}

    
    constexpr bool in_annotation() const noexcept { return _id & IN_ANNOTATION; }
    constexpr bool in_type_expression() const noexcept { return _id & IN_TYPE_EXPRESSION; }
    constexpr bool in_type_cast() const noexcept { return _id & IN_TYPE_CAST; }
    constexpr bool in_parentheses() const noexcept { return _id & IN_PARENTHESES; }
    constexpr bool in_square_brackets() const noexcept { return _id & IN_SQUARE_BRACKETS; }
    constexpr bool in_angle_brackets() const noexcept { return _id & IN_ANGLE_BRACKETS; }
    constexpr bool in_curly_braces() const noexcept { return _id & IN_CURLY_BRACES; }
    constexpr bool in_subshell() const noexcept { return _id & IN_SUBSHELL; }
    constexpr bool in_shell() const noexcept { return _id & IN_SHELL; }
};
