#pragma once

#include "mj/ast/MjModule.hpp"
#include "mj/ast/MjStatement.hpp"
#include "mj/ast/MjModule.hpp"
#include "mj/ast/MjProgram.hpp"
#include "mj/ast/MjType.hpp"
#include "mj/ast/MjImplementation.hpp"


// The parser consumes the output of the scanner and emits the AST components while controlling the parsing context.
class MjPrinter {
private:
    File &out_;
    String tab_;
    u32 depth_ = 0;
public:


    MjPrinter(
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


    void print(const MjType &type, const String &name, bool is_reference, bool is_mutable);


    void print(const MjExpression &expression);


    void print(const MjStatement &statement);
    void print(const MjBlockStatement &statement);
    void print(const MjBreakStatement &statement);
    void print(const MjContinueStatement &statement);
    void print(const MjDoStatement &statement);
    void print(const MjDoUntilStatement &statement);
    void print(const MjDoWhileStatement &statement);
    void print(const MjForStatement &statement);
    void print(const MjForEachStatement &statement);
    void print(const MjIfStatement &statement);
    void print(const MjImportStatement &statement);
    void print(const MjMatchStatement &statement);
    void print(const MjReturnStatement &statement);
    void print(const MjUntilStatement &statement);
    void print(const MjWhileStatement &statement);
    void print(const MjYieldStatement &statement);


    void print(const MjVariable &variable);


    void print(const MjMember &member);


    void print(const MjFunction &function);


    void print(const MjMethod &method);


    void print(const MjBitfieldType &bitfield_type);


    void print(const MjClassType &class_type);


    void print(const MjEnumerationType &enum_type);


    void print(const MjImplementation &inplementation);


    void print(const MjInterfaceType &interface_type);


    /// @brief Print a structure type definition.
    ///
    /// Structures have no constructors, destructors, methods, or operators.
    /// They may be named or anonymous.
    /// They may be generic (only is not anonymous)
    ///
    /// @param structure_type The structure type.
    void print(const MjStructureType &structure_type);


    void print(const MjUnionType &union_type);


    void print(const MjVariantType &variant_type);


    /// @brief Print a module file.
    void print(const MjModule &module);


    /// @brief Create all module files in the program hierarchy.
    void print(const MjProgram &program);
};
