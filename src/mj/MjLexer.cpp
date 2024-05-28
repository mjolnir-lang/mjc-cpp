#include <mj/MjLexer.hpp>


struct MjKeywordInfo {
    const StringView text;
    MjTokenType token_type;
};


void MjLexer::append_token(MjTokenType type, u32 size) {
    if (type != MjTokenType::INDENT) {
        printf("%.*s # %u\n", size, _line.data(), static_cast<u32>(type));
    }

    _tokens.emplace_back(type, _line_index, _file[_line_index].size() - _line.size(), size);
    _line += size;
}


void MjLexer::append_subtoken(MjTokenType type, u32 offset, u32 size) {
    const MjToken &token = _tokens.back();
    printf("%.*s # %u\n", size, _file[token.line].data() + token.offset + offset, static_cast<u32>(type));
    _tokens.emplace_back(type, token.line, token.offset + offset, size);
}


void MjLexer::error(const MjToken &token, StringView message) {
    printf("%s:%u:%u: \x1B[31merror:\x1B[m ",
        _file.path().c_str(), token.line + 1, token.offset
    );
    printf("%.*s\n", message.size(), message.data());
    printf("\x1B[35m%*.*s\x1B[m",
        token.offset, token.size, "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
    );
}


void MjLexer::parse() {
    if (!_file.is_open()) {
        printf("Failed to open file! '%s'\n", _file.path().c_str());
        return;
    }

    _line = _file[0];

    //u32 i = 0;
    //for (StringView line : file.lines()) {
    //    printf("%3u|%.*s\n", ++i, line.size(), line.data());
    //}

    parse_tokens();
}


void MjLexer::parse_tokens() {
    while (true) {
        //if (parse_numeric_literal()) {
        //    continue;
        //}

        //return;
        //skip_whitespace();

        if (parse_operator().is_success()) {
            continue;
        }

        if (parse_identifier().is_success()) {
            continue;
        }

        if (parse_string_literal().is_success()) {
            continue;
        }

        break;
    }
}


void MjLexer::skip_whitespace() {

    // Parse horizontal whitespace.
    u32 i = 0;

    while (i < _line.size() && _line[i] == ' ') {
        i += 1;
    }

    if (i > 0) {
        append_token(MjTokenType::WHITESPACE, i);
    }

    // Check for middle of line.
    if (_line.size() > 0) {
        return;
    }

    // Skip empty lines.
    do {
        _line_index += 1;
        _line = _file[_line_index];
    } while (_line.size() == 0);

    // Parse indentation.
    i = 0;

    while (i < _line.size() && _line[i] == ' ') {
        i += 1;
    }

    // Check for invalid indentation.
    if (i % 4 != 0) {
        error("Invalid indentation!");
    }

    _last_indent = _line_indent;
    _line_indent = i / 4;
    append_token(MjTokenType::INDENT, i);
}










Error MjLexer::parse_token(StringView text, MjTokenType token_type, bool skip_trailing_whitespace) {
    if (!_line.starts_with(text)) {
        return Error::FAILURE;
    }

    append_token(token_type, text.size());

    if (skip_trailing_whitespace) {
        skip_whitespace();
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_operator(StringView text, MjTokenType token_type, bool skip_trailing_whitespace) {
    if (!_line.starts_with(text)) {
        return Error::FAILURE;
    }

    append_token(token_type, text.size());

    if (skip_trailing_whitespace) {
        skip_whitespace();
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_word(StringView text, MjTokenType token_type, bool skip_trailing_whitespace) {
    if (
        !_line.starts_with(text) || (
            text.size() < _line.size() &&
            (Char::is_alnum(_line[text.size()]) || _line[text.size()] == '_')
        )
    ) {
        return Error::FAILURE;
    }

    // Make sure this word is not part of a namespace.
    for (u32 i = text.size(); i < _line.size(); i++) {
        if (_line[i] == ':') {
            return Error::FAILURE;
        }
    }

    append_token(token_type, text.size());

    if (skip_trailing_whitespace) {
        skip_whitespace();
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_operator() {
    skip_whitespace();

    if (_line.is_empty()) {
        return Error::FAILURE;
    }

    switch (_line[0]) {
    case '@':
        append_token(MjTokenType::AT, _line.size());
        return Error::SUCCESS;
    case ';':
        append_token(MjTokenType::SEMICOLON, 1);
        return Error::SUCCESS;
    case ',':
        append_token(MjTokenType::COMMA, 1);
        return Error::SUCCESS;
    case '[':
        append_token(MjTokenType::OPEN_SQUARE_BRACKET, 1);
        return Error::SUCCESS;
    case ']':
        append_token(MjTokenType::CLOSE_SQUARE_BRACKET, 1);
        return Error::SUCCESS;
    case '(':
        append_token(MjTokenType::OPEN_PARENTHESIS, 1);
        return Error::SUCCESS;
    case ')':
        append_token(MjTokenType::CLOSE_PARENTHESIS, 1);
        return Error::SUCCESS;
    case '{':
        append_token(MjTokenType::OPEN_CURLY_BRACE, 1);
        return Error::SUCCESS;
    case '}':
        append_token(MjTokenType::CLOSE_CURLY_BRACE, 1);
        return Error::SUCCESS;
    case '*':
        if (_line.size() > 1 && _line[1] == '=') {
            append_token(MjTokenType::MULTIPLY_SET, 2);
            return Error::SUCCESS;
        }

        append_token(MjTokenType::MULTIPLY, 1);
        return Error::SUCCESS;
    case '/':
        if (_line.size() > 1) {
            if (_line[1] == '/') {
                MjTokenType token_type;

                if (_line.size() > 2 && _line[2] == '/') {
                    token_type = _line.contains("`") ? MjTokenType::FORMATTED_BLOCK_COMMENT : MjTokenType::BLOCK_COMMENT;
                } else {
                    token_type = _line.contains("`") ? MjTokenType::FORMATTED_LINE_COMMENT : MjTokenType::LINE_COMMENT;
                }

                append_token(token_type, _line.size());
                return Error::SUCCESS;
            }

            if (_line.size() > 1 && _line[1] == '=') {
                append_token(MjTokenType::DIVIDE_SET, 2);
                return Error::SUCCESS;
            }
        }

        append_token(MjTokenType::DIVIDE, 1);
        return Error::SUCCESS;
    case '%':
        if (_line.size() > 1 && _line[1] == '=') {
            append_token(MjTokenType::REMAINDER_SET, 2);
            return Error::SUCCESS;
        }

        append_token(MjTokenType::REMAINDER, 1);
        return Error::SUCCESS;
    case '+':
        if (_line.size() > 1) {
            if (_line[1] == '=') {
                append_token(MjTokenType::PLUS_SET, 2);
                return Error::SUCCESS;
            }

            if (_line[1] - '0' < 10) {
                // This is a positive numeric literal.
                return Error::FAILURE;
            }
        }

        append_token(MjTokenType::PLUS, 1);
        return Error::SUCCESS;
    case '-':
        if (_line.size() > 1) {
            if (_line[1] == '=') {
                append_token(MjTokenType::MINUS_SET, 2);
                return Error::SUCCESS;
            }

            if (_line[1] - '0' < 10) {
                // This is a negative numeric literal.
                return Error::FAILURE;
            }
        }

        append_token(MjTokenType::MINUS, 1);
        return Error::SUCCESS;
    case '&':
        if (_line.size() > 1) {
            if (_line[1] == '&') {
                if (_line.size() > 2 && _line[2] == '=') {
                    append_token(MjTokenType::LOGICAL_AND_SET, 3);
                    return Error::SUCCESS;
                }

                append_token(MjTokenType::LOGICAL_AND, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '=') {
                append_token(MjTokenType::BITWISE_AND_SET, 2);
                return Error::SUCCESS;
            }
        }

        append_token(MjTokenType::BITWISE_AND, 1);
        return Error::SUCCESS;
    case '^':
        if (_line.size() > 1) {
            if (_line[1] == '|') {
                if (_line.size() > 2 && _line[2] == '=') {
                    append_token(MjTokenType::LOGICAL_XOR_SET, 3);
                    return Error::SUCCESS;
                }

                append_token(MjTokenType::LOGICAL_XOR, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '=') {
                append_token(MjTokenType::BITWISE_XOR_SET, 2);
                return Error::SUCCESS;
            }
        }

        append_token(MjTokenType::BITWISE_XOR, 1);
        return Error::SUCCESS;
    case '|':
        if (_line.size() > 1) {
            if (_line[1] == '|') {
                if (_line.size() > 2 && _line[2] == '=') {
                    append_token(MjTokenType::LOGICAL_OR_SET, 3);
                    return Error::SUCCESS;
                }

                append_token(MjTokenType::LOGICAL_OR, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '=') {
                append_token(MjTokenType::BITWISE_OR_SET, 2);
                return Error::SUCCESS;
            }
        }

        append_token(MjTokenType::BITWISE_OR, 1);
        return Error::SUCCESS;
    case '~':
        append_token(MjTokenType::INVERT, 1);
        return Error::SUCCESS;
    case '=':
        if (_line.size() > 1) {
            if (_line[1] == '=') {
                append_token(MjTokenType::EQUAL, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '>') {
                append_token(MjTokenType::LAMBDA, 2);
                return Error::SUCCESS;
            }
        }

        append_token(MjTokenType::SET, 1);
        return Error::SUCCESS;
    case '!':
        if (_line.size() > 1 && _line[1] == '=') {
            append_token(MjTokenType::NOT_EQUAL, 2);
            return Error::SUCCESS;
        }

        append_token(MjTokenType::NOT, 1);
        return Error::SUCCESS;
    case '?':
        append_token(MjTokenType::QUESTION, 1);
        return Error::SUCCESS;
    case '.':
        append_token(MjTokenType::DOT, 1);
        return Error::SUCCESS;
    case ':':
        if (_line.size() > 1 && _line[1] == ':') {
            append_token(MjTokenType::SCOPE, 2);
            return Error::SUCCESS;
        }

        append_token(MjTokenType::COLON, 1);
        return Error::SUCCESS;
    case '<':
        if (_line.size() > 1) {
            if (_line[1] == '<') {
                if (_line.size() > 2 && _line[2] == '=') {
                    append_token(MjTokenType::LEFT_SHIFT_SET, 3);
                    return Error::SUCCESS;
                }

                append_token(MjTokenType::LEFT_SHIFT, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '=') {
                if (_line.size() > 2 && _line[2] == '>') {
                    append_token(MjTokenType::SPACESHIP, 3);
                    return Error::SUCCESS;
                }

                append_token(MjTokenType::LESS_THAN_OR_EQUAL, 2);
                return Error::SUCCESS;
            }
        }

        append_token(MjTokenType::LESS_THAN, 1);
        return Error::SUCCESS;
    case '>':
        if (_line.size() > 1) {
            if (_line[1] == '<') {
                if (_line.size() > 2 && _line[2] == '=') {
                    append_token(MjTokenType::RIGHT_SHIFT_SET, 3);
                    return Error::SUCCESS;
                }

                append_token(MjTokenType::RIGHT_SHIFT, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '=') {
                append_token(MjTokenType::GREATER_THAN_OR_EQUAL, 2);
                return Error::SUCCESS;
            }
        }

        append_token(MjTokenType::GREATER_THAN, 1);
        return Error::SUCCESS;
    default:
        return Error::FAILURE;
    }
}


Error MjLexer::parse_type_expression() {
    skip_whitespace();

    MjLexerPosition pos = save();

    // Parse the base type.
    while (parse_type_qualifier().is_success());

    if (parse_identifier().is_failure()) {
        restore(pos);
        return Error::FAILURE;
    }

    // Parse the type modifiers.
    //while (parse_type_modifier());

    return Error::SUCCESS;
}


Error MjLexer::parse_unit_expression() {
    skip_whitespace();
    u32 i = 0;

    // [A-Za-zµΩÅ°'"]|^g|1/
    while (true) {
        if (i == _line.size()) {
            return Error::FAILURE;
        }

        u32 value = _line[i];

        if (
            (value | 0x20u) - 'a' < 26 ||
            value == '\'' ||
            value == '"'
        ) {
            i += 1;
            break;
        }

        if (i + 1u == _line.size()) {
            return Error::FAILURE;
        }

        value = (value << 8) | _line[i + 1];

        if (
            value == (('^' << 8) | 'g') || // '^g'
            value == (('1' << 8) | '/') || // '1/'
            value == 0xC2B0u || // '°'
            value == 0xC2B5u || // 'µ'
            value == 0xC2B7u || // '·'
            value == 0xC385u || // 'Å'
            value == 0xCEA9u    // 'Ω'
        ) {
            i += 2;
            break;
        }

        return Error::FAILURE;
    }

    // [A-Za-z0-9µΩÅ°'"⁰¹²³⁴⁵⁶⁷⁸⁹⁻⸍·^*/-]*
    while (true) {
        if (i == _line.size()) {
            break;
        }

        u32 value = _line[i];

        if (
            (value | 0x20u) - 'a' < 26 || value - '0' < 10 ||
            value == '\'' ||
            value == '"' ||
            value == '^' ||
            value == '*' ||
            value == '/' ||
            value == '-'
        ) {
            i += 1;
            continue;
        }

        if (i + 1u == _line.size()) {
            break;
        }

        value = (value << 8) | _line[i + 1];

        if (
            value == 0xC2B0u || // '°'
            value == 0xC2B2u || // '²'
            value == 0xC2B3u || // '³'
            value == 0xC2B5u || // 'µ'
            value == 0xC2B7u || // '·'
            value == 0xC2B9u || // '¹'
            value == 0xC385u || // 'Å'
            value == 0xCEA9u    // 'Ω'
        ) {
            i += 2;
            continue;
        }

        if (i + 2u == _line.size()) {
            break;
        }

        value = (value << 8) | _line[i + 2];

        if (
            value == 0xE281B0u || // '⁰'
            value == 0xE281B4u || // '⁴'
            value == 0xE281B5u || // '⁵'
            value == 0xE281B6u || // '⁶'
            value == 0xE281B7u || // '⁷'
            value == 0xE281B8u || // '⁸'
            value == 0xE281B9u || // '⁹'
            value == 0xE281BBu || // '⁻'
            value == 0xE2B88Du    // '⸍'
        ) {
            i += 3;
            continue;
        }

        break;
    }

    append_token(MjTokenType::UNIT, i);
    return Error::SUCCESS;
}




Error MjLexer::parse_string_literal() {
    if (parse_interpolated_string_literal().is_success()) {
        return Error::SUCCESS;
    }

    return parse_raw_string_literal();
}


Error MjLexer::parse_interpolated_string_literal() {
    skip_whitespace();

    if (!_line.starts_with('"')) {
        return Error::FAILURE;
    }

    u32 i = 1;
    MjTokenType token_type = MjTokenType::STRING_LITERAL;

    while (i < _line.size() && _line[i] != '"') {
        if (_line[i] == '\\') {
            token_type = MjTokenType::INTERPOLATED_STRING_LITERAL;
            i += 1;

            if (i == _line.size()) {
                break;
            }

            MjToken escape_sequence = MjToken(
                MjTokenType::CHARACTER_ESCAPE_SEQUENCE,
                _line_index,
                _file[_line_index].size() - _line.size(),
                0
            );

            switch (_line[i]) {
            case '\\': // '\\'
                break;
            case '"': // '\"'
                break;
            case 'e': // '\e'
                break;
            case 'n': // '\n'
                break;
            case 'r': // '\r'
                break;
            case 't': // '\t'
                break;
            case '0': // '\0'
                break;
            case 'o': // '\o377'
                for (u32 n = i + 3; i < n; i++) {
                    if (i == _line.size() || _line[i] - '0' < 8) {
                        escape_sequence.size = i;
                        error(escape_sequence, "Invalid string escape sequence! (\"\\o\" requires 3 octal digits)");
                        // consume the character and continue parsing.
                        break;
                    }
                }

                if (_line[i - 3] > '3') {
                    escape_sequence.size = 5;
                    error(escape_sequence, "Invalid string escape sequence! (Max value is \"\\o377\")");
                }

                break;
            case 'x': // '\x7F'
                for (u32 n = i + 2; i < n; i++) {
                    if (i == _line.size() || _line[i] - '0' < 10 || (_line[i] | 0x20u) - 'a' < 6) {
                        escape_sequence.size = i;
                        error(escape_sequence, "Invalid string escape sequence! (\"\\x\" requires 2 hexadecimal digits)");
                        // consume the character and continue parsing.
                        break;
                    }
                }

                if (_line[i - 2] > '7') {
                    escape_sequence.size = 4;
                    error(escape_sequence, "Invalid string escape sequence! (Max value is \"\\x7F\")");
                }

                break;
            case 'u': // '\uFFFF'
                for (u32 n = i + 4; i < n; i++) {
                    if (i == _line.size() || _line[i] - '0' < 10 || (_line[i] | 0x20u) - 'a' < 6) {
                        escape_sequence.size = i;
                        error(escape_sequence, "Invalid Unicode string escape sequence! (\"\\u\" requires 4 hexadecimal digits)");
                        // consume the character and continue parsing.
                        break;
                    }
                }

                break;
            case 'U': // '\U10FFFF'
                for (u32 n = i + 6; i < n; i++) {
                    if (i == _line.size() || _line[i] - '0' < 10 || (_line[i] | 0x20u) - 'a' < 6) {
                        escape_sequence.size = i;
                        error(escape_sequence, "Invalid Unicode string escape sequence! (\"\\U\" requires 6 hexadecimal digits)");
                        // consume the character and continue parsing.
                        break;
                    }
                }

                if (_line[i - 6] > '1' || (_line[i - 6] == '1' && _line[i - 5] > '0')) {
                    escape_sequence.size = 8;
                    error(escape_sequence, "Invalid string escape sequence! (Max value is \"\\U10FFFF\")");
                }

                break;
            default:
                escape_sequence.size = 2;
                error(escape_sequence, "Invalid string escape sequence!");
                // consume the character and continue parsing.
            }
        }

        i += 1;
    }

    if (i == _line.size()) {
        error("Unterminated string literal!");
        // consume the rest of the line and continue parsing.
    }

    append_token(token_type, i);
    return Error::SUCCESS;
}


Error MjLexer::parse_raw_string_literal() {
    skip_whitespace();

    if (!_line.starts_with('\'')) {
        return Error::FAILURE;
    }

    u32 i = _line.size();
    while (_line[--i] != '\'');

    if (i == 0) {
        error("Unterminated raw string literal!");
        return Error::FAILURE;
    }

    append_token(MjTokenType::RAW_STRING_LITERAL, i);
    return Error::SUCCESS;
}





Error MjLexer::parse_expression() {
    while (true) {

        if (parse_numeric_literal().is_success()) {
            continue;
        }

        if (parse_identifier().is_success()) {
            continue;
        }

        if (parse_operator().is_success()) {
            continue;
        }

        if (parse_string_literal().is_success()) {
            continue;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}







Error MjLexer::parse_template_parameter_list() {
    MjLexerPosition pos = save();

    if (parse_operator("<", MjTokenType::OPEN_ANGLE_BRACKET).is_failure()) {
        return Error::FAILURE;
    }

    // We need to make sure this is an opening angle bracket and not a less than operator.

    do {
        if (parse_type_expression().is_failure()) {
            break;
        }
    } while (parse_token(",", MjTokenType::COMMA).is_success());

    if (parse_operator(">", MjTokenType::CLOSE_ANGLE_BRACKET).is_failure()) {
        restore(pos);
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_template_argument_list() {
    MjLexerPosition pos = save();

    if (parse_token("<", MjTokenType::OPEN_ANGLE_BRACKET).is_failure()) {
        return Error::FAILURE;
    }

    // We need to make sure this is an opening angle bracket and not a less than operator.
    do {
        if (parse_word("type", MjTokenType::TYPE).is_success()) {
            if (parse_type_name().is_failure()) {
                error("Missing type name!");
            }

            if (parse_operator("=", MjTokenType::SET).is_success()) {
                if (parse_type_expression().is_success()) {
                    error("Missing default type expression!");
                }
            }
        } else if (parse_type_expression().is_success()) {
            if (parse_variable_name().is_failure()) {
                error("Missing variable name!");
            }

            if (parse_operator("=", MjTokenType::SET).is_success()) {
                if (parse_expression().is_failure()) {
                    error("Missing default expression!");
                }
            }
        } else {
            error("Invalid template argument!");
            // Look for another ',' or '>' to synchronize, but we might be missing those...
            // See what's next and go from there.
        }
    } while (parse_token(",", MjTokenType::COMMA).is_success());

    if (parse_operator(">", MjTokenType::CLOSE_ANGLE_BRACKET).is_failure()) {
        restore(pos);
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_function_parameter_list() {
    MjLexerPosition pos = save();

    if (parse_token("(", MjTokenType::OPEN_PARENTHESIS).is_failure()) {
        return Error::FAILURE;
    }

    do {
        if (parse_type_expression().is_success()) {
        }
    } while (parse_token(",", MjTokenType::COMMA).is_success());

    if (parse_token(")", MjTokenType::CLOSE_PARENTHESIS).is_failure()) {
        restore(pos);
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_function_argument_list() {
    MjLexerPosition pos = save();

    if (parse_token("(", MjTokenType::OPEN_PARENTHESIS).is_failure()) {
        return Error::FAILURE;
    }

    do {
        if (parse_type_expression().is_failure()) {
            break;
        }
    } while (parse_token(",", MjTokenType::COMMA).is_success());

    if (parse_token(")", MjTokenType::CLOSE_PARENTHESIS).is_failure()) {
        restore(pos);
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_parenthesis_expression() {
    skip_whitespace();

    MjLexerPosition pos = save();

    if (parse_token("(", MjTokenType::OPEN_PARENTHESIS).is_failure()) {
        return Error::FAILURE;
    }

    if (parse_expression().is_failure()) {
        return Error::FAILURE;
    }

    if (parse_token(")", MjTokenType::CLOSE_PARENTHESIS).is_failure()) {
        restore(pos);
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_type_cast_expression() {
    skip_whitespace();

    MjLexerPosition pos = save();

    if (parse_token("(", MjTokenType::OPEN_PARENTHESIS).is_failure()) {
        return Error::FAILURE;
    }

    if (parse_type_expression().is_success()) {
        parse_token(":", MjTokenType::COLON);
        parse_expression();
    }

    if (parse_token(")", MjTokenType::CLOSE_PARENTHESIS).is_failure()) {
        restore(pos);
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}















// [0-9]*[a-_z][a-z0-_9]*
// [A-Z][A-Z0-_9]+|[0-_9]+[A-Z][A-Z0-_9]*
Error MjLexer::parse_identifier() {
    skip_whitespace();

    if (_line.is_empty()) {
        return Error::FAILURE;
    }

    u32 i = 0;
    u32 variable_end = 0;
    MjTokenType token_type = MjTokenType::INVALID_IDENTIFIER;




    // Module name

    // [A-Za-z0-9]
    if (i >= _line.size() || !Char::is_alnum(_line[i])) {
        return Error::FAILURE;
    }

    i += 1;

    // [A-Za-z0-9.+-]*
    while (i < _line.size() && (Char::is_alnum(_line[i]) || _line[i] == '+' || _line[i] == '-' || _line[i] == '.')) {
        i += 1;
    }

    // (?=::)
    if (i + 1u >= _line.size() || _line[i] != ':' || _line[i + 1] != ':') {
        return Error::FAILURE;
    }

    append_token(MjTokenType::MODULE_NAME, i);
    append_token(MjTokenType::SCOPE, 2);




    // Check for word boundary.
    if (Char::is_alnum(_line[i]) || _line[i] == '_') {
        return Error::FAILURE;
    }



    // Check for word boundary.
    if (i < _line.size() && (Char::is_alnum(_line[i]) || _line[i] == '_')) {
        return Error::FAILURE;
    }



    if (token_type == MjTokenType::VARIABLE_NAME) {

        // These keywords are not safe to use as variable or function names.
        static
        const MjKeywordInfo PURE_KEYWORDS[] = {
            {"break", MjTokenType::BREAK},
            {"bool", MjTokenType::TYPE_NAME},
            {"const", MjTokenType::CONST},
            {"continue", MjTokenType::CONTINUE},
            {"f16",  MjTokenType::TYPE_NAME},
            {"f32",  MjTokenType::TYPE_NAME},
            {"f64",  MjTokenType::TYPE_NAME},
            {"f80",  MjTokenType::TYPE_NAME},
            {"f128", MjTokenType::TYPE_NAME},
            {"fail", MjTokenType::FAIL},
            {"false", MjTokenType::CONSTANT_NAME},
            {"i8",   MjTokenType::TYPE_NAME},
            {"i16",  MjTokenType::TYPE_NAME},
            {"i32",  MjTokenType::TYPE_NAME},
            {"i64",  MjTokenType::TYPE_NAME},
            {"i128", MjTokenType::TYPE_NAME},
            {"mutable", MjTokenType::MUTABLE},
            {"null", MjTokenType::CONSTANT_NAME},
            {"return", MjTokenType::RETURN},
            {"safe", MjTokenType::SAFE},
            {"true", MjTokenType::CONSTANT_NAME},
            {"u8",   MjTokenType::TYPE_NAME},
            {"u16",  MjTokenType::TYPE_NAME},
            {"u32",  MjTokenType::TYPE_NAME},
            {"u64",  MjTokenType::TYPE_NAME},
            {"u128", MjTokenType::TYPE_NAME},
            {"uninitialized", MjTokenType::CONSTANT_NAME},
            {"void", MjTokenType::TYPE_NAME},
            {"volatile", MjTokenType::VOLATILE},
            {"yield", MjTokenType::YIELD},
        };

        for (const MjKeywordInfo &info : PURE_KEYWORDS) {
            if (parse_word(info.text, info.token_type).is_success()) {
                return Error::SUCCESS;
            }
        }

        // These keywords have trailing context.
        MjLexerPosition pos = save();

        // These keywords are safe to use as variable or function names, but they
        // may not be used as generic function names.
        static
        const MjKeywordInfo GENERIC_KEYWORDS[] = {
            {"bitfield", MjTokenType::BITFIELD},
            {"enum", MjTokenType::ENUM},
            {"impl", MjTokenType::IMPL},
            {"type", MjTokenType::TYPE},
            {"unit", MjTokenType::UNIT},
            {"variant", MjTokenType::VARIANT},
            {"where", MjTokenType::WHERE},
        };

        for (const MjKeywordInfo &info : GENERIC_KEYWORDS) {
            if (parse_word(info.text, info.token_type, false).is_success()) {
                if (_line.starts_with('<')) {
                    parse_template_argument_list();
                    return Error::SUCCESS;
                }

                restore(pos);
                return Error::FAILURE;
            }
        }

        // These keywords are followed by a type name, a variable name, or an open brace '{'.
        //
        // If they are followed by the keywords 'as' or 'is', then those keywords
        // must be followed by type expressions. If neither 'as' nor 'is' is
        // followed by a type expression, then they are not keyword operators, and
        // the potential match is a keyword.
        //
        // These keywords are safe to use as variable or function names.
        static
        const MjKeywordInfo SCOPED_KEYWORDS[] = {
            {"asm", MjTokenType::ASM},
            {"class", MjTokenType::CLASS},
            {"do", MjTokenType::DO},
            {"else", MjTokenType::ELSE},
            {"import", MjTokenType::IMPORT},
            {"interface", MjTokenType::INTERFACE},
            {"struct", MjTokenType::STRUCT},
            {"union", MjTokenType::UNION},
        };

        for (const MjKeywordInfo &info : SCOPED_KEYWORDS) {
            if (parse_word(info.text, info.token_type, false).is_success()) {
                if (_line.starts_with(' ')) {
                    skip_whitespace();

                    if (_line.size() > 0 && (_line[0] == '{' || (_line[0] | 0x20u) - 'a' < 26 || _line[0] - '0' < 10 || _line[0] == '_')) {
                        return Error::SUCCESS;
                    }
                }

                restore(pos);
                return Error::FAILURE;
            }
        }

        // These keywords are followed by a whitespace and an open parenthesis '('.
        // The space is necessary to differentiate them from function names.
        //
        // These keywords are safe to use as variable or function names.
        static
        const MjKeywordInfo PARAMETERIZED_KEYWORDS[] = {
            {"for", MjTokenType::FOR},               // 'for ('
            {"if", MjTokenType::IF},                 // 'if ('
            {"match", MjTokenType::MATCH},           // 'match ('
            {"until", MjTokenType::UNTIL},           // 'until ('
            {"while", MjTokenType::WHILE},           // 'while ('
        };

        for (const MjKeywordInfo &info : PARAMETERIZED_KEYWORDS) {
            if (parse_word(info.text, info.token_type, false).is_success()) {
                if (_line.starts_with(' ')) {
                    skip_whitespace();

                    if (_line.starts_with('(')) {
                        return Error::SUCCESS;
                    }
                }

                restore(pos);
                return Error::FAILURE;
            }
        }

        // These keywords are binary operators that require a type as the right
        // hand operand. In situations where they may be confused as unit
        // expressions, the following token will determine their type. If followed
        // by a type expression, they are keywords, otherwise they are subject to
        // default parsing rules.
        //
        // These keywords are safe to use as variable or function names.
        static
        const MjKeywordInfo TYPE_OP_KEYWORDS[] = {
            {"as", MjTokenType::AS},                 // 'as (type)'
            {"is", MjTokenType::IS},                 // 'is (type)'
        };

        for (const MjKeywordInfo &info : TYPE_OP_KEYWORDS) {
            if (parse_word(info.text, info.token_type, false).is_success()) {
                if (_line.starts_with(' ')) {
                    skip_whitespace();
                    return Error::SUCCESS;
                }

                restore(pos);
                return Error::FAILURE;
            }
        }

        append_token(MjTokenType::VARIABLE_NAME, i);
    }



    append_token(MjTokenType::VARIABLE_NAME, i);
    return Error::SUCCESS;
}















































Error MjLexer::parse_numeric_literal() {
    skip_whitespace();
    u32 token_size = 0;
    MjTokenType token_type = MjTokenType::I32_LITERAL;

    // Parse the sign.
    bool has_sign = token_size < _line.size() && (_line[token_size] == '+' || _line[token_size] == '-');

    if (has_sign) {
        token_size += 1;
    }

    // Parse the base prefix.
    u32 base = 10;

    if (token_size + 1u < _line.size() && _line[token_size] == '0') {
        token_size += 1;

        if (_line[token_size] == 'x') {
            token_size += 1;
            token_type = MjTokenType::U32_LITERAL;
            base = 16;
        } else if (_line[token_size] == 'o') {
            token_size += 1;
            token_type = MjTokenType::U32_LITERAL;
            base = 8;
        } else if (_line[token_size] == 'b') {
            token_size += 1;
            token_type = MjTokenType::U32_LITERAL;
            base = 2;
        }
    }

    // Parse the integer portion.
    while (token_size < _line.size() && Char::is_digit_upper(_line[token_size], base)) {
        token_size += 1;
    }

    if (token_size == 0 || !Char::is_digit_upper(_line[token_size - 1], base)) {
        return Error::FAILURE;
    }

    // Parse the fractional portion.
    if ((base == 10 || base == 16) && token_size < _line.size() && _line[token_size] == '.') {
        token_size += 1;
        token_type = MjTokenType::F64_LITERAL;

        while (token_size < _line.size() && Char::is_digit_upper(_line[token_size], base)) {
            token_size += 1;
        }
    }

    // Parse the exponent portion.
    if (token_size < _line.size() && ((base == 10 && _line[token_size] == 'e') || (base == 16 && _line[token_size] == 'p'))) {
        token_size += 1;
        token_type = MjTokenType::F64_LITERAL;

        // Parse the exponent sign.
        if (token_size < _line.size() && (_line[token_size] == '+' || _line[token_size] == '-')) {
            token_size += 1;
        }

        while (token_size < _line.size() && Char::is_digit(_line[token_size])) {
            token_size += 1;
        }
    }

    // Parse the type suffix.
    static
    const MjKeywordInfo NUMERIC_LITERAL_SUFFIXES[] = {
        {"f128", MjTokenType::F128_LITERAL},
        {"f16", MjTokenType::F16_LITERAL},
        {"f32", MjTokenType::F32_LITERAL},
        {"f64", MjTokenType::F64_LITERAL},
        {"f80", MjTokenType::F80_LITERAL},
        {"f", MjTokenType::F32_LITERAL},
        {"i128", MjTokenType::I128_LITERAL},
        {"i16", MjTokenType::I16_LITERAL},
        {"i32", MjTokenType::I32_LITERAL},
        {"i64", MjTokenType::I64_LITERAL},
        {"i8", MjTokenType::I8_LITERAL},
        {"i", MjTokenType::I32_LITERAL},
        {"u128", MjTokenType::U128_LITERAL},
        {"u16", MjTokenType::U16_LITERAL},
        {"u32", MjTokenType::U32_LITERAL},
        {"u64", MjTokenType::U64_LITERAL},
        {"u8", MjTokenType::U8_LITERAL},
        {"u", MjTokenType::U32_LITERAL},
    };

    u32 postfix_size = 0;

    for (const MjKeywordInfo &info : NUMERIC_LITERAL_SUFFIXES) {
        if (_line.slice(token_size).starts_with(info.text)) {
            postfix_size = info.text.size();
            token_size += postfix_size;
            token_type = info.token_type;
            break;
        }
    }

    // Parse module name.
    if (parse_module_name()) {
        return Error::FAILURE;
    }

    // Check for word boundary.
    if (token_size < _line.size() && (Char::is_alnum(_line[token_size]) || _line[token_size] == '_')) {
        return Error::FAILURE;
    }



    // Check for module name.

    append_token(token_type, token_size);

    if (_emit_subtokens) {
        if (base != 10) {
            append_subtoken(MjTokenType::NUMERIC_LITERAL_PREFIX, token_size - 2, 2);
        }

        if (postfix_size > 0) {
            append_subtoken(MjTokenType::NUMERIC_LITERAL_POSTFIX, postfix_size, postfix_size);
        }
    }

    if (!_line.is_empty() && _line[0] == ' ') {
        // Unit expression has priority after a numeric literal.
        parse_unit_expression();
    }

    if (has_sign) {
        // Only a numeric literal can start with a sign character, so no identifiers will match.
        // Check for an operator token.
    }

    return Error::SUCCESS;
}































MjTokenType MjLexer::parse_token(bool skip_trailing_whitespace) {
skip_whitespace();

    if (_line.is_empty()) {
        return Error::FAILURE;
    }

    switch (_line[0]) {
    case '@':
        append_token(MjTokenType::AT, _line.size());
        return Error::SUCCESS;
    case ';':
        append_token(MjTokenType::SEMICOLON, 1);
        return Error::SUCCESS;
    case ',':
        append_token(MjTokenType::COMMA, 1);
        return Error::SUCCESS;
    case '[':
        append_token(MjTokenType::OPEN_SQUARE_BRACKET, 1);
        return Error::SUCCESS;
    case ']':
        append_token(MjTokenType::CLOSE_SQUARE_BRACKET, 1);
        return Error::SUCCESS;
    case '(':
        append_token(MjTokenType::OPEN_PARENTHESIS, 1);
        return Error::SUCCESS;
    case ')':
        append_token(MjTokenType::CLOSE_PARENTHESIS, 1);
        return Error::SUCCESS;
    case '{':
        append_token(MjTokenType::OPEN_CURLY_BRACE, 1);
        return Error::SUCCESS;
    case '}':
        append_token(MjTokenType::CLOSE_CURLY_BRACE, 1);
        return Error::SUCCESS;
    case '*':
        if (_line.size() > 1 && _line[1] == '=') {
            append_token(MjTokenType::MULTIPLY_SET, 2);
            return Error::SUCCESS;
        }

        append_token(MjTokenType::MULTIPLY, 1);
        return Error::SUCCESS;
    case '/':
        if (_line.size() > 1) {
            if (_line[1] == '/') {
                MjTokenType token_type;

                if (_line.size() > 2 && _line[2] == '/') {
                    token_type = _line.contains("`") ? MjTokenType::FORMATTED_BLOCK_COMMENT : MjTokenType::BLOCK_COMMENT;
                } else {
                    token_type = _line.contains("`") ? MjTokenType::FORMATTED_LINE_COMMENT : MjTokenType::LINE_COMMENT;
                }

                append_token(token_type, _line.size());
                return Error::SUCCESS;
            }

            if (_line.size() > 1 && _line[1] == '=') {
                append_token(MjTokenType::DIVIDE_SET, 2);
                return Error::SUCCESS;
            }
        }

        append_token(MjTokenType::DIVIDE, 1);
        return Error::SUCCESS;
    case '%':
        if (_line.size() > 1 && _line[1] == '=') {
            append_token(MjTokenType::REMAINDER_SET, 2);
            return Error::SUCCESS;
        }

        append_token(MjTokenType::REMAINDER, 1);
        return Error::SUCCESS;
    case '+':
        if (_line.size() > 1) {
            if (_line[1] == '=') {
                append_token(MjTokenType::PLUS_SET, 2);
                return Error::SUCCESS;
            }

            if (_line[1] - '0' < 10) {
                // This is a positive numeric literal.
                return Error::FAILURE;
            }
        }

        append_token(MjTokenType::PLUS, 1);
        return Error::SUCCESS;
    case '-':
        if (_line.size() > 1) {
            if (_line[1] == '=') {
                append_token(MjTokenType::MINUS_SET, 2);
                return Error::SUCCESS;
            }

            if (_line[1] - '0' < 10) {
                // This is a negative numeric literal.
                return Error::FAILURE;
            }
        }

        append_token(MjTokenType::MINUS, 1);
        return Error::SUCCESS;
    case '&':
        if (_line.size() > 1) {
            if (_line[1] == '&') {
                if (_line.size() > 2 && _line[2] == '=') {
                    append_token(MjTokenType::LOGICAL_AND_SET, 3);
                    return Error::SUCCESS;
                }

                append_token(MjTokenType::LOGICAL_AND, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '=') {
                append_token(MjTokenType::BITWISE_AND_SET, 2);
                return Error::SUCCESS;
            }
        }

        append_token(MjTokenType::BITWISE_AND, 1);
        return Error::SUCCESS;
    case '^':
        if (_line.size() > 1) {
            if (_line[1] == '|') {
                if (_line.size() > 2 && _line[2] == '=') {
                    append_token(MjTokenType::LOGICAL_XOR_SET, 3);
                    return Error::SUCCESS;
                }

                append_token(MjTokenType::LOGICAL_XOR, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '=') {
                append_token(MjTokenType::BITWISE_XOR_SET, 2);
                return Error::SUCCESS;
            }
        }

        append_token(MjTokenType::BITWISE_XOR, 1);
        return Error::SUCCESS;
    case '|':
        if (_line.size() > 1) {
            if (_line[1] == '|') {
                if (_line.size() > 2 && _line[2] == '=') {
                    append_token(MjTokenType::LOGICAL_OR_SET, 3);
                    return Error::SUCCESS;
                }

                append_token(MjTokenType::LOGICAL_OR, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '=') {
                append_token(MjTokenType::BITWISE_OR_SET, 2);
                return Error::SUCCESS;
            }
        }

        append_token(MjTokenType::BITWISE_OR, 1);
        return Error::SUCCESS;
    case '~':
        append_token(MjTokenType::INVERT, 1);
        return Error::SUCCESS;
    case '=':
        if (_line.size() > 1) {
            if (_line[1] == '=') {
                append_token(MjTokenType::EQUAL, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '>') {
                append_token(MjTokenType::LAMBDA, 2);
                return Error::SUCCESS;
            }
        }

        append_token(MjTokenType::SET, 1);
        return Error::SUCCESS;
    case '!':
        if (_line.size() > 1 && _line[1] == '=') {
            append_token(MjTokenType::NOT_EQUAL, 2);
            return Error::SUCCESS;
        }

        append_token(MjTokenType::NOT, 1);
        return Error::SUCCESS;
    case '?':
        append_token(MjTokenType::QUESTION, 1);
        return Error::SUCCESS;
    case '.':
        append_token(MjTokenType::DOT, 1);
        return Error::SUCCESS;
    case ':':
        if (_line.size() > 1 && _line[1] == ':') {
            append_token(MjTokenType::SCOPE, 2);
            return Error::SUCCESS;
        }

        append_token(MjTokenType::COLON, 1);
        return Error::SUCCESS;
    case '<':
        if (_line.size() > 1) {
            if (_line[1] == '<') {
                if (_line.size() > 2 && _line[2] == '=') {
                    append_token(MjTokenType::LEFT_SHIFT_SET, 3);
                    return Error::SUCCESS;
                }

                append_token(MjTokenType::LEFT_SHIFT, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '=') {
                if (_line.size() > 2 && _line[2] == '>') {
                    append_token(MjTokenType::SPACESHIP, 3);
                    return Error::SUCCESS;
                }

                append_token(MjTokenType::LESS_THAN_OR_EQUAL, 2);
                return Error::SUCCESS;
            }
        }

        append_token(MjTokenType::LESS_THAN, 1);
        return Error::SUCCESS;
    case '>':
        if (_line.size() > 1) {
            if (_line[1] == '<') {
                if (_line.size() > 2 && _line[2] == '=') {
                    append_token(MjTokenType::RIGHT_SHIFT_SET, 3);
                    return Error::SUCCESS;
                }

                append_token(MjTokenType::RIGHT_SHIFT, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '=') {
                append_token(MjTokenType::GREATER_THAN_OR_EQUAL, 2);
                return Error::SUCCESS;
            }
        }

        append_token(MjTokenType::GREATER_THAN, 1);
        return Error::SUCCESS;
    default:
        return Error::FAILURE;
    }

    append_token(token_type, text.size());

    if (skip_trailing_whitespace) {
        skip_whitespace();
    }

    return Error::SUCCESS;
}
