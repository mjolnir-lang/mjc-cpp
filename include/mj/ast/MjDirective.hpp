#pragma once

#include <mj/ast/MjItem.hpp>


// A definition is a structured unit of code.
class MjDirective : public MjItem {
protected:


    ///
    /// Constructors
    ///


    constexpr
    MjDirective(MjItemKind item_kind, Slice<const MjToken> tokens = nullptr) noexcept : MjItem(item_kind, tokens) {}


    ///
    /// Destructor
    ///


    virtual
    ~MjDirective() = default;
public:


    ///
    /// Properties
    ///


    ///
    /// Methods
    ///


};
