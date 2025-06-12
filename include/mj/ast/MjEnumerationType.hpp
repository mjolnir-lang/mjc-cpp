#pragma once

#include <mj/ast/MjVariable.hpp>


class MjEnumerationType : public MjType {
private:
    MjType *_index_type;
    MjType *_value_type;
    MjToken _name;
public:


    constexpr
    MjEnumerationType(
        MjToken name,
        MjType *index_type,
        MjType *value_type,
        Slice<const MjToken> tokens = nullptr
    ) :
        MjType(MjItemKind::ENUMERATION_TYPE, tokens),
        _index_type(index_type),
        _value_type(value_type),
        _name(name)
    {}


    ///
    /// Properties
    ///


    constexpr
    const MjType *value_type() const noexcept {
        return _value_type;
    }


    constexpr
    MjType *value_type() noexcept {
        return _value_type;
    }


    constexpr
    const MjType *index_type() const noexcept {
        return _index_type;
    }


    constexpr
    MjType *index_type() noexcept {
        return _index_type;
    }


    constexpr
    Slice<const MjVariable *> &values() const noexcept {
        return _items;
    }


    constexpr
    Slice<MjVariable *> &values() noexcept {
        return _items;
    }


    ///
    /// Methods
    ///


};
