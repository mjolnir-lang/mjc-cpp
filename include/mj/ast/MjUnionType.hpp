#pragma once

#include <mj/ast/MjType.hpp>


class MjUnionType : public MjType {
private:
public:


    MjUnionType() noexcept : MjType(MjTypeKind::UNION) {}


    ///
    /// Properties
    ///


    /// @brief Return the size of the type in bytes.
    u32 size() const noexcept;


    /// @brief Return the alignment of the type in bytes.
    u32 alignment() const noexcept;
};
