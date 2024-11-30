#pragma once

#include <core/Enum.hpp>


namespace platform::system::Linux::internal {


template<class FileAccessMode>
struct FileAccessModeValues {

    /// Open for execute only (non-directory files). The result is unspecified if this flag is applied to a directory.
    static constexpr FileAccessMode EXEC{0};

    /// Open for reading only.
    static constexpr FileAccessMode READ_ONLY{0};

    /// Open for reading and writing. The result is undefined if this flag is applied to a FIFO.
    static constexpr FileAccessMode READ_WRITE{0};

    /// Open directory for search only. The result is unspecified if this flag is applied to a non-directory file.
    static constexpr FileAccessMode SEARCH{0};

    /// Open for writing only.
    static constexpr FileAccessMode WRITE_ONLY{0};
};


struct FileAccessMode : public Enum<u8>, public FileAccessModeValues<FileAccessMode> {

    constexpr
    explicit
    FileAccessMode(u8 id) noexcept : Enum(id) {}
};


}
