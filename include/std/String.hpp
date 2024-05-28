#pragma once

#include <std/Vector.hpp>
#include <std/StringView.hpp>


class String {
private:
    Vector<u8> _data;
public:


    constexpr
    String() noexcept : _data() {}


    constexpr
    String(std::nullptr_t) noexcept : _data(nullptr) {}


    constexpr
    String(Slice<const u8> other) noexcept : _data(other) {}


    constexpr
    String() noexcept : _data() {}


    constexpr
    String() noexcept : _data() {}


    constexpr
    String() noexcept : _data() {}


    ///
    /// Type Casts
    ///


    constexpr
    operator StringView() const noexcept {
        return Slice<const u8>(_data);
    }
};
