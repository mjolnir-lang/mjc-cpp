#pragma once

#include <core/StringView.hpp>


struct StringParserFormatOptions {
    StringView extra; // 
    u8 size = 0;      // 
    u8 index = 0;     // The format argument index
    u8 width = 0;     // The width field
    u8 base = 0;      // The number base: [2, 36]
    u8 type = 0;      // The type specifier: [A-Za-z]


    static constexpr u8 TYPE_NONE = 0;
};
