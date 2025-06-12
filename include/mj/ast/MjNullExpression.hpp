#pragma once

#include <mj/ast/MjExpression.hpp>


class MjNullExpression : public MjExpression {
protected:


    ///
    /// Constructors
    ///


    constexpr
    MjNullExpression() noexcept : MjExpression(MjItemKind::NULL_EXPRESSION) {}
public:


    ///
    /// Properties
    ///


    bool is_deterministic() const noexcept final {
        return true;
    }


    const MjType *result_type() const noexcept final {
        return item_manager->get_type("null");
    }


    const MjType *result_type(const MjType *expected_type) const noexcept {
        return result_type();
    }
};
