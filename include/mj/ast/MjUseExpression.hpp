#pragma once

#include <mj/ast/MjExpression.hpp>


/// A `use` expression is a structured expression which accepts a fallible expression as the primary
/// argument and removes the fallible type qualifier from the result type.
///
/// ```
/// use FALLIBLE_EXPRESSION
/// ```
class MjUseExpression : public MjExpression {
private:
    MjExpression *_expression;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjUseExpression(
        MjExpression *expression,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjExpression(MjItemKind::USE_EXPRESSION, tokens),
        _expression(expression)
    {}


    constexpr
    MjUseExpression(
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjExpression(MjItemKind::USE_EXPRESSION, tokens),
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


    ///
    /// Methods
    ///


    void set_expression(MjExpression *expression) {
        _expression = expression;
    }
};
