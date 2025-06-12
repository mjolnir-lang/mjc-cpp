#pragma once

#include <mj/ast/MjThenStatement.hpp>
#include <mj/ast/MjElseStatement.hpp>


class MjIfStatement : public MjStatement {
private:
    MjExpression *_condition;
    MjThenStatement *_then_statement;
    MjElseStatement *_else_statement;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjIfStatement(
        MjExpression *condition,
        MjThenStatement *then_statement,
        MjElseStatement *else_statement,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjStatement(MjItemKind::IF_STATEMENT, tokens),
        _condition(condition),
        _then_statement(then_statement),
        _else_statement(else_statement)
    {}


    constexpr
    MjIfStatement(
        MjExpression *condition,
        MjThenStatement *then_statement,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjStatement(MjItemKind::IF_STATEMENT, tokens),
        _condition(condition),
        _then_statement(then_statement),
        _else_statement(nullptr)
    {}


    constexpr
    MjIfStatement(
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjStatement(MjItemKind::IF_STATEMENT, tokens),
        _condition(nullptr),
        _then_statement(nullptr),
        _else_statement(nullptr)
    {}


    ///
    /// Shared Properties
    ///


    static
    constexpr
    bool is_type_of(const MjItem *item) {
        return item->item_kind() == MjItemKind::IF_STATEMENT;
    }


    ///
    /// Properties
    ///


    constexpr
    bool is_deterministic() const noexcept final {
        return (
            _condition->is_deterministic() &&
            _then_statement->is_deterministic() &&
            (
                _else_statement == nullptr ||
                _else_statement->is_deterministic()
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
    const MjThenStatement *then_statement() const noexcept {
        return _then_statement;
    }


    constexpr
    MjThenStatement *then_statement() noexcept {
        return _then_statement;
    }


    constexpr
    bool has_else_statement() const noexcept {
        return _else_statement != nullptr;
    }


    constexpr
    const MjElseStatement *else_statement() const noexcept {
        return _else_statement;
    }


    constexpr
    MjElseStatement *else_statement() noexcept {
        return _else_statement;
    }


    ///
    /// Methods
    ///


    void set_condition(MjExpression *expression) {
        _condition = expression;
    }


    void set_then_statement(MjThenStatement *statement) {
        _then_statement = statement;
    }


    void set_else_statement(MjElseStatement *statement) {
        _else_statement = statement;
    }
};
