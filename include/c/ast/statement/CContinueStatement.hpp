#pragma once

#include <c/ast/CStatement.hpp>


class CContinueStatement : public CStatement {
private:
    u32 depth_;
public:


    CContinueStatement(u32 depth) : depth_(depth) {}


    CStatementType statement_type() const {
        return CStatementType::CONTINUE;
    }


    u32 depth() const {
        return depth_;
    }


    bool is_deterministic() const {
        return true;
    }
};
