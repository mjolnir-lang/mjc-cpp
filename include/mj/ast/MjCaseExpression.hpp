#pragma once

#include <mj/ast/MjExpression.hpp>


class MjCaseExpression : public MjExpression {
private:
    MjStatement *_error_declaration;
    MjExpression *_body;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjCaseExpression(
        MjStatement *error,
        MjExpression *body,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjExpression(MjItemKind::CASE_EXPRESSION, tokens),
        _body(body)
    {}


    constexpr
    MjCaseExpression(
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjExpression(MjItemKind::CASE_EXPRESSION, tokens),
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
    bool has_error_type() const noexcept {
        return _body != nullptr;
    }


    constexpr
    bool has_error_variable() const noexcept {
        return _body != nullptr;
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
