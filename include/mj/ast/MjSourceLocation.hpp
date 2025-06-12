#pragma once

#include <mj/ast/MjSourceFile.hpp>
#include <mj/ast/MjTokenSpan.hpp>


class MjSourceLocation {
private:
    const MjSourceFile *_source_file;
    MjTokenSpan _tokens;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjSourceLocation(
        const MjSourceFile *source_file,
        MjTokenSpan tokens
    ) noexcept :
        _source_file(source_file),
        _tokens(tokens)
    {}


    ///
    /// Properties
    ///


    constexpr
    const MjSourceFile *source_file() const noexcept {
        return _source_file;
    }


    constexpr
    MjTokenSpan tokens() const noexcept {
        return _tokens;
    }
};
