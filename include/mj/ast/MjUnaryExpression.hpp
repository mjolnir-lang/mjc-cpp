#pragma once

#include <mj/ast/MjExpression.hpp>
#include <mj/ast/MjOperatorType.hpp>


class MjUnaryExpression : public MjExpression {
private:
    MjExpression *_arg;
    const MjOperatorType _operator_type;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjUnaryExpression(MjOperatorType operator_type, MjExpression *arg, Slice<const MjToken> tokens = nullptr) noexcept :
        MjExpression(tokens), _operator_type(operator_type), _arg(arg)
    {}


    ///
    /// Properties
    ///


    bool is_deterministic() const noexcept final {
        return _arg->is_deterministic();
    }


    const MjType *result_type() const noexcept final {
        MjFunction *op = MjFunction::lookup_operator(_operator_type, _arg->result_type());
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
