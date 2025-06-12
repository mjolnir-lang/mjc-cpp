#pragma once

#include <mj/ast/MjExpression.hpp>


class MjDoWhileLoop : public MjStatement {
private:
    MjStatement *_unconditional_block;
    MjExpression *_condition;
    MjStatement *_conditional_block;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjDoWhileLoop(
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjStatement(MjItemKind::DO_WHILE_LOOP, tokens)
    {}


    constexpr
    MjDoWhileLoop(
        MjStatement *unconditional_block,
        MjExpression *condition,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjStatement(MjItemKind::DO_WHILE_LOOP, tokens),
        _unconditional_block(unconditional_block),
        _condition(condition),
        _conditional_block(nullptr)
    {}


    constexpr
    MjDoWhileLoop(
        MjStatement *unconditional_block,
        MjExpression *condition,
        MjStatement *conditional_block,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjStatement(MjItemKind::DO_WHILE_LOOP, tokens),
        _unconditional_block(unconditional_block),
        _condition(condition),
        _conditional_block(conditional_block)
    {}


    ///
    /// Properties
    ///


    constexpr
    bool is_deterministic() const noexcept final {
        return (_unconditional_block->is_deterministic() && (
            _condition == nullptr || (
            _condition->is_deterministic() && (
                _conditional_block == nullptr ||
                _conditional_block->is_deterministic()
        ))));
    }


    constexpr
    bool has_unconditional_block() const noexcept {
        return _unconditional_block != nullptr;
    }


    constexpr
    const MjStatement *unconditional_block() const noexcept {
        return _unconditional_block;
    }


    constexpr
    MjStatement *unconditional_block() noexcept {
        return _unconditional_block;
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
    bool has_condition_block() const noexcept {
        return _conditional_block != nullptr;
    }


    constexpr
    const MjStatement *conditional_block() const noexcept {
        return _conditional_block;
    }


    constexpr
    MjStatement *conditional_block() noexcept {
        return _conditional_block;
    }


    ///
    /// Methods
    ///


    void set_condition(MjExpression *expression) {
        _condition = expression;
    }


    void set_unconditional_block(MjStatement *block_statement) {
        _unconditional_block = block_statement;
    }


    void set_conditional_block(MjStatement *block_statement) {
        _conditional_block = block_statement;
    }
};
