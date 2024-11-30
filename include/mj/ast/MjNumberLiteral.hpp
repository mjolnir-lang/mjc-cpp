#pragma once

#include <mj/ast/MjExpression.hpp>

#include <type_traits>


class MjNumberLiteral : public MjExpression {
private:
    MjType *_type;
    union {
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
    } _value;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjNumberLiteral(Slice<const MjToken> tokens) noexcept : MjExpression(tokens) {}


    ///
    /// Properties
    ///


    constexpr
    MjType *result_type() const noexcept final {
        return _type;
    }


    constexpr
    MjType *type() noexcept {
        return _type;
    }


    template<class T>
    constexpr
    T value() const noexcept {
        if constexpr (std::is_same_v<T, u8>) {
            return _value.as_u8;
        } else if constexpr (std::is_same_v<T, u16>) {
            return _value.as_u16;
        } else if constexpr (std::is_same_v<T, u32>) {
            return _value.as_u32;
        } else if constexpr (std::is_same_v<T, u64>) {
            return _value.as_u64;
        } else if constexpr (std::is_same_v<T, i8>) {
            return _value.as_i8;
        } else if constexpr (std::is_same_v<T, i16>) {
            return _value.as_i16;
        } else if constexpr (std::is_same_v<T, i32>) {
            return _value.as_i32;
        } else if constexpr (std::is_same_v<T, i64>) {
            return _value.as_i64;
        } else if constexpr (std::is_same_v<T, f32>) {
            return _value.as_f32;
        } else if constexpr (std::is_same_v<T, f64>) {
            return _value.as_f64;
        } else {
            static_assert(false, "Invalid type!");
        }
    }
};
