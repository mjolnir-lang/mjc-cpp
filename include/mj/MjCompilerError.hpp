#pragma once

#include <core/StringView.hpp>


/*
// semantic error (types, operators, math, templates, usages, missing, duplicate)
class MjCompilerError {
private:
    StringView _message;
public:


    constexpr
    MjCompilerError(StringView message) noexcept : _message(message) {}
};
*/


template<class MjCompilerError>
struct MjCompilerErrorValues {
    static constexpr MjCompilerError AA{0};
};


class MjCompilerError : public Enum<u8>, public MjCompilerErrorValues<MjCompilerError> {
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
    MjCompilerError(u16 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    constexpr
    StringView message() const noexcept {}
};
