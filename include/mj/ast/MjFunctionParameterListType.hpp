#pragma once

#include <mj/ast/MjType.hpp>


class MjFunctionParameterListType {
private:
    const MjFunctionParameterListType *_next;
    const MjType *_parameter_type;
public:


    constexpr
    MjFunctionParameterListType(
        const MjFunctionParameterListType *next,
        const MjType *parameter_type
    ) noexcept :
        _next(next),
        _parameter_type(parameter_type)
    {}


    constexpr
    MjFunctionParameterListType(std::nullptr_t = nullptr) noexcept :
        _next(this),
        _parameter_type(nullptr)
    {}


    ///
    /// Operators
    ///


    constexpr
    const MjType *operator[](u32 index) const noexcept {
        return index == 0 ? _parameter_type : (*_next)[index - 1];
    }


    ///
    /// Properties
    ///


    constexpr
    const MjFunctionParameterListType *next() const noexcept {
        return _next;
    }


    constexpr
    const MjType *parameter_type() const noexcept {
        return _parameter_type;
    }


    constexpr
    u32 size() const noexcept {
        return _next != this ? _next->size() : 1;
    }
};
