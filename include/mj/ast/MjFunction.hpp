#pragma once

#include <mj/ast/MjType.hpp>


using MjFunctionArgument = MjExpression;


using MjFunctionArgumentList = Vector<MjFunctionArgument *>;


class MjFunctionParameter : public MjVariable {
public:
    const MjType &type_;
    const MjToken *name_;
    MjExpression *default_value_;


    MjFunctionParameter(
        const MjType &type,
        const MjToken *name,
        MjExpression *default_value
    ) :
        type_(type),
        name_(name),
        default_value_(default_value)
    {}


    bool has_name() const {
        return name_ != nullptr;
    }


    bool has_default_value() const {
        return default_value_ != nullptr;
    }


    const MjToken &name() const {
        return *name_;
    }


    const MjType &type() const {
        return type_;
    }


    const MjExpression &default_value() const {
        return *default_value_;
    }


    MjExpression &default_value() {
        return *default_value_;
    }


    void set_default_value(MjExpression &expression) {
        default_value_ = &expression;
    }
};


using MjFunctionParameterList = Vector<MjFunctionParameter *>;


/// @brief An `MjFunction` is an `MjStatement` object associated with a name and an `MjFunctionType`.
class MjFunction {
private:
    MjType *_type;
    MjComment *_comment;
    MjStatement *_body;
    const MjToken *_name;
    Slice<const MjToken> _tokens;
    MjFunctionParameterList _parameter_list;
public:


    constexpr
    MjFunction(Slice<const MjToken> tokens, const MjToken *name) noexcept :
        _tokens(tokens),
        _name(name)
    {}


    ///
    /// Properties
    ///


    // The comment associated with the variable
    constexpr
    bool has_comment() const noexcept {
        return _comment != nullptr;
    }


    // The comment associated with the variable
    constexpr
    bool has_name() const noexcept {
        return _name != nullptr;
    }


    // The comment associated with the variable
    constexpr
    bool is_anonymous() const noexcept {
        return _name == nullptr;
    }


    // The comment associated with the variable
    constexpr
    MjComment *comment() const noexcept {
        return _comment;
    }


    // The variable name
    constexpr
    const MjToken *name() const noexcept {
        return _name;
    }


    // The function type
    constexpr
    MjType *type() const noexcept {
        return _type;
    }


    // The temporary sequence of tokens that make the definition
    constexpr
    MjStatement *body() const noexcept {
        return _body;
    }


    constexpr
    MjType *return_type() const noexcept {
        return _type ? _type->return_type() : nullptr;
    }


    constexpr
    bool is_constructor() const noexcept {
        return _type->is_constructor();
    }


    constexpr
    bool is_destructor() const noexcept {
        return _type->is_destructor();
    }


    constexpr
    bool is_operator() const noexcept {
        return _type->is_operator();
    }


    constexpr
    bool is_lambda() const noexcept {
        return _type->is_lambda();
    }


    constexpr
    bool is_operator() const noexcept {
        return _type->is_operator();
    }


    constexpr
    bool is_method() const noexcept {
        return _type->is_method();
    }


    constexpr
    bool is_deterministic(MjFunctionArgumentList *argument_list) const noexcept {
        if () {
            // deterministic for all arguments...
            return true;
        }

        if (is_method()) {
            return false;
        }

        for (MjFunctionArgument *argument : *argument_list) {
            if (!argument->is_deterministic()) {
                return false;
            }
        }

        return true;
    }


    constexpr
    MjFunctionParameterList *function_parameter_list() const noexcept {
        return _type->function_parameter_list();
    }
};
