#pragma once

#include "mj/ast/MjModule.hpp"

#include "std/Vector.hpp"
#include "fs/Path.hpp"


// An MjObjectFile is a precompiled Mjolnir source file which represents a module.
class MjObjectFile {
    Vector<const Path *> dependencies_;
    Path path_;
    u64 last_run_;
    bool is_valid_;


    MjObjectFile() {}


    void compile() {

        // Build all dependencies
        for (const Path *depencency : dependencies_) {

            // Check if the module is already loaded.
            if (MjModule::is_loaded(depencency)) {
                continue;
            }

            // Look for precompiled file.
            if (depencency.set_ext(".mjo").is_file()) {
                if (depencency.modified_time > depencency_obj.modified_time || depencency.modified_time > this.modified_time) {
                    // also check checksum to determine if a previous build was canceled or corrupted!
                    MjModule &mod = MjModule::compile(depencency);
                }
            } else if (depencency.set_ext(".mj").is_file()) {
                // Check modified time.
                if (modified_time > this.modified_time) {
                    MjModule &mod = MjModule::compile(depencency);
                }
            } else {
                // Missing import!
            }
        }

        // TODO: recipe...
    }


    // Encode the file.
    void encode(const Path &path) {

    }


    // Decode the file.
    void decode(const Path &path) {

    }
};
