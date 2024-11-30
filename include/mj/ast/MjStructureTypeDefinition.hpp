#pragma once

#include <mj/ast/MjTypeDefinition.hpp>
#include <mj/ast/MjStatement.hpp>


class MjStructureTypeDefinition : public MjTypeDefinition {
private:
    Vector<MjStatement *> _statements;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjStructureTypeDefinition(Slice<const MjToken> tokens = nullptr) noexcept : MjTypeDefinition(tokens) {}


    ///
    /// Properties
    ///


    constexpr
    const Vector<MjStatement *> &statements() const noexcept {
        return _statements;
    }


    constexpr
    Vector<MjStatement *> &statements() noexcept {
        return _statements;
    }
};
