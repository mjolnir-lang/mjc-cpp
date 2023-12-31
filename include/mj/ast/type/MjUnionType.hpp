#pragma once

#include "mj/ast/MjBasicType.hpp"


class MjUnionType : public MjBasicType {
private:
    Vector<MjTemplateParameter *> template_parameters_;
    Vector<MjUnionType *> derivations_; // The derived types
    Vector<MjMember *> members_; // Members
    const MjTypeName &name_;     // The type identifier sequence (TODO)
    const MjComment &comment_;   // The type documentation comment
    u32 size_;             // The type size in bytes
    u32 alignment_;        // The type alignment in bytes
    const bool is_const_;        // The type mutability. Memory may not be modified through this type
    const bool is_volatile_;     // The type volatility. Memory may be modified outside of the program
public:


    MjUnionType(
        const MjTypeName &name,
        Vector<MjTemplateParameter *> template_parameters,
        Vector<MjMember *> members,
        const MjComment &comment,
        bool is_const,
        bool is_volatile
    ) :
        name_(name),
        comment_(comment)
    {}


    ~MjUnionType() = default;


    const MjTypeName &name() const {
        return name_;
    }


    /// @brief Return the comment.
    const MjComment &comment() const {
        return comment_;
    }


    const Vector<MjTemplateParameter *> template_parameters() const {
        return template_parameters_;
    }
};
