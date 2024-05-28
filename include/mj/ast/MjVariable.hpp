#pragma once

#include <mj/ast/MjObject.hpp>
#include <mj/ast/MjStatement.hpp>
#include <std/Vector.hpp>


/// @brief An `MjVariable` is an `MjObject` associated with an identifier.
class MjVariable {
private:
    Slice<const MjToken> _tokens;
    MjStatement *_definition;
    MjToken *_name;
    MjObject *_object;
    MjType *_type;

    MjComment *_comment;   // The comment associated with the variable
    MjStorage *_storage_;  // The data of the variable
    u64 _address;          // The absolute address of the variable storage
    MjType *_owner;        // The type that owns the member
    u32 _offset;           // offset relative to owner data
    bool _is_mutable_;     // The property does not inherit the 'const'-ness of its owner (does not apply to references)
public:


    constexpr
    MjVariable(Slice<const MjToken> tokens) noexcept : _tokens(tokens) {}


    ///
    /// Properties
    ///


    constexpr
    bool has_comment() const {
        return _definition->has_comment();
    }


    /// The comment associated with the variable
    constexpr
    const MjComment *comment() const noexcept {
        return _definition->comment();
    }


    /// The variable name
    constexpr
    const MjToken *name() const noexcept {
        return _name;
    }


    /// The temporary sequence of tokens that make the definition
    constexpr
    const MjStatement *definition() const noexcept {
        return _definition;
    }


    /// The absolute address of the variable storage
    constexpr
    u64 address() const noexcept {
        return _object->address();
    }


    /// The memory will not be modified
    constexpr
    bool is_literal() const noexcept {
        return false;
    }


    /// The memory may be be modified even when const
    constexpr
    bool is_safe() const noexcept {
        return false;
    }


    /// The variable is a reference (storage is indeterminate)
    constexpr
    bool is_reference() const noexcept {
        return false;
    }


    /// The variable is a reference (storage is not needed)
    constexpr
    bool is_alias() const noexcept {
        return false;
    }


    constexpr
    bool is_deterministic() const noexcept {
        return !_type->is_volatile();
    }


    constexpr
    MjType *type() const noexcept {
        return _type;
    }
};
