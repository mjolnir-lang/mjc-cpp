#pragma once

#include <mj/ast/MjElseStatement.hpp>
#include <mj/ast/MjThenStatement.hpp>

#include <container/Vector.hpp>


/// A `try` statement is a structured statement which accepts a fallible statement as the primary
/// argument and one or more chained `catch`, `then`, or `else` statements. The chain continues
/// until indentation decrements or an invalid statement.
///
/// ```
/// try {
///     fun()
/// } else {
///     // handle errors
/// }
/// ```
class MjTryStatement : public MjStatement {
private:
    MjStatement *_body;
    Vector<MjStatement *> _catch_statements;
    MjThenStatement *_then_statement;
    MjElseStatement *_else_statement;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjTryStatement(
        MjStatement *body,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjStatement(MjItemKind::TRY_STATEMENT, tokens),
        _body(body)
    {}


    constexpr
    MjTryStatement(
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjStatement(MjItemKind::TRY_STATEMENT, tokens),
        _body(nullptr)
    {}


    ///
    /// Properties
    ///


    constexpr
    bool is_deterministic() const noexcept final {
        return _body->is_deterministic();
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


    constexpr
    bool has_then_statement() const noexcept {
        return _then_statement != nullptr;
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
    bool has_catch_statements() const noexcept {
        return !_catch_statements.empty();
    }


    constexpr
    Slice<const MjStatement *const> catch_statements() const noexcept {
        return {_catch_statements.data(), _catch_statements.size()};
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


    void set_body(MjStatement *body) {
        _body = body;
    }
};
