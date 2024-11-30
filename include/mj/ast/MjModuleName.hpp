#pragma once

#include <mj/ast/MjToken.hpp>


/// 
class MjModuleName {
private:
    const MjToken *_name;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjModuleName(const MjToken *name) noexcept : _name(name) {}


    ///
    /// Properties
    ///


    constexpr
    const MjToken *name() const noexcept {
        return _name;
    }
};
