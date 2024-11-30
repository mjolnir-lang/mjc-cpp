#pragma once

#include <core/StringView.hpp>
#include <core/Enum.hpp>


template<class MjCompilerWarning>
struct MjCompilerWarningValues {
    static constexpr MjCompilerWarning AA{0};
};


class MjCompilerWarning : public Enum<u8>, public MjCompilerWarningValues<MjCompilerWarning> {
private:
public:


    constexpr
    explicit
    MjCompilerWarning(u16 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    constexpr
    StringView message() const noexcept {}
};
