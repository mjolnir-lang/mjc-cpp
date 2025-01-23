#include <mj/MjLexer.hpp>
#include <format/ASCII/Ascii.hpp>

#include <fstream>


struct MjKeywordInfo {
    const StringView text;
    MjTokenKind token_kind;
};


MjFile *MjLexer::parse_file(std::filesystem::path file_path, bool emit_subtokens) noexcept {
    std::vector<u8> data(load_file_data(file_path));

    if (data.empty()) {
        return nullptr;
    }

    MjFile *file = new MjFile(file_path, data.size());
    MjLexer(*file, emit_subtokens).parse();
    return file;
}


std::vector<u8> MjLexer::load_file_data(std::filesystem::path file_path) noexcept {
    std::basic_ifstream<u8> file_stream(file_path, std::ios::binary | std::ios::ate);

    if (!file_stream.is_open()) {
        printf("Failed to open file! '%s'\n", file_path.c_str());
        return {};
    }

    std::streamsize file_size = file_stream.tellg();

    if (file_size < 0) {
        printf("Failed to get file size! '%s'\n", file_path.c_str());
        return {};
    }

    std::vector<u8> data(file_size + 1);
    file_stream.seekg(0, std::ios::beg);

    if (!file_stream.read(data.data(), file_size)) {
        printf("Failed to read file data! '%s'\n", file_path.c_str());
        return {};
    }

    data.back() = 0;
    return data;
}


///
/// Token Parsing
///


Error MjLexer::parse() noexcept {
    _line_index = 0;
    _line_indent = 0;
    _ch = _data.data();
    parse_indent();

    while (!is_eof()) {
        parse_token();
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_token(MjTokenKind token_kind) noexcept {
    if (parse_token().is_failure() || token().kind() != token_kind) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_token() noexcept {
    parse_whitespace();

    if (!_has_leading_whitespace && token().kind() != MjTokenKind::OPEN_CURLY_BRACE) {
        return Error::FAILURE;
    }

    StringView error_message;
    MjTokenKind token_kind = MjTokenKind::NONE;

    switch (*_ch) {
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
        if (_ch[1] == '(') {
            token_kind = MjTokenKind::OPEN_PARENTHESIS;
            push_state(MjLexerState::IN_SUBSHELL);
        } else {
            token_kind = MjTokenKind::DOLLAR_SIGN;
            push_state(MjLexerState::IN_SHELL);
        }

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
        } else {
            token_kind = MjTokenKind::TERNARY_THEN;
        }

        break;
    } case '!': {
        if (_state.in_type_expression()) {
            token_kind = MjTokenKind::NO_RETURN_TYPE_MODIFIER;
        } else if (_ch[1] == '=') {
            token_kind = MjTokenKind::NOT_EQUAL;
        } else {
            token_kind = MjTokenKind::NOT;
        }

        break;
    } case '*': {
        if (_state.in_type_expression()) {
            token_kind = MjTokenKind::POINTER_TYPE_MODIFIER;
        } else if (_ch[1] == '=') {
            token_kind = MjTokenKind::MULTIPLY_SET;
        } else {
            if (_has_trailing_whitespace) {
                token_kind = MjTokenKind::MULTIPLY;
            } else {
                token_kind = MjTokenKind::DEREFERENCE;
            }
        }

        break;
    } case '/': {
        if (_ch[1] == '/') {
            _ch += 2;

            if (_skip_comments) {
                for (; *_ch >= ' '; ++_ch);
                return Error::SUCCESS;
            }

            if (*_ch == '/') {
                token_kind = MjTokenKind::BLOCK_COMMENT;
                _ch += 1;
            } else {
                token_kind = MjTokenKind::LINE_COMMENT;
            }

            if (*_ch == ' ') {
                _ch += 1;
            }

            const u8 *token_data = _ch;
            for (; *_ch >= ' '; ++_ch) {
                if (*_ch == '`') {
                    token_kind += 1; // Get the formatted version of the token kind.
                    for (; *_ch >= ' '; ++_ch);
                }
            }

            u32 token_size = _ch - token_data;
            //for (; _ch[token_size] == ' '; --token_size);
            _file.append_inline_token(token_kind, {token_data, token_size});
            return Error::SUCCESS;
        }

        if (_ch[1] == '=') {
            token_kind = MjTokenKind::DIVIDE_SET;
        } else {
            token_kind = MjTokenKind::DIVIDE;
        }

        break;
    } case '%': {
        token_kind = MjTokenKind::REMAINDER;

        if (_ch[1] == '=') {
            token_kind += 1;
        }

        if (_ch[1] == '=') {
            token_kind = MjTokenKind::REMAINDER_SET;
        } else {
            token_kind = MjTokenKind::REMAINDER;
        }

        break;
    } case '+': {
        if (_ch[1] == '=') {
            token_kind = MjTokenKind::PLUS_SET;
        } else if (parse_numeric_literal().is_success()) {
            return Error::SUCCESS;
        } else {
            token_kind = MjTokenKind::PLUS;
        }

        break;
    } case '-': {
        if (_ch[1] == '=') {
            token_kind = MjTokenKind::MINUS_SET;
        } else if (parse_numeric_literal().is_success()) {
            return Error::SUCCESS;
        } else if (_state.in_shell() || _state.in_subshell()) {
            if (parse_shell_option().is_success()) {
                return Error::SUCCESS;
            }
        } else {
            token_kind = MjTokenKind::MINUS;
        }

        break;
    } case '&': {
        if (_state.in_type_expression()) {
            token_kind = MjTokenKind::REFERENCE_TYPE_MODIFIER;
        } else if (_ch[1] == '&') {
            token_kind = MjTokenKind::LOGICAL_AND;
        } else if (_ch[1] == '=') {
            token_kind = MjTokenKind::BITWISE_AND_SET;
        } else {
            token_kind = MjTokenKind::BITWISE_AND;
        }

        break;
    } case '^': {
        if (_ch[1] == '=') {
            token_kind = MjTokenKind::BITWISE_XOR_SET;
        } else {
            token_kind = MjTokenKind::BITWISE_XOR;
        }

        break;
    } case '|': {
        if (_ch[1] == '|') {
            token_kind = MjTokenKind::LOGICAL_OR;
        } else if (_ch[1] == '=') {
            token_kind = MjTokenKind::BITWISE_OR_SET;
        } else {
            token_kind = MjTokenKind::BITWISE_OR;
        }

        break;
    } case '=': {
        if (_ch[1] == '=') {
            token_kind = MjTokenKind::EQUAL;
        } else if (_ch[1] == '>') {
            token_kind = MjTokenKind::LAMBDA;
        } else {
            token_kind = MjTokenKind::SET;
        }

        break;
    } case ':': {
        if (_ch[1] == ':') {
            token_kind = MjTokenKind::SCOPE;
        } else {
            token_kind = MjTokenKind::COLON;
        }

        break;
    } case '<': {
        if (_ch[1] == '<') {
            if (_ch[2] == '=') {
                token_kind = MjTokenKind::LEFT_SHIFT_SET;
            } else {
                token_kind = MjTokenKind::LEFT_SHIFT;
            }
        } else if (_ch[1] == '=') {
            if (_ch[2] == '>') {
                token_kind = MjTokenKind::SPACESHIP;
            } else {
                token_kind = MjTokenKind::LESS_THAN_OR_EQUAL;
            }
        } else {
            token_kind = MjTokenKind::LESS_THAN;
        }

        break;
    } case '>': {
        if (token().kind() == MjTokenKind::INDENT || token().kind() == MjTokenKind::CLOSE_ANGLE_BRACKET) {
            token_kind = MjTokenKind::CLOSE_ANGLE_BRACKET;

            if (_state.in_angle_brackets()) {
                pop_state();
            } else {
                error_message = "Unmatched angle bracket!";
            }
        } else if (_ch[1] == '>') {
            if (_ch[2] == '=') {
                token_kind = MjTokenKind::RIGHT_SHIFT_SET;
            } else {
                token_kind = MjTokenKind::RIGHT_SHIFT;
            }
        } else if (_ch[1] == '=') {
            token_kind = MjTokenKind::GREATER_THAN_OR_EQUAL;
        } else {
            token_kind = MjTokenKind::GREATER_THAN;
        }

        break;
    } case '\'': {
        token_kind = MjTokenKind::RAW_STRING_LITERAL;
        _ch += 1;
        const u8 *token_data = _ch;
        u32 token_size = 0;

        for (; *_ch >= ' '; ++_ch) {
            if (*_ch == '\'') {
                token_size = _ch - token_data;
            }
        }

        if (token_size == 0) {
            error("Unterminated string literal!");
            return Error::FAILURE;
        }

        _ch -= (_ch - token_data) - token_size;
        _file.append_inline_token(token_kind, {token_data, token_size - 1});
        return Error::SUCCESS;
    } case '"': {
        return parse_interpolated_string_literal();
    } default: {
        if (parse_numeric_literal().is_success()) {
            return Error::SUCCESS;
        }

        if (parse_identifier().is_success()) {
            return Error::SUCCESS;
        }

        _file.append_inline_token(MjTokenKind::INVALID, {_ch, Utf8::size(_ch)});
        error("Invalid UTF-8 character!");
        return Error::FAILURE;
    }
    }

    if (token_kind.requires_leading_whitespace()) {
        // is binary operator or nested prefix operator
    }

    if (token_kind.requires_trailing_whitespace()) {
        // is binary operator or nested postfix operator
    }

    _file.append_token(token_kind);
    return Error::SUCCESS;
}






















































Error MjLexer::parse_type_expression() noexcept {

    // Parse the base type.
    while (parse_token().is_success() && token().kind().is_type_qualifier());

    if (parse_token(MjTokenKind::TYPE_NAME).is_failure()) {
        return Error::FAILURE;
    }

    // Parse the type modifiers.
    while (parse_token().is_success()) {
        switch (token().kind()) {
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

Error MjLexer::parse_shell_token() noexcept {
    parse_whitespace();

    if (!_has_leading_whitespace && token().kind() != MjTokenKind::OPEN_CURLY_BRACE) {
        return Error::FAILURE;
    }

    StringView token_text;
    StringView error_message;
    MjTokenKind token_kind = MjTokenKind::NONE;

    switch (*_ch) {
    case '-': {
        if (_ch[1] == '=') {
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




    while (parse_token().is_success() && token().kind() != MjTokenKind::INDENT) {
        if (_state.in_subshell()) {
            if (token().kind() != MjTokenKind::INDENT) {
                error("Expected ')' to close subshell!");
                return Error::FAILURE;
            }

            pop_state();
            break;
        }
    }

    if (_state.in_subshell()) {
        if (token().kind() == MjTokenKind::INDENT) {
            error("Expected ')' to close subshell!");
            return Error::FAILURE;
        }

        pop_state();
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_shell_option() noexcept {
    return Error::FAILURE;
}













Error MjLexer::parse_identifier() noexcept {

    // Parse a lowercase word
    const u8 *token_data = _ch;

    while (Ascii::is_lower(*_ch)) {
        _ch += 1;
    }

    StringView token_text{token_data, _ch - token_data};

    // Check for word boundary.
    if (Ascii::is_alnum(*_ch) || *_ch == '_') {

        // Early exit if module name.
        if (*_ch == ':' && _ch[1] == ':') {
            _ch += 2;
            _file.append_string_token(MjTokenKind::MODULE_NAME, token_text);
            _file.append_token(MjTokenKind::SCOPE);
            return Error::SUCCESS;
        }

        if (parse_keyword().is_success()) {
            return Error::SUCCESS;
        }
    }


    ///
    /// Check for user defined identifier
    ///


    if (Ascii::is_upper(*_ch)) {
        _ch += 1;

        while ((Ascii::is_upper(*_ch) || Ascii::is_digit(*_ch) || *_ch == '_')) {
            _ch += 1;
        }

        if (Ascii::is_lower(*_ch)) {
        }

        token_kind = token_size > 1 ? MjTokenKind::CONSTANT_NAME : MjTokenKind::TYPE_NAME;
    } else if (Ascii::is_lower(*_ch)) {
        _ch += 1;

        while ((Ascii::is_lower(*_ch) || Ascii::is_digit(*_ch) || *_ch == '_')) {
            _ch += 1;
        }

        token_text = {token_data, _ch - token_data};

        if (*_ch == '(') {
            trailing_token_type = MjTokenKind::OPEN_PARENTHESIS;
            push_state(MjLexerState::IN_PARENTHESES);
        } else if (*_ch == '<') {
            trailing_token_type = MjTokenKind::OPEN_ANGLE_BRACKET;
            push_state(MjLexerState::IN_ANGLE_BRACKETS);
        } else if (*_ch == '&') {
            trailing_token_type = MjTokenKind::FUNCTION_REFERENCE;
        }

        if (trailing_token_type != MjTokenKind::NONE) {
            _file.append_string_token(MjTokenKind::FUNCTION_NAME, token_text);
            _file.append_token(trailing_token_type);
            _ch += 1;
        } else {
            _file.append_string_token(MjTokenKind::VARIABLE_NAME, token_text);
        }
    } else {
    }


    ///
    /// Type Name - (?:[0-9][0-9+-]*)?[A-Z][A-Z0-9+-]*[a-z][A-Za-z0-9+-]*
    ///

    do {

        // (?:[0-9][0-9+-]*)?
        if (Ascii::is_digit(*_ch)) {
            for (_ch += 1; Ascii::is_digit(*_ch) || *_ch == '+' || *_ch == '-'; ++_ch);
        }

        // [A-Z]
        if (!Ascii::is_alnum(*_ch)) {
            _ch = token_data;
            break;
        }

        // [A-Z0-9+-]*
        for (_ch += 1; Ascii::is_upper(*_ch) || Ascii::is_digit(*_ch) || *_ch == '+' || *_ch == '-'; ++_ch);

        // [a-z]
        if (!Ascii::is_alnum(*_ch)) {
            _ch = token_data;
            break;
        }

        // [A-Za-z0-9+-]*
        for (_ch += 1; Ascii::is_alnum(*_ch) || *_ch == '+' || *_ch == '-'; ++_ch);
    } while (false);


    ///
    /// Module Name - [0-9A-Za-z][0-9A-Za-z+-]*(?=::)
    ///

    token_text = {token_data, _ch - token_data};

    // (?=::)
    if (*_ch == ':' && _ch[1] == ':') {
        _ch += 2;
        _file.append_string_token(MjTokenKind::MODULE_NAME, token_text);
        _file.append_token(MjTokenKind::SCOPE);
        return Error::SUCCESS;
    }


    _file.append_string_token(MjTokenKind::VARIABLE_NAME, token_text);
    return Error::SUCCESS;
}


Error MjLexer::parse_type_name() noexcept {

    // (?:[0-9][0-9+-]*)?[A-Z][A-Z0-9+-]*[a-z][A-Za-z0-9+-]*
    const u8 *token_data = _ch;

    // (?:[0-9][0-9+-]*)?
    if (Ascii::is_digit(*_ch)) {
        for (_ch += 1; Ascii::is_digit(*_ch) || *_ch == '+' || *_ch == '-'; ++_ch);
    }

    // [A-Z]
    if (!Ascii::is_upper(*_ch)) {
        _ch = token_data;
        return Error::FAILURE;
    }

    // [A-Z0-9+-]*
    for (_ch += 1; Ascii::is_upper(*_ch) || Ascii::is_digit(*_ch) || *_ch == '+' || *_ch == '-'; ++_ch);

    // [a-z]
    if (!Ascii::is_lower(*_ch)) {
        _ch = token_data;
        return Error::FAILURE;
    }

    // [A-Za-z0-9+-]*
    for (_ch += 1; Ascii::is_alnum(*_ch) || *_ch == '+' || *_ch == '-'; ++_ch);

    // Check for word boundary.
    if (*_ch == '_') {
        _ch = token_data;
        return Error::FAILURE;
    }

    StringView token_text{token_data, _ch - token_data};

    // Check for module name.
    if (*_ch == ':' && _ch[1] == ':') {
        _ch += 2;
        _file.append_string_token(MjTokenKind::MODULE_NAME, token_text);
        _file.append_token(MjTokenKind::SCOPE);
        return Error::SUCCESS;
    }

    _file.append_string_token(MjTokenKind::TYPE_NAME, token_text);
    return Error::SUCCESS;
}


Error MjLexer::parse_module_name(StringView token_text) noexcept {
    if (*_ch == ':' && _ch[1] == ':') {
        return Error::FAILURE;
    }

    _ch += 2;
    _file.append_string_token(MjTokenKind::MODULE_NAME, token_text);
    _file.append_token(MjTokenKind::SCOPE);
    return Error::SUCCESS;
}


Error MjLexer::parse_keyword() noexcept {

    // Parse a lowercase word
    const u8 *token_data = _ch;

    while (Ascii::is_lower(*_ch)) {
        _ch += 1;
    }

    StringView token_text{token_data, _ch - token_data};

    // Check for word boundary.
    if (Ascii::is_alnum(*_ch) || *_ch == '_') {
        
    }

    // Early exit if module name.
    if (*_ch == ':' && _ch[1] == ':') {
        _ch += 2;
        _file.append_string_token(MjTokenKind::MODULE_NAME, token_text);
        _file.append_token(MjTokenKind::SCOPE);
        return Error::SUCCESS;
    }




    // Test priority names







    ///
    /// Numeric Type Names
    ///


    u8 token_size = 0;

    while (*_ch == 'f' || *_ch == 'i' || *_ch == 'u') {

        // Two-character type names: [iu]8
        u32 packed = (*_ch << 8) | _ch[1];

        if (packed == 0x6938u || packed == 0x7538u) { // "i8" or "u8"
            token_size = 2;
            break;
        }

        // Make sure the last character wasn't a null byte.
        if (!_ch[1]) {
            break;
        }

        // Three-character type names: [fiu](16|32|64)
        packed = ((packed & 0xFFu) << 8) | _ch[2];

        if (packed == 0x3136u || packed == 0x3332u || packed == 0x3634u) { // "16", "32", or "64"
            token_size = 3;
            break;
        }

        // Make sure the last character wasn't a null byte.
        if (!_ch[2]) {
            break;
        }

        // Four-character type names: [fiu]128
        if ((packed << 8) | _ch[3] == 0x313238u) { // "128"
            token_size = 4;
        }

        break;
    }

    if (token_size > 0) {
        _ch += token_size;

        if (*_ch == '<') {
            _file.append_string_token(MjTokenKind::TYPE_NAME, token_text);
            _file.append_token(MjTokenKind::OPEN_ANGLE_BRACKET);
            push_state(MjLexerState::IN_ANGLE_BRACKETS);
            parse_unit_expression();
            return Error::SUCCESS;
        }

        if (*_ch == 'x') {
            _file.append_string_token(MjTokenKind::TYPE_NAME, token_text);
            // vectorized register
            return Error::SUCCESS;
        }

        _file.append_string_token(MjTokenKind::TYPE_NAME, token_text);
    } else if (token_text.size() == 4) {
        if (token_text == StringView("bool") || token_text == StringView("void")) {
            _file.append_string_token(MjTokenKind::TYPE_NAME, token_text);
            return Error::SUCCESS;
        }
    }







    if (*_ch == '(') {
        _file.append_string_token(MjTokenKind::FUNCTION_NAME, token_text);
        _file.append_token(MjTokenKind::OPEN_PARENTHESIS);
        push_state(MjLexerState::IN_PARENTHESES);
        return Error::SUCCESS;
    }

    if (*_ch == '&') {
        _file.append_string_token(MjTokenKind::FUNCTION_NAME, token_text);
        _file.append_token(MjTokenKind::FUNCTION_REFERENCE);
        return Error::SUCCESS;
    }

    if (*_ch == '<') {

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

        if (token_kind == MjTokenKind::FUNCTION_NAME) {
            _file.append_string_token(token_kind, token_text);
        } else {
            _file.append_token(token_kind);
        }

        _file.append_token(MjTokenKind::OPEN_ANGLE_BRACKET);
        push_state(MjLexerState::IN_ANGLE_BRACKETS);

        if (token_kind == MjTokenKind::UNIT) {
            parse_unit_expression();
        }

        return Error::SUCCESS;
    }

    if (*_ch == ' ' && _ch[1] == '(') {
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

        if (token_kind == MjTokenKind::VARIABLE_NAME) {
            _file.append_string_token(token_kind, token_text);
        } else {
            _file.append_token(token_kind);
        }

        _ch += 1;
        _file.append_token(MjTokenKind::OPEN_PARENTHESIS);
        push_state(MjLexerState::IN_PARENTHESES);
        return Error::SUCCESS;
    }

    if (*_ch == '&') {
        trailing_token_type = MjTokenKind::FUNCTION_REFERENCE;
    } else if (Ascii::is_upper(*_ch) || Ascii::is_digit(*_ch)) {

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
            if (token_text == info.text) {
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
            if (token_text == info.text) {
                if (*_ch == ' ') {
                    parse_whitespace();

                    if (*_ch == '{' || (*_ch | 0x20u) - 'a' < 26 || *_ch - '0' < 10 || *_ch == '_') {
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
            if (token_text == info.text) {
                if (_has_trailing_whitespace) {
                    return Error::SUCCESS;
                }

                return Error::FAILURE;
            }
        }

        _file.append_string_token(MjTokenKind::VARIABLE_NAME, token_text);
    }

    if (trailing_token_type != MjTokenKind::NONE) {
        token_kind = MjTokenKind::FUNCTION_NAME;
    } else {
        token_kind = MjTokenKind::VARIABLE_NAME;
    }

}


Error MjLexer::parse_numeric_literal() noexcept {
    const u8 *token_data = _ch;
    const u8 *checkpoint = nullptr;

    // Parse the sign.
    bool has_sign = *_ch == '+' || *_ch == '-';
    _ch += has_sign;

    // Parse the base prefix.
    u8 base = 10;
    u8 delimiter = ',';

    if (*_ch == '0') {
        _ch += 1;

        if (*_ch == 'x') {
            _ch += 1;
            delimiter = '_';
            base = 16;
        } else if (*_ch == 'o') {
            _ch += 1;
            delimiter = '_';
            base = 8;
        } else if (*_ch == 'b') {
            _ch += 1;
            delimiter = '_';
            base = 2;
        } else {
            _ch -= 1;
        }
    }

    // Check that there is an integer portion.
    if (!Ascii::is_uppercase_alnum_digit(*_ch, base)) {
        _ch = token_data;
        return Error::FAILURE;
    }

    // Parse the integer portion.
    for (_ch += 1; Ascii::is_uppercase_alnum_digit(*_ch, base); ++_ch);

    // Parse the optional delimited integer portions.
    while (*_ch == delimiter) {
        if (base == 10) {
            checkpoint = _ch;
        }

        if (Ascii::is_uppercase_alnum_digit(_ch[1], base)) {
            for (_ch += 2; Ascii::is_uppercase_alnum_digit(*_ch, base); ++_ch);
        }
    }

    // Parse the optional fractional portion.
    if (*_ch == '.') {
        checkpoint = _ch;

        if (Ascii::is_uppercase_alnum_digit(_ch[1], base)) {
            for (_ch += 2; Ascii::is_uppercase_alnum_digit(*_ch, base); ++_ch);
        }
    }

    // Parse the optional exponent portion.
    if ((base == 10 && *_ch == 'e') || (base == 16 && *_ch == 'p')) {
        _ch += 1;

        // Parse the optional exponent sign.
        if (*_ch == '+' || *_ch == '-') {
            _ch += 1;
        }

        for (; Ascii::is_decimal_digit(*_ch); ++_ch);
    }

    // Parse the type suffix.
    u8 type_suffix_size = 0;

    while (*_ch == 'f' || *_ch == 'i' || *_ch == 'u') {
        type_suffix_size = 1;

        // Two-character suffixes: [iu]8
        u32 packed = (*_ch << 8) | _ch[1];

        if (packed == 0x6938u || packed == 0x7538u) { // "i8" or "u8"
            type_suffix_size = 2;
            break;
        }

        // Make sure the last character wasn't a null byte.
        if (!_ch[1]) {
            break;
        }

        // Three-character suffixes: [fiu](16|32|64)
        packed = ((packed & 0xFFu) << 8) | _ch[2];

        if (packed == 0x3136u || packed == 0x3332u || packed == 0x3634u) { // "16", "32", or "64"
            type_suffix_size = 3;
            break;
        }

        // Make sure the last character wasn't a null byte.
        if (!_ch[2]) {
            break;
        }

        // Four-character suffixes: [fiu]128
        if ((packed << 8) | _ch[3] == 0x313238u) { // "128"
            type_suffix_size = 4;
        }

        break;
    }

    _ch += type_suffix_size;

    // Check for word boundary.
    if ((Ascii::is_alnum(*_ch) || *_ch == '_')) {
        if (!checkpoint) {
            _ch = token_data;
            return Error::FAILURE;
        }

        _ch = checkpoint;
        type_suffix_size = 0;
    }

    // Emit tokens.
    _file.append_string_token(MjTokenKind::NUMERIC_LITERAL, {token_data, _ch - token_data});

    if (_emit_subtokens) {
        if (base != 10) {
            _file.append_subtoken(MjTokenKind::NUMERIC_LITERAL_PREFIX, has_sign, 2);
        }

        if (type_suffix_size > 0) {
            _file.append_subtoken(MjTokenKind::NUMERIC_LITERAL_SUFFIX, u8(_ch - token_data) - type_suffix_size, type_suffix_size);
        }
    }

    // Check for a unit expression after a numeric literal.
    if (*_ch == ' ') {

        // Check for an "as" or "is" keyword because they take priority over a unit expression.
        if (StringView(_ch, 2) == StringView("as") || StringView(_ch, 2) == StringView("is")) {
            // TODO
        } else {
            parse_unit_expression();
        }
    }

    return Error::SUCCESS;
}


Error MjLexer::parse_unit_expression() noexcept {
    const u8 *token_data = _ch;

    // Match the first portion: [A-Za-zµΩÅ°'"]|^g|1/
    while (true) {
        if (!*_ch) {
            return Error::FAILURE;
        }

        u16 value = *_ch;

        if (
            (value | 0x20u) - 'a' < 26 ||
            value == '\'' ||
            value == '"'
        ) {
            _ch += 1;
            break;
        }

        if (!_ch[1]) {
            return Error::FAILURE;
        }

        value = (value << 8) | _ch[1];

        if (
            value == (('^' << 8) | 'g') || // '^g'
            value == (('1' << 8) | '/') || // '1/'
            value == 0xC2B0u || // '°'
            value == 0xC2B5u || // 'µ'
            value == 0xC2B7u || // '·'
            value == 0xC385u || // 'Å'
            value == 0xCEA9u    // 'Ω'
        ) {
            _ch += 2;
            break;
        }

        return Error::FAILURE;
    }

    // [A-Za-z0-9µΩÅ°'"⁰¹²³⁴⁵⁶⁷⁸⁹⁻⸍·^*/-]*
    while (*_ch) {
        u32 value = *_ch;

        if (
            (value | 0x20u) - 'a' < 26 || value - '0' < 10 ||
            value == '\'' ||
            value == '"' ||
            value == '^' ||
            value == '*' ||
            value == '/' ||
            value == '-'
        ) {
            _ch += 1;
            continue;
        }

        value = (value << 8) | _ch[1];

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
            _ch += 2;
            continue;
        }

        if (!_ch[1]) {
            break;
        }

        value = (value << 8) | _ch[2];

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
            _ch += 3;
            continue;
        }

        break;
    }

    _file.append_string_token(MjTokenKind::UNIT_EXPRESSION, {token_data, _ch - token_data});
    return Error::SUCCESS;
}


Error MjLexer::parse_interpolated_string_literal() noexcept {
    _ch += 1;
    //parse_whitespace();

    //if (*_ch != '"') {
    //    return Error::FAILURE;
    //}
    struct SubToken {
        MjTokenKind kind;
        u8 offset;
        u8 size;
    };

    std::vector<SubToken> escape_sequences;
    u32 token_size = 1;
    MjTokenKind token_kind = MjTokenKind::STRING_LITERAL;

    while (_ch[token_size] != '"') {
        if (_ch[token_size] == 0) {
            error("Unterminated string literal!");
            break;
        }

        if (_ch[token_size] == '\\') {
            token_kind = MjTokenKind::INTERPOLATED_STRING_LITERAL;
            token_size += 1;

            if (!_ch[token_size]) {
                break;
            }

            SubToken escape_sequence{MjTokenKind::CHARACTER_ESCAPE_SEQUENCE, _token_offset, 2};

            switch (_ch[token_size]) {
            case '\\': // '\\'
            case '"': // '\"'
            case 'e': // '\e'
            case 'n': // '\n'
            case 'r': // '\r'
            case 't': // '\t'
            case '0': // '\0'
                break;
            case 'o': { // '\o377'
                for (u32 n = token_size + 3; token_size < n; token_size++) {
                    if (!Ascii::is_octal_digit(_ch[token_size])) {
                        escape_sequence.kind = MjTokenKind::INVALID_ESCAPE_SEQUENCE;
                        escape_sequence.size = token_size;
                        error(escape_sequence, "Invalid string escape sequence! '\\o' requires 3 octal digits!");
                        break;
                    }
                }

                if (_ch[token_size - 3] > '3') {
                    escape_sequence.kind = MjTokenKind::INVALID_ESCAPE_SEQUENCE;
                    escape_sequence.size = 5;
                    error(escape_sequence, "Invalid string escape sequence! Max value is \"\\o377\"!");
                }

                break;
            } case 'x': { // '\x7F'
                for (u32 n = token_size + 2; token_size < n; token_size++) {
                    if (!Ascii::is_uppercase_hexadecimal_digit(_ch[token_size])) {
                        escape_sequence.kind = MjTokenKind::INVALID_ESCAPE_SEQUENCE;
                        escape_sequence.size = token_size;
                        error(escape_sequence, "Invalid string escape sequence! '\\x' requires 2 hexadecimal digits!");
                        break;
                    }
                }

                if (_ch[token_size - 2] > '7') {
                    escape_sequence.kind = MjTokenKind::INVALID_ESCAPE_SEQUENCE;
                    escape_sequence.size = 4;
                    error(escape_sequence, "Invalid string escape sequence! Max value is \"\\x7F\"!");
                }

                break;
            } case 'u': { // '\uFFFF'
                for (u32 n = token_size + 4; token_size < n; token_size++) {
                    if (!Ascii::is_uppercase_hexadecimal_digit(_ch[token_size])) {
                        escape_sequence.kind = MjTokenKind::INVALID_ESCAPE_SEQUENCE;
                        escape_sequence.size = token_size;
                        error(escape_sequence, "Invalid Unicode string escape sequence! '\\u' requires 4 hexadecimal digits!");
                        break;
                    }
                }

                break;
            } case 'U': { // '\U10FFFF'
                for (u32 n = token_size + 6; token_size < n; token_size++) {
                    if (!Ascii::is_uppercase_hexadecimal_digit(_ch[token_size])) {
                        escape_sequence.kind = MjTokenKind::INVALID_ESCAPE_SEQUENCE;
                        escape_sequence.size = token_size;
                        error(escape_sequence, "Invalid Unicode string escape sequence! '\\U' requires 6 hexadecimal digits!");
                        break;
                    }
                }

                if (_ch[token_size - 6] > '1' || (_ch[token_size - 6] == '1' && _ch[token_size - 5] > '0')) {
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

        token_size += 1;
    }

    _file.append_string_token(token_kind, {_ch, token_size});

    for (SubToken escape_sequence : escape_sequences) {
        _file.append_subtoken(escape_sequence.kind, escape_sequence.offset, escape_sequence.size);
    }

    return Error::SUCCESS;
}


///
/// Line Control and Whitespace Parsing
///


void MjLexer::parse_whitespace() noexcept {
    for (; *_ch == ' '; ++_ch);

    if (*_ch == '\n') {
        parse_indent();
        _file.append_indent_token(_ch - _file.line(_line_index).ptr());
        _line_index += 1;

        if (*_ch) {
            _ch += 1;
        }
    } else {
        _has_leading_whitespace = _ch[-1] == ' ';
    }
}


void MjLexer::parse_indent() noexcept {
    const u8 *token_data;

    do {
        for (token_data = _ch; *_ch == ' '; ++_ch);
    } while (parse_newline());

    u32 indent_size = _ch - token_data;
    _last_indent = _line_indent;
    _line_indent = indent_size / INDENT_WIDTH;
    _file.append_indent_token(_line_indent);
    _line_index += 1;
    _ch += indent_size % INDENT_WIDTH;

    // Reset line dependent parsing states.
    _has_leading_whitespace = true;

    if (_state.in_annotation() || _state.in_shell()) {
        pop_state();
    }
}


bool MjLexer::parse_newline() noexcept {
    if (*_ch != '\n') {
        return false;
    }

    _file.append_indent_token(_ch - _file.line(_line_index).ptr());
    _line_index += 1;

    if (!*_ch) {
        return false;
    }

    _ch += 1;
    return true;
}


///
/// Error Handling
///


void MjLexer::error(MjToken token, StringView message) noexcept {
    printf(
        "%s:%u:%u: \x1B[31;1mError:\x1B[m %.*s\n"
        "%.*s\n"
        "\x1B[35;1m%*.*s\x1B[m\n",
        _file.path().c_str(), _line_offsets[token.] + 1, token.offset, message.size(), message.data(),
        _file.line(token.line).size(), _file.line(token.line).ptr(),
        token.offset, token.size, "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
    );
}
