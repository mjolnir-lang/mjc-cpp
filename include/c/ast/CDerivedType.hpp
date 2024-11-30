#pragma once

#include <c/ast/CExpression.hpp>
#include <c/ast/CStatement.hpp>
#include <c/ast/CType.hpp>


// A 'Derived Type' is an anonymous type which builds upon another Basic or
// Derived type.
class CDerivedType : public CType {
public:


    virtual ~CDerivedType() = default;
};


#include <c/ast/CArrayType.hpp>
#include <c/ast/CFunctionType.hpp>
#include <c/ast/CPointerType.hpp>
