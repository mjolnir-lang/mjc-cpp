#pragma once

#include <c/ast/CStatement.hpp>


class CBreakStatement : public CStatement {
private:
    u32 depth_;
public:


    CBreakStatement(u32 depth) : depth_(depth) {}


    CStatementType statement_type() const {
        return CStatementType::BREAK;
    }


    bool is_deterministic() const {
        return false;
    }


    u32 depth() const {
        return depth_;
    }
};
