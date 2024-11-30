#pragma once

#include <unit/Dimension.hpp>

#include <ratio>

namespace unit {


template<class D>
struct BaseUnit {
    using Dimension = D;

    template<class U2>
    using Per = std::conditional_t<std::is_same_v<U2, BaseUnit<D>>, std::ratio<1>, std::ratio_divide<std::ratio<1>, typename U2::template Per<BaseUnit<D>>>>;
};


template<u64 A, u64 B, class U>
struct Unit {
    using Dimension = typename U::Dimension;

    //template<class U2>
    //using Per = std::conditional_t<std::is_same_v<U2, Unit<A, B, U>>, std::ratio<1>, std::ratio_multiply<std::ratio<A, B>, typename U::template Per<U2>>>;

    template<class U2, class = Where::is_same<U2, Unit<A, B, U>>>
    using Per = std::ratio_multiply<std::ratio<A, B>, typename U::template Per<U2>>;

};

template<class U2, class = Where::is_same<U2, Unit<A, B, U>>>
using Per<> = std::ratio<1>;

}
