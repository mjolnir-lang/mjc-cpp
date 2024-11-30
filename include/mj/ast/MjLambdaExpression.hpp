#pragma once

#include <mj/ast/MjExpression.hpp>


/// @brief An `MjFunction` is an `MjStatement` object associated with a name and an `MjFunctionType`.
class MjLambdaExpression : public MjExpression {
private:
public:


    constexpr
    MjLambdaExpression(Slice<const MjToken> tokens = nullptr) noexcept :
        MjExpression(tokens)
    {}


    ///
    /// Properties
    ///


};
