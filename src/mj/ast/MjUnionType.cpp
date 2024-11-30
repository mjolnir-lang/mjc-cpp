#pragma once

#include <mj/ast/MjUnionType.hpp>

#include <mj/ast/MjExpression.hpp>
#include <mj/ast/MjFunction.hpp>
#include <mj/ast/MjVariable.hpp>
#include <mj/ast/MjMethod.hpp>
#include <mj/ast/MjTypeTemplate.hpp>


u32 MjUnionType::size() const noexcept {
    u32 size = 0;

    for (auto *member : members()) {
        size = std::max(size, member->type()->size());
    }

    return size;
}


u32 MjUnionType::alignment() const noexcept {
    u32 alignment = 0;

    for (auto *member : members()) {
        alignment = std::max(alignment, member->type()->alignment());
    }

    return alignment;
}

