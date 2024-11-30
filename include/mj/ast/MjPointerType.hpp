#pragma once

#include <mj/ast/MjType.hpp>


class MjPointerType : public MjType {
private:
    MjType *_base_type;
protected:


    MjPointerType(MjType *base_type, MjTypeQualifiers type_qualifiers = MjTypeQualifiers::NONE) noexcept :
        MjType(MjTypeKind::POINTER, type_qualifiers),
        _base_type(base_type)
    {}


public:


    constexpr
    const MjType *base_type() const noexcept {
        return _base_type;
    }


    constexpr
    MjType *base_type() noexcept {
        return _base_type;
    }
};
