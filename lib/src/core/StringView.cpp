#include <core/StringView.hpp>
#include <io/StringParser.hpp>
#include <io/StringPrinter.hpp>

#include <cerrno>


Error Printer<StringView>::print(StringPrinter &out) noexcept {
    return Error::SUCCESS;
}


u32 StringView::parse(StringView format, std::initializer_list<Parsable> args) const noexcept {
    ParseFormat parse_format = {
        .next_index = 0 // Set this for use as the first the default index while parsing.
    };
    StringView string = *this;
    u32 bytes_parsed = 0;

    while (!format.is_empty()) {
        u32 n = format.find_first('{');

        if (n == format.size()) {
            break;
        }

        // parse a literal "{" character when we see "{{".
        if (format[n + 1] == '{') {
            for (u32 i = 0; i < n + 1 && string[bytes_parsed] == format[i]; i++) {
                bytes_parsed += 1;
            }

            format += n + 2;
            continue;
        }

        // Write the normal format string characters up to the beginning of the format specifier
        for (u32 i = 0; i < n && string[bytes_parsed] == format[i]; i++) {
            bytes_parsed += 1;
        }

        // Adjust the format string reference.
        format += n;

        // Parse the format specifier.
        if (ParseFormat::parse(parse_format, format, args, parse_format.next_index)) {
            break;
        }

        format += parse_format.size;

        if (parse_format.type == 'n') {
            args.begin()[parse_format.index].set_value<u32>(bytes_parsed);
        } else {
            bytes_parsed += args.begin()[parse_format.index].parse(string, parse_format);
        }
    }

    // Upon failure, print the rest of the format string directly.
    return bytes_parsed;
}



















/*
static
u32 parse_f64_value(StringView string, ParseFormat &format, Parsable &arg) {
    static
    const f64 METRIC_FACTORS[11] = {
        1099511627776.0, 1073741824.0, 1048576.0, 1024.0, 1e12, 1e9, 1e6, 1e3, 1e-3, 1e-6, 1e-9
    };
    static
    const StringView METRIC_PREFIXES[11] = {
        "Ti", "Gi", "Mi", "Ki", "T", "G", "M", "k", "m", "μ", "n"
    };

    u32 i = parse_float(string, format, arg);

    if (string[i] == ' ') {
        i++;
    }

    // Parse the unit prefix and magnitude.
    u32 n = 0;
    for (; !string.slice(i).starts_with(METRIC_PREFIXES[n]); n++);
    f64 bias = METRIC_FACTORS[n];
    i += METRIC_PREFIXES[n].size();

    // Parse the unit.
    while (Char::is_alnum(string[i])) {
        i++;
    }

    // Parse the unit.
    StringView unit;

    if (i == format.extra.size()) {
        unit = prefix;
        prefix = nullptr;
    } else {
        unit = format.extra.slice(i);
    }

    // Adjust the value to represent the biased or nearest unit prefix.
    if (!prefix) {
        f64 magnitude = value < 0 ? -value : value;
        u32 n = start;
        for (; n < end && METRIC_FACTORS[n] >= magnitude; n++);
        bias = METRIC_FACTORS[n];
        prefix = METRIC_FACTORS[n];
    }

    *value /= bias;
    return i;
}
*/


u32 StringView::parse_u64(u64 &value, u8 base) const noexcept {
    u32 i = 0;

    // Determine the base based on the prefix.
    if ((base == 0 || base == 16) && (i + 1 < _data.size() && _data[i] == '0' && (_data[i + 1] | 0x20u) == 'x')) {
        i += 2;
        base = 16;
    } else if ((base == 0 || base == 2) && (i + 1 < _data.size() && _data[i] == '0' && (_data[i + 1] | 0x20u) == 'b')) {
        i += 2;
        base = 2;
    } else if ((base == 0 || base == 8) && i < _data.size() && _data[i] == '0') {
        i += 1;
        base = 8;
    } else if (base == 0) {
        base = 10;
    }

    // Parse the integer digits.
    u32 i_max = std::min<u32>(_data.size(), i + 256);
    u32 n = 0; // The number of integer digits
    u8 digits[256]; // The significant figures

    for (; i < i_max && Char::parse_digit(_data[i], digits[n], base).is_success(); i++) {
        // Skip leading zeros.
        if (digits[0] > 0) {
            n += 1;
        }
    }

    if (i == 0) {
        // No integer digits.
        return 0;
    }

    u32 m = n; // The total number of digits

    if (i + 1 < _data.size() && _data[i] == '.') {
        // Parse the fractional digits.
        u32 size = i;
        i += 1;
        i_max = std::min<u32>(_data.size(), i + 256 - m);
        for (; i < i_max && Char::parse_digit(_data[i], digits[m], base).is_success(); i++) {

            // Skip leading zeros only if the integer component was 0.
            if (digits[0] > 0) {
                m += 1;
            }
        }

        if (i == size + 1) {
            // No fractional digits.
            i = size;
        } else if (m == 256) {
            // Too many digits.
            return 0;
        }
    }

    if (i + 1 < _data.size() && (
        (base == 10 && (_data[i] | 0x20u) == 'e') ||
        (base == 16 && (_data[i] | 0x20u) == 'p')
    )) {
        // Parse the exponent value.
        u32 size = i;
        i += 1;

        // Parse the exponent sign.
        bool is_exponent_negative = false;

        if (_data[i] == '-') {
            i += 1;
            is_exponent_negative = true;
        } else if (_data[i] == '+') {
            i += 1;
        }

        // Parse the exponent magnitude.
        u32 start = i;
        u32 exponent = 0;

        for (u8 digit; i < _data.size() && Char::parse_digit(_data[i], digit).is_success(); i++) {
            if (exponent >= (U32_MAX / 10) - digit) {
                // Integer overflow. The exponent is too large.
                return 0;
            }

            exponent = (10 * exponent) + digit;
        }

        if (i == start) {
            // No exponent digits.
            i = size;
        } else {
            // Adjust the number of integer digits by the value of the exponent.
            if (is_exponent_negative) {
                if (n > exponent) {
                    n -= exponent;
                } else {
                    // The value has no integer component.
                    n = 0;
                }
            } else {
                n += exponent;
            }
        }
    }

    if (n > 64 / base) {
        // Too many integer digits.
        return 0;
    }

    // Compute integer value from integer digits.
    value = 0;

    for (u32 j = 0; j < n; j++) {
        if (value > U64_MAX / base) {
            // Unsigned integer overflow.
            return 0;
        }

        value *= base;

        if (j < m) {
            if (value > U64_MAX - digits[j]) {
                // Unsigned integer overflow.
                return 0;
            }

            value += digits[j];
        }
    }

    return i;
}


u32 StringView::parse_i64(i64 &value, u8 base) const noexcept {
    u32 i = 0;

    // Parse the sign.
    bool is_negative = false;

    if (i < _data.size() && _data[i] == '-') {
        is_negative = true;
        i += 1;
    }

    // Parse the magnitude.
    u64 magnitude;
    u32 j = slice(i).parse_u64(magnitude, base);

    if (j == 0) {
        return 0;
    }

    // Perform range check.
    if (magnitude > static_cast<u64>(I64_MAX) + static_cast<u64>(is_negative)) {
        return 0;
    }

    value = static_cast<i64>(is_negative ? -magnitude : magnitude);
    return i + j;
}


u32 StringView::parse_f64(f64 &value) const noexcept {
    u8 *end;
    value = strtod(reinterpret_cast<const char *>(_data.data()), reinterpret_cast<char **>(&end));

    if (errno == ERANGE) {
        return 0;
    }

    return end - _data;
}











u32 StringView::print(StringPrinter &stream_printer) noexcept {
    StringView value = arg.value<StringView>();

    if (format.has_precision) {
        value = StringView(value, std::min<u32>(format.precision, value.size()));
    }

    if (!format.has_alternate) {
        return writable.print_string(
            value,
            format.width,
            format.align == PrintFormatAlign::NONE ? PrintFormatAlign::LEFT : format.align,
            format.fill
        );
    }

    String buffer = nullptr;

    for (u32 i = 0; i < value.size(); i++) {
        if (value[i] == '\\') {
            buffer.append("\\\\");
        } else if (isprint(value[i])) {
            buffer.append(value[i]);
        } else if (value[i] == '\t') {
            buffer.append("\\t");
        } else if (value[i] == '\n') {
            buffer.append("\\n");
        } else if (value[i] == '\r') {
            buffer.append("\\r");
        } else {
            buffer.append("\\x");
            u8 ch = value[i] >> 4;
            buffer.append(ch < 10 ? ch + '0' : ch + 'A');
            ch = value[i] & 0xFu;
            buffer.append(ch < 10 ? ch + '0' : ch + 'A');
        }
    }

    return writable.print_string(
        StringView(buffer, format.has_precision ? std::min<u32>(format.precision, buffer.size()) : buffer.size()),
        format.width,
        format.align == PrintFormatAlign::NONE ? PrintFormatAlign::LEFT : format.align,
        format.fill
    );
}


Error StringView::parse(StringParser &string_parser) noexcept {
    u32 n = 0;
    u32 max_size = string_parser.string().size();

    if (max_size > string_parser.format_options().width && string_parser.format_options().width > 0) {
        max_size = string_parser.format_options().width;
    }

    for (; n < max_size && StringView(" \t\r\n").contains(string_parser.string()[n]); n++);
    string_parser.set_value(string_parser.string().slice(0, n));
    string_parser.string() += n;
    return Error::SUCCESS;
}
