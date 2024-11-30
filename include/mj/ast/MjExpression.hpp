#pragma once

#include <mj/ast/MjType.hpp>


class MjExpression : public MjStatement {
protected:


    ///
    /// Constructors
    ///


    constexpr
    MjExpression(Slice<const MjToken> tokens) noexcept :
        MjStatement(tokens)
    {}
public:


    ///
    /// Properties
    ///


    constexpr
    Slice<const MjToken> tokens() const noexcept {
        return _tokens;
    }


    virtual
    bool is_deterministic() const noexcept = 0;


    virtual
    const MjType *result_type() const noexcept = 0;


    virtual
    const MjType *result_type(const MjType *expected_type) const noexcept = 0;
};
