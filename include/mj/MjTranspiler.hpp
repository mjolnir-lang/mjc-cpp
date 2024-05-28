#pragma once

#include <mj/ast/MjProgram.hpp>


class MjTranspiler {
private:
    MjProgram &program_;
public:


    MjTranspiler(
        MjProgram &program
    ) :
        program_(program)
    {}


    ~MjTranspiler() {
        ;
    }


    void transpile(const Path &path) {
    }
};
