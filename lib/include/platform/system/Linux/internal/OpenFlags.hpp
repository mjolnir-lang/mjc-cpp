#pragma once

#include <core/Enum.hpp>


namespace platform::system::Linux::internal {


template<class OpenFlags>
struct OpenFlagsValues {

    /// allows use of file sizes represented by off64_t
    static constexpr OpenFlags LARGEFILE{0};

    /// create file if it doesn't exist
    static constexpr OpenFlags CREAT{64};

    /// ensure creation of file
    static constexpr OpenFlags EXCL{128};

    /// if pathname is a terminal device, don't become controlling terminal
    static constexpr OpenFlags NOCTTY{256};

    /// if file exists, overwrite it (careful!)
    static constexpr OpenFlags TRUNC{512};

    /// append to existing file
    static constexpr OpenFlags APPEND{1024};

    /// same as O_NONBLOCK
    static constexpr OpenFlags NDELAY{2048};

    /// if possible, open file with non-blocking IO
    static constexpr OpenFlags NONBLOCK{2048};

    /// ensure output is sent to hardware and metadata written before return
    static constexpr OpenFlags DSYNC{4096};

    /// use signal-driven IO
    static constexpr OpenFlags ASYNC{8192};

    /// bypass cache (slower)
    static constexpr OpenFlags DIRECT{16384};

    /// fail if pathname isn't a directory
    static constexpr OpenFlags DIRECTORY{65536};

    /// fail if pathname is symbolic link
    static constexpr OpenFlags NOFOLLOW{131072};

    /// do not increment access time upon open
    static constexpr OpenFlags NOATIME{262144};

    /// use close-on-exec (avoid race conditions and lock contentions)
    static constexpr OpenFlags CLOEXEC{524288};

    /// wait for IO to complete before returning
    static constexpr OpenFlags SYNC{1052672};

    /// open descriptor for obtaining permissions and status of a file but does not allow read/write operations
    static constexpr OpenFlags PATH{2097152};

    /// create an unnamed, unreachable (via any other open call) temporary file
    static constexpr OpenFlags TMPFILE{4259840};
};


struct OpenFlags : public Enum<u8>, public OpenFlagsValues<OpenFlags> {

    constexpr
    explicit
    OpenFlags(u8 id) noexcept : Enum(id) {}
};


}
