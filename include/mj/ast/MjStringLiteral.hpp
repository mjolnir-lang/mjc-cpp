#pragma once

#include <mj/ast/MjExpression.hpp>
#include <core/String.hpp>


class MjStringLiteral : public MjExpression {
private:
    StringView _value;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjStringLiteral(StringView value, Slice<const MjToken> tokens = nullptr) noexcept :
        MjExpression(tokens), _value(value)
    {}


    ///
    /// Properties
    ///


    bool is_deterministic() const noexcept final {
        return true;
    }


    const MjType *result_type() const noexcept final {
        return MjTypePool::get("string_literal");
    }


    constexpr
    StringView value() const noexcept {
        return _value;
    }
};
