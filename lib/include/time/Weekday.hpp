#pragma once

#include <core/Enum.hpp>
#include <core/StringView.hpp>

namespace time {


template<class Weekday>
struct WeekdayValues {
    static constexpr Weekday SUNDAY{0};
    static constexpr Weekday MONDAY{1};
    static constexpr Weekday TUESDAY{2};
    static constexpr Weekday WEDNESDAY{3};
    static constexpr Weekday THURSDAY{4};
    static constexpr Weekday FRIDAY{5};
    static constexpr Weekday SATURDAY{6};
};


class Weekday : public Enum<u8>, public WeekdayValues<Weekday> {
private:
    static
    constexpr
    StringView NAMES[] {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
    };
public:


    constexpr
    explicit
    Weekday(u8 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    /// The week index [1, 7]
    u8 week_index() const noexcept {
        return _id + 1;
    }


    /// The full name of the weekday.
    StringView name() const noexcept {
        return NAMES[_id];
    }


    /// The three letter abbreviated name of the weekday.
    StringView abbreviation() const noexcept {
        return NAMES[_id].head(3);
    }
};


}
