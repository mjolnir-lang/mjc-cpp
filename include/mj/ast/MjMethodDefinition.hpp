#pragma once

#include <mj/ast/MjDefinition.hpp>
#include <mj/ast/MjFunctionParameterList.hpp>


class MjBlockStatement;


/// @brief An `MjFunction` is an `MjStatement` object associated with a name and an `MjFunctionType`.
class MjMethodDefinition : public MjDefinition {
private:
    MjBlockStatement *_body;
    const MjToken *_name;
    MjFunctionParameterList _parameter_list;
public:


    constexpr
    MjMethodDefinition(const MjToken *name, Slice<const MjToken> tokens = nullptr) noexcept :
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
};
