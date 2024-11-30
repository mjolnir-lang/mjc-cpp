#include <std/StreamPrinter.hpp>


Error Printer<u8>::print(StringPrinter &out) noexcept {
    if (format.type == 'c') {
        return out.print_char(
            arg.value<u8>(),
            format.has_precision ? format.precision : 1,
            format.width,
            format.align == PrintFormatAlign::NONE ? PrintFormatAlign::LEFT : format.align,
            format.fill
        );
    }

    return out.print_u32(format, arg.value<u8>());
}


Error Printer<u16>::print(StringPrinter &out) noexcept {
    if (format.type == 'c') {
        return out.print_char(
            arg.value<u16>(),
            format.has_precision ? format.precision : 1,
            format.width,
            format.align == PrintFormatAlign::NONE ? PrintFormatAlign::LEFT : format.align,
            format.fill
        );
    }

    return out.print_u32(format, arg.value<u16>());
}


Error Printer<u32>::print(StringPrinter &out) noexcept {
    if (format.type == 'c') {
        return out.print_char(
            arg.value<u32>(),
            format.has_precision ? format.precision : 1,
            format.width,
            format.align == PrintFormatAlign::NONE ? PrintFormatAlign::LEFT : format.align,
            format.fill
        );
    }

    return out.print_u32(format, arg.value<u32>());
}


Error Printer<u64>::print(StringPrinter &out) noexcept {
    if (format.type == 'c') {
        return out.print_char(
            arg.value<u64>(),
            format.has_precision ? format.precision : 1,
            format.width,
            format.align == PrintFormatAlign::NONE ? PrintFormatAlign::LEFT : format.align,
            format.fill
        );
    }

    return out.print_u64(format, arg.value<u64>());
}


Error Printer<i8>::print(StringPrinter &out) noexcept {
    if (format.type == 'c') {
        return out.print_char(
            arg.value<i8>(),
            format.has_precision ? format.precision : 1,
            format.width,
            format.align == PrintFormatAlign::NONE ? PrintFormatAlign::LEFT : format.align,
            format.fill
        );
    }

    return out.print_i32(format, arg.value<i8>());
}


Error Printer<i16>::print(StringPrinter &out) noexcept {
    if (format.type == 'c') {
        return out.print_char(
            arg.value<i16>(),
            format.has_precision ? format.precision : 1,
            format.width,
            format.align == PrintFormatAlign::NONE ? PrintFormatAlign::LEFT : format.align,
            format.fill
        );
    }

    return out.print_i32(format, arg.value<i16>());
}


Error Printer<i32>::print(StringPrinter &out) noexcept {
    if (format.type == 'c') {
        return out.print_char(
            arg.value<i32>(),
            format.has_precision ? format.precision : 1,
            format.width,
            format.align == PrintFormatAlign::NONE ? PrintFormatAlign::LEFT : format.align,
            format.fill
        );
    }

    return out.print_i32(format, arg.value<i32>());
}


Error Printer<i64>::print(StringPrinter &out) noexcept {
    if (format.type == 'c') {
        return out.print_char(
            arg.value<i64>(),
            format.has_precision ? format.precision : 1,
            format.width,
            format.align == PrintFormatAlign::NONE ? PrintFormatAlign::LEFT : format.align,
            format.fill
        );
    }

    return out.print_i64(format, arg.value<i64>());
}


Error Printer<f32>::print(StringPrinter &out) noexcept {
    return out.print_f64(format, arg.value<f64>());
}


Error Printer<f64>::print(StringPrinter &out) noexcept {
    return out.print_f64(format, arg.value<f64>());
}


Error Printer<bool>::print(StringPrinter &out) noexcept {
    static
    const StringView VALUES[8] = {
        "false", "true", // {:b}
        "0",     "1",    // {:#b}
        "False", "True", // {:B}
        "FALSE", "TRUE", // {:#B}
    };

    return out.print_string(
        VALUES[
            static_cast<u32>(format.type == 'B') << 2 |
            static_cast<u32>(format.has_alternate) << 1 |
            static_cast<u32>(arg.value<bool>())
        ],
        format.width,
        format.align == PrintFormatAlign::NONE ? PrintFormatAlign::LEFT : format.align,
        format.fill
    );
}


Error Printer<const void *>::print(StringPrinter &out) noexcept {
    if (format.align == PrintFormatAlign::NONE) {
        // TODO
        //align = PrintFormatAlign::RIGHT;
    }

    const void *value = arg.value<const void *>();
    u32 i = 0;

    if (format.has_alternate) {
        i += out.write("0x");
    }

    u8 letter_offset = format.type == 'P' ? 'A' - '0' - 10 : 'a' - '0' - 10;

    for (u32 n = 8 * sizeof(void *); n;) {
        n -= 4;
        const u8 ch = ((((uintptr_t) value) >> n) & 0xFu) + '0';
        i += out.write(ch > '9' ? ch + letter_offset : ch);
    }

    return i;
}
