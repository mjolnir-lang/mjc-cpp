#pragma once

#include <mj/ast/MjToken.hpp>


/// lexical errors (invalid tokens, unterminated string literals, invalid numbers, invalid identifiers, invalid operators)
// Lexical    Lexer    Scanner
// Syntax     Parser
// Semantics  Lexer
class MjLexerError {
private:
    MjToken _token;
    StringView _message;
public:


    constexpr
    MjLexerError(MjToken token, StringView message) noexcept :
        _token(token),
        _message(message)
    {}
};


/*
template<class MjLexerError>
struct MjLexerErrorValues {
    static constexpr MjLexerError AA{0};
};


class MjLexerError : public Enum<u8>, public MjLexerErrorValues<MjLexerError> {
private:
    static
    constexpr
    struct Data {
        StringView message;
        u32 args;
    } DATA[] {
        {"", 0},
        {"", 0},
        {"", 0},
        {"", 0},
        {"", 0},
        {"", 0},
        {"", 0},
        {"", 0},
        {"", 0},
        {"", 0},
        {"", 0},
        {"", 0},
        {"", 0},
        {"", 0},
    };
public:


    constexpr
    explicit
    MjLexerError(u16 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    constexpr
    StringView message() const noexcept {}
};
*/
