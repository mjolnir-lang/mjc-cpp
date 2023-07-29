#pragma once

#include "mj/ast/MjToken.hpp"


class MjUnit {
private:
    const MjToken &name_;
public:


    MjUnit(
        const MjToken &name
    ) :
        name_(name)
    {}
};
