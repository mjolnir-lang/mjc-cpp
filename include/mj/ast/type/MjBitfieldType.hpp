#pragma once

#include "mj/ast/MjBasicType.hpp"


class MjBitfieldType : public MjBasicType {
private:
    const MjType &value_type;
public:


    MjBitfieldType(
        u32 size,
        u32 alignment,
        bool is_const,
        bool is_volatile,
        const MjToken &name,
        Vector<MjType *> template_parameters,
        const MjComment *comment
    ) :
        MjBasicType(size, alignment, is_const, is_volatile, name, template_parameters, comment)
    {}


    ~MjBitfieldType() {}


    void to_mjolnir(Utf8File &out) const {
        out.newline();
        out.write("bitfield<");
        value_type.to_mjolnir(out);
        out.write("> ");
        type.to_mjolnir(out);
        out.write(" {");
        out.indent();

        for (member : members) {
            out.newline();
            member.to_mjolnir(out);
        }

        out.undent();
        out.newline();
        out.write("}");
    }


    void to_c(Utf8File &out) const {
        out.newline();
        ;
    }
};
