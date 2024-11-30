#pragma once

#include <mj/ast/MjTypeDefinition.hpp>


class MjBitfieldTypeDefinition : public MjTypeDefinition {
private:
    Vector<MjDefinition *> _definitions;
    const MjToken *_name;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjBitfieldTypeDefinition(const MjToken *name, Slice<const MjToken> tokens = nullptr) noexcept :
        MjTypeDefinition(tokens), _name(name)
    {}


    ///
    /// Properties
    ///


    constexpr
    const Vector<MjDefinition *> &definitions() const noexcept {
        return _definitions;
    }


    constexpr
    Vector<MjDefinition *> &definitions() noexcept {
        return _definitions;
    }
};
