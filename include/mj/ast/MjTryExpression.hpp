#pragma once

#include <mj/ast/MjElseExpression.hpp>
#include <mj/ast/MjThenStatement.hpp>

#include <container/Vector.hpp>


/// A `try` expression is a structured expression which accepts a fallible expression as the primary
/// argument and one or more chained `catch`, `then`, or `else` expressions. The chain continues
/// until indentation decrements or an invalid expression.
///
/// ```
/// try FALLIBLE_EXPRESSION else DEFAULT_VALUE
/// try fun()
///     catch FileError => fail 2
///     catch Error error => fail error - 32
///     catch error => fail error
///     catch fail
///     else c -= 1
/// ```
class MjTryExpression : public MjExpression {
private:
    MjExpression *_expression;
    Vector<MjExpression *> _catch_expressions;
    MjThenStatement *_then_statement;
    MjElseExpression *_else_expression;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjTryExpression(
        MjExpression *expression,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjExpression(MjItemKind::TRY_EXPRESSION, tokens),
        _expression(expression)
    {}


    constexpr
    MjTryExpression(
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjExpression(MjItemKind::TRY_EXPRESSION, tokens),
        _expression(nullptr)
    {}


    ///
    /// Properties
    ///


    constexpr
    bool is_deterministic() const noexcept final {
        return _expression->is_deterministic();
    }


    constexpr
    const MjType *result_type() const noexcept final {
        return _expression->result_type();
    }


    constexpr
    const MjType *result_type(const MjType *expected_type) const noexcept final {
        return _expression->result_type(expected_type);
    }


    constexpr
    bool has_expression() const noexcept {
        return _expression != nullptr;
    }


    constexpr
    const MjExpression *expression() const noexcept {
        return _expression;
    }


    constexpr
    MjExpression *expression() noexcept {
        return _expression;
    }


    constexpr
    bool has_then_statement() const noexcept {
        return _then_statement != nullptr;
    }


    constexpr
    const MjThenStatement *then_statement() const noexcept {
        return _then_statement;
    }


    constexpr
    MjThenStatement *then_statement() noexcept {
        return _then_statement;
    }


    constexpr
    bool has_catch_expressions() const noexcept {
        return !_catch_expressions.empty();
    }


    constexpr
    Slice<const MjExpression *const> catch_expressions() const noexcept {
        return {_catch_expressions.data(), _catch_expressions.size()};
    }


    constexpr
    bool has_else_expression() const noexcept {
        return _else_expression != nullptr;
    }


    constexpr
    const MjElseExpression *else_expression() const noexcept {
        return _else_expression;
    }


    constexpr
    MjElseExpression *else_expression() noexcept {
        return _else_expression;
    }


    ///
    /// Methods
    ///


    void set_expression(MjExpression *expression) {
        _expression = expression;
    }
};
