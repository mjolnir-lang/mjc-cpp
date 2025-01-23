#pragma once

#include <mj/ast/MjToken.hpp>
#include <mj/MjStringSet.hpp>

#include <filesystem>
#include <algorithm>


/// A source file object represented as a sequence of tokens and efficient string data.
/// Token ranges within the file can be accessed independently and errors and warnings emitted
/// during the lexer phase are recorded.
class MjFile {
private:
    const std::filesystem::path _path;
    MjStringSet _strings;

    // The string IDs referenced in this file. (used for symbol lookup and removal)
    std::vector<u16> string_ids;

    // The offsets of each indent token in the token stream.
    std::vector<u8> _tokens;

    /// The offsets in bytes of each line in the file by index.
    /// An extra entry to allow calculations using the index of the line after the last line.
    std::vector<u16> _line_offsets;

    // The size of the file in bytes.
    const u32 _size = 0;
public:


    ///
    /// Constructors
    ///


    MjFile(std::filesystem::path path, u32 size = 0) noexcept : _path(path), _size(size) {}


    ///
    /// Factory
    ///


    Error load(std::filesystem::path path) noexcept;


    /// Encode this object into a tokenized file.
    Error encode(std::filesystem::path file_path) noexcept;


    /// Decode a tokenized file.
    static
    Result<MjFile> decode(std::filesystem::path file_path) noexcept;


    ///
    /// Properties
    ///


    constexpr
    const std::vector<u8> &tokens() const noexcept {
        return _tokens;
    }


    constexpr
    std::vector<u8> &tokens() noexcept {
        return _tokens;
    }


    /// The file path.
    const std::filesystem::path &path() const noexcept {
        return _path;
    }


    /// The size of the file in bytes.
    constexpr
    u32 size() const noexcept {
        return _size;
    }


    /// The number of lines in the file.
    constexpr
    u32 line_count() const noexcept {
        return _line_offsets.size();
    }


    /// The offset of the line in bytes by index.
    constexpr
    u16 line_offset(u16 index) const noexcept {
        return _line_offsets[index];
    }


    /// The offset of the line in bytes by index.
    constexpr
    u16 line_offset(MjToken token) const noexcept {
        return *std::upper_bound(_line_offsets.begin(), _line_offsets.end(), u16(token.ptr() - _tokens.data()));
    }


    /// The token at the start the line at the given index.
    constexpr
    MjToken line(u16 index) const noexcept {
        return &_tokens[line_offset(index)];
    }


    /// The token at the start the line containing the given token.
    constexpr
    MjToken line(MjToken token) const noexcept {
        return &_tokens[line_offset(token)];
    }


    /// The size in bytes of the line by index.
    constexpr
    u32 line_size(u16 index) const noexcept {
        return _line_offsets[index + 1] - _line_offsets[index] - 1;
    }


    /// Return the text associated with the given token.
    constexpr
    StringView text_of(MjToken token) const noexcept {
        if (token.has_builtin_text()) {
            return token.builtin_text();
        }

        return _strings[token.string_id()];
    }


    ///
    /// Methods
    ///


    u32 append_string_token(MjTokenKind token_kind, StringView token_text) noexcept {
        u32 token_index = _tokens.size();
        u16 id = _strings.insert(token_text);
        _tokens.insert(_tokens.end(), {token_kind, u8(id & 0xFFu), u8(id >> 8)});
        return token_index;
    }


    u32 append_inline_token(MjTokenKind token_kind, StringView token_text) noexcept {
        u32 token_index = _tokens.size();
        _tokens.insert(_tokens.end(), {token_kind, u8(token_text.size() & 0xFFu), u8(token_text.size() >> 8)});
        _tokens.insert(_tokens.end(), token_text.begin(), token_text.end());
        return token_index;
    }


    u32 append_indent_token(u8 indent_width) noexcept {
        u32 token_index = _tokens.size();
        _tokens.insert(_tokens.end(), {MjTokenKind::INDENT, indent_width});
        _line_offsets.push_back(token_index);
        return token_index;
    }


    u32 append_whitespace_token(u8 spaces) noexcept {
        u32 token_index = _tokens.size();
        _tokens.insert(_tokens.end(), {MjTokenKind::WHITESPACE, spaces});
        return token_index;
    }


    u32 append_token(MjTokenKind token_kind) noexcept {
        u32 token_index = _tokens.size();
        _tokens.push_back(token_kind);
        return token_index;
    }


    u32 append_subtoken(MjTokenKind token_kind, u8 char_offset, u8 token_size) noexcept {
        u32 token_index = _tokens.size();
        _tokens.insert(_tokens.end(), {token_kind, char_offset, token_size});
        return token_index;
    }


    ///
    /// Type Names
    ///


    StringView string(u16 id) const noexcept {
        return _strings[id];
    }


    bool has_string_id(u16 id) const noexcept {
        return _strings.has_string_id(id);
    }


    bool has_string(StringView string) const noexcept {
        return _strings.has_string(string);
    }


    u16 string_id(StringView string) const noexcept {
        return _strings.id_of(string);
    }
};
