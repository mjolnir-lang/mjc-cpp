#pragma once

#include <core/Enum.hpp>


template<class MjTemplateParameterKind>
struct MjTemplateParameterKindValues {
    static constexpr MjTemplateParameterKind UNKNOWN{0};
    static constexpr MjTemplateParameterKind TYPE{1};
    static constexpr MjTemplateParameterKind VARIABLE{2};
    static constexpr MjTemplateParameterKind TEMPLATE{3};
};


/// @brief There are three kinds of template arguments, type, non-type, and template
struct MjTemplateParameterKind : public Enum<u8>, public MjTemplateParameterKindValues<MjTemplateParameterKind> {

    constexpr
    explicit
    MjTemplateParameterKind(u8 id) noexcept : Enum(id) {}
};
