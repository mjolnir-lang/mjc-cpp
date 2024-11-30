#pragma once

#include <mj/ast/MjOperatorType.hpp>


class MjOperator {
private:
    MjOperatorType _operator_type;
public:


    constexpr
    MjOperator(MjOperatorType operator_type) noexcept : _operator_type(operator_type) {}


    ///
    /// Properties
    ///


};
