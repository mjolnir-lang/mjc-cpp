#pragma once

#include <mj/ast/MjItem.hpp>


template<IsMjItem T>
class MjItemIterator {
private:
    MjItem **_item;
public:


    constexpr
    MjItemIterator(MjItem **item) noexcept : _item(item) {
        next();
    }


    bool operator!=(std::nullptr_t) const noexcept {
        return _item != nullptr;
    }


    T &operator*() const noexcept {
        return *_item->as<T>();
    }


    MjItemIterator<T> &operator++() noexcept {
        ++_item;
        next();
        return *this;
    }
private:


    void next() noexcept {
        while (*_item != nullptr && !(*_item)->is<T>()) {
            ++_item;
        }
    }
};


template<IsMjItem T>
class MjItemIterator<const T> {
private:
    const MjItem **_item;
public:


    constexpr
    MjItemIterator(const MjItem **item) noexcept : _item(item) {
        next();
    }


    bool operator!=(std::nullptr_t) const noexcept {
        return _item != nullptr;
    }


    const T &operator*() const noexcept {
        return *_item->as<T>();
    }


    MjItemIterator<const T> &operator++() noexcept {
        ++_item;
        next();
        return *this;
    }
private:


    void next() noexcept {
        while (*_item != nullptr && !(*_item)->is<T>()) {
            ++_item;
        }
    }
};
