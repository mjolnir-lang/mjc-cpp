#pragma once

#include <mj/ast/MjIntegerType.hpp>


class MjBitfieldType : public MjType {
private:
    MjIntegerType *_base_type;
    u32 _start : 12;
    u32 _end : 12;
protected:


    constexpr
    MjBitfieldType(MjIntegerType *base_type, u32 start, u32 end) noexcept :
        _base_type(base_type),
        _start(start),
        _end(end)
    {}
 

public:


    constexpr
    bool is_unsigned() const noexcept {
        return _base_type->is_unsigned();
    }


    constexpr
    bool is_signed() const noexcept {
        return _base_type->is_signed();
    }


    constexpr
    u32 size() const noexcept {
        return _base_type->size();
    }


    constexpr
    u32 width() const noexcept {
        return _end - _start;
    }


    constexpr
    u32 start() const noexcept {
        return _start;
    }


    constexpr
    u32 end() const noexcept {
        return _end;
    }




    /// @brief Return the size of the type in bytes.
    u32 size() const noexcept {
        return _base_type->alignment();
    }


    /// @brief Return the alignment of the type in bytes.
    u32 alignment() const noexcept {
        return _base_type->alignment();
    }


};
