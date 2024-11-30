#include <io/StringPrinter.hpp>
#include <io/OutputStream.hpp>





/// @brief Write all pending data.
void StringPrinter::flush() noexcept {
    return _output_stream.flush();
}


/// @brief Begin writing a sequence of elements.
/// @param data The elements to write
/// @return 
Error StringPrinter::write(Slice<const u8> data) noexcept {
    u32 expected = _bytes_written + data.size();
    _bytes_written += _output_stream.write(data);
    return Error(_bytes_written < expected);
}


/// @brief Write a byte repeatedly.
/// @param ch The byte to write
/// @return 
Error StringPrinter::fill(u8 ch, u32 size) noexcept {
    u32 expected = _bytes_written + size;
    _bytes_written += _output_stream.fill(ch, size);
    return Error(_bytes_written < expected);
}



Error StringPrinter::vprint(StringView format, Slice<Printable> args) noexcept {
    _bytes_written += _output_stream.vprint(format, args);
}










Error StringPrinter::print() noexcept {
    while (!_format_string.is_empty()) {
        u32 n = _format_string.find_first("{");

        if (n == _format_string.size()) {
            break;
        }

        // Print a literal "{" character when we see "{{".
        if (_format_string[n + 1] == '{') {
            _bytes_written += _output_stream.write(_format_string, n + 1);
            _format_string += n + 2;
            continue;
        }

        // Write the normal format string characters up to the beginning of the format specifier
        _bytes_written += _output_stream.write(_format_string, n);

        // Adjust the format string reference.
        _format_string += n;

        // Parse the format specifier.
        if (PrintFormat::parse(_print_format, _format_string, _args, _print_format.next_index)) {
            break;
        }

        _format_string += _print_format.size;

        // Check for an optional format string.
        if (_print_format.is_optional) {
            if (_print_format.is_true) {
                _bytes_written += _output_stream.write(_print_format.extra);
            }

            continue;
        }

        if (_print_format.type == 'n') {
            *_args.begin()[_print_format.index].value<u32 *>() = _bytes_written;
        } else {
            if (_args.begin()[_print_format.index].print(*this).is_failure()) {
                return Error::FAILURE;
            }
        }
    }

    // Upon failure, print the rest of the format string directly.
    _bytes_written += _output_stream.write(_format_string);
    return Error::SUCCESS;
}


Error StringPrinter::print_string(StringView string, u32 width, u8 align, u8 fill_character) noexcept {
    u32 i = 0;

    if (string.size() < width && align != PrinterFormatAlign::LEFT) {
        i = width - string.size();

        if (align == PrinterFormatAlign::CENTER) {
            i /= 2;
        }

        i = fill(fill_character, i);
    }

    i += write(string);

    if (i < width) {
        i += fill(fill_character, width - i);
    }

    return i;
}


u32 StringPrinter::print_char(u8 value, u8 repeat_count, u32 width, u8 align, u8 fill_character) noexcept {
    u32 i = 0;

    if (align == PrinterFormatAlign::NONE) {
        align = PrinterFormatAlign::LEFT;
    }

    if (width < repeat_count) {
        i = repeat_count - width;

        if (align == PrinterFormatAlign::CENTER) {
            i /= 2;
        }

        i = fill(fill_character, i);
    }

    i += write(value);

    if (i < repeat_count) {
        i += fill(fill_character, repeat_count - i);
    }

    return i;
}


u32 StringPrinter::print_u32(const StringPrinterFormatOptions &format, u32 value, bool is_negative) noexcept {
    u8 base = format.base;

    if (format.type == 'o') {
        base = 8;
    } else if (format.type == 'x' || format.type == 'X') {
        base = 16;
    }

    u32 n = 67;
    const u8 letter_offset = format.type < 'a' ? 'A' - '0' - 10 : 'a' - '0' - 10;
    u8 buffer[67];

    // Print the digits.
    do {
        buffer[--n] = (value % base) + '0';

        if (buffer[n] > '9') {
            buffer[n] += letter_offset;
        }

        value /= base;
    } while (value);

    u32 m = n;

    // Print the prefix.
    if (format.has_alternate) {
        if (base == 16) {
            buffer[--m] = 'x';
            buffer[--m] = '0';
        } else if (base == 8 && buffer[n] != '0') {
            buffer[--m] = '0';
        } else if (base == 2) {
            buffer[--m] = 'b';
            buffer[--m] = '0';
        }
    }

    // Print the sign.
    if (is_negative) {
        buffer[--m] = '-';
    } else if (format.sign != PrinterFormatSign::NONE) {
        buffer[--m] = format.sign == PrinterFormatSign::PLUS ? '+' : ' ';
    }

    // Print the buffer.
    u32 i = 0;

    u8 align = format.align;
    u8 width = format.width;

    if (align == PrinterFormatAlign::NONE) {
        align = PrinterFormatAlign::RIGHT;
    } else if (align == PrinterFormatAlign::AFTER_SIGN) {

        // Change the alignment and width to account for the leading sign and
        // prefix.
        const u32 prefix_width = n - m;
        i += write(&buffer[m], prefix_width);
        align = PrinterFormatAlign::RIGHT;
        width -= std::min<u32>(width, prefix_width);
    } else {
        n = m;
    }

    return i + print_string(StringView(&buffer[n], 67 - n), align, width, format.fill);
}


u32 StringPrinter::print_u64(const StringPrinterFormatOptions &format, u64 value, bool is_negative) noexcept {
    u8 base = format.base != 0 ? format.base : 10;

    if (format.type == 'o') {
        base = 8;
    } else if (format.type == 'x' || format.type == 'X') {
        base = 16;
    }

    u32 n = 67;
    const u8 letter_offset = format.type < 'a' ? 'A' - '0' - 10 : 'a' - '0' - 10;
    u8 buffer[67];

    // Print the digits.
    do {
        buffer[--n] = (value % base) + '0';

        if (buffer[n] > '9') {
            buffer[n] += letter_offset;
        }

        value /= base;
    } while (value);

    u32 m = n;

    // Print the prefix.
    if (format.has_alternate) {
        if (base == 16) {
            buffer[--m] = 'x';
            buffer[--m] = '0';
        } else if (base == 8 && buffer[n] != '0') {
            buffer[--m] = '0';
        } else if (base == 2) {
            buffer[--m] = 'b';
            buffer[--m] = '0';
        }
    }

    // Print the sign.
    if (is_negative) {
        buffer[--m] = '-';
    } else if (format.sign != PrinterFormatSign::NONE) {
        buffer[--m] = format.sign == PrinterFormatSign::PLUS ? '+' : ' ';
    }

    // Print the buffer.
    u32 i = 0;

    u8 width = format.width;
    u8 align = format.align;

    if (align == PrinterFormatAlign::NONE) {
        align = PrinterFormatAlign::RIGHT;
    } else if (align == PrinterFormatAlign::AFTER_SIGN) {

        // Change the alignment and width to account for the leading sign and
        // prefix.
        const u32 prefix_width = n - m;
        i += write(&buffer[m], prefix_width);
        align = PrinterFormatAlign::RIGHT;
        width -= std::min<u32>(format.width, prefix_width);
    } else {
        n = m;
    }

    return i + print_string(StringView(&buffer[n], 67 - n), width, align, format.fill);
}


u32 StringPrinter::print_f64(const StringPrinterFormatOptions &format, f64 value) noexcept {
    u8 base = format.base;
    u8 precision = format.has_precision ? format.precision : 6;

    if (format.type == 'A' || format.type == 'a') {
        base = 16;
    } else if (base != 10 && base != 16) {
        return 0;
    }

    const u8 uppercase_offset = format.type < 'a' ? 'A' - 'a' : 0;
    f64 val = value;
    const bool is_negative = val < 0.0;
    u32 n = 512;
    const u8 letter_offset = uppercase_offset ? 'A' - '0' - 10 : 'a' - '0' - 10;
    u8 buffer[512];

    // Print the representation.
    if (val != val) {
        buffer[--n] = 'n' + uppercase_offset;
        buffer[--n] = 'a' + uppercase_offset;
        buffer[--n] = 'n' + uppercase_offset;
    } else if (val == 1.0 / 0.0 || val == -1.0 / 0.0) {
        buffer[--n] = 'f' + uppercase_offset;
        buffer[--n] = 'n' + uppercase_offset;
        buffer[--n] = 'i' + uppercase_offset;
    } else {
        if (is_negative) {
            val = -val;
        }

        const u32 ebase = base == 10 ? 10 : 2; // exponent is base 2 for hexadecimal
        bool is_scientific = format.type == 'A' || format.type == 'a' || format.type == 'E' || format.type == 'e';
        const bool is_exponent_negative = val < 1.0;

        // If using general format, determine the shortest representation.
        if (format.type == 'G' || format.type == 'g') {
            u32 ival_width = 1; // either base 10 or base 16 digits
            u32 eval_width = 1; // always base 10 digits

            for (f64 v = val; v >= base; v /= base) {
                ival_width += 1;
            }

            for (u32 v = ival_width - 1; v >= ebase; v /= ebase) {
                eval_width += 1;
            }

            is_scientific = eval_width + 3 < ival_width;

            if (is_scientific) {
                if (precision) {
                    precision -= 1;
                }
            } else {
                precision = ival_width < precision ? precision - ival_width : 0;
                // TODO: Rounding in fixedpoint format can add one extra digit.
            }
        }

        // If using scientific format, adjust the value and get the exponential component.
        u32 eval = 0;

        if (is_scientific) {
            for (; val < 1.0; val *= ebase) {
                eval += 1;
            }

            for (; val > ebase; val /= ebase) {
                eval += 1;
            }
        }

        // Partition the value into integral and fractional components.
        u64 ival = val;
        f64 factor = 1.0;

        for (u32 i = 0; i < precision; i++) {
            factor *= base;
        }

        val = (val - ival) * factor;
        u64 fval = val;
        val -= fval;

        // Round the integral and fractional components (ties to even).
        if (val > 0.5 || (val == 0.5 && (precision == 0 ? ival : fval) & 1)) {
            fval += 1;

            // Correct the components after rounding.
            if (fval >= factor) {
                fval = 0;
                ival += 1;

                if (is_scientific && ival == ebase) {
                    ival = 1;
                    eval += 1;
                }
            }
        }

        // Print the exponential digits. (exponent digits are always base 10)
        if (is_scientific) {
            do {
                buffer[--n] = (eval % 10) + '0';

                if (buffer[n] > '9') {
                    buffer[n] += letter_offset;
                }

                eval /= 10;
            } while (eval);

            buffer[--n] = is_exponent_negative ? '-' : '+';
            buffer[--n] = base == 10 ? 'e' + uppercase_offset : 'p';
        }

        // Print the fractional digits.
        if (precision) {
            bool has_precision = format.has_precision;

            for (u32 j = 0; j < precision; j++) {
                buffer[--n] = (fval % base) + '0';

                if (buffer[n] > '9') {
                    buffer[n] += letter_offset;
                }

                // Do not store trailing zeros if we do not have precision.
                if (!has_precision) {
                    if (buffer[n] == '0') {
                        n += 1;
                    } else {
                        has_precision = true;
                    }
                }

                fval /= base;
            }

            buffer[--n] = '.';
        }

        // Print the integer digits.
        do {
            buffer[--n] = (ival % base) + '0';

            if (buffer[n] > '9') {
                buffer[n] += letter_offset;
            }

            ival /= base;
        } while (ival);
    }

    u32 m = n;

    // Print the prefix.
    if (format.has_alternate) {
        if (base == 16) {
            buffer[--m] = 'x';
            buffer[--m] = '0';
        } else if (base == 8 && buffer[n] != '0') {
            buffer[--m] = '0';
        } else if (base == 2) {
            buffer[--m] = 'b';
            buffer[--m] = '0';
        }
    }

    // Print the sign.
    if (is_negative) {
        buffer[--m] = '-';
    } else if (format.sign != PrinterFormatSign::NONE) {
        buffer[--m] = format.sign == PrinterFormatSign::PLUS ? '+' : ' ';
    }

    // Print the buffer.
    u32 i = 0;
    u32 width = format.width;
    u8 align = format.align;

    if (align == PrinterFormatAlign::NONE) {
        align = PrinterFormatAlign::RIGHT;
    } else if (align == PrinterFormatAlign::AFTER_SIGN) {

        // Change the alignment and width to account for the leading sign and
        // prefix.
        const u32 prefix_width = n - m;
        i += write(&buffer[m], prefix_width);
        align = PrinterFormatAlign::RIGHT;
        width -= std::min<u32>(width, prefix_width);
    } else {
        n = m;
    }

    return i + print_string(StringView(&buffer[n], 512 - n), width, align, format.fill);
}


/*
u32 Formatter_Memory_print(StringView *format_string, const FormatArgs *args) {
    const u32 type_size = format.type_width / 8;
    const u32 cols = 16 / type_size;
    const u32 mask = ByteOrder::Native == ByteOrder::LittleEndian ? type_size - 1 : 0;
    const u32 address_size = address + size > 0xFFFFU ? 4 : 2;
    i32 n = -static_cast<i32>(address % cols);
    u32 i = 0;
    const u8 letter_offset = format.type == 'M' ? 'A' - '0' - 10 : 'a' - '0' - 10;
    u8 string_view[16];

    for (u32 a = address + n; n < static_cast<i32>(size); a += 16) {
        if (i) {
            i += this.write('\n');
        }

        for (u32 j = 8 * address_size; j;) {
            j -= 4;
            u8 ch = ((a >> j) & 0xFU) + '0';

            if (ch > '9') {
                ch += letter_offset;
            }

            i += this.write(ch);
        }

        i += this.write(' ');

        for (u32 col = 0; col < cols; col++, n++) {
            i += this.write(' ');

            if (n < 0 || n >= static_cast<i32>(size)) {
                for (u32 j = 0; j < type_size; j++) {
                    i += this.write("  ");

                    if (format.has_alternate) {
                        string_view[(type_size * col) + j] = ' ';
                    }
                }
            } else {
                for (u32 j = 0; j < type_size; j++) {
                    u8 val = reinterpret_cast<const u8 *>(values)[((type_size * n) + j) ^ mask];

                    if (format.has_alternate) {
                        string_view[((type_size * col) + j) ^ mask] = Char::is_print(val) ? val : '.';
                    }

                    u8 ch = ((val >> 4) & 0xFU) + '0';

                    if (ch > '9') {
                        ch += letter_offset;
                    }

                    i += this.write(ch);
                    ch = (val & 0xFU) + '0';

                    if (ch > '9') {
                        ch += letter_offset;
                    }

                    i += this.write(ch);
                }
            }
        }

        if (format.has_alternate) {
            i += write(' ');
            i += write(' ');
            i += write(string_view, 16);
        }
    }

    return i;
}


u32 Formatter_print_value(StringPrinterFormatOptions &format, va_list *args) {
    static const f64 metric_factors[13] = {
        1099511627776.0, 1073741824.0, 1048576.0, 1024.0, 1.0, 1e12, 1e9, 1e6, 1e3, 1.0, 1e-3, 1e-6, 1e-9
    };
    static const u8 *metric_prefixes[13] = {
        "Ti", "Gi", "Mi", "Ki", "", "T", "G", "M", "k", "", "m", "μ", "n"
    };
    static const u8 metric_prefix_keys[13] = {
        'T', 'G', 'M', 'K', '\0', 'T', 'G', 'M', 'k', '\0', 'm', 'u', 'n'
    };

    const bool is_memory = format.type == 'V';
    const u32 start = is_memory ? 0 : 4;
    const u32 end = is_memory ? 5 : 13;
    u32 i = 0;

    // Get the value.
    f64 value = 0.0;

    if (format.extra[i] == 'u') {
        i += 1;
        value = va_arg(*args, u32);
    } else if (format.extra[i] == 'i' || format.extra[i] == 'd') {
        i += 1;
        value = va_arg(*args, i32);
    } else {
        value = va_arg(*args, f64);
    }

    // Parse the unit separator.
    const u8 *sep = " ";

    if (format.extra[i] == '*') {
        i += 1;
        sep = "°";
    } else if (format.extra[i] == ' ') {
        i += 1;
    }

    // Parse the bias unit prefix and magnitude. If a unit prefix is found, the
    // value adjusted by the corresponding bias factor.
    f64 bias = 1.0;
    const u8 *prefix = nullptr;

    for (u32 n = start; n < end; n++) {
        if (format.extra[i] == metric_prefix_keys[n]) {
            i += 1;

            if (is_memory && format.extra[i++] != 'i') {
                i -= 2;
            } else {
                bias = metric_factors[n];
                prefix = metric_prefixes[n];
            }

            break;
        }
    }

    // Parse the unit.
    const u8 *unit = nullptr;
    u8 buffer[format.extra_size - i + 1];

    if (i == format.extra_size) {
        unit = prefix;
        prefix = nullptr;
    } else if (format.extra[i] == '_') {
        i += 1;
        unit = nullptr;
    } else if (format.extra[i] == '*') {
        i += 1;
        unit = va_arg(*args, const u8 *);
    } else {
        u32 n = 0;

        while (i < format.extra_size) {
            buffer[n++] = format.extra[i++];
        }

        buffer[n] = '\0';
        unit = buffer;
    }

    // Adjust the value to represent the biased or nearest unit prefix.
    if (!prefix) {
        const f64 magnitude = value < 0 ? -value : value;
        u32 n = start;
        for (; n < end && metric_factors[n] >= magnitude; n++);
        bias = metric_factors[n];
        prefix = metric_prefixes[n];
    }

    format.type = 'f';
    format.base = 10;

    if (!format.has_precision) {
        format.precision = 3;
    }

    i = print_float(format, value / bias);
    i += this.write(sep);
    i += this.write(prefix);

    if (unit) {
        i += this.write(unit);
    }

    return i;
}
*/
