#pragma once

#include <mj/ast/MjToken.hpp>
#include <mj/ast/MjItemInfo.hpp>
#include <mj/ast/MjItemKind.hpp>

#include <core/Slice.hpp>
#include <core/Where.hpp>


class MjItem {
protected:
    MjItemInfo _item_info;


    ///
    /// Constructors
    ///


    constexpr
    MjItem(MjItemInfo item_info) noexcept :
        _item_info(item_info)
    {}


    constexpr
    MjItem(MjItemKind item_kind) noexcept :
        _item_info(item_kind)
    {}


public:
 	MjItem(MjItem &&) = delete;
 	MjItem(const MjItem &) = delete;


    ///
    /// Operators
    ///


    MjItem &operator=(MjItem &&) = delete;
    MjItem &operator=(const MjItem &) = delete;


    ///
    /// Properties
    ///


    constexpr
    bool is_valid() const noexcept {
        return _item_info.is_valid();
    }


    constexpr
    MjItemInfo item_info() const noexcept {
        return _item_info;
    }


    constexpr
    MjItemKind item_kind() const noexcept {
        return _item_info.item_kind();
    }


    constexpr
    bool has_tokens() const noexcept {
        return _item_info.has_tokens();
    }


    ///
    /// Type Identity Properties
    ///


    template<class T, class = Where::is_derived_from<MjItem, T>>
    bool is() noexcept {
        return T::is_type_of(this);
    }


    template<class T, class = Where::is_derived_from<MjItem, T>>
    const T *as() const noexcept {
        assert(is<T>() && "Invalid cast!");
        return static_cast<const T *>(this);
    }


    template<class T, class = Where::is_derived_from<MjItem, T>>
    T *as() noexcept {
        assert(is<T>() && "Invalid cast!");
        return static_cast<T *>(this);
    }


    template<class T, class = Where::is_derived_from<MjItem, T>>
    const T *as(const T *other) const noexcept {
        return is<T>() ? static_cast<const T *>(this) : other;
    }


    template<class T, class = Where::is_derived_from<MjItem, T>>
    T *as(T *other) noexcept {
        return is<T>() ? static_cast<T *>(this) : other;
    }


    ///
    /// Derived Properties
    ///


    constexpr
    bool is_basic_type() noexcept {
        return item_kind().is_basic();
    }


    constexpr
    bool is_derived_type() noexcept {
        return item_kind().is_derived();
    }


    constexpr
    bool is_builtin_type() noexcept {
        return item_kind().is_builtin();
    }


    constexpr
    bool is_type_alias() const noexcept {
        return item_kind() == MjItemKind::TYPE_ALIAS;
    }


    constexpr
    bool is_void_type() const noexcept {
        return item_kind() == MjItemKind::VOID_TYPE;
    }


    constexpr
    bool is_array_type() const noexcept {
        return item_kind() == MjItemKind::ARRAY_TYPE;
    }


    constexpr
    bool is_bitfield_type() const noexcept {
        return item_kind() == MjItemKind::BITFIELD_TYPE;
    }


    constexpr
    bool is_class_type() const noexcept {
        return item_kind() == MjItemKind::CLASS_TYPE;
    }


    constexpr
    bool is_enumeration_type() const noexcept {
        return item_kind() == MjItemKind::ENUMERATION_TYPE;
    }


    constexpr
    bool is_structure_type() const noexcept {
        return item_kind() == MjItemKind::STRUCTURE_TYPE;
    }


    constexpr
    bool is_union_type() const noexcept {
        return item_kind() == MjItemKind::UNION_TYPE;
    }


    constexpr
    bool is_interface_type() const noexcept {
        return item_kind() == MjItemKind::INTERFACE_TYPE;
    }


    constexpr
    bool is_slice_type() const noexcept {
        return item_kind() == MjItemKind::SLICE_TYPE;
    }


    constexpr
    bool is_pointer_type() const noexcept {
        return item_kind() == MjItemKind::POINTER_TYPE;
    }


    constexpr
    bool is_method_type() const noexcept {
        return item_kind() == MjItemKind::METHOD_TYPE;
    }


    constexpr
    bool is_function_type() const noexcept {
        return item_kind() == MjItemKind::FUNCTION_TYPE;
    }


    constexpr
    bool is_operator_type() const noexcept {
        return item_kind() == MjItemKind::OPERATOR_TYPE;
    }


    constexpr
    bool is_constructor_type() const noexcept {
        return item_kind() == MjItemKind::CONSTRUCTOR_TYPE;
    }


    constexpr
    bool is_destructor_type() const noexcept {
        return item_kind() == MjItemKind::DESTRUCTOR_TYPE;
    }


    ///
    /// Methods
    ///


    void set_tokens(Slice<const MjToken> tokens) noexcept {
        //_tokens = tokens;
    }


    void set_end_token(const MjToken &token) noexcept {
        //_tokens.set_end(token);
    }
};


template<class T>
concept IsMjItem = std::derived_from<T, MjItem>;
