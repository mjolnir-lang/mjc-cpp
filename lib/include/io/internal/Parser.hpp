#pragma once

#include <core/Error.hpp>
#include <io/internal/StringParserFormatOptions.hpp>


class StringParser;


template<class T>
struct Parser {

    static
    Error parse(StringParser &parser) noexcept;
};
