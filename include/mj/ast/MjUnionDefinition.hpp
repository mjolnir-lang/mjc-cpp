#pragma once

#include <mj/ast/MjTypeDefinition.hpp>


class MjUnionDefinition : public MjTypeDefinition {
private:
    Vector<MjTypeDefinition *> _members;
    const MjToken *_name;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjUnionDefinition(const MjToken *name, Slice<const MjToken> tokens = nullptr) noexcept :
        MjTypeDefinition(tokens), _name(name)
    {}


    ///
    /// Properties
    ///


    constexpr
    u32 alignment() const noexcept {
        return 0;
    }


    constexpr
    u32 size() const noexcept {
        return 0;
    }


    constexpr
    const Vector<MjTypeDefinition *> &members() const noexcept {
        return _members;
    }


    constexpr
    Vector<MjTypeDefinition *> &members() noexcept {
        return _members;
    }
};
