#pragma once

#include <mj/ast/MjStatement.hpp>


// A statement is a structured unit of execution.
class MjYieldStatement : public MjStatement {
private:
    MjExpression *_result;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjYieldStatement(Slice<const MjToken> tokens = nullptr) noexcept : MjStatement(tokens) {}


    constexpr
    MjYieldStatement(MjExpression *result, Slice<const MjToken> tokens = nullptr) noexcept :
        MjStatement(tokens),
        _result(result)
    {}



    ///
    /// Properties
    ///


    constexpr
    bool is_deterministic() const noexcept final {
        if (false) {
            return _is_deterministic;
        }

        return _result == nullptr || _result->is_deterministic();
    }


    constexpr
    bool has_yield_value() const noexcept {
        return _result != nullptr;
    }


    constexpr
    const MjExpression *yield_value() const noexcept {
        return _result;
    }


    constexpr
    MjExpression *yield_value() noexcept {
        return _result;
    }


    ///
    /// Methods
    ///


    constexpr
    void set_yield_value(MjExpression *expression) {
        _result = expression;
    }
};
