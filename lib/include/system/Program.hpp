#pragma once

#include <io/InputStream.hpp>
#include <io/OutputStream.hpp>


class Program {
private:
public:


    static
    InputStream<u8> &STDIN;

    static
    OutputStream<u8> &STDOUT;

    static
    OutputStream<u8> &STDERR;
};
