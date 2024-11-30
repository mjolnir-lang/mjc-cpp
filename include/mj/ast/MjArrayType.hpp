#pragma once

#include <mj/ast/MjDerivedType.hpp>


class MjArrayType : public MjDerivedType {
private:
    u32 _array_size;
protected:


    constexpr
    MjArrayType(
        MjType *base_type,
        u32 array_size,
        MjTypeQualifiers type_qualifiers = MjTypeQualifiers::NONE
    ) noexcept :
        MjDerivedType(MjTypeType::ARRAY, base_type, type_qualifiers),
        _array_size(array_size)
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
