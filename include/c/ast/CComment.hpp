#pragma once

#include <c/ast/CToken.hpp>


/// @brief An `CComment` is a source code annotation attatched to AST objects.
class CComment {
private:
    String &text_;
    //String &brief;
    //String &params;
    //String &returns;
    bool is_documentation_;
public:


    CComment(
        String &text
    ) :
        text_(text)
    {}


    bool is_documentation() const {
        return is_documentation_;
    }


    StringView text() const {
        return text_;
    }
};
