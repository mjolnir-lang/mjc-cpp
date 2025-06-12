#include <io/StringParser.hpp>


Error ParseFormat::parse(ParseFormat &parse_format, StringView format, std::initializer_list<Parsable> args, u32 default_index) {
    u32 i = 0;

    // Test the beginning of the format string.
    if (format.size() < 2 || format[i++] != '{') {
        return Error::FAILURE;
    }

    u32 index = i;

    // Look for a matching a closing brace. If we reach the end of the format
    // string before we find it, then the format string is invalid and we fail.
    // By determining a properly terminated format string, we remove the need
    // for end-of-string tests when accessing each character.
    for (u32 depth = 1; depth; i++) {
        if (i == format.size()) {
            return Error::FAILURE;
        }

        if (format[i] == '{') {
            depth += 1;
        } else if (format[i] == '}') {
            depth -= 1;
        }
    }

    // Save the format string to be trimmed after all format specifiers have been parsed.
    parse_format.extra = format.slice(index, i - 1);

    // Save the size of the format string and restore the parsing index to just
    // after the opening brace.
    parse_format.size = i;
    i = index;

    // Parse format argument index from the format string.
    index = 0;

    for (u32 digit; (digit = format[i] - '0') < 10u; i++) {
        index = (10u * index) + digit;
    }

    parse_format.index = i > 1 ? index : default_index;

    // Verify the argument index.
    if (parse_format.index > args.size()) {
        return Error::FAILURE;
    }

    parse_format.next_index = parse_format.index + 1;

    // Handle the empty format options case.
    if (format[i] == '}') {

        // Set default values.
        parse_format.type = ParseFormat::TYPE_NONE;
        parse_format.base = 10u;
        return Error::SUCCESS;
    }

    // Test for the beginning of format options specifier.
    if (format[i] == ':') {
        i += 1;

        // Parse the numeric base specifier from the format string.
        if (format[i] == '_') {
            i += 1;
            bool is_nested = format[i] == '{';

            if (is_nested) {
                i += 1;
            }

            index = i;
            parse_format.base = 0;

            for (u32 digit; (digit = format[i] - '0') < 10u; i++) {
                parse_format.base = (10u * parse_format.base) + digit;
            }

            if (is_nested) {
                parse_format.next_index = (i == index ? parse_format.next_index : parse_format.base) + 1;

                if (parse_format.base < args.size() && format[i] == '}') {
                    i += 1;
                    parse_format.base = args.begin()[parse_format.base].value<u32>();
                } else {
                    return Error::FAILURE;
                }
            }

            if (parse_format.base < 2u || parse_format.base > 36u) {
                return Error::FAILURE;
            }
        } else {
            parse_format.base = 10u;
        }

        // Parse the type specifier from the format string.
        parse_format.type = format[i];

        if (parse_format.type - 'A' <= 'Z' - 'A' || parse_format.type - 'a' <= 'z' - 'a') {
            i += 1;
        } else {
            parse_format.type = ParseFormat::TYPE_NONE;
        }
    }

    // Custom formatting
    if (format[i] == '!') {
        i += 1;
    } else if (format[i] != '}') {
        return Error::FAILURE;
    }

    // Remove the parsed format specifiers from the extra format data.
    parse_format.extra = parse_format.extra.slice(i - 1);
    return Error::SUCCESS;
}
