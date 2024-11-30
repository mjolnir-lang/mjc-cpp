#pragma once

#include <core/Enum.hpp>


template<class MjTemplateArgumentKind>
struct MjTemplateArgumentKindValues {
    static constexpr MjTemplateArgumentKind UNKNOWN{0};
    static constexpr MjTemplateArgumentKind TYPE{1};
    static constexpr MjTemplateArgumentKind VARIABLE{2};
    static constexpr MjTemplateArgumentKind TEMPLATE{3};
};


/// @brief There are three kinds of template arguments, type, non-type, and template
struct MjTemplateArgumentKind : public Enum<u8>, public MjTemplateArgumentKindValues<MjTemplateArgumentKind> {

    constexpr
    explicit
    MjTemplateArgumentKind(u8 id) noexcept : Enum(id) {}
};
