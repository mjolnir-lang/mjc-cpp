#pragma once

#include <unit/Quantity.hpp>
#include <unit/SiPrefix.hpp>

namespace unit {


using second = BaseUnit<dimension::Time>;

using millisecond = milli<second>;
using microsecond = micro<second>;
using nanosecond = nano<second>;
using picosecond = pico<second>;
using femtosecond = femto<second>;

using minute = Unit<60, 1, second>;
using hour = Unit<60, 1, minute>;
using day = Unit<24, 1, hour>;
using week = Unit<7, 1, day>;

using common_year = Unit<365, 1, day>;
using leap_year = Unit<366, 1, day>;
using mean_year = Unit<146097, 400, day>;

using year = common_year;



}
