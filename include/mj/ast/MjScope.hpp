#pragma once

#include "mj/ast/MjType.hpp"

#include "std/List.hpp"


// There are several types of scopes:
// class/struct/union/variant/enum/interface definition
// struct/union/variant initialization
// function/method
// shared
// implementation
// statement
class MjScope {
public:


    MjScope(
        MjScope *parent = nullptr
    ) :
        parent(parent)
    {}


    // basic type lookup, then derived type walking
    MjBasicType *get_type(const MjToken &name) {
        MjBasicType *type = types[name];

        if (type) {
            return type;
        }

        if (parent) {
            return parent->get_type(name);
        }

        return nullptr;
    }


    MjVariable *get_member(const MjToken &name) {
        MjVariable *member = properties[name];

        if (member) {
            return member;
        }

        member = methods[name];

        if (member) {
            return member;
        }

        if (parent) {
            return parent->get_member(name);
        }

        return nullptr;
    }


    MjModule *get_module(const MjToken &name) {
        MjModule *mod = modules[name];

        if (mod) {
            return mod;
        }

        if (parent) {
            return parent->get_module(name);
        }

        return nullptr;
    }
};
