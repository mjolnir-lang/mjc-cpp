#pragma once

#include <mj/ast/MjDefinition.hpp>
#include <mj/ast/MjFunctionParameterList.hpp>
#include <mj/ast/MjFunctionParameterListType.hpp>


class MjStatement;


/// @brief An `MjFunction` is an `MjStatement` object associated with a name and an `MjFunctionType`.
class MjFunctionDefinition : public MjDefinition {
private:
    MjStatement *_body;
    const MjToken *_name;
    MjFunctionParameterList *_parameter_list;
    MjFunctionParameterListType *_parameter_list_type;
public:


    constexpr
    MjFunctionDefinition(const MjToken *name, Slice<const MjToken> tokens = nullptr) noexcept :
        MjDefinition(tokens),
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
    const MjFunctionParameterList *parameter_list() const noexcept {
        return _parameter_list;
    }


    constexpr
    const MjFunctionParameterListType *parameter_list_type() const noexcept {
        return _parameter_list_type;
    }
};
