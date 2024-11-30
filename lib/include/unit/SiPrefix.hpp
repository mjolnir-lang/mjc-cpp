#pragma once

#include <unit/Unit.hpp>

namespace unit {


/// (x10^-1)
template<class U>
using deci = Unit<1, 10, U>;

/// (x10^-2)
template<class U>
using centi = Unit<1, 100, U>;

/// (x10^-3)
template<class U>
using milli = Unit<1, 1000, U>;

/// (x10^-6)
template<class U>
using micro = Unit<1, 1000, milli<U>>;

/// (x10^-9)
template<class U>
using nano = Unit<1, 1000, micro<U>>;

/// (x10^-12)
template<class U>
using pico = Unit<1, 1000, nano<U>>;

/// (x10^-15)
template<class U>
using femto = Unit<1, 1000, pico<U>>;

/// (x10^-18)
template<class U>
using atto = Unit<1, 1000, femto<U>>;

/// (x10^-21)
template<class U>
using zepto = Unit<1, 1000, atto<U>>;

/// (x10^-24)
template<class U>
using yocto = Unit<1, 1000, zepto<U>>;

/// (x10^-27)
template<class U>
using ronto = Unit<1, 1000, yocto<U>>;

/// (x10^-30)
template<class U>
using quecto = Unit<1, 1000, ronto<U>>;



/// (x10^1)
template<class U>
using deca = Unit<10, 1, U>;

/// (x10^2)
template<class U>
using hecto = Unit<100, 1, U>;

/// (x10^3)
template<class U>
using kilo = Unit<1000, 1, U>;

/// (x10^6)
template<class U>
using mega = Unit<1000000, 1, U>;

/// (x10^9)
template<class U>
using giga = Unit<1000000000, 1, U>;

/// (x10^12)
template<class U>
using tera = Unit<1000000000000, 1, U>;

/// (x10^15)
template<class U>
using peta = Unit<1000000000000000, 1, U>;

/// (x10^18)
template<class U>
using exa = Unit<1000000000000000000, 1, U>;

/*
/// (x10^21)
template<class U>
using zetta = Unit<1000000000000000000000, 1, U>;

/// (x10^24)
template<class U>
using yotta = Unit<100000000000000000000000, 1, U>;

/// (x10^27)
template<class U>
using ronna = Unit<1000000000000000000000000000, 1, U>;

/// (x10^30)
template<class U>
using quetta = Unit<1000000000000000000000000000000, 1, U>;
*/

}
