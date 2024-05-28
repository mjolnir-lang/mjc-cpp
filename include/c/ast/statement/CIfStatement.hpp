#pragma once

#include <c/ast/CExpression.hpp>
#include <c/ast/CStatement.hpp>


// An 'if' statement is a structured unit of conditional execution.
//
// if ($condition) $statement else $else_statement
class CIfStatement : public CStatement {
private:
    CStatement &init_statement_;
    CExpression condition_;
    CBlockStatement if_block_;
    CBlockStatement else_block_;
public:


    CIfStatement(
        CStatement &init_statement,
        CExpression condition,
        CBlockStatement if_block,
        CBlockStatement else_block
    ) :
        init_statement_(init_statement),
        condition_(condition),
        if_block_(if_block),
        else_block_(else_block)
    {}


    CStatementType statement_type() const {
        return CStatementType::IF;
    }


    bool is_deterministic() const {
        return false;
    }


    const CExpression &condition() const {
        return condition_;
    }


    const CBlockStatement &if_block() const {
        return if_block_;
    }


    const CBlockStatement &else_block() const {
        return else_block_;
    }
};
