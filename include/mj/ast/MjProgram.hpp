#pragma once

#include <mj/ast/MjModule.hpp>


/// @brief A Program is an executable without a platform.
/// It lists dependencies and has a startup and a main function.
class MjProgram {
private:
    Vector<MjModule *> modules_;
    MjFunction *startup_function_;
    MjFunction *main_function_;
public:


    void export_source(const FilePath &file_path) noexcept {

        // Write module dependencies.
        //for (MjModule &mod : scope.modules) {
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
