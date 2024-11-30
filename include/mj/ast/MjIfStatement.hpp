#pragma once

#include <mj/ast/MjBlockStatement.hpp>


class MjIfStatement : public MjStatement {
private:
    MjExpression *_condition;
    MjBlockStatement *_then_block;
    MjStatement *_else_block;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjIfStatement(Slice<const MjToken> tokens = nullptr) noexcept : MjStatement(tokens) {}


    constexpr
    MjIfStatement(
        MjExpression *condition,
        MjBlockStatement *then_block,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjStatement(tokens),
        _condition(condition),
        _then_block(then_block),
        _else_block(nullptr)
    {}


    constexpr
    MjIfStatement(
        MjExpression *condition,
        MjBlockStatement *then_block,
        MjStatement *else_block,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjStatement(tokens),
        _condition(condition),
        _then_block(then_block),
        _else_block(else_block)
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
            _condition->is_deterministic() &&
            _then_block->is_deterministic() &&
            (
                _else_block == nullptr ||
                _else_block->is_deterministic()
            )
        );
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
    const MjBlockStatement *then_block() const noexcept {
        return _then_block;
    }


    constexpr
    MjBlockStatement *then_block() noexcept {
        return _then_block;
    }


    constexpr
    bool has_else_block() const noexcept {
        return _else_block != nullptr;
    }


    constexpr
    const MjStatement *else_block() const noexcept {
        return _else_block;
    }


    constexpr
    MjStatement *else_block() noexcept {
        return _else_block;
    }


    ///
    /// Methods
    ///


    void set_condition(MjExpression *expression) {
        _condition = expression;
    }


    void set_then_block(MjBlockStatement *block_statement) {
        _then_block = block_statement;
    }


    void set_else_block(MjBlockStatement *block_statement) {
        _else_block = block_statement;
    }


    void set_else_block(MjIfStatement *if_statement) {
        _else_block = if_statement;
    }
};
