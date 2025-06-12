#pragma once

#include <mj/ast/MjItemKind.hpp>


class MjItemInfo {
private:
    u64 _data;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjItemInfo(u64 data) noexcept : _data(data) {}


    constexpr
    MjItemInfo(MjItemKind item_kind) noexcept : _data(item_kind << 56) {}


    ///
    /// Operators
    ///


    constexpr
    bool operator==(MjItemInfo other) const noexcept {
        return _data == other._data;
    }


    ///
    /// Properties
    ///


    constexpr
    bool is_valid() const noexcept {
        return _data != 0;
    }


    constexpr
    u64 data() const noexcept {
        return _data;
    }


    constexpr
    MjItemKind item_kind() const noexcept {
        return MjItemKind(_data >> 56);
    }


    constexpr
    bool has_tokens() const noexcept {
        return _data << 8;
    }


    ///
    /// Methods
    ///


    constexpr
    void set_data(u64 data) noexcept {
        _data = data;
    }


    constexpr
    void set_item_kind(MjItemKind item_kind) noexcept {
        _data = (_data & (0xFF << 56)) | (item_kind << 56);
    }
};
