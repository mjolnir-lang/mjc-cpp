#pragma once

#include <time/Date.hpp>
#include <time/Time.hpp>

namespace time {


class DateTime {
private:
    u64 seconds;
public:



    constexpr
    DateTime(Date date, Time time) noexcept {}
};


}
