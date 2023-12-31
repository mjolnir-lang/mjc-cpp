#pragma once

#include "mj/ast/type/MjFunctionType.hpp"


class MjMethodType : public MjFunctionType {
private:
    MjType &owner_;
    const u32 member_offset_;
public:


    MjMethodType(
        MjType &owner,
        Vector<MjVariable> parameters,
        u32 size,
        u32 alignment,
        bool is_const,
        bool is_volatile
    ) :
        owner_(owner)
    {}


    ~MjMethodType() = default;


    const MjType &owner() const {
        return owner_;
    }


    MjMemberType member_type() {
        return MjMemberType::METHOD;
    }


    u32 member_offset() const {
        return member_offset_;
    }
};
