#pragma once

#include <c/ast/CType.hpp>


class CFunctionParameter : public CVariable {
public:
    const CType &type_;
    const CToken *name_;
    CExpression *default_value_;


    CFunctionParameter(
        const CType &type,
        const CToken *name,
        CExpression *default_value
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


    const CToken &name() const {
        return *name_;
    }


    const CType &type() const {
        return type_;
    }


    const CExpression &default_value() const {
        return *default_value_;
    }


    CExpression &default_value() {
        return *default_value_;
    }


    void set_default_value(CExpression &expression) {
        default_value_ = &expression;
    }
};


class CFunctionParameterList {
public:
    Vector<CFunctionParameter> parameters_;
};


/// @brief An `CFunction` is an `CStatement` object associated with a name and an `CFunctionType`.
class CFunction {
public:


    virtual ~CFunction() = default;


    // The comment associated with the variable
    virtual const CComment &comment() const = 0;


    // The variable name
    virtual const CToken &name() const = 0;


    // The variable type
    virtual const CFunctionType &type() const = 0;


    // The temporary sequence of tokens that make the definition
    virtual const List<const CToken *> &tokens() const = 0;
};

