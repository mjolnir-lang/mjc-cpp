#pragma once

#include <c/ast/CVariable.hpp>
#include <c/ast/CDerivedType.hpp>


class CFunctionType : public CDerivedType {
public:


    virtual ~CFunctionType() = default;


    virtual const Vector<CVariable> parameters() const = 0;


    virtual const CBlockStatement &statement() const = 0;


    virtual const CExpression &expression() const = 0;
};
