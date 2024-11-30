#pragma once

#include <c/ast/CExpression.hpp>
#include <c/ast/CStatement.hpp>


class CForStatement : public CStatement {
private:
    CStatement &statement_;
    CBlockStatement &block_;
    CExpression &expression_;
    CExpression &condition_;
public:


    CForStatement(
        CExpression &expression,
        CExpression &condition,
        CStatement &statement,
        CBlockStatement &block
    ) :
        statement_(statement),
        condition_(condition),
        block_(block),
        expression_(expression)
    {}


    CStatementType statement_type() const {
        return CStatementType::FOR;
    }


    bool is_deterministic() const {
        return false;
    }


    CStatement &statement() {
        return statement_;
    }


    const CStatement &statement() const {
        return statement_;
    }


    CBlockStatement &block() {
        return block_;
    }


    const CBlockStatement &block() const {
        return block_;
    }


    CExpression &expression() {
        return expression_;
    }


    const CExpression &expression() const {
        return expression_;
    }
};
