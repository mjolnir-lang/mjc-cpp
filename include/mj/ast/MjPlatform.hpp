#pragma once

#include <mj/ast/MjModule.hpp>


class MjPlatform {
private:
    const String name_;
public:


    MjPlatform(
        const String &name
    ) :
        name_(name)
    {
        //add_builtins()
    }
};
