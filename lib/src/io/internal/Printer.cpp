#include <io/StringPrinter.hpp>


Error Printer<u8>::print(StringPrinter &printer) noexcept {
    if (printer.format().type == 'c') {
        return printer.print_char(
            printer.arg<u8>(),
            printer.format().has_precision ? printer.format().precision : 1,
            printer.format().width,
            printer.format().align == PrinterFormatAlign::NONE ? PrinterFormatAlign::LEFT : printer.format().align,
            printer.format().fill
        );
    }

    return printer.print_u32(printer.arg<u8>());
}


Error Printer<u16>::print(StringPrinter &printer) noexcept {
    if (printer.format().type == 'c') {
        return printer.print_char(
            printer.arg<u16>(),
            printer.format().has_precision ? printer.format().precision : 1,
            printer.format().width,
            printer.format().align == PrinterFormatAlign::NONE ? PrinterFormatAlign::LEFT : printer.format().align,
            printer.format().fill
        );
    }

    return printer.print_u32(printer.arg<u16>());
}


Error Printer<u32>::print(StringPrinter &printer) noexcept {
    if (printer.format().type == 'c') {
        return printer.print_char(
            printer.arg<u32>(),
            printer.format().has_precision ? printer.format().precision : 1,
            printer.format().width,
            printer.format().align == PrinterFormatAlign::NONE ? PrinterFormatAlign::LEFT : printer.format().align,
            printer.format().fill
        );
    }

    return printer.print_u32(printer.arg<u32>());
}


Error Printer<u64>::print(StringPrinter &printer) noexcept {
    if (printer.format().type == 'c') {
        return printer.print_char(
            printer.arg<u64>(),
            printer.format().has_precision ? printer.format().precision : 1,
            printer.format().width,
            printer.format().align == PrinterFormatAlign::NONE ? PrinterFormatAlign::LEFT : printer.format().align,
            printer.format().fill
        );
    }

    return printer.print_u64(printer.arg<u64>());
}


Error Printer<i8>::print(StringPrinter &printer) noexcept {
    if (printer.format().type == 'c') {
        return printer.print_char(
            printer.arg<i8>(),
            printer.format().has_precision ? printer.format().precision : 1,
            printer.format().width,
            printer.format().align == PrinterFormatAlign::NONE ? PrinterFormatAlign::LEFT : printer.format().align,
            printer.format().fill
        );
    }

    return printer.print_i32(printer.arg<i8>());
}


Error Printer<i16>::print(StringPrinter &printer) noexcept {
    if (printer.format().type == 'c') {
        return printer.print_char(
            printer.arg<i16>(),
            printer.format().has_precision ? printer.format().precision : 1,
            printer.format().width,
            printer.format().align == PrinterFormatAlign::NONE ? PrinterFormatAlign::LEFT : printer.format().align,
            printer.format().fill
        );
    }

    return printer.print_i32(printer.arg<i16>());
}


Error Printer<i32>::print(StringPrinter &printer) noexcept {
    if (printer.format().type == 'c') {
        return printer.print_char(
            printer.arg<i32>(),
            printer.format().has_precision ? printer.format().precision : 1,
            printer.format().width,
            printer.format().align == PrinterFormatAlign::NONE ? PrinterFormatAlign::LEFT : printer.format().align,
            printer.format().fill
        );
    }

    return printer.print_i32(printer.arg<i32>());
}


Error Printer<i64>::print(StringPrinter &printer) noexcept {
    if (printer.format().type == 'c') {
        return printer.print_char(
            printer.arg<i64>(),
            printer.format().has_precision ? printer.format().precision : 1,
            printer.format().width,
            printer.format().align == PrinterFormatAlign::NONE ? PrinterFormatAlign::LEFT : printer.format().align,
            printer.format().fill
        );
    }

    return printer.print_i64(printer.arg<i64>());
}


Error Printer<f32>::print(StringPrinter &printer) noexcept {
    return printer.print_f64(printer.arg<f64>());
}


Error Printer<f64>::print(StringPrinter &printer) noexcept {
    return printer.print_f64(printer.arg<f64>());
}


Error Printer<bool>::print(StringPrinter &printer) noexcept {
    static
    const StringView VALUES[8] = {
        "false", "true", // {:b}
        "0",     "1",    // {:#b}
        "False", "True", // {:B}
        "FALSE", "TRUE", // {:#B}
    };

    return printer.print_string(
        VALUES[
            static_cast<u32>(printer.format().type == 'B') << 2 |
            static_cast<u32>(printer.format().has_alternate) << 1 |
            static_cast<u32>(printer.arg<bool>())
        ],
        printer.format().width,
        printer.format().align == PrinterFormatAlign::NONE ? PrinterFormatAlign::LEFT : printer.format().align,
        printer.format().fill
    );
}


Error Printer<const void *>::print(StringPrinter &printer) noexcept {
    if (printer.format().align == PrinterFormatAlign::NONE) {
        // TODO
        //align = PrinterFormatAlign::RIGHT;
    }

    const void *value = printer.arg<const void *>();

    if (printer.format().has_alternate && printer.write("0x").is_failure()) {
        return Error::FAILURE;
    }

    u8 letter_offset = printer.format().type == 'P' ? 'A' - '0' - 10 : 'a' - '0' - 10;

    for (u32 n = 8 * sizeof(void *); n;) {
        n -= 4;
        const u8 ch = ((((uintptr_t) value) >> n) & 0xFu) + '0';

        if (printer.write(ch > '9' ? ch + letter_offset : ch).is_failure()) {
            return Error::FAILURE;
        }
    }

    return Error::SUCCESS;
}
