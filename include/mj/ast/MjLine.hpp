#pragma once

#include <mj/ast/MjToken.hpp>
#include <string>


class MjLine {
private:
    const MjToken _indent_token;
public:


    ///
    /// Properties
    ///


    constexpr
    MjTokenIterator tokens() const noexcept {
        return _indent_token;
    }


    /// Return the size of the line in bytes.
    u32 line_size() const noexcept {
        return size;
    }


    /// Return the text associated with the given token.
    std::string text() const noexcept {
        std::string text;

        for (const u8 token : _tokens) {
            text.push_back(token);
        }

        return text;
    }


    constexpr
    MjTokenIterator begin() const noexcept {
        return _indent_token;
    }


    constexpr
    MjTokenIterator end() const noexcept {
        return nullptr;
    }
};
