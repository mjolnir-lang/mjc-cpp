#pragma once

#include <core/Enum.hpp>


template<class ByteOrder>
struct ByteOrderValues {
    static constexpr ByteOrder LSB{0};         // Least Significant Byte First
    static constexpr ByteOrder MSB{1};         // Most Significant Byte First
    static constexpr ByteOrder LITTLE{LSB};    // Little Endian (LSB first)
    static constexpr ByteOrder BIG{MSB};       // Big Endian (MSB first)
    static constexpr ByteOrder NATIVE{LITTLE}; // The system byte order
    static constexpr ByteOrder SWAPPED{BIG};   // The inverse of the system byte order
};


class ByteOrder : public Enum<u8>, public ByteOrderValues<ByteOrder> {
public:


    ///
    /// Constructors
    ///


    constexpr
    explicit
    ByteOrder(u8 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    /// @brief The number of days in the month.
    constexpr
    bool is_little() const noexcept {
        return _id == LITTLE;
    }


    /// @brief The number of days in the month.
    constexpr
    bool is_big() const noexcept {
        return _id == BIG;
    }


    /// @brief The number of days in the month.
    constexpr
    bool is_native() const noexcept {
        return _id == NATIVE;
    }
};
