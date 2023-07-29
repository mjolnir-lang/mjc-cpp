#pragma once

#include "mj/ast/MjToken.hpp"


enum class MjStatementType : u8 {
    BLOCK,
    BREAK,
    CONTINUE,
    DO,
    DO_UNTIL,
    DO_WHILE,
    EXPRESSION,
    FOR,
    FOR_EACH,
    IF,
    IMPORT,
    MATCH,
    RETURN,
    UNTIL,
    WHILE,
    YIELD,
};


// A statement is a structured unit of execution.
class MjStatement {
public:


    virtual ~MjStatement() = default;


    virtual MjStatementType statement_type() const = 0;


    virtual bool is_deterministic() const = 0;
};


#include "mj/ast/statement/MjBlockStatement.hpp"
#include "mj/ast/statement/MjBreakStatement.hpp"
#include "mj/ast/statement/MjContinueStatement.hpp"
#include "mj/ast/statement/MjDoStatement.hpp"
#include "mj/ast/statement/MjDoWhileStatement.hpp"
#include "mj/ast/statement/MjDoUntilStatement.hpp"
#include "mj/ast/statement/MjForStatement.hpp"
#include "mj/ast/statement/MjForEachStatement.hpp"
#include "mj/ast/statement/MjIfStatement.hpp"
#include "mj/ast/statement/MjImportStatement.hpp"
#include "mj/ast/statement/MjMatchStatement.hpp"
#include "mj/ast/statement/MjReturnStatement.hpp"
#include "mj/ast/statement/MjUntilStatement.hpp"
#include "mj/ast/statement/MjWhileStatement.hpp"
#include "mj/ast/statement/MjYieldStatement.hpp"
