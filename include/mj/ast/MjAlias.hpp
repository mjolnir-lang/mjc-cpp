#pragma once

#include "mj/ast/MjBasicType.hpp"


// A type alias is an identifier which is used to reference another type.
class MjTypeAlias {
protected:
    const MjType &target_; // The type identifier sequence (TODO)


    MjTypeAlias(
        const MjType &target,
        bool is_const,
        bool is_volatile,
        const MjToken &name,
        Vector<MjType *> template_parameters,
        const MjComment *comment,
        MjBasicType &index_type
    ) :
        target_(target)
    {}


    virtual ~MjTypeAlias() {}
public:


    const MjType &target() const { return target_; }


    /// \brief Write the type declaration to the Mjolnir source file.
    /// \param out The source file to which to write
    /// \param name The name of the instance associated with the type
    void to_mjolnir_declaration(Utf8File &out, const String *name = nullptr) const {
        out.newline();
        out.write("alias ");
        target_.to_mjolnir_left(out);
        out.write(name.text);

        if (!template_parameters().is_empty()) {

            // Write the template parameter list.
            out.write("<");
            bool once = true;

            for (MjType &type : template_parameters()) {
                if (once) once = false; else out.write(", ");
                type.to_mjolnir(out);
            }

            out.write(">");
        }

        out.write(" ");
        target_.to_mjolnir_right(out);
        out.write(";");
    }


    /// \brief Write the type declaration to the C source file.
    /// \param out The source file to which to write
    /// \param name The name of the instance associated with the type
    void to_c_declaration(Utf8File &out, const String *name = nullptr) const {
        out.newline();
        out.write("typedef ");
        target_.to_c_left(out);
        out.write(name.text);

        if (!template_parameters().is_empty()) {

            // Write the template parameter list.
            out.write("<");
            bool once = true;

            for (MjType &type : template_parameters()) {
                if (once) once = false; else out.write(", ");
                type.to_c(out);
            }

            out.write(">");
        }

        out.write(" ");
        target_.to_c_right(out);
        out.write(";");
    }
};
