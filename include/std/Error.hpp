#pragma once

#include <std/Enum.hpp>


template<class Error>
struct ErrorValues {
    static constexpr Error SUCCESS{0};
    static constexpr Error FAILURE{1};
};


class Error : public Enum<Error, u32>, public ErrorValues<Error> {
public:


    constexpr
    explicit
    Error(u32 id) noexcept : Enum(id) {}


    constexpr
    bool is_success() const noexcept {
        return _id == 0;
    }


    constexpr
    bool is_failure() const noexcept {
        return _id != 0;
    }
};
