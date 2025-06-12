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
    MjReturnStatement(MjItemInfo item_info) noexcept : MjStatement(item_info) {}


    constexpr
    MjReturnStatement(MjItemInfo item_info, MjExpression *result) noexcept :
        MjStatement(item_info),
        _result(result)
    {}


    ///
    /// Properties
    ///


    constexpr
    bool is_deterministic() const noexcept final {
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
