#pragma once

#include <core/Function.hpp>
#include <io/internal/Printer.hpp>


class StringPrinter;


/// @brief A PrintArg object contains a reference to the object to be
/// formatted/printed and the printer function associated with that object's
/// type.
class Printable {
private:
    union Value {
        const void *as_ptr;
        u32 as_u32;
        u64 as_u64;
        i32 as_i32;
        i64 as_i64;
        f32 as_f32;
        f64 as_f64;


        constexpr Value(const void *value) noexcept : as_ptr(value) {}
        constexpr Value(bool value) noexcept : as_u32(value) {}
        constexpr Value(u32 value) noexcept : as_u32(value) {}
        constexpr Value(u64 value) noexcept : as_u64(value) {}
        constexpr Value(i32 value) noexcept : as_i32(value) {}
        constexpr Value(i64 value) noexcept : as_i64(value) {}
        constexpr Value(f32 value) noexcept : as_f32(value) {}
        constexpr Value(f64 value) noexcept : as_f64(value) {}
    } _value;
    Function<Error(StringPrinter &)> _print;
public:


    ///
    /// Constructors
    ///


    template<class T>
    constexpr
    Printable(const T &value) noexcept : _value(value), _print(&Printer<T>::print) {}


    template<class T>
    constexpr
    Printable(const T *value) noexcept : _value(value), _print(&Printer<const void *>::print) {}


    template<u32 SIZE>
    constexpr
    Printable(const char (&value)[SIZE]) noexcept : _value(StringView(value)), _print(&Printer<StringView>::print) {}


    ///
    /// Properties
    ///


    /// @brief Return the format argument value given the expected value of the type.
    /// @tparam T The type of argument.
    template<class T>
    constexpr
    const T &value() const noexcept {
        return *static_cast<const T *>(_value.as_ptr);
    }


    ///
    /// Methods
    ///


    Error print(StringPrinter &stream_printer) const noexcept {
        return _print(stream_printer);
    }
};
