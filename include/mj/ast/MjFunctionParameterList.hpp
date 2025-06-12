#pragma once

#include <mj/ast/MjVariable.hpp>
#include <mj/ast/MjExpression.hpp>


class MjFunctionParameterList : public MjItem {
private:
    MjVariable *_variable;
    MjExpression *_default_value;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjFunctionParameterList(MjVariable *variable, MjExpression *default_value = nullptr) noexcept :
        _variable(variable),
        _default_value(default_value)
    {}


    ///
    /// Properties
    ///


    constexpr
    const MjVariable *variable() const noexcept {
        return _variable;
    }


    constexpr
    MjVariable *variable() noexcept {
        return _variable;
    }


    constexpr
    bool has_default_value() const noexcept {
        return _default_value != nullptr;
    }


    constexpr
    const MjExpression *default_value() const noexcept {
        return _default_value;
    }


    constexpr
    MjExpression *default_value() noexcept {
        return _default_value;
    }


    ///
    /// Methods
    ///


    constexpr
    void set_default_value(MjExpression *expression) noexcept {
        _default_value = expression;
    }
};
