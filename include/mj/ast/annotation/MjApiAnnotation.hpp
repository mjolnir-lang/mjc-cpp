#pragma once

#include "mj/ast/MjAnnotation.hpp"


class MjApiAnnotation : public MjAnnotation {
private:
    u32 major_;
    u32 minor_;
public:


    MjApiAnnotation(
        u32 major,
        u32 minor
    ) :
        major_(major),
        minor_(minor)
    {}


    ~MjApiAnnotation() = default;
};
