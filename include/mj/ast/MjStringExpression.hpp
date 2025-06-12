#pragma once

#include <mj/MjItemManager.hpp>
#include <mj/ast/MjExpression.hpp>
#include <core/String.hpp>


class MjStringExpression : public MjExpression {
private:
    StringView _value;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjStringExpression(StringView value, MjItemInfo item_info) noexcept :
        MjExpression(item_info), _value(value)
    {}


    ///
    /// Properties
    ///


    bool is_deterministic() const noexcept final {
        return true;
    }


    const MjType *result_type() const noexcept final {
        return item_manager->get("core::String");
    }


    constexpr
    StringView value() const noexcept {
        return _value;
    }
};
