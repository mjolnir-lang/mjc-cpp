#pragma once

#include "mj/ast/MjType.hpp"


class MjFunctionParameter : public MjVariable {
public:
    const MjType &type_;
    const MjToken *name_;
    MjExpression *default_value_;


    MjFunctionParameter(
        const MjType &type,
        const MjToken *name,
        MjExpression *default_value
    ) :
        type_(type),
        name_(name),
        default_value_(default_value)
    {}


    bool has_name() const {
        return name_ != nullptr;
    }


    bool has_default_value() const {
        return default_value_ != nullptr;
    }


    const MjToken &name() const {
        return *name_;
    }


    const MjType &type() const {
        return type_;
    }


    const MjExpression &default_value() const {
        return *default_value_;
    }


    MjExpression &default_value() {
        return *default_value_;
    }


    void set_default_value(MjExpression &expression) {
        default_value_ = &expression;
    }
};


class MjFunctionParameterList {
public:
    Vector<MjFunctionParameter> parameters_;
};


/// @brief An `MjFunction` is an `MjStatement` object associated with a name and an `MjFunctionType`.
class MjFunction {
public:


    virtual ~MjFunction() = default;


    // The comment associated with the variable
    virtual const MjComment &comment() const = 0;


    // The variable name
    virtual const MjToken &name() const = 0;


    // The variable type
    virtual const MjFunctionType &type() const = 0;


    // The temporary sequence of tokens that make the definition
    virtual const List<const MjToken *> &tokens() const = 0;
};

