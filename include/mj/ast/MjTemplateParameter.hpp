#pragma once

#include <mj/ast/MjTemplateParameterKind.hpp>


class MjType;
class MjVariable;
class MjTemplate;


class MjTemplateParameter {
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
private:


    Value _value;
    MjTemplateParameterKind _type;
public:


    constexpr
    MjTemplateParameter(std::nullptr_t = nullptr) noexcept : _value(nullptr), _type(MjTemplateParameterKind::UNKNOWN) {}


    constexpr
    MjTemplateParameter(MjType *type) noexcept : _value(type), _type(MjTemplateParameterKind::TYPE) {}


    constexpr
    MjTemplateParameter(MjVariable *variable) noexcept : _value(variable), _type(MjTemplateParameterKind::VARIABLE) {}


    constexpr
    MjTemplateParameter(MjTemplate *template_) noexcept : _value(template_), _type(MjTemplateParameterKind::TEMPLATE) {}
};
