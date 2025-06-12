#pragma once

#include <mj/ast/MjExpression.hpp>


class MjElseExpression : public MjExpression {
private:
    MjExpression *_body;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjElseExpression(
        MjExpression *body,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjExpression(MjItemKind::ELSE_EXPRESSION, tokens),
        _body(body)
    {}


    constexpr
    MjElseExpression(
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjExpression(MjItemKind::ELSE_EXPRESSION, tokens),
        _body(nullptr)
    {}


    ///
    /// Properties
    ///


    constexpr
    bool is_deterministic() const noexcept final {
        return _body->is_deterministic();
    }


    constexpr
    bool has_body() const noexcept {
        return _body != nullptr;
    }


    constexpr
    const MjExpression *body() const noexcept {
        return _body;
    }


    constexpr
    MjExpression *body() noexcept {
        return _body;
    }


    ///
    /// Methods
    ///


    void set_body(MjExpression *expression) {
        _body = expression;
    }
};
