#pragma once

#include <mj/ast/MjDefinition.hpp>


class MjTypeDefinition : public MjDefinition {
protected:
public:


    ///
    /// Constructors
    ///


    constexpr
    MjTypeDefinition(Slice<const MjToken> tokens = nullptr) noexcept : MjDefinition(tokens) {}


    ///
    /// Destructors
    ///


    ~MjTypeDefinition() = default;



    ///
    /// Properties
    ///


    constexpr
    const MjToken *name() const noexcept {
        return nullptr;
    }
};
