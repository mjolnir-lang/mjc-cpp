#pragma once

#include <mj/ast/MjBlockStatement.hpp>


class MjUntilStatement : public MjStatement {
private:
    MjExpression *_condition;
    MjBlockStatement *_until_block;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjUntilStatement() noexcept : MjStatement() {}


    ///
    /// Properties
    ///


    constexpr
    bool is_deterministic() const noexcept final {
        if (false) {
            return _is_deterministic;
        }

        return (
            _condition->is_deterministic() &&
            (_until_block == nullptr || _until_block->is_deterministic())
        );
    }


    constexpr
    bool has_condition() const noexcept {
        return _condition != nullptr;
    }


    constexpr
    const MjExpression *condition() const noexcept {
        return _condition;
    }


    constexpr
    MjExpression *condition() noexcept {
        return _condition;
    }


    constexpr
    bool has_until_block() const noexcept {
        return _until_block != nullptr;
    }


    constexpr
    const MjStatement *until_block() const noexcept {
        return _until_block;
    }


    constexpr
    MjStatement *until_block() noexcept {
        return _until_block;
    }


    ///
    /// Methods
    ///


    void set_condition(MjExpression *expression) {
        _condition = expression;
    }


    void set_until_block(MjBlockStatement *block_statement) {
        _until_block = block_statement;
    }
};
