#pragma once

#include <mj/ast/MjItem.hpp>


// A statement is a structured unit of execution.
class MjStatement : public MjItem {
protected:
    bool _is_deterministic;


    ///
    /// Constructors
    ///


    constexpr
    MjStatement(MjItemKind item_kind, Slice<const MjToken> tokens = nullptr) noexcept : MjItem(item_kind, tokens) {}


    ///
    /// Destructor
    ///


    virtual
    ~MjStatement() = default;
public:


    ///
    /// Properties
    ///


    virtual
    bool is_deterministic() const noexcept = 0;


    ///
    /// Methods
    ///


};
