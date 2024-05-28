#pragma once

#include <mj/ast/MjModule.hpp>
#include <mj/ast/MjStatement.hpp>
#include <mj/ast/MjProgram.hpp>
#include <mj/ast/MjType.hpp>
#include <mj/ast/MjTypeImplementation.hpp>
#include <mj/ast/MjTypeEnumeration.hpp>


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


    void print(const MjVariable &variable);


    void print(const MjMember &member);


    void print(const MjFunction &function);


    void print(const MjType &type);


    void print(const MjTypeEnumeration &type_enumeration);


    void print(const MjTypeImplementation &type_implementation);


    /// @brief Print a module file.
    void print(const MjModule &module);


    /// @brief Create all module files in the program hierarchy.
    void print(const MjProgram &program);
};
