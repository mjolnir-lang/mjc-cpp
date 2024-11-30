#pragma once

#include <core/Error.hpp>


template<class FileSystemError>
struct FileSystemErrorValues {
    static constexpr FileSystemError FILE_NOT_FOUND{0};
};


class FileSystemError : public Enum<u32>, public FileSystemErrorValues<FileSystemError> {
private:
public:


    constexpr
    explicit
    FileSystemError(u32 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


};
