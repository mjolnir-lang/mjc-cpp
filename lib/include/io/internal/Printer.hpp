#pragma once

#include <core/Error.hpp>


class StringPrinter;


template<class T>
struct Printer {

    static
    Error print(StringPrinter &printer) noexcept;
};
