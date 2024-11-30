#pragma once

#include <c/ast/CBasicType.hpp>


class CUnionType : public CBasicType {
private:
    Vector<CUnionType *> derivations_; // The derived types
    Vector<CMember *> members_; // Members
    const CTypeName &name_;     // The type identifier sequence (TODO)
    const CComment &comment_;   // The type documentation comment
    u32 size_;             // The type size in bytes
    u32 alignment_;        // The type alignment in bytes
    const bool is_const_;        // The type mutability. Memory may not be modified through this type
    const bool is_volatile_;     // The type volatility. Memory may be modified outside of the program
public:


    CUnionType(
        const CTypeName &name,
        Vector<CMember *> members,
        const CComment &comment,
        bool is_const,
        bool is_volatile
    ) :
        name_(name),
        comment_(comment)
    {}


    ~CUnionType() = default;


    const CTypeName &name() const {
        return name_;
    }


    /// @brief Return the comment.
    const CComment &comment() const {
        return comment_;
    }
};
