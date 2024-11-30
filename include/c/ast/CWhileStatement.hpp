#pragma once

#include <c/ast/CExpression.hpp>
#include <c/ast/CStatement.hpp>


// A 'while' statement is a structured unit of conditional execution.
//
// while (CONDITION) STATEMENT
class CWhileStatement : public CStatement {
private:
    CBlockStatement block_;
    CExpression &condition_;
public:


    CWhileStatement(
        CExpression &condition,
        CBlockStatement block
    ) :
        block_(block),
        condition_(condition)
    {}


    CStatementType statement_type() const {
        return CStatementType::WHILE;
    }


    bool is_deterministic() const {
        return false;
    }


    const CExpression &condition() const {
        return condition_;
    }


    const CBlockStatement &block() const {
        return block_;
    }
};
