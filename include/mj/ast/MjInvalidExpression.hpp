#pragma once

#include <mj/ast/MjExpression.hpp>


class MjInvalidExpression : public MjExpression {
protected:


    ///
    /// Constructors
    ///


    constexpr
    MjInvalidExpression(
        MjItem item,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjExpression(MjItemKind::INVALID_EXPRESSION, tokens)
    {}
public:


    ///
    /// Properties
    ///


    virtual
    bool is_deterministic() const noexcept = 0;


    virtual
    const MjType *result_type() const noexcept = 0;


    virtual
    const MjType *result_type(const MjType *expected_type) const noexcept = 0;
};
