#pragma once

#include "mj/ast/MjObject.hpp"


/// @brief An `MjVariable` is an `MjObject` associated with an identifier.
class MjVariable : public MjObject {
public:


    virtual ~MjVariable() = default;


    bool has_comment() const {
        return !comment().text().is_empty();
    }


    // The comment associated with the variable
    virtual const MjComment &comment() const = 0;


    // The variable name
    virtual const MjToken &name() const = 0;


    // The temporary sequence of tokens that make the definition
    virtual const List<const MjToken *> &definition() const = 0;


    // The absolute address of the variable storage
    virtual u64 address() const = 0;


    // The memory will not be modified
    virtual bool is_literal() const = 0;


    // The memory may be be modified even when const
    virtual bool is_safe() const = 0;


    // The variable is a reference (storage is indeterminant)
    virtual bool is_reference() const = 0;


    // The variable is a reference (storage is not needed)
    virtual bool is_alias() const = 0;
};
