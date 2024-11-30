#pragma once

#include <mj/ast/MjToken.hpp>
#include <mj/ast/MjItem.hpp>


/// @brief An `MjComment` is a source code annotation attached to AST objects.
class MjComment : public MjItem {
private:
    StringView _text;
    bool _is_formatted;
public:


    static
    constexpr
    MjItemKind item_kind() noexcept {
        return MjItemKind::COMMENT;
    }


    ///
    /// Constructors
    ///


    MjComment(StringView text, bool is_formatted) noexcept : MjItem(item_kind()),
        _text(text), _is_formatted(is_formatted)
    {}


    ///
    /// Properties
    ///


    bool is_formatted() const {
        return _is_formatted;
    }


    StringView text() const {
        return _text;
    }
};
