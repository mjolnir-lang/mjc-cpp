#pragma once

#include <mj/ast/MjType.hpp>


class MjSliceType : public MjType {
private:
    MjType *_base_type;
protected:


    constexpr
    MjSliceType(
        MjType *base_type,
        MjTypeQualifiers type_qualifiers = MjTypeQualifiers::NONE
    ) noexcept :
        MjType(MjItemKind::SLICE_TYPE)
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
