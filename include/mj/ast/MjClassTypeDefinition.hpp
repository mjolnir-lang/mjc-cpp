#pragma once

#include <mj/ast/MjTypeDefinition.hpp>


class MjClassTypeDefinition : public MjTypeDefinition {
private:
    Vector<MjDefinition *> _definitions;
    const MjToken *_name;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjClassTypeDefinition(const MjToken *name, Slice<const MjToken> tokens = nullptr) noexcept :
        MjTypeDefinition(tokens), _name(name)
    {}


    ///
    /// Properties
    ///


    constexpr
    Slice<MjDefinition *const> definitions() const noexcept {
        return _definitions;
    }


    constexpr
    Vector<MjDefinition *> &definitions() noexcept {
        return _definitions;
    }
};
