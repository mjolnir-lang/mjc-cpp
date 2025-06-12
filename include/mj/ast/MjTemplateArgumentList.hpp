#pragma once

#include <mj/ast/MjItem.hpp>


class MjTemplateArgumentList : public MjItem {
private:
    MjItem *_value;
public:


    constexpr
    MjTemplateArgumentList(std::nullptr_t = nullptr) noexcept : _value(nullptr) {}


    constexpr
    MjTemplateArgumentList(MjItem *value) noexcept : _value(value) {}
};
