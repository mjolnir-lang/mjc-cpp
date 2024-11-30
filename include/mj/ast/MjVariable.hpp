#pragma once

#include <mj/ast/MjVariableDefinition.hpp>
#include <mj/ast/MjObject.hpp>


/// @brief An `MjVariable` is an `MjObject` associated with an identifier.
class MjVariable {
private:
    MjVariableDefinition *_definition;
    MjObject *_object;
    MjType *_owner;        // The type that owns the member
    bool _is_mutable;     // The property does not inherit the 'const'-ness of its owner (does not apply to references)
public:


    constexpr
    MjVariable(MjVariableDefinition *definition) noexcept : _definition(definition) {}


    ///
    /// Properties
    ///


    /// The variable is a reference (storage is not needed)
    constexpr
    bool is_alias() const noexcept {
        return false;
    }


    constexpr
    bool is_deterministic() const noexcept {
        return !type()->is_volatile();
    }


    constexpr
    bool has_comment() const {
        return _definition->has_comment();
    }


    /// The comment associated with the variable
    constexpr
    const MjComment *comment() const noexcept {
        return _definition->comment();
    }


    /// The comment associated with the variable
    constexpr
    MjComment *comment() noexcept {
        return _definition->comment();
    }


    /// The variable name
    constexpr
    const MjToken *name() const noexcept {
        return _definition->name();
    }


    constexpr
    const MjType *type() const noexcept {
        return _definition->type();
    }


    constexpr
    MjType *type() noexcept {
        return _definition->type();
    }


    /// The temporary sequence of tokens that make the definition
    constexpr
    const MjVariableDefinition *definition() const noexcept {
        return _definition;
    }


    /// The absolute address of the variable storage
    constexpr
    u64 address() const noexcept {
        return _object->address();
    }


    /// The absolute address of the variable storage
    constexpr
    u64 offset() const noexcept {
        return _object->offset();
    }


    /// The absolute address of the variable storage
    constexpr
    u64 size() const noexcept {
        return _object->size();
    }


    ///
    /// Methods
    ///

};
