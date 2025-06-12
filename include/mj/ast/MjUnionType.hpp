#pragma once

#include <mj/ast/MjVariable.hpp>


class MjUnionType : public MjType {
private:
    Vector<MjVariable *> _members;
    MjToken _name;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjUnionType(MjToken name, Slice<const MjToken> tokens = nullptr) noexcept :
        MjType(tokens), _name(name)
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
    const Vector<MjVariable *> &members() const noexcept {
        return _members;
    }


    constexpr
    Vector<MjVariable *> &members() noexcept {
        return _members;
    }
};
