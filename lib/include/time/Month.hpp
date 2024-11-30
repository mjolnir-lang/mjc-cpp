#pragma once

#include <time/Weekday.hpp>

namespace time {


template<class Month>
struct MonthValues {
    static constexpr Month JANUARY{0};
    static constexpr Month FEBRUARY{1};
    static constexpr Month MARCH{2};
    static constexpr Month APRIL{3};
    static constexpr Month MAY{4};
    static constexpr Month JUNE{5};
    static constexpr Month JULY{6};
    static constexpr Month AUGUST{7};
    static constexpr Month SEPTEMBER{8};
    static constexpr Month OCTOBER{9};
    static constexpr Month NOVEMBER{10};
    static constexpr Month DECEMBER{11};
};


class Month : public Enum<u8>, public MonthValues<Month> {
private:

    static
    constexpr
    StringView NAMES[] {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December",
    };

    static
    constexpr
    const u8 DAYS[] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    static
    constexpr
    const u16 YEAR_DAYS[] {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
public:


    ///
    /// Constructor
    ///


    constexpr
    explicit
    Month(u8 id) noexcept : Enum(id) {}


    /// Return the month corresponding to the given index starting at zero.
    static
    constexpr
    Month from_index(u32 index) noexcept {
        return Month(index - 1);
    }


    ///
    /// Properties
    ///


    /// The full name of the month.
    constexpr
    StringView name() const noexcept {
        return NAMES[_id];
    }


    /// The three letter abbreviated name of the month.
    constexpr
    StringView abbreviation() const noexcept {
        return NAMES[_id].head(3);
    }


    /// The number of days before the start of the month
    constexpr
    u8 days_offset() const noexcept {
        return YEAR_DAYS[_id];
    }


    /// The number of days before the start of the month
    constexpr
    u8 days_offset_on_leap_year() const noexcept {
        return YEAR_DAYS[_id] + u8(_id > Month::FEBRUARY._id);
    }


    /// The number of days in the month on a normal year.
    /// [28, 30, 31]
    constexpr
    u8 days() const noexcept {
        return DAYS[_id];
    }


    /// The number of days in the month on a leap year.
    /// [29, 30, 31]
    constexpr
    u8 days_on_leap_year() const noexcept {
        return DAYS[_id] + u8(_id == Month::FEBRUARY._id);
    }


    /// The index [1, 12]
    constexpr
    u8 index() const noexcept {
        return _id + 1;
    }


    constexpr
    Month next() const noexcept {
        return Month(_id < 11 ? _id + 1 : 0);
    }


    constexpr
    Month previous() const noexcept {
        return Month(_id > 0 ? _id - 1 : 11);
    }


    static
    constexpr
    u32 count() noexcept {
        return 12;
    }


    static
    constexpr
    MonthIterator months() noexcept {
        return MonthIterator();
    }
};


class MonthIterator {
private:
    Month _month;
public:


    ///
    /// Constructors
    ///


    constexpr
    MonthIterator() noexcept : _month(0) {}


    ///
    /// Operators
    ///


    constexpr
    Month operator*() const noexcept {
        return _month;
    }


    constexpr
    const Month *operator->() const noexcept {
        return &_month;
    }


    constexpr
    MonthIterator &operator++() noexcept {
        ++_month;
        return *this;
    }


    constexpr
    MonthIterator operator++(int) noexcept {
        MonthIterator temp = *this;
        ++(*this);
        return temp;
    }


    constexpr
    bool operator==(std::nullptr_t) const noexcept {
        return _month == 12;
    }


    constexpr
    MonthIterator begin() const noexcept {
        return *this;
    }


    constexpr
    std::nullptr_t end() const noexcept {
        return nullptr;
    }
};


void test() {
    for (Month m : Month::months()) {
        m;
    }
}

}
