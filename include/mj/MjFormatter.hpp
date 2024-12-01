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
    File &_out;
    String _tab;
    u32 _depth = 0;
public:


    MjPrinter(File &out) :
        _out(out),
        _tab("    ")
    {}


    void indent() {
        _depth += 1;
    }


    void undent() {
        if (_depth) {
            _depth -= 1;
        }
    }


    void newline(u32 n = 1) {
        _out.write('\n', n);

        for (u32 i = 0; i < _depth; i++) {
            _out.write(_tab);
        }
    }


    void write(StringView string) {
        _out.write(string);
    }


    void print(StringView format, ...);


    void print(const MjType &type, const String &name, bool is_reference, bool is_mutable);


    void print(const MjExpression &expression);


    void print(const MjStatement &statement);


    void print(const MjVariable &variable);


    void print(const MjFunction &function);


    void print(const MjType &type);


    void print(const MjTypeEnumeration &type_enumeration);


    void print(const MjTypeImplementation &type_implementation);


    /// @brief Print a module file.
    void print(const MjModule &module);


    /// @brief Create all module files in the program hierarchy.
    void print(const MjProgram &program);
};
