#pragma once

#include <c/ast/CStatement.hpp>


class CBlockStatement : public CStatement {
private:
    Vector<CStatement *> statements_;
public:


    CBlockStatement() {}


    CStatementType statement_type() const {
        return CStatementType::BLOCK;
    }


    Vector<CStatement *> &statements() {
        return statements_;
    }


    bool is_deterministic() const {
        return false;
    }


    const Vector<CStatement *> &statements() const {
        return statements_;
    }
};
