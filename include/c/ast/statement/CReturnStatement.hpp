#pragma once

#include <c/ast/CExpression.hpp>
#include <c/ast/CStatement.hpp>


// return $value;
class CReturnStatement : public CStatement {
private:
    CExpression value_;
public:


    CReturnStatement(
        CExpression value
    ) :
        value_(value)
    {}


    CStatementType statement_type() const {
        return CStatementType::RETURN;
    }


    bool is_deterministic() const {
        return false;
    }


    const CExpression &value() const {
        return value_;
    }
};
