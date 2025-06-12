#pragma once

#include <mj/ast/MjBlockStatement.hpp>
#include <mj/ast/MjExpression.hpp>

#include <container/Vector.hpp>


// A statement is a structured unit of execution.
class MjBlockExpression : public MjExpression {
private:
    MjBlockStatement *_body;
    MjExpression *_result_expression;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjBlockExpression(
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjExpression(MjItemKind::BLOCK_EXPRESSION, tokens)
    {}


    ///
    /// Properties
    ///


    constexpr
    bool is_deterministic() const noexcept final {
        return _body->is_deterministic() && _result_expression->is_deterministic();
    }


    constexpr
    const MjBlockStatement *body() const noexcept {
        return _body;
    }


    constexpr
    MjBlockStatement *body() noexcept {
        return _body;
    }
};
