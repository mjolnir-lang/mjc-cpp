#pragma once

#include <mj/ast/MjFunction.hpp>
#include <mj/ast/MjMethodType.hpp>


/// A method is a member function belonging to an instance of a type, usually a class or an
/// interface.
class MjMethod {
private:
    StringView _name;
    MjMethodType *_type;
    MjBlockStatement *_body;
    MjExpression *_expression;
public:


    constexpr
    MjMethod(StringView name, MjMethodType *type, MjBlockStatement *body) noexcept :
        _name(name), _type(type), _body(body)
    {}


    constexpr
    MjMethod(StringView name, MjMethodType *type, MjExpression *expression) noexcept :
        _name(name), _type(type), _expression(expression)
    {}


    ///
    /// Properties
    ///


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


    // The variable name
    constexpr
    const MjToken *name() const noexcept {
        return _name;
    }


    // The temporary sequence of tokens that make the definition
    constexpr
    MjBlockStatement *body() const noexcept {
        return _body;
    }


    constexpr
    bool is_constructor() const noexcept {
        return false;
    }


    constexpr
    bool is_destructor() const noexcept {
        return false;
    }


    constexpr
    bool is_operator() const noexcept {
        return false;
    }


    constexpr
    bool is_lambda() const noexcept {
        return false;
    }


    constexpr
    bool is_method() const noexcept {
        return true;
    }

    constexpr
    bool is_deterministic(MjFunctionArgumentList *argument_list) const noexcept {
        for (MjFunctionArgument *argument : *argument_list) {
            if (!argument->is_deterministic()) {
                return false;
            }
        }

        return true;
    }
};
