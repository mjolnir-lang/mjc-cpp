#pragma once

#include <core/StringView.hpp>
#include <core/Enum.hpp>


template<class MjLinkerError>
struct MjLinkerErrorValues {
    static constexpr MjLinkerError AA{0};
};


class MjLinkerError : public Enum<u8>, public MjLinkerErrorValues<MjLinkerError> {
private:
public:


    constexpr
    explicit
    MjLinkerError(u16 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    constexpr
    StringView message() const noexcept {}
};
