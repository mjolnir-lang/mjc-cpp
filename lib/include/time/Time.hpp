#pragma once

#include <unit/internal/Time.hpp>

namespace core {


void test() {
    unit::u32<unit::second> sec(32);
    unit::u32<unit::minute> min(3);
    unit::u32<unit::millisecond> ms{min + unit::u32<unit::minute>(sec)};
}


class Time {
private:
    u64 _microseconds;
public:



    constexpr
    Time(u64 microseconds) noexcept : _microseconds(microseconds) {}


    constexpr
    Time(u32 hours, u32 minutes, u32 seconds) noexcept {}


    ///
    /// Operators
    ///


    constexpr
    friend
    auto operator<=>(Time lhs, Time rhs) noexcept = default;


    ///
    /// Builders
    ///


    static
    constexpr
    Time from_h(u64 hours) noexcept {
        return Time(hours * 3600000000);
    }


    static
    constexpr
    Time from_m(u64 minutes) noexcept {
        return Time(minutes * 60000000);
    }


    static
    constexpr
    Time from_s(u64 seconds) noexcept {
        return Time(seconds * 1000000);
    }


    static
    constexpr
    Time from_ms(u64 milliseconds) noexcept {
        return Time(milliseconds * 1000);
    }


    static
    constexpr
    Time from_us(u64 microseconds) noexcept {
        return Time(microseconds);
    }


    static
    constexpr
    Time from_hm(u64 hours, u64 minutes) noexcept {
        return Time((hours * 3600000000) + (minutes * 60000000));
    }


    static
    constexpr
    Time from_hms(u64 hours, u64 minutes, u64 seconds) noexcept {
        return Time((hours * 3600000000) + (minutes * 60000000) + (seconds * 1000000));
    }
};


}
