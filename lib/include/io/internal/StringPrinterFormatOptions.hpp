#pragma once

#include <core/Enum.hpp>
#include <core/StringView.hpp>


template<class PrinterFormatSign>
struct PrinterFormatSignValues {
    static constexpr PrinterFormatSign NONE{0};  // '-' - Do not insert the plus sign
    static constexpr PrinterFormatSign PLUS{1};  // '+' - Always insert the plus sign
    static constexpr PrinterFormatSign SPACE{2}; // ' ' - Insert a space before positive numbers
};


class PrinterFormatSign : public Enum<u8>, public PrinterFormatSignValues<PrinterFormatSign> {
public:


    constexpr
    explicit
    PrinterFormatSign(u8 id) : Enum(id) {}
};


template<class PrinterFormatGroup>
struct PrinterFormatGroupValues {
    static constexpr PrinterFormatGroup NONE{0};
    static constexpr PrinterFormatGroup COMMA{1}; // ',' - Insert a comma between triplets of decimal digits before the decimal point
};


class PrinterFormatGroup : public Enum<u8>, public PrinterFormatGroupValues<PrinterFormatGroup> {
public:


    constexpr
    explicit
    PrinterFormatGroup(u8 id) : Enum(id) {}
};


template<class PrinterFormatAlign>
struct PrinterFormatAlignValues {
    static constexpr PrinterFormatAlign NONE{0};
    static constexpr PrinterFormatAlign LEFT{1}; // '<'
    static constexpr PrinterFormatAlign RIGHT{2}; // '>'
    static constexpr PrinterFormatAlign CENTER{3}; // '^'
    static constexpr PrinterFormatAlign AFTER_SIGN{4}; // '='
};


class PrinterFormatAlign : public Enum<u8>, public PrinterFormatAlignValues<PrinterFormatAlign> {
public:


    constexpr
    explicit
    PrinterFormatAlign(u8 id) : Enum(id) {}
};


/// @brief A format string argument structure.
struct StringPrinterFormatOptions {
    StringView extra;   // The trailing format data
    u8 size;
    u8 next_index;
    u8 index;           // The format argument index
    u8 fill;            // The fill character (only 1 byte, no multibyte characters)
    u8 width;           // The width field
    u8 precision;       // The precision
    u8 base;            // The number base: [2, 36]
    u8 type;            // The type specifier: [A-Za-z]
    u8 align           : 3; // The alignment specifier: NONE or [<>=^]
    u8 sign            : 2; // The sign specifier: [-+ ]
    u8 grouping_option : 1; // The number grouping option: NONE or ','
    bool has_alternate : 1; // If true, print the alternate form of the type
    bool has_precision : 1; // If true, use the precision field
    bool is_optional   : 1; // If true, extra is part of the format string
    bool is_true       : 1; // If true, parse extra
    bool is_debug      : 1; // If true, print the parsed format structure instead


    static constexpr u8 TYPE_NONE = 0;

};
