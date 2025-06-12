#pragma once

#include <mj/ast/MjTokenKind.hpp>


struct TextPosition {
    u32 line_index;
    u16 char_offset;
    u16 size;
};


class MjToken {
private:
    const u8 *_ptr;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjToken(const u8 *ptr) noexcept : _ptr(ptr) {}


    ///
    /// Operators
    ///


    constexpr
    explicit
    operator bool() const noexcept {
        return _ptr != nullptr;
    }


    constexpr
    bool operator==(MjToken other) const noexcept {
        return _ptr == other._ptr;
    }


    constexpr
    std::strong_ordering operator<=>(MjToken other) const noexcept {
        return _ptr <=> other._ptr;
    }


    constexpr
    void operator+=(u32 offset) noexcept {
        _ptr += offset;
    }


    constexpr
    void operator++() noexcept {
        ++_ptr;
    }


    ///
    /// Properties
    ///


    constexpr
    const u8 *ptr() const noexcept {
        return _ptr;
    }


    constexpr
    u8 size() const noexcept {
        return kind().encoded_size();
    }


    /// The kind of the token.
    constexpr
    MjTokenKind kind() const noexcept {
        return MjTokenKind(*_ptr);
    }


    /// The string kind of the token.
    constexpr
    u8 string_kind() const noexcept {
        return kind().string_kind();
    }


    constexpr
    u8 indent() const noexcept {
        return _ptr[1];
    }


    constexpr
    u8 spaces() const noexcept {
        return _ptr[1];
    }


    /// The ID of the token.
    constexpr
    u16 string_id() const noexcept {
        return u16(_ptr[1]) | u16(_ptr[2]);
    }


    /// The kind of the token.
    constexpr
    bool has_builtin_text() const noexcept {
        return kind().has_builtin_text();
    }


    /// The kind of the token.
    constexpr
    StringView builtin_text() const noexcept {
        return kind().builtin_text();
    }


    constexpr
    bool has_whitespace(MjToken other) const noexcept {
        return kind().has_whitespace(other.kind());
    }
};



class MjTokenRange {
private:
    MjToken _token;
public:


    constexpr
    MjTokenRange(MjToken token) noexcept : _token(token) {}
};



class MjTokenIterator {
private:
    MjToken _token;
public:


    constexpr
    MjTokenIterator(MjToken token) noexcept : _token(token) {}
};
