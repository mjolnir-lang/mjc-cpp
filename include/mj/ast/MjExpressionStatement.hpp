#pragma once

#include <mj/ast/MjStatement.hpp>


// A statement is a structured unit of execution.
class MjExpressionStatement : public MjStatement {
private:
    MjExpression *_expression;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjExpressionStatement() noexcept : MjStatement() {}


    ///
    /// Properties
    ///


    constexpr
    bool is_deterministic() const noexcept final {
        if (false) {
            return _is_deterministic;
        }

        return _expression == nullptr || _expression->is_deterministic();
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


    constexpr
    void set_expression(MjExpression *expression) {
        _expression = expression;
    }
};
