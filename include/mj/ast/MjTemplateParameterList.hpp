#pragma once

#include <mj/ast/MjDeclaration.hpp>


class MjTemplateParameterList : public MjItem {
private:
    MjDeclaration *_value;
public:


    constexpr
    MjTemplateParameterList(std::nullptr_t = nullptr) noexcept : _value(nullptr) {}


    constexpr
    MjTemplateParameterList(MjDeclaration *value) noexcept : _value(value) {}
};
