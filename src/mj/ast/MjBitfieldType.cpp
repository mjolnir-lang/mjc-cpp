#pragma once

#include <mj/ast/MjBitfieldType.hpp>

#include <mj/ast/MjExpression.hpp>
#include <mj/ast/MjFunction.hpp>
#include <mj/ast/MjVariable.hpp>
#include <mj/ast/MjMethod.hpp>
#include <mj/ast/MjTypeTemplate.hpp>



/// @brief Return the size of the type in bytes.
u32 MjBitfieldType::size() const noexcept {
    return _base_type->alignment();
}


/// @brief Return the alignment of the type in bytes.
u32 MjBitfieldType::alignment() const noexcept {
    return _base_type->alignment();
}

