#pragma once

#include <mj/ast/MjToken.hpp>
#include <filesystem>
#include <vector>


/// A source file object represented a a sequence of tokens and efficient string data.
class MjFile {
private:
    std::filesystem::path _path;
    std::vector<u8> _data;
    std::vector<u32> _line_offsets;
    std::vector<MjToken> _tokens;
    std::vector<u8> _strings;
    /// The offsets in bytes of each line in the file by index.
    /// An extra entry to allow calculations using the index of the line after the last line.
    u32 _size = 0;
public:


    Error load(std::filesystem::path path) noexcept;


    ///
    /// Properties
    ///


    constexpr
    const std::vector<MjToken> &tokens() const noexcept {
        return _tokens;
    }


    constexpr
    std::vector<MjToken> &tokens() noexcept {
        return _tokens;
    }


    /// Return the file path.
    const std::filesystem::path &file_path() const noexcept {
        return _path;
    }


    const std::vector<u8> &file_data() const noexcept {
        return _data;
    }


    /// Return the size of the file in bytes.
    u32 file_size() const noexcept {
        return _size;
    }


    /// Return the number of lines in the file.
    u32 line_count() const noexcept {
        return _line_offsets.size();
    }


    /// Return the offset in bytes of the line by index.
    u32 line_offset(u32 index) const noexcept {
        return _line_offsets[index];
    }


    /// Return the size in bytes of the line by index.
    u32 line_size(u32 index) const noexcept {
        return _line_offsets[index + 1] - _line_offsets[index] - 1;
    }


    /// Return the offset in bytes of the line by index.
    StringView line(u32 index) const noexcept {
        return StringView(&_data[line_offset(index)], line_size(index));
    }


    /// Return the index of the line associated with the given token.
    u32 line_of(const MjToken &token) const noexcept {
        return token.line;
    }


    /// Return the text associated with the given token.
    StringView text_of(const MjToken &token) const noexcept {
        return StringView(&_strings[token.offset], token.size);
    }


    ///
    /// Methods
    ///


    void append_line(u32 line_offset) noexcept {
        _line_offsets.push_back(line_offset);
    }


    template<class... Args>
    void append_token(Args &&... args) noexcept {
        _tokens.emplace_back(std::forward<Args>(args)...);
    }


    void append_subtoken(MjTokenKind kind, u32 offset, u32 size) noexcept {
        const MjToken &token = _tokens.back();
        _tokens.emplace_back(kind, token.line, token.offset + offset, size);
    }

};
