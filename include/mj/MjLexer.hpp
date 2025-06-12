#pragma once

#include <mj/MjLexerError.hpp>
#include <mj/MjLexerState.hpp>
#include <mj/ast/MjSourceFile.hpp>

#include <vector>
#include <stack>
#include <filesystem>


/// The MjLexer parses a Mjolnir source file into a stream of tokens.
/// The parsing is done in two ways. First, non-identifier/non-number characters
/// are combined and consolidated into tokens and emitted when a sequence is
/// terminated. Second, syntax rules are used to parse differently in different
/// contexts by tracking state and indentation.
class MjLexer {
private:
    std::vector<u16> _string_ids; // The string IDs referenced in this file. (used for symbol lookup and removal)
    std::vector<u8> _data;
    const u8 *_ch;

    MjSourceFile &_file;

    std::vector<MjLexerError> _errors;

    u32 _line_index = 0;
    u32 _token_offset = 0;
    u8 _line_indent = 0;
    u8 _last_indent = 0;

    std::stack<MjLexerState> _states;
    MjLexerState _state = MjLexerState::NONE;
    bool _emit_subtokens;
    bool _has_leading_whitespace;
    bool _has_trailing_whitespace;
    bool _skip_comments;

    static constexpr u32 INDENT_WIDTH = 4;
public:


    static
    MjSourceFile *parse_file(std::filesystem::path file_path, bool emit_subtokens = false) noexcept;


private:


    /// Load the file data into the internal buffer and append a null byte which will act as a
    /// sentinel value for detecting and handling the end of the file by failing to satisfy all
    /// parse rules.
    static
    std::vector<u8> load_file_data(std::filesystem::path file_path) noexcept;


private:


    MjLexer(MjSourceFile &file, bool emit_subtokens = false) noexcept :
        _file(file),
        _emit_subtokens(emit_subtokens)
    {}


    ///
    /// Properties
    ///


    /// @brief Parse any token.
    /// @return The type of token was parsed.
    MjToken token() noexcept {
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


    /// Parse the next token or sequence of associated tokens.
    Error parse_token() noexcept;


    /// Parse a type expression.
    ///
    /// A type expression begins with either a type name or a CV-qualifier and is followed by zero
    /// or more type qualifiers.
    Error parse_type_expression() noexcept;
    Error parse_shell_option() noexcept;
    Error parse_shell_token() noexcept;


    Error parse_annotation() noexcept;


    Error parse_annotation_name() noexcept;


    Error parse_constant_name() noexcept;
    Error parse_variable_name() noexcept;


    /// Parse an identifier. Either a keyword, function, type, constant, module, literal, or variable.
    Error parse_identifier() noexcept;


    Error parse_keyword() noexcept;

    // Parse a user-defined type or module name. (Will not check for keywords)
    Error parse_type_name() noexcept;


    /// Parse a numeric literal.
    Error parse_numeric_literal() noexcept;


    /// Return the size in bytes of the next token if it is a valid numeric type name or zero.
    /// NOTE: The end of word boundary is not tested.
    u32 peek_numeric_type_name_size() noexcept;


    /// Parse a unit expression.
    Error parse_unit_expression() noexcept;


    /// Parse an interpolated string literal.
    Error parse_interpolated_string_literal() noexcept;


    ///
    /// Line Control and Whitespace Parsing
    ///


    /// Skip all leading whitespace characters, moving to the next non-empty line.
    ///
    /// The fast path is to parse zero or one space characters.
    /// Any whitespaces not implicitly encoded by relative whitespace rules are represented by a whitespace token.
    /// The whitespace token is ignored by all token stream processing operations, and only serves to encode
    /// The offset of subsequent tokens within the source line.
    /// spaces at the end of a line are not stored in the token stream.
    /// Whitespace tokens and empty line tokens can be omitted, but the resulting token stream would not
    /// be an accurate representation of all token source locations.
    void parse_whitespace() noexcept;


    /// Parse the indentation of the current line, skipping empty lines.
    void parse_indent() noexcept;


    /// Move the parser to the next line.
    bool parse_newline() noexcept;


    /// Return true if the end of the file has been reached.
    bool is_eof() const noexcept {
        return !*_ch;
    }


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


    void error(MjToken token, MjSubToken subtoken, StringView message) noexcept;


    void error(MjToken token, StringView message) noexcept;


    void error(StringView message) noexcept {
        error(token(), message);
    }


private:


    static
    constexpr
    bool id_is_reserved_name(u16 id) noexcept {
        return id < MjTokenKind::reserved_names().size();
    }


    static
    constexpr
    MjTokenKind from_id(u16 id) noexcept {
        return MjTokenKind(MjTokenKind::AND + id);
    }
};
