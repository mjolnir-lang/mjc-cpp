#pragma once

#include <mj/ast/MjProgram.hpp>


class MjAssembler {
private:
    MjProgram &program_;
public:


    MjAssembler(
        MjProgram &program
    ) :
        program_(program)
    {}


    void assemble(const Path &path) {
    }
};
