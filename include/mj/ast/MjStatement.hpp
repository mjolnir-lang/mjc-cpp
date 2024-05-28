#pragma once

#include <mj/ast/MjExpression.hpp>


template<class MjStatementType>
struct MjStatementTypeValues {
    static constexpr MjStatementType BLOCK{0};
    static constexpr MjStatementType BREAK{1};
    static constexpr MjStatementType CONTINUE{2};
    static constexpr MjStatementType CLASS_DEFINITION{3};
    static constexpr MjStatementType DO{4};
    static constexpr MjStatementType DO_UNTIL{5};
    static constexpr MjStatementType DO_WHILE{6};
    static constexpr MjStatementType ENUMERATION_DEFINITION{7};
    static constexpr MjStatementType EXPRESSION{8};
    static constexpr MjStatementType FAIL{9};
    static constexpr MjStatementType FOR{10};
    static constexpr MjStatementType FOR_EACH{11};
    static constexpr MjStatementType IF{12};
    static constexpr MjStatementType IMPORT{13};
    static constexpr MjStatementType INTERFACE_DEFINITION{14};
    static constexpr MjStatementType MATCH{15};
    static constexpr MjStatementType RETURN{16};
    static constexpr MjStatementType STRUCTURE_DEFINITION{17};
    static constexpr MjStatementType UNTIL{18};
    static constexpr MjStatementType UNION_DEFINITION{19};
    static constexpr MjStatementType VARIABLE_DECLARATION{20};
    static constexpr MjStatementType VARIANT_DEFINITION{21};
    static constexpr MjStatementType WHILE{22};
    static constexpr MjStatementType YIELD{23};
};


class MjStatementType : public Enum<MjStatementType, u8>, public MjStatementTypeValues<MjStatementType> {
public:


    constexpr
    explicit
    MjStatementType(u8 id) noexcept : Enum(id) {}
};


// A statement is a structured unit of execution.
class MjStatement {
private:
    Vector<MjStatement *> _statements;
    MjExpression *_expression;
    union As {
        struct {
        } _block;
    } _as;
    Slice<const MjToken> _tokens;
    MjStatementType _type;
    bool _is_deterministic;
public:


    //constexpr
    //MjStatement(MjStatementType type, Slice<const MjToken> tokens) noexcept : _type(type), _tokens(tokens) {}
    constexpr
    MjStatement() noexcept {}


    ///
    /// Properties
    ///


    MjStatementType type() const noexcept {
        return _type;
    }


    Slice<const MjToken> tokens() const noexcept {
        return _tokens;
    }


    constexpr
    bool is_deterministic() const noexcept {
        if (false) {
            return _is_deterministic;
        }

        switch (_type) {
        case MjStatementType::BLOCK:
            for (const MjStatement *statement : _statements) {
                if (!statement->is_deterministic()) {
                    return false;
                }
            }

            return true;
        case MjStatementType::BREAK:
            return true;
        case MjStatementType::CONTINUE:
            return true;
        case MjStatementType::DO:
            for (const MjStatement *statement : _statements) {
                if (!statement->is_deterministic()) {
                    return false;
                }
            }

            return true;
        case MjStatementType::DO_UNTIL:
            for (const MjStatement *statement : _statements) {
                if (!statement->is_deterministic()) {
                    return false;
                }
            }

            return true;
        case MjStatementType::DO_WHILE:
            for (const MjStatement *statement : _statements) {
                if (!statement->is_deterministic()) {
                    return false;
                }
            }

            return true;
        case MjStatementType::EXPRESSION:
            return expression->is_deterministic();
        case MjStatementType::FAIL:
            return expression->is_deterministic();
        case MjStatementType::FOR:
            return true;
        case MjStatementType::IF:
            return (
                _condition->is_deterministic() &&
                _if_block->is_deterministic() &&
                (
                    _else_block == nullptr ||
                    _else_block->is_deterministic()
                )
            );
        case MjStatementType::IMPORT:
            return true;
        case MjStatementType::MATCH:
            return true;
        case MjStatementType::RETURN:
            return _expression == nullptr || _expression->is_deterministic();
        case MjStatementType::UNTIL:
            return true;
        case MjStatementType::VARIABLE_DECLARATION:
            return true;
        case MjStatementType::WHILE:
            return true;
        case MjStatementType::YIELD:
            return _expression == nullptr || _expression->is_deterministic();
        default:
            return false;
        }
    }


    const Vector<MjStatement *> &block_statements() const noexcept {
        return _statements;
    }


    Vector<MjStatement *> &block_statements() noexcept {
        return _statements;
    }


    MjStatement *do_block() noexcept {
        return _do_block;
    }


    const MjStatement *do_block() const noexcept {
        return _do_block;
    }


    MjStatement *until_block() noexcept {
        return _until_block;
    }


    const MjStatement *until_block() const noexcept {
        return _until_block;
    }


    MjExpression *condition() noexcept {
        return _condition;
    }


    const MjExpression *condition() const noexcept {
        return _condition;
    }


    u32 depth() const noexcept {
        return _depth;
    }


    const MjStatement *variable_declaration() const {
        return _variable_declaration;
    }


    MjStatement *variable_declaration() {
        return _variable_declaration;
    }


    const MjExpression *iterable_expression() const {
        return _iterable_expression;
    }


    MjExpression *iterable_expression() {
        return _iterable_expression;
    }


    const MjStatement *block_statement() const {
        return _block_statement;
    }


    MjStatement *block_statement() {
        return _block_statement;
    }


    const MjExpression *condition() const {
        return _condition;
    }


    MjExpression *condition() {
        return _condition;
    }


    const MjStatement *if_block() const {
        return _if_block;
    }


    MjStatement *if_block() {
        return _if_block;
    }


    const MjStatement *else_block() const {
        return _else_block;
    }


    MjStatement *else_block() {
        return _else_block;
    }


    const MjModule &module() const {
        return _module;
    }


    /// @brief Return the expression 
    const MjExpression *return_value() const {
        return _return_value;
    }


    MjExpression *return_value() {
        return _return_value;
    }


    ///
    /// Methods
    ///


    void set_type(MjStatementType type) noexcept {
        _type = type;
    }


    void set_tokens(Slice<const MjToken> tokens) noexcept {
        _tokens = tokens;
    }


    void set_return_value(MjExpression *value) {
        _return_value = value;
    }



    void set_condition(MjExpression *condition) {
        _condition = condition;
    }


    void set_if_block(MjStatement *if_block) {
        _if_block = if_block;
    }


    void set_else_block(MjStatement *else_block) {
        _else_block = else_block;
    }


    void set_variable_declaration(MjStatement *variable_declaration) {
        _variable_declaration;
    }


    void set_iterable_expression(MjExpression &iterable_expression) {
        _iterable_expression;
    }


    void set_block_statement(MjStatement *block_statement) {
        _block_statement = block_statement;
    }


    void set_depth(u32 depth) noexcept {
        _depth = depth;
    }
};
