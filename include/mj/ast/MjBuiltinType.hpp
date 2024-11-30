#pragma once

#include <mj/ast/MjType.hpp>


class MjBuiltinType : public MjType {
protected:


    constexpr
    MjBuiltinType(
        MjTypeType type_type,
        MjTypeQualifiers type_qualifiers = MjTypeQualifiers::NONE
    ) noexcept :
        MjType(type_type, type_qualifiers, nullptr)
    {}


public:
};
