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


#include <c/ast/CBlockStatement.hpp>
#include <c/ast/CBreakStatement.hpp>
#include <c/ast/CContinueStatement.hpp>
#include <c/ast/CDoWhileStatement.hpp>
#include <c/ast/CForStatement.hpp>
#include <c/ast/CGotoStatement.hpp>
#include <c/ast/CIfStatement.hpp>
#include <c/ast/CSwitchStatement.hpp>
#include <c/ast/CReturnStatement.hpp>
#include <c/ast/CWhileStatement.hpp>
