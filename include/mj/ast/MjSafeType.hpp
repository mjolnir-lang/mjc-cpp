#pragma once

#include <mj/ast/MjConstantType.hpp>


class MjSafeType : public MjType {
private:
    MjConstantType *_constant_type;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjSafeType(
        MjType *base_type
    ) noexcept :
        MjType(MjItemKind::SAFE_TYPE),
        _constant_type(base_type->is<MjConstantType>() ? base_type->as<MjConstantType>() : new MjConstantType(base_type))
    {}


    ///
    /// Properties
    ///


    constexpr
    const MjConstantType *constant_type() const noexcept {
        return _constant_type;
    }


    constexpr
    MjConstantType *constant_type() noexcept {
        return _constant_type;
    }


    constexpr
    const MjType *non_constant_type() const noexcept {
        return _constant_type->base_type();
    }


    constexpr
    MjType *non_constant_type() noexcept {
        return _constant_type->base_type();
    }


    ///
    /// Methods
    ///


};
