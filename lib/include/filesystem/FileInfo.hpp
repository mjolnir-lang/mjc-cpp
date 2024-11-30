#pragma once

#include <filesystem/FileType.hpp>
#include <filesystem/FilePermission.hpp>


/// The file information
struct FileInfo {

    /// The file type
    FileType type;

    /// The file permissions
    FilePermission permissions;
};
