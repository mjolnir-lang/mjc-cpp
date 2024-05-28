#pragma once

#include <c/ast/CObject.hpp>


/// @brief An `CVariable` is an `CObject` associated with an identifier.
class CVariable : public CObject {
public:


    virtual ~CVariable() = default;


    bool has_comment() const {
        return !comment().text().is_empty();
    }


    // The comment associated with the variable
    virtual const CComment &comment() const = 0;


    // The variable name
    virtual const CToken &name() const = 0;


    // The temporary sequence of tokens that make the definition
    virtual const List<const CToken *> &definition() const = 0;


    // The absolute address of the variable storage
    virtual u64 address() const = 0;


    // The memory will not be modified
    virtual bool is_literal() const = 0;


    // The memory may be be modified even when const
    virtual bool is_safe() const = 0;


    // The variable is a reference (storage is indeterminate)
    virtual bool is_reference() const = 0;


    // The variable is a reference (storage is not needed)
    virtual bool is_alias() const = 0;
};
