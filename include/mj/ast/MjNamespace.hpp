#pragma once

#include "mj/ast/MjComment.hpp"
#include "mj/ast/MjScope.hpp"
#include "mj/ast/MjToken.hpp"


/// A named scope
class MjNamespace {
private:
    const MjToken &name_;
    MjScope *parent_;
    MjComment comment_;
    MjScope scope_;
public:


    MjNamespace(
        const MjToken &name,
        MjScope &parent,
        MjComment comment
    ) :
        name_(name),
        parent_(parent),
        comment_(comment)
    {}
};
