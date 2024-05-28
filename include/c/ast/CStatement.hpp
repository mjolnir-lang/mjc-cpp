#pragma once

#include <c/ast/CToken.hpp>


enum class CStatementType : u8 {
    BLOCK,
    BREAK,
    CONTINUE,
    DO_WHILE,
    EXPRESSION,
    FOR,
    GOTO,
    IF,
    SWITCH,
    RETURN,
    WHILE,
};


// A statement is a structured unit of execution.
class CStatement {
public:


    virtual ~CStatement() = default;


    virtual CStatementType statement_type() const = 0;


    virtual bool is_deterministic() const = 0;
};


#include <c/ast/statement/CBlockStatement.hpp>
#include <c/ast/statement/CBreakStatement.hpp>
#include <c/ast/statement/CContinueStatement.hpp>
#include <c/ast/statement/CDoWhileStatement.hpp>
#include <c/ast/statement/CForStatement.hpp>
#include <c/ast/statement/CGotoStatement.hpp>
#include <c/ast/statement/CIfStatement.hpp>
#include <c/ast/statement/CSwitchStatement.hpp>
#include <c/ast/statement/CReturnStatement.hpp>
#include <c/ast/statement/CWhileStatement.hpp>
