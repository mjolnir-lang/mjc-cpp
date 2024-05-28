#pragma once

#include <mj/ast/MjType.hpp>
#include <std/String.hpp>


class MjStringLiteral {
private:
    String _value;
    const MjToken *_definition;
public:


    constexpr
    MjStringLiteral(const MjToken *definition, String &&value) noexcept : _value(std::move(value)), _definition(definition) {}


    ///
    /// Properties
    ///


    constexpr
    MjType *type() const noexcept {
        return nullptr;
    }


    constexpr
    StringView value() const noexcept {
        return _value;
    }
};
