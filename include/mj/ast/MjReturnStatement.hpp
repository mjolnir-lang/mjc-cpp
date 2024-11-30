#pragma once

#include <mj/ast/MjStatement.hpp>


// A statement is a structured unit of execution.
class MjReturnStatement : public MjStatement {
private:
    MjExpression *_result;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjReturnStatement(Slice<const MjToken> tokens = nullptr) noexcept : MjStatement(tokens) {}


    constexpr
    MjReturnStatement(MjExpression *result, Slice<const MjToken> tokens = nullptr) noexcept :
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
    bool has_return_value() const noexcept {
        return _result != nullptr;
    }


    constexpr
    const MjExpression *return_value() const noexcept {
        return _result;
    }


    constexpr
    MjExpression *return_value() noexcept {
        return _result;
    }


    ///
    /// Methods
    ///


    constexpr
    void set_return_value(MjExpression *expression) {
        _result = expression;
    }
};
