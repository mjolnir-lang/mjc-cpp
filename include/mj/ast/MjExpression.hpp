#pragma once

#include <mj/ast/MjStatement.hpp>
#include <mj/ast/MjOperator.hpp>
#include <mj/ast/MjVariable.hpp>
#include <mj/ast/MjStringLiteral.hpp>
#include <mj/ast/MjNumberLiteral.hpp>
#include <mj/ast/MjType.hpp>


template<class MjExpressionType>
struct MjExpressionTypeValues {
    static constexpr MjExpressionType UNINITIALIZED{0};
    static constexpr MjExpressionType VARIABLE{1};
    static constexpr MjExpressionType FUNCTION_CALL{2};
    static constexpr MjExpressionType TYPE_EXPRESSION{3};
};


class MjExpressionType : public Enum<MjExpressionType, u8>, public MjExpressionTypeValues<MjExpressionType> {
private:
public:


    constexpr
    explicit
    MjExpressionType(u8 id) noexcept : Enum(id) {}
};


class MjExpression {
private:
    Slice<const MjToken> _tokens;
    union Data {
        MjVariable *_variable;
        MjType *_type_expression;
        struct {
            MjFunction *function;
            MjFunctionArgumentList *function_argument_list;
        } _function_call;

    
        constexpr
        Data(std::nullptr_t) noexcept : _variable(nullptr) {}

    
        constexpr
        Data(MjVariable *variable) noexcept : _variable(variable) {}


        constexpr
        Data(MjType *type_expression) noexcept : _type_expression(type_expression) {}


        constexpr
        Data(MjFunction *function, MjFunctionArgumentList *function_argument_list) noexcept :
            _function_call{function, function_argument_list}
        {}
    } _data;
    MjExpressionType _type;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjExpression(Slice<const MjToken> tokens) noexcept :
        _tokens(tokens),
        _data(nullptr),
        _type(MjExpressionType::UNINITIALIZED)
    {}


    constexpr
    MjExpression(
        Slice<const MjToken> tokens,
        MjFunction *function,
        MjFunctionArgumentList *function_argument_list
    ) noexcept :
        _tokens(tokens),
        _data(function, function_argument_list),
        _type(MjExpressionType::FUNCTION_CALL)
    {}


    constexpr
    MjExpression(Slice<const MjToken> tokens, MjVariable *variable) noexcept :
        _tokens(tokens),
        _data(variable),
        _type(MjExpressionType::VARIABLE)
    {}


    constexpr
    MjExpression(Slice<const MjToken> tokens, MjType *type_expression) noexcept :
        _tokens(tokens),
        _data(type_expression),
        _type(MjExpressionType::TYPE_EXPRESSION)
    {}


    ///
    /// Properties
    ///


    constexpr
    MjExpressionType type() const noexcept {
        return _type;
    }


    constexpr
    Slice<const MjToken> tokens() const noexcept {
        return _tokens;
    }


    constexpr
    bool is_deterministic() const noexcept {
        switch (_type) {
        case MjExpressionType::UNINITIALIZED: return true;
        case MjExpressionType::VARIABLE: return _data._variable->is_deterministic();
        case MjExpressionType::FUNCTION_CALL: return _data._function_call.function->is_deterministic(_data._function_call.function_argument_list);
        default: return false;
        }
    }


    constexpr
    const MjType *return_type() const noexcept {
        switch (_type) {
        case MjExpressionType::VARIABLE: return _data._variable->type();
        case MjExpressionType::FUNCTION_CALL: return _data._function_call.function->return_type();
        default: return nullptr;
        }
    }


    MjExpression *evaluate() const noexcept {
        switch (_type) {
        case MjExpressionType::VARIABLE: return _data._variable->evaluate();
        case MjExpressionType::FUNCTION_CALL: return _data._function_call.function->evaluate(_data._function_call.function_argument_list);
        default: return nullptr;
        }
    }
};
