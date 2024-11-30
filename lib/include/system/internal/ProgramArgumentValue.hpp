#pragma once

#include <core/StringView.hpp>


/// @brief The argument value.
class ProgramArgumentValue {
private:
    union Value {
        StringView as_str;
        size_t as_size;
        bool as_bool;
        u8 as_u8;
        u16 as_u16;
        u32 as_u32;
        u64 as_u64;
        i8 as_i8;
        i16 as_i16;
        i32 as_i32;
        i64 as_i64;
        f32 as_f32;
        f64 as_f64;


        constexpr Value(const Value &other) noexcept = default;
        constexpr Value() noexcept : as_str(nullptr) {}
        constexpr Value(std::nullptr_t) noexcept : as_str(nullptr) {}
        constexpr Value(StringView value) noexcept : as_str(value) {}
        constexpr Value(size_t value) noexcept : as_size(value) {}
        constexpr Value(bool value) noexcept : as_bool(value) {}
        constexpr Value(u8 value) noexcept : as_u8(value) {}
        constexpr Value(u16 value) noexcept : as_u16(value) {}
        constexpr Value(u32 value) noexcept : as_u32(value) {}
        constexpr Value(u64 value) noexcept : as_u64(value) {}
        constexpr Value(i8 value) noexcept : as_i8(value) {}
        constexpr Value(i16 value) noexcept : as_i16(value) {}
        constexpr Value(i32 value) noexcept : as_i32(value) {}
        constexpr Value(i64 value) noexcept : as_i64(value) {}
        constexpr Value(f32 value) noexcept : as_f32(value) {}
        constexpr Value(f64 value) noexcept : as_f64(value) {}
    } _value;
public:


    ///
    /// Constructors
    ///


    template<class T>
    constexpr
    ProgramArgumentValue(T value, bool is_list = false) noexcept : _value(value) {}


    ///
    /// Properties
    ///


    template<class T>
    constexpr
    T value() const noexcept {
        if constexpr (std::is_same_v<T, StringView>) {
            return as_str;
        } else if constexpr (std::is_same_v<T, size_t>) {
            return as_size;
        } else if constexpr (std::is_same_v<T, bool>) {
            return as_bool;
        } else if constexpr (std::is_same_v<T, u8>) {
            return as_u8;
        } else if constexpr (std::is_same_v<T, u16>) {
            return as_u16;
        } else if constexpr (std::is_same_v<T, u32>) {
            return as_u32;
        } else if constexpr (std::is_same_v<T, u64>) {
            return as_u64;
        } else if constexpr (std::is_same_v<T, i8>) {
            return as_i8;
        } else if constexpr (std::is_same_v<T, i16>) {
            return as_i16;
        } else if constexpr (std::is_same_v<T, i32>) {
            return as_i32;
        } else if constexpr (std::is_same_v<T, i64>) {
            return as_i64;
        } else if constexpr (std::is_same_v<T, f32>) {
            return as_f32;
        } else if constexpr (std::is_same_v<T, f64>) {
            return as_f64;
        } else {
            static_assert(false, "Invalid argument type!");
        }
    }
};
