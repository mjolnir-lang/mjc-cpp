#pragma once

#include <mj/ast/MjItem.hpp>
#include <mj/ast/MjItemIterator.hpp>

#include <container/Vector.hpp>
#include <core/Where.hpp>


class MjDeclaration : public MjItem {
protected:
    Vector<MjItem *> _items;


    ///
    /// Constructors
    ///


    constexpr
    MjDeclaration(MjItemInfo item_info) noexcept : MjItem(item_info) {}


public:
 	MjDeclaration(MjDeclaration &&) = delete;
 	MjDeclaration(const MjDeclaration &) = delete;


    ///
    /// Operators
    ///


    MjDeclaration &operator=(MjDeclaration &&) = delete;
    MjDeclaration &operator=(const MjDeclaration &) = delete;


    ///
    /// Properties
    ///


    template<IsMjItem T>
    constexpr
    bool has_item() const noexcept {
        for (MjItem *item : _items) {
            if (item->is<T>()) {
                return true;
            }
        }

        return false;
    }


    template<IsMjItem T>
    constexpr
    MjItemIterator<const T> items() const noexcept {
        return _items.data();
    }


    template<IsMjItem T>
    constexpr
    MjItemIterator<T> items() noexcept {
        return _items.data();
    }


    ///
    /// Methods
    ///


    void append(MjItem *item) noexcept {
        _items.push_back(item);
    }
};
