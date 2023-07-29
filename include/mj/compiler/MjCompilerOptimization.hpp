#pragma once

#include "mj/ast/MjProgram.hpp"


class MjCompilerOptimization {
private:
    MjProgram &program_;
public:


    MjCompilerOptimization(
        MjProgram &program
    ) :
        program_(program)
    {}


    void optimize(MjProgram &program) {
        ;
    }
};
