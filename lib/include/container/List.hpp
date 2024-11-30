#pragma once

#include <core/Common.hpp>

#include <list>


template<class T>
using List = std::list<T>;

/*
template<class T>
class List {

    template<class T>
    class Node {
        T value;
        Node<T> *ptr;


        constexpr
        Node<T> *prev(Node<T> *next) noexcept {
            return ptr ^ next;
        }

        constexpr
        Node<T> *next(Node<T> *prev) noexcept {
            return ptr ^ prev;
        }
    }
};
*/
