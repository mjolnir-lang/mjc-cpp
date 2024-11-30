#pragma once

#include <mj/ast/MjTypeDefinition.hpp>
#include <mj/ast/MjMethod.hpp>


class MjInterfaceDefinition : public MjTypeDefinition {
private:
    Vector<MjMethod *> _methods;
    const MjToken *_name;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjInterfaceDefinition(const MjToken *name, Slice<const MjToken> tokens = nullptr) noexcept :
        MjTypeDefinition(tokens), _name(name)
    {}


    ///
    /// Properties
    ///


    constexpr
    const Vector<MjMethod *> &methods() const noexcept {
        return _methods;
    }


    constexpr
    Vector<MjMethod *> &methods() noexcept {
        return _methods;
    }
};
