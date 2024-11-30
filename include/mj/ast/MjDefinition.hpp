#pragma once

#include <mj/ast/MjItem.hpp>
#include <mj/ast/MjAnnotation.hpp>
#include <container/Vector.hpp>


// A definition is a structured unit of code.
class MjDefinition : public MjItem {
protected:
    Vector<MjAnnotation> _annotations;
    MjComment *_comment;
    u32 _flags;


    ///
    /// Constructors
    ///


    constexpr
    MjDefinition(MjItemKind item_kind, Slice<const MjToken> tokens = nullptr) noexcept : MjItem(item_kind, tokens) {}


    ///
    /// Destructor
    ///


    virtual
    ~MjDefinition() = default;
public:


    ///
    /// Properties
    ///


    constexpr
    bool is_internal() const noexcept {
        return false;
    }


    constexpr
    bool is_shared() const noexcept {
        return false;
    }


    constexpr
    bool is_type() const noexcept {
        return false;
    }


    constexpr
    bool is_function() const noexcept {
        return false;
    }


    constexpr
    bool is_class() const noexcept {
        return false;
    }


    constexpr
    bool is_template() const noexcept {
        return false;
    }


    constexpr
    bool is_global() const noexcept {
        return false;
    }


    // The comment associated with the variable
    constexpr
    bool has_comment() const noexcept {
        return _comment != nullptr;
    }


    // The comment associated with the variable
    constexpr
    const MjComment *comment() const noexcept {
        return _comment;
    }


    // The comment associated with the variable
    constexpr
    MjComment *comment() noexcept {
        return _comment;
    }


    ///
    /// Methods
    ///


};
