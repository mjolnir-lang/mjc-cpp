#pragma once

#include <c/ast/CExpression.hpp>
#include <c/ast/CStatement.hpp>


// A 'do-while' statement is a structured unit of conditional execution.
//
// do $statement while ($condition) while_block
class CDoWhileStatement : public CStatement {
private:
    CBlockStatement *do_block_;
    CBlockStatement *while_block_;
    CExpression *condition_;
public:


    CDoWhileStatement(
        CExpression &condition,
        CBlockStatement &do_block,
        CBlockStatement &while_block
    ) :
        do_block_(&do_block),
        while_block_(&while_block),
        condition_(&condition)
    {}


    CStatementType statement_type() const {
        return CStatementType::DO_WHILE;
    }


    bool is_deterministic() const {
        return false;
    }


    CBlockStatement &do_block() { return *do_block_; }
    const CBlockStatement &do_block() const { return *do_block_; }
    CBlockStatement &while_block() { return *while_block_; }
    const CBlockStatement &while_block() const { return *while_block_; }
    CExpression &condition() { return *condition_; }
    const CExpression &condition() const { return *condition_; }
};
