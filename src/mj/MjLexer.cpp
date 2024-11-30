#include <mj/MjLexer.hpp>
#include <format/ASCII/Ascii.hpp>


struct MjKeywordInfo {
    const StringView text;
    MjTokenKind token_kind;
};


MjFile *MjLexer::parse_file(std::filesystem::path path) noexcept {
    MjFile *file = new MjFile();

    if (file->load(path).is_failure()) {
        printf("Failed to open file! '%s'\n", path.c_str());
        return nullptr;
    }

    MjLexer lexer{*file};

    if (lexer.parse().is_failure()) {
        return nullptr;
    }

    return file;
}


Error MjLexer::parse() noexcept {
    _line_index = 0;
    _line_indent = 0;
    _line = _file.line(0);
    parse_indent();

    while (!_at_eof) {
        //if (parse_numeric_literal()) {
        //    continue;
        //}

        //return;

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

    return Error::SUCCESS;
}












Error MjLexer::parse_token(StringView text, MjTokenKind token_type, bool skip_trailing_whitespace) noexcept {
    if (!_line.starts_with(text)) {
        return Error::FAILURE;
    }

    parse_text(token_type, text.size());

    if (skip_trailing_whitespace) {
        skip_whitespace();
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_operator(StringView text, MjTokenKind token_type, bool skip_trailing_whitespace) noexcept {
    if (!_line.starts_with(text)) {
        return Error::FAILURE;
    }

    parse_text(token_type, text.size());

    if (skip_trailing_whitespace) {
        skip_whitespace();
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_word(StringView text, MjTokenKind token_type, bool skip_trailing_whitespace) noexcept {
    if (
        !_line.starts_with(text) || (
            text.size() < _line.size() &&
            (Ascii::is_alnum(_line[text.size()]) || _line[text.size()] == '_')
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

    parse_text(token_type, text.size());

    if (skip_trailing_whitespace) {
        skip_whitespace();
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_token(MjTokenKind token_kind) noexcept {
    if (parse_token().is_failure() || token()->kind != token_kind) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_token() noexcept {
    skip_whitespace();

    if (_at_eof) {
        return Error::FAILURE;
    }

    u32 token_size = 1;
    MjTokenKind token_kind = MjTokenKind::NONE;

    switch (_line[0]) {
    case '@': {
        parse_text(MjTokenKind::AT);
        push_state(MjLexerState::IN_ANNOTATION);
        return Error::SUCCESS;
    } case ';': {
        parse_text(MjTokenKind::SEMICOLON);
        return Error::SUCCESS;
    } case ',': {
        parse_text(MjTokenKind::COMMA);
        return Error::SUCCESS;
    } case '[': {
        parse_text(MjTokenKind::OPEN_SQUARE_BRACKET);
        return Error::SUCCESS;
    } case ']': {
        parse_text(MjTokenKind::CLOSE_SQUARE_BRACKET);
        return Error::SUCCESS;
    } case '(': {
        parse_text(MjTokenKind::OPEN_PARENTHESIS);
        return Error::SUCCESS;
    } case ')': {
        parse_text(MjTokenKind::CLOSE_PARENTHESIS);
        return Error::SUCCESS;
    } case '{': {
        parse_text(MjTokenKind::OPEN_CURLY_BRACE);
        return Error::SUCCESS;
    } case '}': {
        parse_text(MjTokenKind::CLOSE_CURLY_BRACE);
        return Error::SUCCESS;
    } case '$': {
        parse_text(MjTokenKind::DOLLAR_SIGN);
        return Error::SUCCESS;
    } case '#': {
        parse_text(MjTokenKind::HASH);
        return Error::SUCCESS;
    } case '?': {
        if (_state.in_type_expression()) {
            parse_text(MjTokenKind::NO_RETURN_TYPE_MODIFIER);
        }

        parse_text(MjTokenKind::QUESTION);
        return Error::SUCCESS;
    } case '.': {
        parse_text(MjTokenKind::DOT);
        return Error::SUCCESS;
    } case '~': {
        parse_text(MjTokenKind::INVERT);
        return Error::SUCCESS;
    } case '*': {
        if (_line.size() > 1 && _line[1] == '=') {
            parse_text(MjTokenKind::MULTIPLY_SET, 2);
            return Error::SUCCESS;
        }

        if (_state.in_type_expression()) {
            parse_text(MjTokenKind::POINTER_TYPE_MODIFIER);
            return Error::SUCCESS;
        }

        parse_text(MjTokenKind::MULTIPLY);
        return Error::SUCCESS;
    } case '/': {
        if (_line.size() > 1) {
            if (_line[1] == '/') {
                MjTokenKind token_kind = MjTokenKind::NONE;

                if (_line.size() > 2 && _line[2] == '/') {
                    token_kind = _line.contains("`") ? MjTokenKind::FORMATTED_BLOCK_COMMENT : MjTokenKind::BLOCK_COMMENT;
                } else {
                    token_kind = _line.contains("`") ? MjTokenKind::FORMATTED_LINE_COMMENT : MjTokenKind::LINE_COMMENT;
                }

                parse_text(token_kind, _line.size());
                return Error::SUCCESS;
            }

            if (_line[1] == '=') {
                parse_text(MjTokenKind::DIVIDE_SET, 2);
                return Error::SUCCESS;
            }
        }

        parse_text(MjTokenKind::DIVIDE);
        return Error::SUCCESS;
    } case '%': {
        if (_line.size() > 1 && _line[1] == '=') {
            parse_text(MjTokenKind::REMAINDER_SET, 2);
            return Error::SUCCESS;
        }

        parse_text(MjTokenKind::REMAINDER, 1);
        return Error::SUCCESS;
    } case '+': {
        if (_line.size() > 1) {
            if (_line[1] == '=') {
                parse_text(MjTokenKind::PLUS_SET, 2);
                return Error::SUCCESS;
            }

            if (_line[1] - '0' < 10) {
                // This is a positive numeric literal.
                return Error::FAILURE;
            }
        }

        parse_text(MjTokenKind::PLUS, 1);
        return Error::SUCCESS;
    } case '-': {
        if (_line.size() > 1) {
            if (_line[1] == '=') {
                parse_text(MjTokenKind::MINUS_SET, 2);
                return Error::SUCCESS;
            }

            if (_line[1] - '0' < 10) {
                // This is a negative numeric literal.
                return Error::FAILURE;
            }
        }

        parse_text(MjTokenKind::MINUS, 1);
        return Error::SUCCESS;
    } case '&': {
        if (_line.size() > 1) {
            if (_line[1] == '&') {
                parse_text(MjTokenKind::LOGICAL_AND, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '=') {
                parse_text(MjTokenKind::BITWISE_AND_SET, 2);
                return Error::SUCCESS;
            }
        }

        if (_state.in_type_expression()) {
            parse_text(MjTokenKind::REFERENCE_TYPE_MODIFIER);
            return Error::SUCCESS;
        }

        parse_text(MjTokenKind::BITWISE_AND);
        return Error::SUCCESS;
    } case '^': {
        if (_line.size() > 1 && _line[1] == '=') {
            parse_text(MjTokenKind::BITWISE_XOR_SET, 2);
            return Error::SUCCESS;
        }

        parse_text(MjTokenKind::BITWISE_XOR);
        return Error::SUCCESS;
    } case '|': {
        if (_line.size() > 1) {
            if (_line[1] == '|') {
                parse_text(MjTokenKind::LOGICAL_OR, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '=') {
                parse_text(MjTokenKind::BITWISE_OR_SET, 2);
                return Error::SUCCESS;
            }
        }

        parse_text(MjTokenKind::BITWISE_OR);
        return Error::SUCCESS;
    } case '=': {
        if (_line.size() > 1) {
            if (_line[1] == '=') {
                parse_text(MjTokenKind::EQUAL, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '>') {
                parse_text(MjTokenKind::LAMBDA, 2);
                return Error::SUCCESS;
            }
        }

        parse_text(MjTokenKind::SET);
        return Error::SUCCESS;
    } case '!': {
        if (_line.size() > 1 && _line[1] == '=') {
            parse_text(MjTokenKind::NOT_EQUAL, 2);
            return Error::SUCCESS;
        }

        parse_text(MjTokenKind::NOT);
        return Error::SUCCESS;
    } case ':': {
        if (_line.size() > 1 && _line[1] == ':') {
            parse_text(MjTokenKind::SCOPE, 2);
            return Error::SUCCESS;
        }

        parse_text(MjTokenKind::COLON);
        return Error::SUCCESS;
    } case '<': {
        if (_line.size() > 1) {
            if (_line[1] == '<') {
                if (_line.size() > 2 && _line[2] == '=') {
                    parse_text(MjTokenKind::LEFT_SHIFT_SET, 3);
                    return Error::SUCCESS;
                }

                parse_text(MjTokenKind::LEFT_SHIFT, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '=') {
                if (_line.size() > 2 && _line[2] == '>') {
                    parse_text(MjTokenKind::SPACESHIP, 3);
                    return Error::SUCCESS;
                }

                parse_text(MjTokenKind::LESS_THAN_OR_EQUAL, 2);
                return Error::SUCCESS;
            }
        }

        parse_text(MjTokenKind::LESS_THAN);
        return Error::SUCCESS;
    } case '>': {
        if (token()->kind == MjTokenKind::INDENT || token()->kind == MjTokenKind::CLOSE_ANGLE_BRACKET) {
            parse_text(MjTokenKind::CLOSE_ANGLE_BRACKET);
            return Error::SUCCESS;
        }

        if (_line.size() > 1) {
            if (_line[1] == '>') {
                if (_line.size() > 2 && _line[2] == '=') {
                    parse_text(MjTokenKind::RIGHT_SHIFT_SET, 3);
                    return Error::SUCCESS;
                }

                parse_text(MjTokenKind::RIGHT_SHIFT, 2);
                return Error::SUCCESS;
            }

            if (_line[1] == '=') {
                parse_text(MjTokenKind::GREATER_THAN_OR_EQUAL, 2);
                return Error::SUCCESS;
            }
        }

        parse_text(MjTokenKind::GREATER_THAN);
        return Error::SUCCESS;
    } default: {
        return Error::FAILURE;
    }
    }
}






// +
// ++
// -
// --
// <
// <<
// <<=
// <=
// <=>
// >
// >>
// >>=
// >=
// *
// *=
// /
// /=
// %
// %=
// +=
// -=
// &
// &&
// &=
// |
// ||
// |=
// ^
// ^=
// =
// ==
// =>
// !
// !=
// :
// ::
// ?






Error MjLexer::parse_binary_operator() noexcept {
    skip_whitespace();

    if (!_has_leading_whitespace && token()->kind != MjTokenKind::OPEN_CURLY_BRACE) {
        return Error::FAILURE;
    }

    MjTokenKind token_kind = MjTokenKind::NONE;
    u8 c1 =_line.size() > 1 ? _line[1] : 0;
    u8 c2 =_line.size() > 2 ? _line[2] : 0;

    StringView token_text;
    StringView error_message;
    // identifier
    // operator (prefix, postfix, infix)
    // literal

    switch (_line[0]) {
    case '@': {
        token_kind = MjTokenKind::AT;
        push_state(MjLexerState::IN_ANNOTATION);
        break;
    } case ';': {
        token_kind = MjTokenKind::SEMICOLON;
        break;
    } case ',': {
        token_kind = MjTokenKind::COMMA;
        break;
    } case '$': {
        if (c1 == '(') {
            token_kind = MjTokenKind::OPEN_PARENTHESIS;
            push_state(MjLexerState::IN_SUBSHELL);
            break;
        }

        token_kind = MjTokenKind::DOLLAR_SIGN;
        push_state(MjLexerState::IN_SHELL);
        break;
    } case '#': {
        token_kind = MjTokenKind::HASH;
        break;
    } case '.': {
        token_kind = MjTokenKind::DOT;
        break;
    } case '~': {
        token_kind = MjTokenKind::INVERT;
        break;
    } case '[': {
        token_kind = MjTokenKind::OPEN_SQUARE_BRACKET;
        push_state(MjLexerState::IN_SQUARE_BRACKETS);
        break;
    } case ']': {
        token_kind = MjTokenKind::CLOSE_SQUARE_BRACKET;

        if (_state.in_square_brackets()) {
            pop_state();
        } else {
            error_message = "Unmatched square bracket!";
        }

        break;
    } case '(': {
        token_kind = MjTokenKind::OPEN_PARENTHESIS;
        push_state(MjLexerState::IN_PARENTHESES);
        break;
    } case ')': {
        token_kind = MjTokenKind::CLOSE_PARENTHESIS;

        if (_state.in_parentheses()) {
            pop_state();
        } else if (_state.in_subshell()) {
            pop_state();
        } else {
            error_message = "Unmatched parenthesis!";
        }

        break;
    } case '{': {
        token_kind = MjTokenKind::OPEN_CURLY_BRACE;
        push_state(MjLexerState::IN_CURLY_BRACES);
        break;
    } case '}': {
        token_kind = MjTokenKind::CLOSE_CURLY_BRACE;

        if (_state.in_curly_braces()) {
            pop_state();
        } else {
            error_message = "Unmatched curly brace!";
        }

        break;
    } case '?': {
        if (_state.in_type_expression()) {
            token_kind = MjTokenKind::FALLIBLE_TYPE_MODIFIER;
            break;
        }

        token_kind = MjTokenKind::QUESTION;
        break;
    } case '!': {
        if (_state.in_type_expression()) {
            token_kind = MjTokenKind::NO_RETURN_TYPE_MODIFIER;
            break;
        }

        if (_line.size() > 1 && _line[1] == '=') {
            token_kind = MjTokenKind::NOT_EQUAL;
            break;
        }

        token_kind = MjTokenKind::NOT;
        break;
    } case '*': {
        if (_state.in_type_expression()) {
            token_kind = MjTokenKind::POINTER_TYPE_MODIFIER;
            break;
        }

        if (c1 == '=') {
            token_kind = MjTokenKind::MULTIPLY_SET;
            break;
        }

        // ambiguous
        if (c1 == ' ') {
            token_kind = MjTokenKind::MULTIPLY;
        } else {
            token_kind = MjTokenKind::DEREFERENCE;
        }
        break;
    } case '/': {
        if (c1 == '=') {
            token_kind = MjTokenKind::DIVIDE_SET;
            break;
        }

        token_kind = MjTokenKind::DIVIDE;
        break;
    } case '%': {
        if (c1 == '=') {
            token_kind = MjTokenKind::REMAINDER_SET;
            break;
        }

        token_kind = MjTokenKind::REMAINDER;
        break;
    } case '+': {
        if (c1 == '=') {
            token_kind = MjTokenKind::PLUS_SET;
            break;
        }

        if (parse_numeric_literal().is_success()) {
            return Error::SUCCESS;
        }

        token_kind = MjTokenKind::PLUS;
        break;
    } case '-': {
        if (c1 == '=') {
            token_kind = MjTokenKind::MINUS_SET;
            break;
        }

        if (parse_numeric_literal().is_success()) {
            return Error::SUCCESS;
        }

        if (_state.in_shell() || _state.in_subshell()) {
            if (parse_shell_option().is_success()) {
                return Error::SUCCESS;
            }
        }

        token_kind = MjTokenKind::MINUS;
        break;
    } case '&': {
        if (_state.in_type_expression()) {
            token_kind = MjTokenKind::REFERENCE_TYPE_MODIFIER;
            break;
        }

        if (c1) {
            if (c1 == '&') {
                token_kind = MjTokenKind::LOGICAL_AND;
                break;
            }

            if (c1 == '=') {
                token_kind = MjTokenKind::BITWISE_AND_SET;
                break;
            }
        }

        token_kind = MjTokenKind::BITWISE_AND;
        break;
    } case '^': {
        if (c1 == '=') {
            token_kind = MjTokenKind::BITWISE_XOR_SET;
            break;
        }

        token_kind = MjTokenKind::BITWISE_XOR;
        break;
    } case '|': {
        if (c1) {
            if (c1 == '|') {
                token_kind = MjTokenKind::LOGICAL_OR;
                break;
            }

            if (c1 == '=') {
                token_kind = MjTokenKind::BITWISE_OR_SET;
                break;
            }
        }

        token_kind = MjTokenKind::BITWISE_OR;
        break;
    } case '=': {
        if (c1) {
            if (c1 == '=') {
                token_kind = MjTokenKind::EQUAL;
                break;
            }

            if (c1 == '>') {
                token_kind = MjTokenKind::LAMBDA;
                break;
            }
        }

        token_kind = MjTokenKind::SET;
        break;
    } case ':': {
        if (c1 == ':') {
            token_kind = MjTokenKind::SCOPE;
            break;
        }

        token_kind = MjTokenKind::COLON;
        break;
    } case '<': {
        if (c1) {
            if (c1 == '<') {
                if (c2 == '=') {
                    token_kind = MjTokenKind::LEFT_SHIFT_SET;
                    break;
                }

                token_kind = MjTokenKind::LEFT_SHIFT;
                break;
            }

            if (c1 == '=') {
                if (c2 == '>') {
                    token_kind = MjTokenKind::SPACESHIP;
                    break;
                }

                token_kind = MjTokenKind::LESS_THAN_OR_EQUAL;
                break;
            }
        }

        token_kind = MjTokenKind::LESS_THAN;
        break;
    } case '>': {
        if (token()->kind == MjTokenKind::INDENT || token()->kind == MjTokenKind::CLOSE_ANGLE_BRACKET) {
            token_kind = MjTokenKind::CLOSE_ANGLE_BRACKET;

            if (_state.in_angle_brackets()) {
                pop_state();
            } else {
                error_message = "Unmatched angle bracket!";
            }

            break;
        }

        if (c1) {
            if (c1 == '>') {
                if (c2 == '=') {
                    token_kind = MjTokenKind::RIGHT_SHIFT_SET;
                    break;
                }

                token_kind = MjTokenKind::RIGHT_SHIFT;
                break;
            }

            if (c1 == '=') {
                token_kind = MjTokenKind::GREATER_THAN_OR_EQUAL;
                break;
            }
        }

        token_kind = MjTokenKind::GREATER_THAN;
        break;
    } case '"': {
        if (parse_interpolated_string_literal().is_success()) {
            return Error::SUCCESS;
        }

        break;
    } case '\'': {
        if (parse_raw_string_literal().is_success()) {
            return Error::SUCCESS;
        }
    }
    }

    if (token_kind == MjTokenKind::NONE) {
        return Error::FAILURE;
    }

    u32 token_size = token_kind.size();

    if (token_kind.requires_leading_whitespace()) {
        // is binary operator or nested prefix operator
    }

    if (token_kind.requires_trailing_whitespace()) {
        // is binary operator or nested postfix operator
    }

    parse_text(token_kind, token_size);
    return Error::SUCCESS;
}





Error MjLexer::parse_shell_option() noexcept {
    return Error::FAILURE;
}


Error MjLexer::parse_shell_token() noexcept {
    skip_whitespace();

    if (!_has_leading_whitespace && token()->kind != MjTokenKind::OPEN_CURLY_BRACE) {
        return Error::FAILURE;
    }

    MjTokenKind token_kind = MjTokenKind::NONE;
    u8 c1 =_line.size() > 1 ? _line[1] : 0;
    u8 c2 =_line.size() > 2 ? _line[2] : 0;

    StringView token_text;
    StringView error_message;
    // identifier
    // operator (prefix, postfix, infix)
    // literal

    switch (_line[0]) {
    case '-': {
        if (c1 == '=') {
            token_kind = MjTokenKind::MINUS_SET;
            break;
        }

        if (parse_numeric_literal().is_success()) {
            return Error::SUCCESS;
        }

        if (_state.in_shell() || _state.in_subshell()) {
            if (parse_shell_option().is_success()) {
                return Error::SUCCESS;
            }
        }

        token_kind = MjTokenKind::MINUS;
        break;
    } case '(': {
    } case '$': {
    }
    }




    while (parse_token().is_success() && token()->kind != MjTokenKind::INDENT) {
        if (_state.in_subshell()) {
            if (token()->kind != MjTokenKind::INDENT) {
                error("Expected ')' to close subshell!");
                return Error::FAILURE;
            }

            pop_state();
            break;
        }
    }

    if (_state.in_subshell()) {
        if (token()->kind == MjTokenKind::INDENT) {
            error("Expected ')' to close subshell!");
            return Error::FAILURE;
        }

        pop_state();
    }

    return Error::SUCCESS;
}
































Error MjLexer::parse_type_expression() noexcept {

    // Parse the base type.
    while (parse_type_qualifier().is_success());

    if (parse_token(MjTokenKind::TYPE_NAME).is_failure()) {
        return Error::FAILURE;
    }

    // Parse the type modifiers.
    while (parse_token().is_success()) {
        switch (token()->kind) {
        case MjTokenKind::POINTER_TYPE_MODIFIER: {
            break;
        } case MjTokenKind::REFERENCE_TYPE_MODIFIER: {
            break;
        } case MjTokenKind::OPEN_ANGLE_BRACKET: {
            break;
        } case MjTokenKind::OPEN_SQUARE_BRACKET: {
            break;
        } case MjTokenKind::OPEN_PARENTHESIS: {
            break;
        } case MjTokenKind::COLON: {
            if (_state.in_type_cast()) {
                pop_state();
            }
            // fall-through
        } default: {
            pop_state();
            return Error::SUCCESS;
        }
        }
    }

    return Error::SUCCESS;
}



Error MjLexer::parse_identifier() noexcept {
    skip_whitespace();

    if (_at_eof) {
        return Error::FAILURE;
    }

    u32 token_size = 0;
    MjTokenKind token_kind = MjTokenKind::NONE;
    MjTokenKind trailing_token_type = MjTokenKind::NONE;

    while (token_size < _line.size() && Ascii::is_lower(_line[token_size])) {
        token_size += 1;
    }

    if (token_size + 1 < _line.size() && _line[token_size] == ':' && _line[token_size + 1] == ':') {
        parse_text(MjTokenKind::MODULE_NAME, token_size);
        parse_text(MjTokenKind::SCOPE, 2);
        return Error::SUCCESS;
    }

    StringView token_text = _line.head(token_size);

    static
    const StringView TYPE_NAMES[] = {
        "bool",
        "void",
    };

    for (StringView type_name : TYPE_NAMES) {
        if (token_text == type_name) {
            parse_text(MjTokenKind::TYPE_NAME, token_size);
            return Error::SUCCESS;
        }
    }

    if (token_size < _line.size() && _line[token_size] == '(') {
        parse_text(MjTokenKind::FUNCTION_NAME, token_size);
        parse_text(MjTokenKind::OPEN_PARENTHESIS);
        push_state(MjLexerState::IN_PARENTHESES);
        return Error::SUCCESS;
    }

    if (token_size < _line.size() && _line[token_size] == '&') {
        parse_text(MjTokenKind::FUNCTION_NAME, token_size);
        parse_text(MjTokenKind::FUNCTION_REFERENCE, token_size);
        return Error::SUCCESS;
    }

    if (token_size < _line.size() && _line[token_size] == '<') {

        // These keywords are safe to use as variable or function names, but they
        // may not be used as generic function names.
        static
        const MjKeywordInfo KEYWORDS[] = {
            {"bitfield", MjTokenKind::BITFIELD},
            {"enum", MjTokenKind::ENUM},
            {"impl", MjTokenKind::IMPL},
            {"type", MjTokenKind::TYPE},
            {"union", MjTokenKind::UNION},
            {"unit", MjTokenKind::UNIT},
            {"where", MjTokenKind::WHERE},
        };

        MjTokenKind token_kind = MjTokenKind::FUNCTION_NAME;

        for (const MjKeywordInfo &info : KEYWORDS) {
            if (token_text == info.text) {
                token_kind = info.token_kind;
                break;
            }
        }

        parse_text(token_kind, token_size);
        parse_text(MjTokenKind::OPEN_ANGLE_BRACKET);
        push_state(MjLexerState::IN_ANGLE_BRACKETS);

        if (token_kind == MjTokenKind::UNIT) {
            parse_unit_expression();
        }

        return Error::SUCCESS;
    }

    if (token_size + 1 < _line.size() && _line[token_size] == ' ' && _line[token_size + 1] == '(') {
        static
        const MjKeywordInfo KEYWORDS[] = {
            {"for", MjTokenKind::FOR},
            {"if", MjTokenKind::IF},
            {"match", MjTokenKind::MATCH},
            {"until", MjTokenKind::UNTIL},
            {"while", MjTokenKind::WHILE},
        };

        MjTokenKind token_kind = MjTokenKind::VARIABLE_NAME;

        for (const MjKeywordInfo &info : KEYWORDS) {
            if (token_text == info.text) {
                token_kind = info.token_kind;
                break;
            }
        }

        parse_text(token_kind, token_size);
        parse_text(MjTokenKind::OPEN_PARENTHESIS);
        push_state(MjLexerState::IN_PARENTHESES);
        return Error::SUCCESS;
    }

    if (_line[token_size] == '&') {
        trailing_token_type = MjTokenKind::FUNCTION_REFERENCE;
    } else if (Ascii::is_upper(_line[token_size]) || Ascii::is_digit(_line[token_size])) {
        // end of word.
    }

    if (trailing_token_type != MjTokenKind::NONE) {
        token_kind = MjTokenKind::FUNCTION_NAME;
    } else {
        token_kind = MjTokenKind::VARIABLE_NAME;
    }


    // These keywords are not safe to use as variable or function names.
    static
    const MjKeywordInfo PURE_KEYWORDS[] = {
        {"break", MjTokenKind::BREAK},
        {"bool", MjTokenKind::TYPE_NAME},
        {"const", MjTokenKind::CONST},
        {"continue", MjTokenKind::CONTINUE},
        {"fail", MjTokenKind::FAIL},
        {"false", MjTokenKind::CONSTANT_NAME},
        {"mutable", MjTokenKind::MUTABLE},
        {"null", MjTokenKind::CONSTANT_NAME},
        {"return", MjTokenKind::RETURN},
        {"safe", MjTokenKind::SAFE},
        {"true", MjTokenKind::CONSTANT_NAME},
        {"uninitialized", MjTokenKind::CONSTANT_NAME},
        {"void", MjTokenKind::TYPE_NAME},
        {"volatile", MjTokenKind::VOLATILE},
        {"yield", MjTokenKind::YIELD},
    };

    for (const MjKeywordInfo &info : PURE_KEYWORDS) {
        if (parse_word(info.text, info.token_kind).is_success()) {
            return Error::SUCCESS;
        }
    }

    // These keywords are followed by an open brace '{'.
    //
    // These keywords are safe to use as variable or function names.
    static
    const MjKeywordInfo BRACED_KEYWORDS[] = {
        {"do", MjTokenKind::DO},
    };


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
        {"asm", MjTokenKind::ASM},
        {"class", MjTokenKind::CLASS},
        {"else", MjTokenKind::ELSE},
        {"import", MjTokenKind::IMPORT},
        {"interface", MjTokenKind::INTERFACE},
        {"struct", MjTokenKind::STRUCT},
        {"union", MjTokenKind::UNION},
    };

    for (const MjKeywordInfo &info : SCOPED_KEYWORDS) {
        if (parse_word(info.text, info.token_kind, false).is_success()) {
            if (_line.starts_with(' ')) {
                skip_whitespace();

                if (_line.size() > 0 && (_line[0] == '{' || (_line[0] | 0x20u) - 'a' < 26 || _line[0] - '0' < 10 || _line[0] == '_')) {
                    return Error::SUCCESS;
                }
            }

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
        {"as", MjTokenKind::AS},                 // 'as (type)'
        {"is", MjTokenKind::IS},                 // 'is (type)'
    };

    for (const MjKeywordInfo &info : TYPE_OP_KEYWORDS) {
        if (parse_word(info.text, info.token_kind, false).is_success()) {
            u32 line_index = _line_index;
            skip_whitespace();

            if (_has_leading_whitespace && _line_index == line_index) {
                return Error::SUCCESS;
            }

            return Error::FAILURE;
        }
    }

    parse_text(MjTokenKind::VARIABLE_NAME, token_size);


    ///
    /// Numeric Type Names
    ///


    if (token_text[0] == 'f' || token_text[0] == 'i' || token_text[0] == 'u') {
        static
        const StringView NUMERIC_TYPE_NAMES[] = {
            "f128",
            "f16",
            "f32",
            "f64",
            "f80",
            "i128",
            "i16",
            "i32",
            "i64",
            "i8",
            "u128",
            "u16",
            "u32",
            "u64",
            "u8",
        };

        u32 postfix_size = 0;

        for (StringView type_name : TYPE_NAMES) {
            if (token_text == type_name) {
                parse_text(MjTokenKind::TYPE_NAME, token_size);

                if (token_size < _line.size()) {
                    if (_line[token_size] == '<') {
                        parse_text(MjTokenKind::OPEN_ANGLE_BRACKET);
                        push_state(MjLexerState::IN_ANGLE_BRACKETS);
                        parse_unit_expression();
                    } else if (_line[token_size] == 'x') {
                        ;
                    }
                }

                return Error::SUCCESS;
            }
        }
    }







    if (token_size == 0) {
        while (token_size < _line.size() && (Ascii::is_digit(_line[token_size]) || _line[token_size] == '_')) {
            token_size += 1;
        }
    }

    if (token_size < _line.size() && Ascii::is_upper(_line[token_size])) {
        token_size += 1;

        while (token_size < _line.size() && (Ascii::is_upper(_line[token_size]) || Ascii::is_digit(_line[token_size]) || _line[token_size] == '_')) {
            token_size += 1;
        }

        if (token_size < _line.size() && Ascii::is_lower(_line[token_size])) {
        }

        token_kind = token_size > 1 ? MjTokenKind::CONSTANT_NAME : MjTokenKind::TYPE_NAME;
    } else if (token_size < _line.size() && Ascii::is_lower(_line[token_size])) {
        token_size += 1;

        while (token_size < _line.size() && (Ascii::is_lower(_line[token_size]) || Ascii::is_digit(_line[token_size]) || _line[token_size] == '_')) {
            token_size += 1;
        }

        if (token_size < _line.size()) {
            if (_line[token_size] == '(') {
                trailing_token_type = MjTokenKind::OPEN_PARENTHESIS;
                push_state(MjLexerState::IN_PARENTHESES);
            } else if (_line[token_size] == '<') {
                trailing_token_type = MjTokenKind::OPEN_ANGLE_BRACKET;
                push_state(MjLexerState::IN_ANGLE_BRACKETS);
            } else if (_line[token_size] == '&') {
                trailing_token_type = MjTokenKind::FUNCTION_REFERENCE;
            }
        }

        if (trailing_token_type != MjTokenKind::NONE) {
            token_kind = MjTokenKind::FUNCTION_NAME;
        } else {
            token_kind = MjTokenKind::VARIABLE_NAME;
        }
    } else {
    }


    ///
    /// Type Name - (?:[0-9][0-9.+-]*)?[A-Z][0-9A-Z+-]*[a-z][0-9A-Za-z.+-]*
    ///

    if (token_size < _line.size() && Ascii::is_digit(_line[token_size])) {
        token_size += 1;

        while (token_size < _line.size() && (Ascii::is_digit(_line[token_size]) || _line[token_size] == '.' || _line[token_size] == '+' || _line[token_size] == '-')) {
            token_size += 1;
        }
    }

    // [A-Za-z0-9]
    if (token_size >= _line.size() || !Ascii::is_alnum(_line[token_size])) {
        return Error::FAILURE;
    }

    token_size += 1;

    // [A-Za-z0-9.+-]*
    while (token_size < _line.size() && (Ascii::is_alnum(_line[token_size]) || _line[token_size] == '+' || _line[token_size] == '-' || _line[token_size] == '.')) {
        token_size += 1;
    }


    ///
    /// Module Name - [0-9A-Za-z][0-9A-Za-z.+-]*(?=::)
    ///

    // (?=::)
    if (token_size + 1u >= _line.size() || _line[token_size] != ':' || _line[token_size + 1] != ':') {
        if (has_underscore) {
            token_kind = MjTokenKind::INVALID_MODULE_NAME;
        } else {
            token_kind = MjTokenKind::MODULE_NAME;
        }

        parse_text(token_kind, token_size);
        parse_text(MjTokenKind::SCOPE, 2);
        return Error::SUCCESS;
    }


    parse_text(MjTokenKind::VARIABLE_NAME, token_size);
    return Error::SUCCESS;
}


Error MjLexer::parse_raw_string_literal() noexcept {
    skip_whitespace();

    if (_at_eof) {
        return Error::FAILURE;
    }

    if (!_line.starts_with('\'')) {
        return Error::FAILURE;
    }

    u32 i = _line.size();
    while (_line[--i] != '\'');

    if (i == 0) {
        error("Unterminated raw string literal!");
        return Error::FAILURE;
    }

    parse_text(MjTokenKind::RAW_STRING_LITERAL, i);
    return Error::SUCCESS;
}


Error MjLexer::parse_interpolated_string_literal() noexcept {
    skip_whitespace();

    if (_at_eof) {
        return Error::FAILURE;
    }

    if (!_line.starts_with('"')) {
        return Error::FAILURE;
    }

    std::vector<MjToken> escape_sequences;
    u32 i = 1;
    MjTokenKind token_kind = MjTokenKind::STRING_LITERAL;

    while (i < _line.size() && _line[i] != '"') {
        if (_line[i] == '\\') {
            token_kind = MjTokenKind::INTERPOLATED_STRING_LITERAL;
            i += 1;

            if (i == _line.size()) {
                break;
            }

            MjToken escape_sequence = MjToken(MjTokenKind::CHARACTER_ESCAPE_SEQUENCE, _line_index, _file.line(_line_index).size() - _line.size(), 2);

            switch (_line[i]) {
            case '\\': // '\\'
            case '"': // '\"'
            case 'e': // '\e'
            case 'n': // '\n'
            case 'r': // '\r'
            case 't': // '\t'
            case '0': // '\0'
                break;
            case 'o': { // '\o377'
                for (u32 n = i + 3; i < n; i++) {
                    if (i == _line.size() || !Ascii::is_octal(_line[i])) {
                        escape_sequence.kind = MjTokenKind::INVALID_ESCAPE_SEQUENCE;
                        escape_sequence.size = i;
                        error(escape_sequence, "Invalid string escape sequence! '\\o' requires 3 octal digits!");
                        break;
                    }
                }

                if (_line[i - 3] > '3') {
                    escape_sequence.kind = MjTokenKind::INVALID_ESCAPE_SEQUENCE;
                    escape_sequence.size = 5;
                    error(escape_sequence, "Invalid string escape sequence! Max value is \"\\o377\"!");
                }

                break;
            } case 'x': { // '\x7F'
                for (u32 n = i + 2; i < n; i++) {
                    if (i == _line.size() || !Ascii::is_hex_digit(_line[i])) {
                        escape_sequence.kind = MjTokenKind::INVALID_ESCAPE_SEQUENCE;
                        escape_sequence.size = i;
                        error(escape_sequence, "Invalid string escape sequence! '\\x' requires 2 hexadecimal digits!");
                        break;
                    }
                }

                if (_line[i - 2] > '7') {
                    escape_sequence.kind = MjTokenKind::INVALID_ESCAPE_SEQUENCE;
                    escape_sequence.size = 4;
                    error(escape_sequence, "Invalid string escape sequence! Max value is \"\\x7F\"!");
                }

                break;
            } case 'u': { // '\uFFFF'
                for (u32 n = i + 4; i < n; i++) {
                    if (i == _line.size() || !Ascii::is_hex_digit(_line[i])) {
                        escape_sequence.kind = MjTokenKind::INVALID_ESCAPE_SEQUENCE;
                        escape_sequence.size = i;
                        error(escape_sequence, "Invalid Unicode string escape sequence! '\\u' requires 4 hexadecimal digits!");
                        break;
                    }
                }

                break;
            } case 'U': { // '\U10FFFF'
                for (u32 n = i + 6; i < n; i++) {
                    if (i == _line.size() || !Ascii::is_hex_digit(_line[i])) {
                        escape_sequence.kind = MjTokenKind::INVALID_ESCAPE_SEQUENCE;
                        escape_sequence.size = i;
                        error(escape_sequence, "Invalid Unicode string escape sequence! '\\U' requires 6 hexadecimal digits!");
                        break;
                    }
                }

                if (_line[i - 6] > '1' || (_line[i - 6] == '1' && _line[i - 5] > '0')) {
                    escape_sequence.kind = MjTokenKind::INVALID_ESCAPE_SEQUENCE;
                    escape_sequence.size = 8;
                    error(escape_sequence, "Invalid string escape sequence! Max value is \"\\U10FFFF\"!");
                }

                break;
            } default: {
                escape_sequence.kind = MjTokenKind::INVALID_ESCAPE_SEQUENCE;
                error(escape_sequence, "Invalid string escape sequence!");
            }
            }

            escape_sequences.emplace_back(escape_sequence);
        }

        i += 1;
    }

    if (i == _line.size()) {
        error("Unterminated string literal!");
        // consume the rest of the line and continue parsing.
    }

    parse_text(token_kind, i);

    for (MjToken escape_sequence : escape_sequences) {
        append_subtoken(escape_sequence.kind, escape_sequence.offset, escape_sequence.size);
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_unit_expression() noexcept {
    skip_whitespace();

    if (_at_eof) {
        return Error::FAILURE;
    }

    u32 token_size = 0;

    // [A-Za-zµΩÅ°'"]|^g|1/
    while (true) {
        if (token_size == _line.size()) {
            return Error::FAILURE;
        }

        u32 value = _line[token_size];

        if (
            (value | 0x20u) - 'a' < 26 ||
            value == '\'' ||
            value == '"'
        ) {
            token_size += 1;
            break;
        }

        if (token_size + 1 == _line.size()) {
            return Error::FAILURE;
        }

        value = (value << 8) | _line[token_size + 1];

        if (
            value == (('^' << 8) | 'g') || // '^g'
            value == (('1' << 8) | '/') || // '1/'
            value == 0xC2B0u || // '°'
            value == 0xC2B5u || // 'µ'
            value == 0xC2B7u || // '·'
            value == 0xC385u || // 'Å'
            value == 0xCEA9u    // 'Ω'
        ) {
            token_size += 2;
            break;
        }

        return Error::FAILURE;
    }

    // [A-Za-z0-9µΩÅ°'"⁰¹²³⁴⁵⁶⁷⁸⁹⁻⸍·^*/-]*
    while (true) {
        if (token_size == _line.size()) {
            break;
        }

        u32 value = _line[token_size];

        if (
            (value | 0x20u) - 'a' < 26 || value - '0' < 10 ||
            value == '\'' ||
            value == '"' ||
            value == '^' ||
            value == '*' ||
            value == '/' ||
            value == '-'
        ) {
            token_size += 1;
            continue;
        }

        if (token_size + 1 == _line.size()) {
            break;
        }

        value = (value << 8) | _line[token_size + 1];

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
            token_size += 2;
            continue;
        }

        if (token_size + 2u == _line.size()) {
            break;
        }

        value = (value << 8) | _line[token_size + 2];

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
            token_size += 3;
            continue;
        }

        break;
    }

    parse_text(MjTokenKind::UNIT_EXPRESSION, token_size);
    return Error::SUCCESS;
}


Error MjLexer::parse_numeric_literal() noexcept {
    skip_whitespace();

    if (_at_eof) {
        return Error::FAILURE;
    }

    // Parse the sign.
    u32 token_size = 0;
    bool has_sign = token_size < _line.size() && (_line[token_size] == '+' || _line[token_size] == '-');

    if (has_sign) {
        token_size += 1;
    }

    // Parse the base prefix.
    u32 base = 10;
    MjTokenKind token_kind = MjTokenKind::I32_LITERAL;

    if (token_size + 1 < _line.size() && _line[token_size] == '0') {
        token_size += 1;

        if (_line[token_size] == 'x') {
            token_size += 1;
            token_kind = MjTokenKind::U32_LITERAL;
            base = 16;
        } else if (_line[token_size] == 'o') {
            token_size += 1;
            token_kind = MjTokenKind::U32_LITERAL;
            base = 8;
        } else if (_line[token_size] == 'b') {
            token_size += 1;
            token_kind = MjTokenKind::U32_LITERAL;
            base = 2;
        }
    }

    // Parse the integer portion.
    while (token_size < _line.size() && Ascii::is_digit_upper(_line[token_size], base)) {
        token_size += 1;
    }

    while (token_size < _line.size() && _line[token_size] == '\'') {
        token_size += 1;

        if (token_size < _line.size() && Ascii::is_digit_upper(_line[token_size], base)) {
            token_size += 1;
        }
    }

    if (token_size == 0 || !Ascii::is_digit_upper(_line[token_size - 1], base)) {
        return Error::FAILURE;
    }

    // Parse the fractional portion.
    if ((base == 10 || base == 16) && token_size < _line.size() && _line[token_size] == '.') {
        token_size += 1;
        token_kind = MjTokenKind::F64_LITERAL;

        while (token_size < _line.size() && Ascii::is_digit_upper(_line[token_size], base)) {
            token_size += 1;
        }
    }

    // Parse the exponent portion.
    if (token_size < _line.size() && ((base == 10 && _line[token_size] == 'e') || (base == 16 && _line[token_size] == 'p'))) {
        token_size += 1;
        token_kind = MjTokenKind::F64_LITERAL;

        // Parse the exponent sign.
        if (token_size < _line.size() && (_line[token_size] == '+' || _line[token_size] == '-')) {
            token_size += 1;
        }

        while (token_size < _line.size() && Ascii::is_digit(_line[token_size])) {
            token_size += 1;
        }
    }

    // Parse the type suffix.
    u32 type_suffix_size = 0;

    if (_line[token_size] == 'f' || _line[token_size] == 'i' || _line[token_size] == 'u') {
        static
        const MjKeywordInfo NUMERIC_LITERAL_SUFFIXES[] = {
            {"f", MjTokenKind::F32_LITERAL},
            {"f128", MjTokenKind::F128_LITERAL},
            {"f16", MjTokenKind::F16_LITERAL},
            {"f32", MjTokenKind::F32_LITERAL},
            {"f64", MjTokenKind::F64_LITERAL},
            {"f80", MjTokenKind::F80_LITERAL},
            {"i", MjTokenKind::I32_LITERAL},
            {"i128", MjTokenKind::I128_LITERAL},
            {"i16", MjTokenKind::I16_LITERAL},
            {"i32", MjTokenKind::I32_LITERAL},
            {"i64", MjTokenKind::I64_LITERAL},
            {"i8", MjTokenKind::I8_LITERAL},
            {"u", MjTokenKind::U32_LITERAL},
            {"u128", MjTokenKind::U128_LITERAL},
            {"u16", MjTokenKind::U16_LITERAL},
            {"u32", MjTokenKind::U32_LITERAL},
            {"u64", MjTokenKind::U64_LITERAL},
            {"u8", MjTokenKind::U8_LITERAL},
        };

        for (const MjKeywordInfo &info : NUMERIC_LITERAL_SUFFIXES) {
            if (_line.slice(token_size).starts_with(info.text)) {
                type_suffix_size = info.text.size();
                token_size += type_suffix_size;
                token_kind = info.token_kind;
                break;
            }
        }

        // Check for end of token.

        if (type_suffix_size == 0) {
            
        }
    }



    // Parse module name.
    if (parse_module_name()) {
        return Error::FAILURE;
    }

    // Check for word boundary.
    // (?![A-Za-z0-9_.+-])
    if (token_size < _line.size() && (Ascii::is_alnum(_line[token_size]) || _line[token_size] == '_')) {
        return Error::FAILURE;
    }



    parse_text(token_kind, token_size);

    if (_emit_subtokens) {
        if (base != 10) {
            append_subtoken(MjTokenKind::NUMERIC_LITERAL_PREFIX, token_size - 2, 2);
        }

        if (type_suffix_size > 0) {
            append_subtoken(MjTokenKind::NUMERIC_LITERAL_POSTFIX, type_suffix_size, type_suffix_size);
        }
    }

    if (!_line.is_empty() && _line[0] == ' ') {
        // Unit expression has priority after a numeric literal.
        parse_unit_expression();
    }

    return Error::SUCCESS;
}


///
/// Text Parsing
///


Error MjLexer::parse_text(StringView string, MjTokenKind token_kind) noexcept {
    if (!_line.starts_with(string)) {
        return Error::FAILURE;
    }

    parse_text(token_kind, string.size());
    return Error::SUCCESS;
}


Error MjLexer::parse_text(u8 ch, MjTokenKind token_kind) noexcept {
    if (!_line.starts_with(ch)) {
        return Error::FAILURE;
    }

    parse_text(token_kind, 1);
    return Error::SUCCESS;
}


void MjLexer::parse_text(MjTokenKind kind, u32 size) noexcept {
    if (kind != MjTokenKind::INDENT) {
        printf("%.*s # %u\n", size, _line.data(), static_cast<u32>(kind));
    }

    _file.tokens().emplace_back(kind, _line_index, _file.line(_line_index).size() - _line.size(), size);
    _line += size;
}


void MjLexer::append_token(MjToken token) noexcept {
    printf("%.*s # %u\n", token.size, _file.line(token.line).data() + token.offset, static_cast<u32>(token.kind));
    _file.tokens().push_back(token);
}


void MjLexer::append_subtoken(MjTokenKind kind, u32 offset, u32 size) noexcept {
    const MjToken &token = _file.tokens().back();
    printf("%.*s # %u\n", size, _file.line(token.line).data() + token.offset + offset, static_cast<u32>(kind));
    _file.tokens().emplace_back(kind, token.line, token.offset + offset, size);
}


///
/// Line Control and Whitespace Parsing
///


void MjLexer::skip_whitespace() noexcept {
    if (_at_eof) {
        return;
    }

    for (u32 i = 0; i < _line.size(); ++i) {
        if (_line[i] != ' ') {
            _has_leading_whitespace = i > 0;

            if (_has_leading_whitespace) {
                _line += i;

                if (_state.in_type_expression()) {
                    clear_state(MjLexerState::IN_TYPE_EXPRESSION);
                }
            }

            return;
        }
    }

    move_to_next_line();
    parse_indent();
}


void MjLexer::parse_indent() noexcept {
    while (!_at_eof) {
        for (u32 i = 0; i < _line.size(); ++i) {
            if (_line[i] != ' ') {
                _last_indent = _line_indent;
                _line_indent = i / INDENT_WIDTH;
                parse_text(MjTokenKind::INDENT, _line_indent);
                _line += i % INDENT_WIDTH;

                // Reset line dependent parsing states.
                _has_leading_whitespace = true;

                if (_state.in_annotation()) {
                    pop_state();
                }

                if (_state.in_shell()) {
                    pop_state();
                }

                return;
            }
        }

        move_to_next_line();
    }
}


void MjLexer::move_to_next_line() noexcept {
    if (_at_eof) {
        return;
    }

    _line_index += 1;

    if (_line_index == _file.line_count()) {
        _at_eof = true;
        _line = nullptr;
        return;
    }

    printf("line: %u\n", _line_index + 1);
    _line = _file.line(_line_index);
}


///
/// Error Handling
///


void MjLexer::error(const MjToken &token, StringView message) noexcept {
    printf("%s:%u:%u: \x1B[31merror:\x1B[m ",
        _file.file_path().c_str(), token.line + 1, token.offset
    );
    printf("%.*s\n", message.size(), message.data());
    printf("\x1B[35m%*.*s\x1B[m",
        token.offset, token.size, "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
    );
}
