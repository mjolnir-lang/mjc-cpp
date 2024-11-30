#pragma once

#include <core/StringView.hpp>
#include <core/Enum.hpp>


template<class MjLinkerWarning>
struct MjLinkerWarningValues {
    static constexpr MjLinkerWarning AA{0};
};


class MjLinkerWarning : public Enum<u8>, public MjLinkerWarningValues<MjLinkerWarning> {
private:
public:


    constexpr
    explicit
    MjLinkerWarning(u16 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    constexpr
    StringView message() const noexcept {}
};
