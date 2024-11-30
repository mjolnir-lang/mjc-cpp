#pragma once

#include <mj/ast/MjExpression.hpp>
#include <mj/ast/MjOperatorType.hpp>


class MjTernaryExpression : public MjExpression {
private:
    MjExpression *_lhs;
    MjExpression *_rhs;
    MjOperatorType _operator_type = MjOperatorType::NOT;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjTernaryExpression(MjOperatorType operator_type, Slice<const MjToken> tokens = nullptr) noexcept :
        MjExpression(tokens)
    {}


    ///
    /// Properties
    ///


    bool is_deterministic() const noexcept final {
        return _lhs->is_deterministic() && _rhs->is_deterministic();
    }


    const MjType *result_type() const noexcept final {
        MjFunction *op = MjFunction::lookup_operator(_operator_type, _lhs->result_type(), _rhs->result_type());
        return op ? op->return_type() : nullptr;
    }


    const MjType *result_type(const MjType *expected_type) const noexcept final {
        return nullptr;
    }


    constexpr
    MjObject *evaluate() const noexcept {
        return nullptr;
    }


    ///
    /// Methods
    ///
};
