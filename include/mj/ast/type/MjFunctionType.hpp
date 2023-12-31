#pragma once

#include "mj/ast/MjVariable.hpp"
#include "mj/ast/MjDerivedType.hpp"


class MjFunctionType : public MjDerivedType {
public:


    virtual ~MjFunctionType() = default;


    virtual const Vector<MjVariable> parameters() const = 0;


    virtual const MjBlockStatement &statement() const = 0;


    virtual const MjExpression &expression() const = 0;
};
