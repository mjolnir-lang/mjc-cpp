#pragma once

#include <mj/ast/MjStatement.hpp>


// A statement is a structured unit of execution.
class MjBreakStatement : public MjStatement {
private:
    MjExpression *_expression;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjBreakStatement() noexcept : MjStatement() {}


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
    bool has_depth() const noexcept {
        return _expression != nullptr;
    }


    constexpr
    const MjExpression *depth() const noexcept {
        return _expression;
    }


    constexpr
    MjExpression *depth() noexcept {
        return _expression;
    }


    ///
    /// Methods
    ///


    constexpr
    void set_depth(MjExpression *expression) {
        _expression = expression;
    }
};
