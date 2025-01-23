#pragma once

#include <mj/ast/MjFile.hpp>


// The parser consumes the output of the scanner and emits the AST components while controlling the parsing context.
class MjFileIterator {
private:
    const MjFile &_file;
    const u8 *_next;
    MjToken _token;
public:


    constexpr
    MjFileIterator(const MjFile &file) noexcept : _file(file), _next(file.tokens().data()) {}


    ///
    /// Properties
    ///


    bool is_empty() const noexcept {
        return _next == nullptr;
    }


    bool has_next() const noexcept {
        return _token._token_kind != MjTokenKind::NONE;
    }


    const MjToken &next(u32 count) noexcept {
        if (!has_next()) {
            return _token;
        }

        _next += _token.size();
        _token._token_kind = *_next;
        return _token;
    }


    const MjToken &next(u32 count) noexcept {
        return _token;
    }
};
