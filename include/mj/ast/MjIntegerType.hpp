#pragma once

#include <mj/ast/MjType.hpp>


class MjIntegerType : public MjType {
private:
    u32 _is_unsigned : 1;
    u32 _size : 24;
protected:


    constexpr
    MjIntegerType(bool is_unsigned, u32 size) noexcept :
        _is_unsigned(is_unsigned),
        _size(size)
    {}
 

public:


    constexpr
    bool is_unsigned() const noexcept {
        return _is_unsigned;
    }


    constexpr
    bool is_signed() const noexcept {
        return !_is_unsigned;
    }


    constexpr
    u32 size() const noexcept {
        return _size;
    }
};
