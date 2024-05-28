#pragma once

#include <mj/ast/MjToken.hpp>

#include <std/File.hpp>


/// lexical errors (invalid tokens, unterminated string literals, invalid numbers, invalid identifiers, invalid operators)
// Lexical    Lexer    Scanner
// Syntax     Parser
// Semantics  Compiler
class MjLexerError {
private:
    MjToken _token;
    StringView _message;
public:


    MjLexerError(
        MjToken token,
        StringView message
    ) :
        _token(token),
        _message(message)
    {}
};


// semantic error (types, operators, math, templates, usages, missing, duplicate)
class MjCompilerError {
private:
    StringView _message;
public:


    MjCompilerError(
        StringView message
    ) :
        _message(message)
    {}
};


class MjRuntimeError {
private:
    StringView _message;
public:


    MjRuntimeError(
        StringView message
    ) :
        _message(message)
    {}
};


struct MjLexerPosition {
    u32 tokens_size;
    u32 line_index = 0;
    u16 byte_offset = 0;
    u8 last_indent;
    u8 indent;
};


/// The MjLexer parses a Mjolnir source file into a stream of tokens.
/// The parsing is done in two ways. First, non-identifier/non-number characters
/// are combined and consolidated into tokens and emitted when a sequence is
/// terminated. Second, syntax rules are used to parse differently in different
/// contexts by tracking state and indentation.
class MjLexer {
private:
    File _file;
    Vector<MjToken> _tokens;
    StringView _line = nullptr;
    u32 _line_index = 0;
    u8 _line_indent = 0;
    u8 _last_indent = 0;
    bool _emit_subtokens = false;
public:


    MjLexer(const Path &path) :
        _file(path)
    {}


    void parse();


    const Vector<MjToken> &tokens() const {
        return _tokens;
    }


    StringView token_text(const MjToken &token) const {
        return StringView(&_file[token.line][token.offset], token.size);
    }
private:


    /// This is the main parsing function.
    void parse_tokens();
    void parse_tokens_fsm();
    void parse_tokens_fsm2();


    ///
    /// Error Handling
    ///


    void error(StringView message) {
        error(_tokens.back(), message);
    }


    void error(const MjToken &token, StringView message);


    ///
    /// Parse Context
    ///


    /// @brief Append a new token to the output buffer.
    /// @param type 
    /// @param size 
    void append_token(MjTokenType type, u32 size);
    void append_subtoken(MjTokenType type, u32 offset, u32 size);


    /// @brief Save the Lexer state so that the current position can be restored if a subsequent parse operation fails.
    MjLexerPosition save() {
        return {
            static_cast<u32>(_tokens.size()),
            _line_index,
            static_cast<u16>(_file[_line_index].size() - _line.size()),
            _line_indent,
            _last_indent
        };
    }


    /// @brief Restore the lexer state from a previously saved position.
    /// @param position The lexer position.
    void restore(const MjLexerPosition &position) {
        _tokens.resize(position.tokens_size);
        _line = _file[position.line_index] + position.byte_offset;
        _line_index = position.line_index;
        _line_indent = position.indent;
        _last_indent = position.last_indent;
    }


    ///
    /// Parse Tokens
    ///


    /// @brief Parse any token.
    /// @return The type of token was parsed.
    MjTokenType parse_token(bool skip_trailing_whitespace = true);


    /// @brief Parse the given text as an operator of the given token type.
    /// @param text The text of the token.
    /// @param token_type The type of the token.
    /// @return true if the token was parsed successfully.
    Error parse_token(StringView text, MjTokenType token_type, bool skip_trailing_whitespace = true);


    /// @brief Parse the given text as an operator of the given token type. Operators must have
    /// whitespace around them.
    /// @param text The text of the token.
    /// @param token_type The type of the token.
    /// @return true if the token was parsed successfully.
    Error parse_operator(StringView text, MjTokenType token_type, bool skip_trailing_whitespace = true);


    /// @brief Parse the given text as an operator of the given token type. Words must not be
    /// followed by more word characters or be a module name.
    /// @param text The text of the token.
    /// @param token_type The type of the token.
    /// @return true if the token was parsed successfully.
    Error parse_word(StringView text, MjTokenType token_type, bool skip_trailing_whitespace = true);


    ///
    /// Parse Context
    ///


    /// @brief Parse all whitespace characters. This should be called after each token is parsed to
    /// make sure that the parser is looking at valid text. We call this after each token instead
    /// of before each token because sometimes we have to test the whitespace preceding the current
    /// token. This will also handle newlines and track indentation as needed for end of statement
    /// detection.
    void skip_whitespace();


    ///
    /// Parse Compound Syntax Elements
    ///


    /// Parse an identifier. Either a keyword, function, type, constant, module, literal, or variable.
    /// @return true if the element was parsed successfully.
    Error parse_identifier();

    Error parse_type_qualifier();
    Error parse_type_name();
    Error parse_variable_name();


    /// @return true if the element was parsed successfully.
    Error parse_import_statement();


    /// Attempt to parse the next token as either a raw or an interpolated string.
    ///
    /// NOTE: Tokens are not emitted for escaped character sequences.
    /// @return true if the element was parsed successfully.
    Error parse_string_literal();
    Error parse_raw_string_literal();
    Error parse_interpolated_string_literal();
    Error parse_numeric_literal();


    /// @return true if the element was parsed successfully.
    Error parse_operator();


    /// Parse an expression.
    ///
    /// @return true if the element was parsed successfully.
    Error parse_expression();


    /// Parse a type expression.
    ///
    /// A type expression begins with either a type name or a CV-qualifier and is followed by zero or more type qualifiers.
    /// @return true if the element was parsed successfully.
    Error parse_type_expression();


    /// Parse a unit expression.
    ///
    /// [A-Za-zµΩÅ°'"]|\^g|1/)[A-Za-z0-9⁰¹²³⁴⁵⁶⁷⁸⁹⁻⸍µΩÅ°'"·^*/-]*
    /// @return true if the element was parsed successfully.
    Error parse_unit_expression();


    ///
    /// Parse Compound Enclosed Syntax Elements
    ///


    /// @brief Parse a template parameter list.
    /// <type Type [= Type], Type [var [= expr]], ...>
    /// @return true if the element was parsed successfully.
    Error parse_template_parameter_list();


    /// @brief Parse a template argument list.
    /// <Type, expr, ...>
    /// @return true if the element was parsed successfully.
    Error parse_template_argument_list();


    /// @brief Parse a function parameter list.
    /// (Type [var [= expr]], ...)
    /// @return true if the element was parsed successfully.
    Error parse_function_parameter_list();


    /// @brief Parse a function argument list.
    /// (expr, ...)
    /// @return true if the element was parsed successfully.
    Error parse_function_argument_list();


    /// @brief Parse a parenthesis expression.
    /// (expr)
    /// @return true if the element was parsed successfully.
    Error parse_parenthesis_expression();


    /// @brief Parse a type cast expression.
    /// (Type: expr)
    /// @return true if the element was parsed successfully.
    Error parse_type_cast_expression();
};



// Parser stuff
/*
    void error(MjToken token, StringView message) {
        printf("%s:%u:%u: \x1B[31merror:\x1B[m ",
            _file.path().c_str(), token.line, token.offset
        );
        printf("%.*s\n", message.size(), message.data());
        printf("\x1B[35m%*.*s\x1B[m",
            token.offset, token.size, "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
        );
    }


    const MjToken &next();


    const MjToken *peek() const {
        return _tokens.back();
    }


    const MjToken *next_if_any(MjTokenType type) {
        return _token->type == type ? &next() : nullptr;
    }


    Error next_if(const MjToken &token) {
        return *this->_token == token ? &next() : nullptr;
    }


    void expect(const MjToken &token) {
        if (next() != token) {
            printf("%s:%u:%u: Expected: '%.*s'\n",
                _file.path().c_str(), _token.line, _token.offset, _token.size, &_file[_token.line][_token.offset]
            );
        }
    }


    const MjToken *expect_any(MjTokenType type) {
        if (next().type != type) {
            printf("%s:%u:%u: Expected: '%.*s'\n",
                _file.path().c_str(), _token.line, _token.offset, _token.size, MjTokenType_name(type).size(), MjTokenType_name(type).data()
            );
        }

        return _token;
    }


    /// @brief Return true if the token is the first in the line.
    /// This is used for tracking indentation as a parsing hint for handling errors.
    Error next_is_first() {
        return false;
    }
*/