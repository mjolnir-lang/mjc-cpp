#pragma once

#include <mj/ast/MjTokenKind.hpp>


struct MjToken {
    u32 line;
    u16 offset;
    u8 size;
    MjTokenKind kind;


    constexpr
    MjToken() noexcept :
        line(0),
        offset(0),
        size(0),
        kind(MjTokenKind::NONE)
    {}


    constexpr
    MjToken(MjTokenKind type, u16 line, u16 offset, u8 size) noexcept :
        line(line),
        offset(offset),
        size(size),
        kind(type)
    {}


    constexpr
    bool operator==(const MjToken &other) const noexcept {
        return this->kind == other.kind;
    }


    constexpr
    bool operator==(MjToken &&other) const noexcept {
        return this->kind == other.kind;
    }


    constexpr
    bool operator!=(const MjToken &other) const noexcept {
        return this->kind != other.kind;
    }


    constexpr
    bool operator!=(MjToken &&other) const noexcept {
        return this->kind != other.kind;
    }
};
