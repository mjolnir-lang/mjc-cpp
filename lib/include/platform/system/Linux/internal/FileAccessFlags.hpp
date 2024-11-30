#pragma once

#include <core/Enum.hpp>


namespace platform::system::Linux::internal {


template<class FileAccessFlags>
struct FileAccessFlagsValues {

    /// If set, the file offset shall be set to the end of the file prior to each write.
    static constexpr FileAccessFlags APPEND{};

    /// If set, the FD_CLOEXEC flag for the new file descriptor shall be set.
    static constexpr FileAccessFlags CLOEXEC{};

    /// If the file exists, this flag has no effect except as noted under O_EXCL below. Otherwise,
    /// if O_DIRECTORY is not set the file shall be created as a regular file; the user ID of the
    /// file shall be set to the effective user ID of the process; the group ID of the file shall be
    /// set to the group ID of the file's parent directory or to the effective group ID of the
    /// process; and the access permission bits (see <sys/stat.h>) of the file mode shall be set to
    /// the value of the argument following the oflag argument taken as type mode_t modified as
    /// follows: a bitwise AND is performed on the file- mode bits and the corresponding bits in the
    /// complement of the process' file mode creation mask. Thus, all bits in the file mode whose
    /// corresponding bit in the file mode creation mask is set are cleared. When bits other than
    /// the file permission bits are set, the effect is unspecified. The argument following the
    /// oflag argument does not affect whether the file is open for reading, writing, or for both.
    /// Implementations shall provide a way to initialize the file's group ID to the group ID of the
    /// parent directory. Implementations may, but need not, provide an implementation-defined way
    /// to initialize the file's group ID to the effective group ID of the calling process.
    static constexpr FileAccessFlags CREAT{};

    /// If path resolves to a non-directory file, fail and set errno to [ENOTDIR].
    static constexpr FileAccessFlags DIRECTORY{};

    /// Write I/O operations on the file descriptor shall complete as defined by synchronized I/O
    /// data integrity completion.
    static constexpr FileAccessFlags DSYNC{};

    /// If O_CREAT and O_EXCL are set, open() shall fail if the file exists. The check for the
    /// existence of the file and the creation of the file if it does not exist shall be atomic with
    /// respect to other threads executing open() naming the same filename in the same directory
    /// with O_EXCL and O_CREAT set. If O_EXCL and O_CREAT are set, and path names a symbolic link,
    /// open() shall fail and set errno to [EEXIST], regardless of the contents of the symbolic
    /// link. If O_EXCL is set and O_CREAT is not set, the result is undefined.
    static constexpr FileAccessFlags EXCL{};

    /// If set and path identifies a terminal device, open() shall not cause the terminal device to
    /// become the controlling terminal for the process. If path does not identify a terminal
    /// device, O_NOCTTY shall be ignored.
    static constexpr FileAccessFlags NOCTTY{};

    /// If path names a symbolic link, fail and set errno to [ELOOP].
    static constexpr FileAccessFlags NOFOLLOW{};

    /// When opening a FIFO with O_RDONLY or O_WRONLY set:
    ///
    /// - If O_NONBLOCK is set, an open() for reading-only shall return without delay. An open() for
    ///     writing-only shall return an error if no process currently has the file open for
    ///     reading.
    ///
    /// - If O_NONBLOCK is clear, an open() for reading-only shall block the calling thread until a
    ///     thread opens the file for writing. An open() for writing-only shall block the calling
    ///     thread until a thread opens the file for reading.
    ///
    /// When opening a block special or character special file that supports non-blocking opens:
    ///
    /// - If O_NONBLOCK is set, the open() function shall return without blocking for the device to
    ///     be ready or available. Subsequent behavior of the device is device-specific.
    ///
    /// - If O_NONBLOCK is clear, the open() function shall block the calling thread until the
    ///     device is ready or available before returning.
    ///
    /// Otherwise, the O_NONBLOCK flag shall not cause an error, but it is unspecified whether the
    /// file status flags will include the O_NONBLOCK flag.
    static constexpr FileAccessFlags NONBLOCK{};

    /// Read I/O operations on the file descriptor shall complete at the same level of integrity as
    /// specified by the O_DSYNC and O_SYNC flags. If both O_DSYNC and O_RSYNC are set in oflag, all
    /// I/O operations on the file descriptor shall complete as defined by synchronized I/O data
    /// integrity completion. If both O_SYNC and O_RSYNC are set in flags, all I/O operations on the
    /// file descriptor shall complete as defined by synchronized I/O file integrity completion.
    static constexpr FileAccessFlags RSYNC{};

    /// Write I/O operations on the file descriptor shall complete as defined by synchronized I/O
    /// file integrity completion.
    ///
    /// The O_SYNC flag shall be supported for regular files, even if the Synchronized Input and
    /// Output option is not supported.
    static constexpr FileAccessFlags SYNC{};

    /// If the file exists and is a regular file, and the file is successfully opened O_RDWR or
    /// O_WRONLY, its length shall be truncated to 0, and the mode and owner shall be unchanged. It
    /// shall have no effect on FIFO special files or terminal device files. Its effect on other
    /// file types is implementation- defined. The result of using O_TRUNC without either O_RDWR or
    /// O_WRONLY is undefined.
    static constexpr FileAccessFlags TRUNC{};

    /// If path identifies a terminal device other than a pseudo-terminal, the device is not already
    /// open in any process, and either O_TTY_INIT is set in oflag or O_TTY_INIT has the value zero,
    /// open() shall set any non-standard termios structure terminal parameters to a state that
    /// provides conforming behavior; see the Base Definitions volume of POSIX.1‐2017, Section 11.2,
    /// Parameters that Can be Set.  It is unspecified whether O_TTY_INIT has any effect if the
    /// device is already open in any process. If path identifies the slave side of a pseudo-
    /// terminal that is not already open in any process, open() shall set any non-standard termios
    /// structure terminal parameters to a state that provides conforming behavior, regardless of
    /// whether O_TTY_INIT is set. If path does not identify a terminal device, O_TTY_INIT shall be
    /// ignored.
    static constexpr FileAccessFlags TTY_INIT{};
};


struct FileAccessFlags : public Enum<u8>, public FileAccessFlagsValues<FileAccessFlags> {

    constexpr
    explicit
    FileAccessFlags(u8 id) noexcept : Enum(id) {}
};


}
