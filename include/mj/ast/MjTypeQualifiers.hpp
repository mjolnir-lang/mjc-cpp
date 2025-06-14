#pragma once

#include <core/Enum.hpp>


template<class MjTypeQualifiers>
struct MjTypeQualifiersValues {
    static constexpr MjTypeQualifiers NONE{0};
    static constexpr MjTypeQualifiers CONST{1};
    static constexpr MjTypeQualifiers MUTABLE{2};
    static constexpr MjTypeQualifiers SAFE{3};
};


class MjTypeQualifiers : public Enum<u8>, public MjTypeQualifiersValues<MjTypeQualifiers> {
public:


    constexpr
    explicit
    MjTypeQualifiers(u8 id) noexcept : Enum(id) {}
};
