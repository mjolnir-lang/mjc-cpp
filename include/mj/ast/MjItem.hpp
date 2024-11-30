#pragma once

#include <mj/ast/MjToken.hpp>
#include <mj/ast/MjItemKind.hpp>


class MjItem {
protected:
    Vector<MjItem *> _items;
    MjItem *_parent;
    const MjToken *_tokens_data;
    u32 _tokens_size;
    MjItemKind _item_kind;


    ///
    /// Constructors
    ///


    constexpr
    MjItem(MjItemKind item_kind, Slice<const MjToken> tokens = nullptr) noexcept :
        _tokens_data(tokens.data()),
        _tokens_size(tokens.size()),
        _item_kind(item_kind)
    {}


public:
 	MjItem(MjItem &&) = delete;
 	MjItem(const MjItem &) = delete;
    MjItem &operator=(MjItem &&) = delete;
    MjItem &operator=(const MjItem &) = delete;


    ///
    /// Operators
    ///


    ///
    /// Properties
    ///


    constexpr
    MjItemKind item_kind() const noexcept {
        return _item_kind;
    }


    constexpr
    bool has_tokens() const noexcept {
        return _tokens_size > 0;
    }


    /// Return the statement tokens.
    constexpr
    Slice<const MjToken> tokens() const noexcept {
        return {_tokens_data, _tokens_size};
    }


    template<class T, class = Where::is_derived_from<MjItem, T>>
    bool is() noexcept {
        return _item_kind == T::item_kind();
    }


    template<class T, class = Where::is_derived_from<MjItem, T>>
    const T *as() noexcept {
        assert(is<T>() && "Invalid cast!");
        return static_cast<T *>(this);
    }


    template<class T, class = Where::is_derived_from<MjItem, T>>
    T *as() noexcept {
        assert(is<T>() && "Invalid cast!");
        return static_cast<T *>(this);
    }


    template<class T, class = Where::is_derived_from<MjItem, T>>
    const T *as(const T *other) noexcept {
        return is<T>() ? static_cast<T *>(this) : other;
    }


    template<class T, class = Where::is_derived_from<MjItem, T>>
    T *as(T *other) noexcept {
        return is<T>() ? static_cast<T *>(this) : other;
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


template<IsMjItem T>
class MjItemIterator {
private:
    MjItem *_item;
public:


    constexpr
    MjItemIterator(MjItem *item) noexcept : _item(item) {
        next();
    }


    bool operator!=(std::nullptr_t) const noexcept {
        return _item != nullptr;
    }


    T &operator*() const noexcept {
        return *_item->as<T>();
    }


    MjItemIterator &operator++() noexcept {
        ++_item;
        next();
        return *this;
    }
private:


    void next() noexcept {
        while (_item != nullptr && !_item->is<T>()) {
            ++_item;
        }
    }
};
