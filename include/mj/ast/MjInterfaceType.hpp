#pragma once

#include <mj/ast/MjType.hpp>


class MjInterfaceType : public MjType {
private:
    MjToken _name;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjInterfaceType(MjToken name, Slice<const MjToken> tokens = nullptr) noexcept :
        MjType(tokens), _name(name)
    {}


    ///
    /// Properties
    ///


    /// @brief Return true if the type has no name.
    constexpr
    bool is_anonymous() const noexcept {
        return _name != nullptr;
    }


};
