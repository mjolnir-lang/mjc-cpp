#include <io/StringParser.hpp>

#include <cerrno>


Error Parser<u8>::parse(StringParser &parser) noexcept {
    if (parser.format_options().type == 'c') {
        if (parser.string().is_empty()) {
            return Error::FAILURE;
        }

        parser.set_value(*parser.string());
        parser.string() += 1;
        return Error::SUCCESS;
    }

    u64 value;
    u32 n = parser.string().parse_u64(value, parser.format_options().base);

    if (n == 0 || value > U8_MAX) {
        return Error::FAILURE;
    }

    parser.set_value<u8>(value);
    parser.string() += n;
    return Error::SUCCESS;
}


Error Parser<u16>::parse(StringParser &parser) noexcept {
    u64 value;

    if (parser.string().parse_u64(value, parser.format_options().base).is_failure()) {
        return Error::FAILURE;
    }

    if (value > U16_MAX) {
        return Error::VALUE_OUT_OF_RANGE;
    }

    parser.set_value<u16>(value);
    return Error::SUCCESS;
}


Error Parser<u32>::parse(StringParser &parser) noexcept {
    u64 value;
    u32 n = string.parse_u64(value, parser.format_options().base);

    if (n == 0 || value > U32_MAX) {
        return Error::FAILURE;
    }

    parser.set_value<u32>(value);
    return Error::SUCCESS;
}


Error Parser<u64>::parse(StringParser &parser) noexcept {
    return string.parse_u64(arg.value<u64>(), parser.format_options().base);
}


Error Parser<i8>::parse(StringParser &parser) noexcept {
    i64 value;
    u32 n = string.parse_i64(value, parser.format_options().base);

    if (n == 0 || value > I8_MAX || value < I8_MIN) {
        return Error::FAILURE;
    }

    parser.set_value<i8>(value);
    return Error::SUCCESS;
}


Error Parser<i16>::parse(StringParser &parser) noexcept {
    i64 value;
    u32 n = string.parse_i64(value, parser.format_options().base);

    if (n == 0 || value > I16_MAX || value < I16_MIN) {
        return Error::FAILURE;
    }

    arg.set_value<i16>(value);
    return Error::SUCCESS;
}


Error Parser<i32>::parse(StringParser &parser) noexcept {
    i64 value;
    u32 n = string.parse_i64(value, parser.format_options().base);

    if (n == 0 || value > I32_MAX || value < I32_MIN) {
        return Error::FAILURE;
    }

    arg.set_value<i32>(value);
    return Error::SUCCESS;
}


Error Parser<i64>::parse(StringParser &parser) noexcept {
    return string.parse_i64(arg.value<i64>(), parser.format_options().base);
}


Error Parser<f32>::parse(StringParser &parser) noexcept {
    f64 value;
    u32 n = string.parse_f64(value);

    if (n == 0) {
        return Error::FAILURE;
    }

    parser.set_value<f32>(value);
    return Error::SUCCESS;
}


Error Parser<f64>::parse(StringParser &parser) noexcept {
    return string.parse_f64(arg.value<f64>());
}


Error Parser<bool>::parse(StringParser &parser) noexcept {
    static
    const StringView VALUES[6] {
        "false", "true", // {:b}
        "False", "True", // {:B}
        "FALSE", "TRUE", // {:#B}
    };

    for (StringView value : VALUES) {
        if (parser.string().starts_with(value)) {
            parser.set_value(value.size() == 4);
            return Error::SUCCESS;
        }
    }

    return Error::FAILURE;
}


Error Parser<const void *>::parse(StringParser &parser) noexcept {
    u32 n = 0;

    if (parser.string()[n] == '0' && (parser.string()[n + 1] | 0x20u) == 'x') {
        n += 2;
    }

    uintptr_t val = 0;

    for (u8 digit; Ascii::parse_digit(parser.string()[n], digit, 16).is_success(); n++) {
        val = (val << 4) | digit;
    }

    parser.set_value(reinterpret_cast<void *>(val));
    parser.string() += n;
    return Error::SUCCESS;
}
