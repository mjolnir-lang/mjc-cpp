#pragma once

#include <mj/ast/MjStatement.hpp>
#include <mj/ast/MjType.hpp>


class MjExpression : public MjStatement {
protected:


    ///
    /// Constructors
    ///


    constexpr
    MjExpression(MjItemInfo item_info) noexcept : MjStatement(item_info) {}
public:


    ///
    /// Properties
    ///


    constexpr
    Slice<const MjToken> tokens() const noexcept {
        return _tokens;
    }


    virtual
    const MjType *result_type() const noexcept = 0;


    virtual
    const MjType *result_type(const MjType *expected_type) const noexcept = 0;
};
