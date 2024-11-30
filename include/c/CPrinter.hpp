#pragma once

#include <c/ast/CStatement.hpp>
#include <c/ast/CProgram.hpp>
#include <c/ast/CType.hpp>


// The parser consumes the output of the scanner and emits the AST components while controlling the parsing context.
class CPrinter {
private:
    File &out_;
    String tab_;
    u32 depth_ = 0;
public:


    CPrinter(
        File &out
    ) :
        out_(out),
        tab_("    ")
    {}


    void indent() {
        depth_ += 1;
    }


    void undent() {
        if (depth_) {
            depth_ -= 1;
        }
    }


    void newline(u32 n = 1) {
        out_.write('\n', n);

        for (u32 i = 0; i < depth_; i++) {
            out_.write(tab_);
        }
    }


    void write(StringView string) {
        out_.write(string);
    }


    void print(StringView format, ...);


    void print(const CType &type, const String &name, bool is_reference, bool is_mutable);


    void print(const CExpression &expression);


    void print(const CStatement &statement);
    void print(const CBlockStatement &statement);
    void print(const CBreakStatement &statement);
    void print(const CContinueStatement &statement);
    void print(const CDoWhileStatement &statement);
    void print(const CForStatement &statement);
    void print(const CIfStatement &statement);
    void print(const CMatchStatement &statement);
    void print(const CReturnStatement &statement);
    void print(const CWhileStatement &statement);


    void print(const CVariable &variable);


    void print(const CMember &member);


    void print(const CFunction &function);


    void print(const CEnumerationType &enum_type);


    /// @brief Print a structure type definition.
    ///
    /// Structures have no constructors, destructors, methods, or operators.
    /// They may be named or anonymous.
    /// They may be generic (only is not anonymous)
    ///
    /// @param structure_type The structure type.
    void print(const CStructureType &structure_type);


    void print_type_name(const CType &type) noexcept;
    void print_type_declaration(const CType &type) noexcept;
    void print_type_definition(const CType &type) noexcept;


    void print_structure_type_name(const CStructureType &type) noexcept;
    void print_structure_type_declaration(const CStructureType &type) noexcept;
    void print_structure_type_definition(const CStructureType &type) noexcept;



    void print(const CUnionType &union_type);


    /// @brief Print a module file.
    void print(const CModule &module);


    /// @brief Create all module files in the program hierarchy.
    void print(const CProgram &program);
};
