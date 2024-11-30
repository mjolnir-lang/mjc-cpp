#pragma once

#include <mj/ast/MjProgram.hpp>


class MjCompiler {
private:
    MjProgram &_program;
public:


    MjCompiler(MjProgram &program) noexcept : _program(program) {}


    ~MjCompiler() {
        ;
    }


    void compile(const FilePath &path) {
        ;
    }
};
