#pragma once

#include <c/ast/CStatement.hpp>


class CGotoStatement : public CStatement {
private:
    u32 depth_;
public:


    CGotoStatement(u32 depth) : depth_(depth) {}


    CStatementType statement_type() const {
        return CStatementType::GOTO;
    }


    bool is_deterministic() const {
        return false;
    }


    u32 depth() const {
        return depth_;
    }
};
