#pragma once

#include <mj/ast/MjType.hpp>


class MjTypeName {
private:
    u32 _id;
public:


    constexpr
    MjTypeName(StringView text) noexcept {}


    constexpr
    StringView text() const noexcept {
        return MjTypeName::names[_id];
    }
};


///
/// Relational Operators
///


/// @brief Return true if the contents of the slices are equal.
constexpr
bool operator==(MjTypeName lhs, MjTypeName rhs) noexcept {
    return lhs.is_equal(rhs);
}


/// @brief Return true if the contents of the slices are not equal.
constexpr
bool operator!=(MjTypeName lhs, MjTypeName rhs) noexcept {
    return !(lhs == rhs);
}
