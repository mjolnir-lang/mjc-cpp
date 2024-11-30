#pragma once

#include <core/Enum.hpp>


template<class Error>
struct ErrorValues {
    static constexpr Error SUCCESS{0};
    static constexpr Error FAILURE{1};
    static constexpr Error TIMEOUT{2};
    static constexpr Error RETRY{3};
    static constexpr Error INVALID{4};
    static constexpr Error UNKNOWN{5};
    static constexpr Error EXHAUST{6};
    static constexpr Error ILLEGAL{7};
    static constexpr Error UNSUPPORTED{8};
};


class Error : public Enum<u32>, public ErrorValues<Error> {
public:


    ///
    /// Constructors
    ///


    constexpr
    explicit
    Error(u32 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    /// @brief Return true if the error is SUCCESS.
    constexpr
    bool is_success() const noexcept {
        return _id == 0;
    }


    /// @brief Return true if the error is not SUCCESS.
    constexpr
    bool is_failure() const noexcept {
        return !is_success();
    }
};
