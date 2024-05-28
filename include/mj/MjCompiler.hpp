#pragma once

#include <mj/ast/MjProgram.hpp>


class MjCompiler {
private:
    MjProgram &program_;
public:


    MjCompiler(
        MjProgram &program
    ) :
        program_(program)
    {}


    ~MjCompiler() {
        ;
    }


    void compile(const Path &path) {
        ;
    }
};
