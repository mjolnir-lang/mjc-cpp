#pragma once

#include <mj/ast/MjType.hpp>


class MjTypeAlias : public MjType {
private:
    MjType *_base_type;
public:


    ///
    /// Constructors
    ///


    MjTypeAlias(MjType *base_type) noexcept : MjType(), _base_type(base_type) {}


    ///
    /// Properties
    ///


    constexpr
    const MjType *base_type() const noexcept {
        return _base_type;
    }


    constexpr
    MjType *base_type() noexcept {
        return _base_type;
    }


    ///
    /// Methods
    ///


};
