#pragma once

#include <mj/ast/MjToken.hpp>


/// @brief An `MjComment` is a source code annotation attached to AST objects.
class MjComment {
private:
    String &_text;
    bool _is_formatted;
public:


    MjComment(
        String &text,
        bool is_formatted
    ) :
        _text(text), _is_formatted(is_formatted)
    {}


    bool is_formatted() const {
        return _is_formatted;
    }


    StringView text() const {
        return _text;
    }
};
