#pragma once

#include <mj/ast/MjTemplateArgumentKind.hpp>


class MjType;
class MjVariable;
class MjTemplate;


class MjTemplateArgument {
private:

    union Value {
        MjType *_type;
        MjVariable *_variable;
        MjTemplate *_template;


        constexpr
        Value(std::nullptr_t = nullptr) noexcept : _type(nullptr) {}


        constexpr
        Value(MjType *type) noexcept : _type(type) {}


        constexpr
        Value(MjVariable *variable) noexcept : _variable(variable) {}


        constexpr
        Value(MjTemplate *template_) noexcept : _template(template_) {}
    };


    Value _value;
    MjTemplateArgumentKind _kind;
public:


    constexpr
    MjTemplateArgument(std::nullptr_t = nullptr) noexcept : _value(nullptr), _kind(MjTemplateArgumentKind::UNKNOWN) {}


    constexpr
    MjTemplateArgument(MjType *type) noexcept : _value(type), _kind(MjTemplateArgumentKind::TYPE) {}


    constexpr
    MjTemplateArgument(MjVariable *variable) noexcept : _value(variable), _kind(MjTemplateArgumentKind::VARIABLE) {}


    constexpr
    MjTemplateArgument(MjTemplate *template_) noexcept : _value(template_), _kind(MjTemplateArgumentKind::TEMPLATE) {}
};
