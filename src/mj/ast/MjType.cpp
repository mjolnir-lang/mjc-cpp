#pragma once

#include <mj/ast/MjType.hpp>

#include <mj/ast/MjExpression.hpp>
#include <mj/ast/MjFunction.hpp>
#include <mj/ast/MjVariable.hpp>
#include <mj/ast/MjMethod.hpp>
#include <mj/ast/MjTypeTemplate.hpp>


const MjType *MjType::find_type(const MjToken *name) const noexcept {
    for (const MjType *type : types()) {
        if (type->name() == name) {
            return type;
        }
    }

    return nullptr;
}


const MjType *MjType::find_type_template(const MjToken *name, const MjTemplateArgumentList &argument_list) const noexcept {
    for (const MjTypeTemplate *type_template : type_templates()) {
        if (type_template->name() == name) {
            return type_template;
        }
    }

    return nullptr;
}


const MjVariable *MjType::find_variable(const MjToken *name) const noexcept {

    // Look for a member variable.
    for (const MjVariable *variable : members()) {
        if (variable->name() == name) {
            return variable;
        }
    }

    // Look for a shared member variable.
    for (const MjVariable *variable : variables()) {
        if (variable->name() == name) {
            return variable;
        }
    }

    return nullptr;
}


const MjFunction *MjType::find_function(const MjToken *name, const MjFunctionArgumentList &argument_list) const noexcept {
    for (const MjFunction *function : functions()) {
        if (function->name() == name) {
            return function;
        }
    }

    return nullptr;
}


const MjMethod *MjType::find_method(const MjToken *name, const MjFunctionArgumentList &argument_list) const noexcept {
    for (const MjMethod *method : methods()) {
        if (method->name() == name) {
            return method;
        }
    }

    return nullptr;
}


const MjFunction *MjType::find_operator(MjOperatorKind kind, const MjFunctionArgumentList &argument_list) const noexcept {
    for (const MjFunction *function : operators()) {
        if (function->name() == name) {
            return function;
        }
    }

    return nullptr;
}
