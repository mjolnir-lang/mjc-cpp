#pragma once

#include <c/ast/CExpression.hpp>
#include <c/ast/CStatement.hpp>


struct CWhenStatement {
    CExpression &condition;
    CStatement &statement;
};


class CSwitchStatement : public CStatement {
private:
    Vector<CWhenStatement> cases_;
    CExpression &expression_;
public:


    CSwitchStatement(CExpression &expression) : expression_(expression) {}


    CStatementType statement_type() const {
        return CStatementType::SWITCH;
    }
};
