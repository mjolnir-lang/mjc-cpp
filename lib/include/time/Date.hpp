#pragma once

#include <time/Month.hpp>

namespace time {


class Date {
private:
    u16 _year;
    Month _month;
    u8 _day;
public:


    constexpr
    Date(u32 year, Month month, u32 day) noexcept : _year(year), _month(month), _day(day) {}


    constexpr
    Date(u32 year, u32 month, u32 day) noexcept : _year(year), _month(Month::from_year_index(month)), _day(day) {}


    ///
    /// Operators
    ///


    constexpr
    friend
    auto operator<=>(Date lhs, Date rhs) noexcept = default;


    ///
    /// Properties
    ///


    bool is_bc() const noexcept {
        return _year <= 0;
    }


    bool is_leap_year() const noexcept {
        return (!(_year % 4) && _year % 100) || !(_year % 400);
    }


    bool is_leap_day() const noexcept {
        return _day == 29 && _month == Month::FEBRUARY;
    }


    i32 leap_seconds() const noexcept;


    bool has_leap_seconds() const noexcept {
        return leap_seconds();
    }


    u32 year() const noexcept {
        return is_bc() ? -(_year + 1) : _year;
    }


    u32 month() const noexcept {
        return _month;
    }


    u32 day() const noexcept {
        return _day;
    }


    Weekday weekday() const noexcept;


    u32 day_of_year() const noexcept;


    u32 day_of_week() const noexcept;
};


}
