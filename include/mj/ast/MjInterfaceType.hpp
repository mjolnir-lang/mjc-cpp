#pragma once

#include <mj/ast/MjInterfaceDefinition.hpp>


class MjInterfaceType : public MjType {
private:
    MjInterfaceDefinition *_definition;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjInterfaceType() noexcept : MjType() {}


    ///
    /// Properties
    ///


    /// @brief Return true if the type has no name.
    constexpr
    bool is_anonymous() const noexcept {
        return _name != nullptr;
    }


};
