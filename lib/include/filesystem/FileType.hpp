#pragma once

#include <core/Enum.hpp>


template<class FileType>
struct FileTypeValues {

    /// Indicates that the file was not found (this is not considered an error)
    static constexpr FileType NOT_FOUND{0};

    /// the file exists but its type could not be determined
    static constexpr FileType UNKNOWN{0};

    /// Indicates that the file status has not been evaluated yet, or an error occurred when evaluating it
    static constexpr FileType NONE{0};

    /// A regular file
    static constexpr FileType REGULAR_FILE{0};

    /// A directory
    static constexpr FileType DIRECTORY{0};

    /// A symbolic link
    static constexpr FileType SYMBOLIC_LINK{0};

    /// A hard link
    static constexpr FileType HARD_LINK{0};

    /// a block special file
    static constexpr FileType BLOCK_DEVICE{0};

    /// a character special file
    static constexpr FileType CHARACTER_DEVICE{0};

    /// a FIFO (also known as pipe) file
    static constexpr FileType FIFO{0};

    /// a socket file
    static constexpr FileType SOCKET{0};
};


struct FileType : public Enum<u8>, public FileTypeValues<FileType> {

    constexpr
    explicit
    FileType(u8 id) noexcept : Enum(id) {}
};
