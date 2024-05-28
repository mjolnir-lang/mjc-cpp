#pragma once

#include <c/ast/CFunction.hpp>


/// @brief A Program is an executable without a platform.
/// It lists dependencies and has a startup and a main function.
class CProgram {
private:
    String name_;
    List<CImport> imports_;
    CFunction startup_function_;
    CFunction main_function_;
public:


    CProgram(
        StringView name
    ) :
        name_(name)
    {
        //add_builtins()
    }


    void export_source(const Path &path) {

        // Write module dependencies.
        //for (CModule &mod : scope.modules) {
        //    mod.save(obj);
        //}

        // Write types.

        // Write identifiers.

        // Write data.
        //for (const String &line : obj) {
            //
        //}
    }
};
