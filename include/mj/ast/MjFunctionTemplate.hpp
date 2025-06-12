#pragma once

#include <mj/ast/MjTemplate.hpp>
#include <mj/ast/MjStatement.hpp>
#include <mj/ast/MjFunctionTypeTemplate.hpp>


/// @brief A function template is a template of a function.
class MjFunctionTemplate : public MjTemplate {
    MjFunctionType *_type;
    MjStatement *_body;
    MjToken _name;
    MjFunctionParameterList _parameter_list;
public:


    constexpr
    MjFunctionTemplate(MjToken name, Slice<const MjToken> tokens = nullptr) noexcept :
        MjTemplate(MjItemKind::FUNCTION_TYPE, tokens),
        _name(name)
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
