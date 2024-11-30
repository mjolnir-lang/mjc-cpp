#include <io/StringParser.hpp>


Error StringParser::parse_format_options() noexcept {
    u32 i = 0;

    // Test the beginning of the format string.
    if (_format_string.size() < 2 || _format_string[i++] != '{') {
        return Error::FAILURE;
    }

    u32 index = i;

    // Look for a matching a closing brace. If we reach the end of the format
    // string before we find it, then the format string is invalid and we fail.
    // By determining a properly terminated format string, we remove the need
    // for end-of-string tests when accessing each character.
    for (u32 depth = 1; depth; ++i) {
        if (i == _format_string.size()) {
            return Error::FAILURE;
        }

        if (_format_string[i] == '{') {
            depth += 1;
        } else if (_format_string[i] == '}') {
            depth -= 1;
        }
    }

    // Save the format string to be trimmed after all format specifiers have been parsed.
    _parse_format.extra = _format_string.slice(index, i - 1);

    // Save the size of the format string and restore the parsing index to just
    // after the opening brace.
    _parse_format.size = i;
    i = index;

    // Parse format argument index from the format string.
    index = 0;

    for (u32 digit; (digit = _format_string[i] - '0') < 10u; i++) {
        index = (10u * index) + digit;
    }

    _parse_format.index = i > 1 ? index : _next_index;

    // Verify the argument index.
    if (_parse_format.index > _args.size()) {
        return Error::FAILURE;
    }

    _next_index = _parse_format.index + 1;

    // Handle the empty format options case.
    if (_format_string[i] == '}') {

        // Set default values.
        _parse_format.type = ParseFormat::TYPE_NONE;
        _parse_format.base = 10u;
        return Error::SUCCESS;
    }

    // Test for the beginning of format options specifier.
    if (_format_string[i] == ':') {
        i += 1;

        // Parse the numeric base specifier from the format string.
        if (_format_string[i] == '_') {
            i += 1;
            bool is_nested = _format_string[i] == '{';

            if (is_nested) {
                i += 1;
            }

            index = i;
            _parse_format.base = 0;

            for (u32 digit; (digit = _format_string[i] - '0') < 10u; i++) {
                _parse_format.base = (10u * _parse_format.base) + digit;
            }

            if (is_nested) {
                _next_index = (i == index ? _next_index : _parse_format.base) + 1;

                if (_parse_format.base >= _args.size() || _format_string[i] != '}') {
                    return Error::FAILURE;
                }

                i += 1;
                _parse_format.base = _args[_parse_format.base].value<u32>();
            }

            if (_parse_format.base < 2u || _parse_format.base > 36u) {
                return Error::FAILURE;
            }
        } else {
            _parse_format.base = 10u;
        }

        // Parse the type specifier from the format string.
        _parse_format.type = _format_string[i];

        if (_parse_format.type - 'A' <= 'Z' - 'A' || _parse_format.type - 'a' <= 'z' - 'a') {
            i += 1;
        } else {
            _parse_format.type = ParseFormat::TYPE_NONE;
        }
    }

    // Custom formatting
    if (_format_string[i] == '!') {
        i += 1;
    } else if (_format_string[i] != '}') {
        return Error::FAILURE;
    }

    // Remove the parsed format specifiers from the extra format data.
    _parse_format.extra = _parse_format.extra.slice(i - 1);
    return Error::SUCCESS;
}


Error StringParser::parse(StringView string) noexcept {
    _next_index = 0; // Set this for use as the first the default index while parsing.
    _string = string;
    u32 bytes_parsed = 0;

    while (!_format_string.is_empty()) {
        u32 n = _format_string.find_first('{');

        if (n == _format_string.size()) {
            break;
        }

        // parse a literal "{" character when we see "{{".
        if (_format_string[n + 1] == '{') {
            for (u32 i = 0; i < n + 1 && _string[bytes_parsed] == _format_string[i]; i++) {
                bytes_parsed += 1;
            }

            _format_string += n + 2;
            continue;
        }

        // Write the normal format string characters up to the beginning of the format specifier
        for (u32 i = 0; i < n && _string[bytes_parsed] == _format_string[i]; i++) {
            bytes_parsed += 1;
        }

        // Adjust the format string reference.
        _format_string += n;

        // Parse the format specifier.
        if (parse_format_options().is_failure()) {
            break;
        }

        _format_string += _parse_format.size;

        if (_parse_format.type == 'n') {
            _args[_parse_format.index].set_value<u32>(bytes_parsed);
        } else {
            bytes_parsed += _args[_parse_format.index].parse(*this);
        }
    }

    // Upon failure, print the rest of the format string directly.
    return bytes_parsed;
}
