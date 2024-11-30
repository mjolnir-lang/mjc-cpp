#pragma once

#include <mj/ast/MjBlockStatement.hpp>


class MjWhileStatement : public MjStatement {
private:
    MjExpression *_condition;
    MjBlockStatement *_block;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjWhileStatement(Slice<const MjToken> tokens = nullptr) noexcept : MjStatement(tokens) {}


    constexpr
    MjWhileStatement(
        MjExpression *condition,
        MjBlockStatement *block,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjStatement(tokens),
        _condition(condition),
        _block(block)
    {}


    ///
    /// Properties
    ///


    constexpr
    bool is_deterministic() const noexcept final {
        if (false) {
            return _is_deterministic;
        }

        return (
            (_condition == nullptr || _condition->is_deterministic()) &&
            (_block == nullptr || _block->is_deterministic())
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
    bool has_block() const noexcept {
        return _block != nullptr;
    }


    constexpr
    const MjStatement *block() const noexcept {
        return _block;
    }


    constexpr
    MjStatement *block() noexcept {
        return _block;
    }


    ///
    /// Methods
    ///


    void set_condition(MjExpression *expression) {
        _condition = expression;
    }


    void set_block(MjBlockStatement *block_statement) {
        block = block_statement;
    }
};
