#pragma once

#include <algorithm>
#include <cfloat>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <limits>
#include <utility>


using u8 = char;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using f32 = float;
using f64 = double;


constexpr u8 U8_MAX = std::numeric_limits<u8>::max();
constexpr u16 U16_MAX = std::numeric_limits<u16>::max();
constexpr u32 U32_MAX = std::numeric_limits<u32>::max();
constexpr u64 U64_MAX = std::numeric_limits<u64>::max();

constexpr i8 I8_MAX = std::numeric_limits<i8>::max();
constexpr i16 I16_MAX = std::numeric_limits<i16>::max();
constexpr i32 I32_MAX = std::numeric_limits<i32>::max();
constexpr i64 I64_MAX = std::numeric_limits<i64>::max();

constexpr i8 I8_MIN = std::numeric_limits<i8>::min();
constexpr i16 I16_MIN = std::numeric_limits<i16>::min();
constexpr i32 I32_MIN = std::numeric_limits<i32>::min();
constexpr i64 I64_MIN = std::numeric_limits<i64>::min();
