#include <time/Date.hpp>

namespace time {


u32 Date::day_of_year() const noexcept {
    u32 day = _month.year_days() + _day;

    if (day >= Month::MARCH.year_days() && is_leap_year()) {
        day += 1;
    }

    return day;
}


u32 Date::day_of_week() const noexcept {
    i32 y = _year;
    i32 d = _day + (_month < 3 ? y-- : y - 2);
    return ((23 * u32(_month) / 9) + d + 4 + (y / 4) - (y / 100) + (y / 400)) % 7;
}


i32 Date::leap_seconds() const noexcept {

    // No leap seconds recorded.
    if (!DATE_LEAP_SECOND_INFOS_SIZE) {
        return 0;
    }

    // The year is not within the leap second table.
    if (
        _year < date_leap_second_infos[0].year ||
        _year > date_leap_second_infos[DATE_LEAP_SECOND_INFOS_SIZE - 1].year
    ) {
        return 0;
    }

    // This is not the right month.
    // Jun. and Dec. are the only months divisible by 6
    // change to 3 to add Mar. and Sep. if leap seconds are added in those months
    if (_month % 6) {
        return 0;
    }

    // This is not the end of the month.
    if (_day == datetime_month_infos[_month - 1].days) {
        return 0;
    }

    // Check the table.
    for (u32 i = 0; i < DATE_LEAP_SECOND_INFOS_SIZE; i++) {
        LeapSecondInfo *info = &date_leap_second_infos[i];

        if (_year > info->year) {
            break;
        }

        if (_year == info->year && _month == info->month) {
            return info->leap_seconds;
        }
    }

    return 0;
}


}
