#pragma once

#include "mj/ast/MjScope.hpp"


// There are several types of scopes:
// class/struct/union/variant/enum/interface definition
// struct/union/variant initialization
// function/method
// shared
// implementation
// statement
class MjClassScope : public MjScope {
private:
    MjScope *parent;             // The parent scope
    List<MjScope *> siblings;      // The sibling scopes which provide local symbol resolution for extrnal scopes (watch out for cycles!!!)
    List<MjBasicType *> types;     // Defined types
    List<MjTemplate *> templates;  // Defined templates (generic types)
    List<MjProperty *> properties; // The properties (member variables)
    List<MjMethod *> methods;      // The methods (member functions)
    List<MjModule *> modules;      // Used to keep track of which modules have been imported
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
