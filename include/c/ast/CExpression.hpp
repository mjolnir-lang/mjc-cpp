#pragma once

#include <c/ast/CStatement.hpp>
#include <c/ast/COperator.hpp>
#include <c/ast/CType.hpp>


// An expression is a structured unit of evaluation.
struct CExpression : public CStatement {
protected:
    Vector<CExpression> terms_; // The terms of the expression
    const COperator &op_;          // The operator of the expression
    bool is_deterministic_ = false; // If true, the expression is deterministic
public:


    CExpression(
        const COperator &op
    ) :
        op_(op)
    {}
public:


    const CType &type() const {
        return op_.type();
    }


    CStatementType statement_type() const {
        return CStatementType::EXPRESSION;
    }


    bool is_deterministic() const {
        return is_deterministic_;
    }


    const CExpression &reduce() const {
        return *this;
    }


    const CExpression &evaluate() const {
        return *this;
    }
};
