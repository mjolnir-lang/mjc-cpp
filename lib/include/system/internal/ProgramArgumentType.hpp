#pragma once

#include <core/Enum.hpp>


template<class ProgramArgumentType>
struct ProgramArgumentTypeValues {
    static constexpr ProgramArgumentType STR{0};  // StringView
    static constexpr ProgramArgumentType ENUM{1}; // Slice<StringView> (nullptr terminated list, default is always first element)
    static constexpr ProgramArgumentType FUNC{2}; // Function<void *(StringView)>
    static constexpr ProgramArgumentType SIZE{3}; // size_t
    static constexpr ProgramArgumentType BOOL{4}; // bool
    static constexpr ProgramArgumentType U8{5};   // u8
    static constexpr ProgramArgumentType U16{6};  // u16
    static constexpr ProgramArgumentType U32{7};  // u32
    static constexpr ProgramArgumentType U64{8};  // u64
    static constexpr ProgramArgumentType I8{9};   // i8
    static constexpr ProgramArgumentType I16{10}; // i16
    static constexpr ProgramArgumentType I32{11}; // i32
    static constexpr ProgramArgumentType I64{12}; // i64
    static constexpr ProgramArgumentType F32{13}; // f32
    static constexpr ProgramArgumentType F64{14}; // f64
    static constexpr ProgramArgumentType SLICE{1 << 6}; // Slice<T>
    static constexpr ProgramArgumentType VECTOR{1 << 7}; // Vector<T>
};


/// @brief The argument type.
struct ProgramArgumentType : public Enum<u8>, public ProgramArgumentTypeValues<ProgramArgumentType> {


    ///
    /// Constructors
    ///


    constexpr
    explicit
    ProgramArgumentType(u8 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    /// Return the element type of the vector or slice or itself if not a list type.
    constexpr
    ProgramArgumentType element_type() const noexcept {
        return ProgramArgumentType(_id & 0x3Fu);
    }


    /// Return true if the argument is a list (slice or vector).
    constexpr
    bool is_list() const noexcept {
        return _id & (VECTOR | SLICE);
    }


    /// Return true if the argument is a slice.
    constexpr
    bool is_slice() const noexcept {
        return _id & SLICE;
    }


    /// Return true if the argument is a vector.
    constexpr
    bool is_vector() const noexcept {
        return _id & VECTOR;
    }
};
