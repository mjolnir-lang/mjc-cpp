#pragma once

#include <mj/MjLexerError.hpp>
#include <mj/MjLexerState.hpp>
#include <mj/ast/MjFile.hpp>

#include <vector>
#include <stack>
#include <filesystem>
#include <fstream>


/// The MjLexer parses a Mjolnir source file into a stream of tokens.
/// The parsing is done in two ways. First, non-identifier/non-number characters
/// are combined and consolidated into tokens and emitted when a sequence is
/// terminated. Second, syntax rules are used to parse differently in different
/// contexts by tracking state and indentation.
class MjLexer {
private:
    MjFile &_file;
    const u8 *_ch;
    u32 _line_index = 0;
    u32 _token_offset = 0;
    u8 _line_indent = 0;
    u8 _last_indent = 0;
    std::stack<MjLexerState> _states;
    MjLexerState _state = MjLexerState::NONE;
    bool _emit_subtokens;
    bool _has_leading_whitespace;
    bool _has_trailing_whitespace;

    static constexpr u32 INDENT_WIDTH = 4;
public:


    static
    MjFile *parse_file(std::filesystem::path path, bool emit_subtokens = false) noexcept;


private:


    constexpr
    MjLexer(MjFile &file, bool emit_subtokens = false) noexcept :
        _file(file),
        _emit_subtokens(emit_subtokens)
    {}


    ///
    /// Properties
    ///


    /// @brief Parse any token.
    /// @return The type of token was parsed.
    MjToken *token() noexcept {
        return &_file.tokens().back();
    }


    ///
    /// Token Parsing
    ///


    /// This is the main parsing function.
    Error parse() noexcept;


    /// @brief Parse any token.
    /// @return The type of token was parsed.
    Error parse_token(MjTokenKind token_kind) noexcept;


    /// Parse the nest token or group of associated tokens.
    Error parse_token() noexcept;


    /// Parse a type expression.
    ///
    /// A type expression begins with either a type name or a CV-qualifier and is followed by zero
    /// or more type qualifiers.
    Error parse_type_expression() noexcept;
    Error parse_shell_option() noexcept;
    Error parse_shell_token() noexcept;


    /// Parse an identifier. Either a keyword, function, type, constant, module, literal, or variable.
    Error parse_identifier() noexcept;


    /// Parse a numeric literal.
    Error parse_numeric_literal() noexcept;


    /// Parse a unit expression.
    Error parse_unit_expression() noexcept;


    /// Parse an interpolated string literal.
    Error parse_interpolated_string_literal() noexcept;


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
        if (!string.starts_with(_ch)) {
            return Error::FAILURE;
        }

        return Error::SUCCESS;
    }


    Error peek_text(u8 ch) const noexcept {
        if (*_ch != ch) {
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
    bool parse_newline() noexcept;


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
