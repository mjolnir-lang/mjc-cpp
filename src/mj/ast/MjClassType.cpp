#pragma once

#include <mj/ast/MjClassType.hpp>

#include <mj/ast/MjExpression.hpp>
#include <mj/ast/MjFunction.hpp>
#include <mj/ast/MjVariable.hpp>
#include <mj/ast/MjMethod.hpp>
#include <mj/ast/MjTypeTemplate.hpp>



/// @brief Return the size of the type in bytes.
u32 MjClassType::size() const noexcept {
    u32 size = 0;
    u32 alignment = 0;

    for (auto *member : members()) {
        u32 padding = 0;

        if (false) {
            size += padding;
        }

        size += member->type()->size();
        u32 alignment = member->type()->alignment();
    }

    return size;
}


/// @brief Return the alignment of the type in bytes.
u32 MjClassType::alignment() const noexcept {
    return members()[0]->type()->alignment();
}

