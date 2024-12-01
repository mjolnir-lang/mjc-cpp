#pragma once

#include <core/StringView.hpp>
#include <core/Enum.hpp>


template<class MjParserError>
struct MjParserErrorValues {
    static constexpr MjParserError AA{0};
};


class MjParserError : public Enum<u8>, public MjParserErrorValues<MjParserError> {
private:
public:


    constexpr
    explicit
    MjParserError(u16 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    constexpr
    StringView message() const noexcept {}
};
