#pragma once

#include <mj/ast/MjBlockStatement.hpp>
#include <mj/ast/MjExpression.hpp>


class MjUntilLoop : public MjStatement {
private:
    MjExpression *_condition;
    MjStatement *_body;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjUntilLoop(
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjStatement(MjItemKind::UNTIL_LOOP, tokens)
    {}


    constexpr
    MjUntilLoop(
        MjExpression *condition,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjStatement(MjItemKind::UNTIL_LOOP, tokens),
        _condition(condition),
        _body(nullptr)
    {}


    constexpr
    MjUntilLoop(
        MjExpression *condition,
        MjStatement *body,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjStatement(MjItemKind::UNTIL_LOOP, tokens),
        _condition(condition),
        _body(body)
    {}


    ///
    /// Properties
    ///


    constexpr
    bool is_deterministic() const noexcept final {
        return (
            _condition->is_deterministic() &&
            (_body == nullptr || _body->is_deterministic())
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
    bool has_body() const noexcept {
        return _body != nullptr;
    }


    constexpr
    const MjStatement *body() const noexcept {
        return _body;
    }


    constexpr
    MjStatement *body() noexcept {
        return _body;
    }


    ///
    /// Methods
    ///


    void set_condition(MjExpression *expression) {
        _condition = expression;
    }


    void set_body(MjStatement *block_statement) {
        _body = block_statement;
    }
};
