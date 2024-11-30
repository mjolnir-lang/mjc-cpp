#pragma once

#include <mj/ast/MjFile.hpp>

#include <vector>
#include <stack>
#include <filesystem>
#include <fstream>


/// lexical errors (invalid tokens, unterminated string literals, invalid numbers, invalid identifiers, invalid operators)
// Lexical    Lexer    Scanner
// Syntax     Parser
// Semantics  Compiler
class MjLexerError {
private:
    MjToken _token;
    StringView _message;
public:


    constexpr
    MjLexerError(MjToken token, StringView message) noexcept :
        _token(token),
        _message(message)
    {}
};


// semantic error (types, operators, math, templates, usages, missing, duplicate)
class MjCompilerError {
private:
    StringView _message;
public:


    constexpr
    MjCompilerError(StringView message) noexcept : _message(message) {}
};


class MjRuntimeError {
private:
    StringView _message;
public:


    MjRuntimeError(StringView message) noexcept : _message(message) {}
};


struct MjLexerPosition {
    u32 tokens_size;
    u32 line_index = 0;
    u16 byte_offset = 0;
    u8 last_indent;
    u8 indent;
};


template<class MjLexerState>
struct MjLexerStateValues {
    static constexpr MjLexerState NONE{0};
    static constexpr MjLexerState IN_ANNOTATION{5 << 1};
    static constexpr MjLexerState IN_TYPE_EXPRESSION{6 << 1};
    static constexpr MjLexerState IN_TYPE_CAST{7 << 1};
    static constexpr MjLexerState IN_PARENTHESES{8 << 1};
    static constexpr MjLexerState IN_SQUARE_BRACKETS{9 << 1};
    static constexpr MjLexerState IN_ANGLE_BRACKETS{10 << 1};
    static constexpr MjLexerState IN_CURLY_BRACES{11 << 1};
    static constexpr MjLexerState IN_SUBSHELL{12 << 1};
    static constexpr MjLexerState IN_SHELL{13 << 1};
};


struct MjLexerState : public Enum<u16>, public MjLexerStateValues<MjLexerState> {

    constexpr
    explicit
    MjLexerState(u16 id) noexcept : Enum(id) {}


    
    constexpr bool in_annotation() const noexcept { return _id & IN_ANNOTATION; }
    constexpr bool in_type_expression() const noexcept { return _id & IN_TYPE_EXPRESSION; }
    constexpr bool in_type_cast() const noexcept { return _id & IN_TYPE_CAST; }
    constexpr bool in_parentheses() const noexcept { return _id & IN_PARENTHESES; }
    constexpr bool in_square_brackets() const noexcept { return _id & IN_SQUARE_BRACKETS; }
    constexpr bool in_angle_brackets() const noexcept { return _id & IN_ANGLE_BRACKETS; }
    constexpr bool in_curly_braces() const noexcept { return _id & IN_CURLY_BRACES; }
    constexpr bool in_subshell() const noexcept { return _id & IN_SUBSHELL; }
    constexpr bool in_shell() const noexcept { return _id & IN_SHELL; }
};




/// The MjLexer parses a Mjolnir source file into a stream of tokens.
/// The parsing is done in two ways. First, non-identifier/non-number characters
/// are combined and consolidated into tokens and emitted when a sequence is
/// terminated. Second, syntax rules are used to parse differently in different
/// contexts by tracking state and indentation.
class MjLexer {
private:
    MjFile &_file;
    StringView _line;
    u32 _line_index = 0;
    u8 _line_indent = 0;
    u8 _last_indent = 0;
    std::stack<MjLexerState> _states;
    MjLexerState _state = MjLexerState::NONE;
    bool _emit_subtokens;
    bool _at_eof;
    bool _has_leading_whitespace;
    bool _has_trailing_whitespace;

    static constexpr u32 INDENT_WIDTH = 4;
public:


    static
    MjFile *parse_file(std::filesystem::path path) noexcept;


private:



    constexpr
    MjLexer(MjFile &file, bool emit_subtokens = false) noexcept :
        _file(file),
        _emit_subtokens(emit_subtokens)
    {}


    ///
    /// Internal Properties
    ///


    /// @brief Parse any token.
    /// @return The type of token was parsed.
    MjToken *token() noexcept {
        return &_file.tokens().back();
    }


    ///
    /// Main parsing function
    ///


    /// This is the main parsing function.
    Error parse() noexcept;



    ///
    /// Parse Compound Syntax Elements
    ///


    Error parse_shell_option() noexcept;


    Error parse_shell_token() noexcept;


    /// Parse a type expression.
    ///
    /// A type expression begins with either a type name or a CV-qualifier and is followed by zero
    /// or more type qualifiers.
    Error parse_type_expression() noexcept;


    /// Parse an identifier. Either a keyword, function, type, constant, module, literal, or variable.
    Error parse_identifier() noexcept;


    /// Attempt to parse the next token as either a raw or an interpolated string.
    Error parse_raw_string_literal() noexcept;


    /// Parse an interpolated string literal.
    Error parse_interpolated_string_literal() noexcept;


    /// Parse a numeric literal.
    Error parse_numeric_literal() noexcept;


    /// Parse a unit expression.
    Error parse_unit_expression() noexcept;


    ///
    /// Parse Compound Enclosed Syntax Elements
    ///


    ///
    /// Token Parsing
    ///


    /// @brief Parse any token.
    /// @return The type of token was parsed.
    Error parse_token(MjTokenKind token_kind) noexcept;


    Error parse_token() noexcept;
    Error parse_binary_operator() noexcept;


    /// @brief Parse the given text as an operator of the given token type.
    /// @param text The text of the token.
    /// @param token_kind The type of the token.
    /// @return true if the token was parsed successfully.
    Error parse_token(StringView text, MjTokenKind token_kind, bool skip_trailing_whitespace = true) noexcept;


    /// @brief Parse the given text as an operator of the given token type. Operators must have
    /// whitespace around them.
    /// @param text The text of the token.
    /// @param token_kind The type of the token.
    /// @return true if the token was parsed successfully.
    Error parse_operator(StringView text, MjTokenKind token_kind, bool skip_trailing_whitespace = true) noexcept;


    /// @brief Parse the given text as an operator of the given token type. Words must not be
    /// followed by more word characters or be a module name.
    /// @param text The text of the token.
    /// @param token_kind The type of the token.
    /// @return true if the token was parsed successfully.
    Error parse_word(StringView text, MjTokenKind token_kind, bool skip_trailing_whitespace = true) noexcept;


    ///
    /// Text Parsing
    ///


    Error parse_text(StringView string, MjTokenKind token_kind) noexcept;


    Error parse_text(u8 ch, MjTokenKind token_kind) noexcept;


    /// @brief Parse a token of the given kind with the given size.
    void parse_text(MjTokenKind kind, u32 size = 1) noexcept;


    void append_token(MjToken token) noexcept;


    /// @brief Parse a sub-token of the given kind at the given offset and size within the preceding
    /// token.
    void append_subtoken(MjTokenKind kind, u32 offset, u32 size = 1) noexcept;


    Error peek_text(StringView string) const noexcept {
        if (!_line.starts_with(string)) {
            return Error::FAILURE;
        }

        return Error::SUCCESS;
    }


    Error peek_text(u8 ch) const noexcept {
        if (!_line.starts_with(ch)) {
            return Error::FAILURE;
        }

        return Error::SUCCESS;
    }


    ///
    /// Line Control and Whitespace Parsing
    ///


    /// @brief Skip all leading whitespace characters, moving to the next non-empty line.
    void skip_whitespace() noexcept;


    /// @brief Parse the indentation of the current line, skipping empty lines.
    void parse_indent() noexcept;


    /// @brief Move the parser to the next line.
    void move_to_next_line() noexcept;


    ///
    /// State Control
    ///


    void clear_state(MjLexerState state) noexcept {
        _state &= ~state;
        _states.push(state);
    }


    void push_state(MjLexerState state) noexcept {
        //_state |= state;
        _states.push(state);
    }


    void pop_state() noexcept {
        _state = _states.top();
        _states.pop();
    }



    /// @brief Save the Lexer state so that the current position can be restored if a subsequent parse operation fails.
    //MjLexerPosition save() noexcept {
    //    return {
    //        static_cast<u32>(_file.tokens().size()),
    //        _line_index,
    //        static_cast<u16>(_file.line(_line_index).size() - _line.size()),
    //        _line_indent,
    //        _last_indent
    //    };
    //}


    /// @brief Restore the lexer state from a previously saved position.
    /// @param position The lexer position.
    //void restore(const MjLexerPosition &position) noexcept {
    //    _file.tokens().resize(position.tokens_size);
    //    _line = _file.line(position.line_index) + position.byte_offset;
    //    _line_index = position.line_index;
    //    _line_indent = position.indent;
    //    _last_indent = position.last_indent;
    //}


    ///
    /// Error Handling
    ///


    void error(const MjToken &token, StringView message) noexcept;


    void error(StringView message) noexcept {
        error(*token(), message);
    }
};
