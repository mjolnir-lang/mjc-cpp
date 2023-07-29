#pragma once

#include "mj/ast/MjExpression.hpp"
#include "mj/ast/MjStatement.hpp"
#include "mj/ast/MjType.hpp"

#include "std/List.hpp"


// A 'Derived Type' is an anonymous type which builds upon another Basic or
// Derived type.
class MjDerivedType : public MjType {
public:


    virtual ~MjDerivedType() = default;
};


#include "mj/ast/type/MjArrayType.hpp"
#include "mj/ast/type/MjFunctionType.hpp"
#include "mj/ast/type/MjMethodType.hpp"
#include "mj/ast/type/MjPointerType.hpp"
#include "mj/ast/type/MjSliceType.hpp"
