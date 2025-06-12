#pragma once

#include <mj/ast/MjItem.hpp>
#include <mj/ast/MjItemKind.hpp>
#include <mj/ast/MjToken.hpp>


// A structured unit of execution.
class MjStatement : public MjItem {
protected:


    ///
    /// Constructors
    ///


    constexpr
    MjStatement(MjItemInfo item_info) noexcept : MjItem(item_info) {}


    ///
    /// Destructor
    ///


    virtual
    ~MjStatement() = default;


public:


    ///
    /// Shared Properties
    ///


    static
    constexpr
    bool is_type_of(const MjItem *item) {
        return item->item_kind() == MjItemKind::STATEMENT;
    }


    ///
    /// Properties
    ///


    virtual
    bool is_deterministic() const noexcept = 0;


    ///
    /// Methods
    ///


};
