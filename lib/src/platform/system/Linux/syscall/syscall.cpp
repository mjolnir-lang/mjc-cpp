#include <platform/system/Linux/syscall/syscall.hpp>
#include <system/logger/Logger.hpp>

#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <linux/aio_abi.h>
#include <linux/bpf.h>
//#include <numaif.h>
#include <poll.h>
//#include <stddef.h>
#include <stdio.h>
//#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/epoll.h>
#include <sys/mman.h>
#include <sys/select.h>
//#include <sys/sem.h>
#include <sys/sendfile.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syscall.h>
//#include <sys/types.h>
#include <sys/uio.h>
#include <sys/xattr.h>
#include <unistd.h>

namespace platform::system::Linux::syscall {


///
/// File System (File Operations)
///


Error close(FileDescriptor file_descriptor) {
    errno = 0;

    if (::close(file_descriptor)) {
        switch (errno) {
        case EBADF:
            lib_bug("platform::system::Linux", "Invalid file descriptor!");
            break;
        case EINTR:
            lib_error("platform::system::Linux", "The close() call was interrupted by a signal!");
            break;
        case EIO:
            lib_error("platform::system::Linux", "An I/O error occurred!");
            break;
        case ENOSPC:
        case EDQUOT:
            lib_error("platform::system::Linux", "On NFS, these errors are not normally reported against the first write which exceeds the available storage space, but instead against a subsequent write(), fsync(), or close()!");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error creat(const u8 *path, u32 mode) {
    errno = 0;

    if (::creat(reinterpret_cast<const char *>(path), mode)) {
        switch (errno) {
        case EACCES:
            if (mode & O_CREAT) {
                lib_error("platform::system::Linux", "Where O_CREAT is specified, the protected_fifos or protected_regular sysctl is enabled, the file already exists and is a FIFO or regular file, the owner of the file is neither the current user nor the owner of the containing directory, and the containing directory is both world- or group-writable and sticky.  For details, see the descriptions of /proc/sys/fs/protected_fifos and /proc/sys/fs/protected_regular in proc()!");
            } else {
                lib_error("platform::system::Linux", "The requested access to the file is not allowed, or search permission is denied for one of the directories in the path prefix of pathname, or the file did not exist yet and write access to the parent directory is not allowed.");
            }

            break;
        case EBUSY:
            lib_error("platform::system::Linux", "O_EXCL was specified in flags and pathname refers to a block device that is in use by the system (e.g., it is mounted)!");
            break;
        case EDQUOT:
            lib_bug("platform::system::Linux", "Where O_CREAT is specified, the file does not exist, and the user's quota of disk blocks or inodes on the filesystem has been exhausted!");
            break;
        case EEXIST:
            lib_bug("platform::system::Linux", "pathname already exists and O_CREAT and O_EXCL were used!");
            break;
        case EFAULT:
            lib_bug("platform::system::Linux", "pathname points outside your accessible address space!");
            break;
        case EFBIG:
            lib_bug("platform::system::Linux", "See EOVERFLOW!");
            break;
        case EINTR:
            lib_bug("platform::system::Linux", "While blocked waiting to complete an open of a slow device (e.g., a FIFO; see fifo()), the call was interrupted by a signal handler; see signal()!");
            break;
        case EINVAL:
            lib_bug("platform::system::Linux", "The filesystem does not support the O_DIRECT flag!");
            lib_bug("platform::system::Linux", "Invalid value in flags!");
            lib_bug("platform::system::Linux", "O_TMPFILE was specified in flags, but neither O_WRONLY nor O_RDWR was specified!");
            lib_bug("platform::system::Linux", "O_CREAT was specified in flags and the final component (\"basename\") of the new file's pathname is invalid (e.g., it contains characters not permitted by the underlying filesystem)!");
            lib_bug("platform::system::Linux", "The final component (\"basename\") of pathname is invalid (e.g., it contains characters not permitted by the underlying filesystem)!");
            break;
        case EISDIR:
            lib_bug("platform::system::Linux", "pathname refers to a directory and the access requested involved writing (that is, O_WRONLY or O_RDWR is set)!");
            lib_bug("platform::system::Linux", "pathname refers to an existing directory, O_TMPFILE and one of O_WRONLY or O_RDWR were specified in flags, but this kernel version does not provide the O_TMPFILE functionality!");
            break;
        case ELOOP:
            lib_bug("platform::system::Linux", "Too many symbolic links were encountered in resolving pathname!");
            lib_bug("platform::system::Linux", "pathname was a symbolic link, and flags specified O_NOFOLLOW but not O_PATH!");
            break;
        case EMFILE:
            lib_bug("platform::system::Linux", "The per-process limit on the number of open file descriptors has been reached (see the description of RLIMIT_NOFILE in getrlimit(2))!");
            break;
        case ENAMETOOLONG:
            lib_bug("platform::system::Linux", "pathname was too long!");
            break;
        case ENFILE:
            lib_bug("platform::system::Linux", "The system-wide limit on the total number of open files has been reached!");
            break;
        case ENODEV:
            lib_bug("platform::system::Linux", "pathname refers to a device special file and no corresponding device exists.  (This is a Linux kernel bug; in this situation ENXIO must be returned.!");
            break;
        case ENOENT:
            lib_bug("platform::system::Linux", "O_CREAT is not set and the named file does not exist!");
            lib_bug("platform::system::Linux", "A directory component in pathname does not exist or is a dangling symbolic link!");
            lib_bug("platform::system::Linux", "pathname refers to a nonexistent directory, O_TMPFILE and one of O_WRONLY or O_RDWR were specified in flags, but this kernel version does not provide the O_TMPFILE functionality!");
            break;
        case ENOMEM:
            lib_bug("platform::system::Linux", "The named file is a FIFO, but memory for the FIFO buffer can't be allocated because the per-user hard limit on memory allocation for pipes has been reached and the caller is not privileged; see pipe(7)!");
            lib_bug("platform::system::Linux", "Insufficient kernel memory was available!");
            break;
        case ENOSPC:
            lib_bug("platform::system::Linux", "pathname was to be created but the device containing pathname has no room for the new file!");
            break;
        case ENOTDIR:
            lib_bug("platform::system::Linux", "A component used as a directory in pathname is not, in fact, a directory, or O_DIRECTORY was specified and pathname was not a directory!");
            break;
        case ENXIO:
            lib_bug("platform::system::Linux", "O_NONBLOCK | O_WRONLY is set, the named file is a FIFO, and no process has the FIFO open for reading!");
            lib_bug("platform::system::Linux", "The file is a device special file and no corresponding device exists!");
            lib_bug("platform::system::Linux", "The file is a UNIX domain socket!");
            break;
        case EOPNOTSUPP:
            lib_bug("platform::system::Linux", "The filesystem containing pathname does not support O_TMPFILE!");
            break;
        case EOVERFLOW:
            lib_bug("platform::system::Linux", "pathname refers to a regular file that is too large to be opened!");
            break;
        case EPERM:
            lib_bug("platform::system::Linux", "The O_NOATIME flag was specified, but the effective user ID of the caller did not match the owner of the file and the caller was not privileged!");
            lib_bug("platform::system::Linux", "The operation was prevented by a file seal; see fcntl(2)!");
            break;
        case EROFS:
            lib_bug("platform::system::Linux", "pathname refers to a file on a read-only filesystem and write access was requested!");
            break;
        case ETXTBSY:
            lib_bug("platform::system::Linux", "pathname refers to an executable image which is currently being executed and write access was requested!");
            lib_bug("platform::system::Linux", "pathname refers to a file that is currently in use as a swap file, and the O_TRUNC flag was specified!");
            lib_bug("platform::system::Linux", "pathname refers to a file that is currently being read by the kernel (e.g., for module/firmware loading), and write access was requested!");
            break;
        case EWOULDBLOCK:
            lib_bug("platform::system::Linux", "The O_NONBLOCK flag was specified, and an incompatible lease was held on the file (see fcntl(2))!");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error open(const u8 *path, u32 flags, u32 mode) {
    errno = 0;

    if (::open(reinterpret_cast<const char *>(path), flags, mode)) {
        switch (errno) {
        case EACCES:
            if (mode & O_CREAT) {
                lib_error("platform::system::Linux", "Where O_CREAT is specified, the protected_fifos or protected_regular sysctl is enabled, the file already exists and is a FIFO or regular file, the owner of the file is neither the current user nor the owner of the containing directory, and the containing directory is both world- or group-writable and sticky.  For details, see the descriptions of /proc/sys/fs/protected_fifos and /proc/sys/fs/protected_regular in proc()!");
            } else {
                lib_error("platform::system::Linux", "The requested access to the file is not allowed, or search permission is denied for one of the directories in the path prefix of pathname, or the file did not exist yet and write access to the parent directory is not allowed.");
            }

            break;
        case EBUSY:
            lib_error("platform::system::Linux", "O_EXCL was specified in flags and pathname refers to a block device that is in use by the system!");
            break;
        case EDQUOT:
            lib_bug("platform::system::Linux", "Where O_CREAT is specified, the file does not exist, and the user's quota of disk blocks or inodes on the filesystem has been exhausted!");
            break;
        case EEXIST:
            lib_bug("platform::system::Linux", "pathname already exists and O_CREAT and O_EXCL were used!");
            break;
        case EFAULT:
            lib_bug("platform::system::Linux", "pathname points outside your accessible address space!");
            break;
        case EFBIG:
            lib_bug("platform::system::Linux", "See EOVERFLOW!");
            break;
        case EINTR:
            lib_bug("platform::system::Linux", "While blocked waiting to complete an open of a slow device, the call was interrupted by a signal handler!");
            break;
        case EINVAL:
            lib_bug("platform::system::Linux", "The filesystem does not support the O_DIRECT flag!");
            lib_bug("platform::system::Linux", "Invalid value in flags!");
            lib_bug("platform::system::Linux", "O_TMPFILE was specified in flags, but neither O_WRONLY nor O_RDWR was specified!");
            lib_bug("platform::system::Linux", "O_CREAT was specified in flags and the final component (\"basename\") of the new file's pathname is invalid (e.g., it contains characters not permitted by the underlying filesystem)!");
            lib_bug("platform::system::Linux", "The final component (\"basename\") of pathname is invalid (e.g., it contains characters not permitted by the underlying filesystem)!");
            break;
        case EISDIR:
            lib_bug("platform::system::Linux", "pathname refers to a directory and the access requested involved writing (that is, O_WRONLY or O_RDWR is set)!");
            lib_bug("platform::system::Linux", "pathname refers to an existing directory, O_TMPFILE and one of O_WRONLY or O_RDWR were specified in flags, but this kernel version does not provide the O_TMPFILE functionality!");
            break;
        case ELOOP:
            lib_bug("platform::system::Linux", "Too many symbolic links were encountered in resolving pathname!");
            lib_bug("platform::system::Linux", "pathname was a symbolic link, and flags specified O_NOFOLLOW but not O_PATH!");
            break;
        case EMFILE:
            lib_bug("platform::system::Linux", "The per-process limit on the number of open file descriptors has been reached!");
            break;
        case ENAMETOOLONG:
            lib_bug("platform::system::Linux", "pathname was too long!");
            break;
        case ENFILE:
            lib_bug("platform::system::Linux", "The system-wide limit on the total number of open files has been reached!");
            break;
        case ENODEV:
            lib_bug("platform::system::Linux", "pathname refers to a device special file and no corresponding device exists!");
            break;
        case ENOENT:
            lib_bug("platform::system::Linux", "O_CREAT is not set and the named file does not exist!");
            lib_bug("platform::system::Linux", "A directory component in pathname does not exist or is a dangling symbolic link!");
            lib_bug("platform::system::Linux", "pathname refers to a nonexistent directory, O_TMPFILE and one of O_WRONLY or O_RDWR were specified in flags, but this kernel version does not provide the O_TMPFILE functionality!");
            break;
        case ENOMEM:
            lib_bug("platform::system::Linux", "The named file is a FIFO, but memory for the FIFO buffer can't be allocated because the per-user hard limit on memory allocation for pipes has been reached and the caller is not privileged!");
            lib_bug("platform::system::Linux", "Insufficient kernel memory was available!");
            break;
        case ENOSPC:
            lib_bug("platform::system::Linux", "pathname was to be created but the device containing pathname has no room for the new file!");
            break;
        case ENOTDIR:
            lib_bug("platform::system::Linux", "A component used as a directory in pathname is not, in fact, a directory, or O_DIRECTORY was specified and pathname was not a directory!");
            break;
        case ENXIO:
            lib_bug("platform::system::Linux", "O_NONBLOCK | O_WRONLY is set, the named file is a FIFO, and no process has the FIFO open for reading!");
            lib_bug("platform::system::Linux", "The file is a device special file and no corresponding device exists!");
            lib_bug("platform::system::Linux", "The file is a UNIX domain socket!");
            break;
        case EOPNOTSUPP:
            lib_error("platform::system::Linux", "The filesystem containing pathname does not support O_TMPFILE!");
            break;
        case EOVERFLOW:
            lib_error("platform::system::Linux", "pathname refers to a regular file that is too large to be opened!");
            break;
        case EPERM:
            lib_bug("platform::system::Linux", "The O_NOATIME flag was specified, but the effective user ID of the caller did not match the owner of the file and the caller was not privileged!");
            lib_bug("platform::system::Linux", "The operation was prevented by a file seal; see fcntl()!");
            break;
        case EROFS:
            lib_bug("platform::system::Linux", "pathname refers to a file on a read-only filesystem and write access was requested!");
            break;
        case ETXTBSY:
            lib_bug("platform::system::Linux", "pathname refers to an executable image which is currently being executed and write access was requested!");
            lib_bug("platform::system::Linux", "pathname refers to a file that is currently in use as a swap file, and the O_TRUNC flag was specified!");
            lib_bug("platform::system::Linux", "pathname refers to a file that is currently being read by the kernel (e.g., for module/firmware loading), and write access was requested!");
            break;
        case EWOULDBLOCK:
            lib_bug("platform::system::Linux", "The O_NONBLOCK flag was specified, and an incompatible lease was held on the file (see fcntl(2))!");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error openat(FileDescriptor dirfd, const u8 *path, u32 flags, u32 mode) {
    errno = 0;

    if (::openat(dirfd, reinterpret_cast<const char *>(path), flags, mode)) {
        switch (errno) {
        case EACCES:
            if (flags & O_CREAT) {
                lib_error("platform::system::Linux", "The protected_fifos or protected_regular sysctl is enabled, the file already exists and is a FIFO or regular file, the owner of the file is neither the current user nor the owner of the containing directory, and the containing directory is both world- or group-writable and sticky.  For details, see the descriptions of /proc/sys/fs/protected_fifos and /proc/sys/fs/protected_regular in proc()!");
            } else {
                lib_error("platform::system::Linux", "The requested access to the file is not allowed, or search permission is denied for one of the directories in the path prefix of pathname, or the file did not exist yet and write access to the parent directory is not allowed.");
            }

            break;
        case EBADF:
            lib_error("platform::system::Linux", "openat() pathname is relative but dirfd is neither AT_FDCWD nor a valid file descriptor!");
            break;
        case EBUSY:
            lib_error("platform::system::Linux", "O_EXCL was specified in flags and pathname refers to a block device that is in use by the system (e.g., it is mounted)!");
            break;
        case EDQUOT:
            lib_bug("platform::system::Linux", "Where O_CREAT is specified, the file does not exist, and the user's quota of disk blocks or inodes on the filesystem has been exhausted!");
            break;
        case EEXIST:
            lib_bug("platform::system::Linux", "pathname already exists and O_CREAT and O_EXCL were used!");
            break;
        case EFAULT:
            lib_bug("platform::system::Linux", "pathname points outside your accessible address space!");
            break;
        case EFBIG:
            lib_bug("platform::system::Linux", "See EOVERFLOW!");
            break;
        case EINTR:
            lib_bug("platform::system::Linux", "While blocked waiting to complete an open of a slow device (e.g., a FIFO; see fifo()), the call was interrupted by a signal handler; see signal()!");
            break;
        case EINVAL:
            lib_bug("platform::system::Linux", "The filesystem does not support the O_DIRECT flag!");
            lib_bug("platform::system::Linux", "Invalid value in flags!");
            lib_bug("platform::system::Linux", "O_TMPFILE was specified in flags, but neither O_WRONLY nor O_RDWR was specified!");
            lib_bug("platform::system::Linux", "O_CREAT was specified in flags and the final component (\"basename\") of the new file's pathname is invalid (e.g., it contains characters not permitted by the underlying filesystem)!");
            lib_bug("platform::system::Linux", "The final component (\"basename\") of pathname is invalid (e.g., it contains characters not permitted by the underlying filesystem)!");
            break;
        case EISDIR:
            lib_bug("platform::system::Linux", "pathname refers to a directory and the access requested involved writing (that is, O_WRONLY or O_RDWR is set)!");
            lib_bug("platform::system::Linux", "pathname refers to an existing directory, O_TMPFILE and one of O_WRONLY or O_RDWR were specified in flags, but this kernel version does not provide the O_TMPFILE functionality!");
            break;
        case ELOOP:
            lib_bug("platform::system::Linux", "Too many symbolic links were encountered in resolving pathname!");
            lib_bug("platform::system::Linux", "pathname was a symbolic link, and flags specified O_NOFOLLOW but not O_PATH!");
            break;
        case EMFILE:
            lib_bug("platform::system::Linux", "The per-process limit on the number of open file descriptors has been reached (see the description of RLIMIT_NOFILE in getrlimit(2))!");
            break;
        case ENAMETOOLONG:
            lib_bug("platform::system::Linux", "pathname was too long!");
            break;
        case ENFILE:
            lib_bug("platform::system::Linux", "The system-wide limit on the total number of open files has been reached!");
            break;
        case ENODEV:
            lib_bug("platform::system::Linux", "pathname refers to a device special file and no corresponding device exists.  (This is a Linux kernel bug; in this situation ENXIO must be returned.!");
            break;
        case ENOENT:
            lib_bug("platform::system::Linux", "O_CREAT is not set and the named file does not exist!");
            lib_bug("platform::system::Linux", "A directory component in pathname does not exist or is a dangling symbolic link!");
            lib_bug("platform::system::Linux", "pathname refers to a nonexistent directory, O_TMPFILE and one of O_WRONLY or O_RDWR were specified in flags, but this kernel version does not provide the O_TMPFILE functionality!");
            break;
        case ENOMEM:
            lib_bug("platform::system::Linux", "The named file is a FIFO, but memory for the FIFO buffer can't be allocated because the per-user hard limit on memory allocation for pipes has been reached and the caller is not privileged; see pipe(7)!");
            lib_bug("platform::system::Linux", "Insufficient kernel memory was available!");
            break;
        case ENOSPC:
            lib_bug("platform::system::Linux", "pathname was to be created but the device containing pathname has no room for the new file!");
            break;
        case ENOTDIR:
            lib_bug("platform::system::Linux", "A component used as a directory in pathname is not, in fact, a directory, or O_DIRECTORY was specified and pathname was not a directory!");
            lib_bug("platform::system::Linux", "(openat()) pathname is a relative pathname and dirfd is a file descriptor referring to a file other than a directory!");
            break;
        case ENXIO:
            lib_bug("platform::system::Linux", "O_NONBLOCK | O_WRONLY is set, the named file is a FIFO, and no process has the FIFO open for reading!");
            lib_bug("platform::system::Linux", "The file is a device special file and no corresponding device exists!");
            lib_bug("platform::system::Linux", "The file is a UNIX domain socket!");
            break;
        case EOPNOTSUPP:
            lib_bug("platform::system::Linux", "The filesystem containing pathname does not support O_TMPFILE!");
            break;
        case EOVERFLOW:
            lib_bug("platform::system::Linux", "pathname refers to a regular file that is too large to be opened!");
            break;
        case EPERM:
            lib_bug("platform::system::Linux", "The O_NOATIME flag was specified, but the effective user ID of the caller did not match the owner of the file and the caller was not privileged!");
            lib_bug("platform::system::Linux", "The operation was prevented by a file seal!");
            break;
        case EROFS:
            lib_bug("platform::system::Linux", "pathname refers to a file on a read-only filesystem and write access was requested!");
            break;
        case ETXTBSY:
            lib_bug("platform::system::Linux", "pathname refers to an executable image which is currently being executed and write access was requested!");
            lib_bug("platform::system::Linux", "pathname refers to a file that is currently in use as a swap file, and the O_TRUNC flag was specified!");
            lib_bug("platform::system::Linux", "pathname refers to a file that is currently being read by the kernel (e.g., for module/firmware loading), and write access was requested!");
            break;
        case EWOULDBLOCK:
            lib_bug("platform::system::Linux", "The O_NONBLOCK flag was specified, and an incompatible lease was held on the file (see fcntl(2))!");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error mknodat(FileDescriptor dirfd, const u8 *path, u32 mode, u32 dev) {
    errno = 0;

    if (::mknodat(dirfd, reinterpret_cast<const char *>(path), mode, dev)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error rename(const u8 *src, const u8 *dst) {
    errno = 0;

    if (::rename(reinterpret_cast<const char *>(src), reinterpret_cast<const char *>(dst))) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error renameat(FileDescriptor olddirfd, const u8 *oldpath, FileDescriptor newdirfd, const u8 *newpath) {
    errno = 0;

    if (::renameat(olddirfd, reinterpret_cast<const char *>(oldpath), newdirfd, reinterpret_cast<const char *>(newpath))) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error truncate(const u8 *path, u64 size) {
    errno = 0;

    if (::truncate(reinterpret_cast<const char *>(path), size)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error ftruncate(FileDescriptor fd, u64 size) {
    errno = 0;

    if (::ftruncate(fd, size)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error fallocate(FileDescriptor fd, u32 mode, u64 offset, u64 size) {
    errno = 0;

    if (::fallocate(fd, mode, offset, size)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


///
/// File System (Directory Operations)
///


Error mkdir(const u8 *path, u32 mode) {
    errno = 0;

    if (::mkdir(reinterpret_cast<const char *>(path), mode)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error mkdirat(FileDescriptor dirfd, const u8 *path, u32 mode) {
    errno = 0;

    if (::mkdirat(dirfd, reinterpret_cast<const char *>(path), mode)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error rmdir(const u8 *path) {
    errno = 0;

    if (::rmdir(reinterpret_cast<const char *>(path))) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error getcwd(u8 *buffer, u32 size) {
    errno = 0;

    if (::getcwd(reinterpret_cast<char *>(buffer), size)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error chdir(const u8 *path) {
    errno = 0;

    if (::chdir(reinterpret_cast<const char *>(path))) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error fchdir(FileDescriptor fd) {
    errno = 0;

    if (::fchdir(fd)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error getdents(FileDescriptor fd, DirectoryEntry *dirp, u32 size) {
    errno = 0;

    if (::syscall(SYS_getdents, fd, dirp, size)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}












///
/// File System (Link Operations)
///


Error link(FilePath oldpath, FilePath newpath) {
    errno = 0;

    if (1) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error linkat(int olddirfd, FilePath oldpath, int newdirfd, FilePath newpath, int flags) {
    errno = 0;

    if (1) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error symlink(FilePath oldpath, FilePath newpath) {
    errno = 0;

    if (1) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error symlinkat(FilePath target, int newdirfd, FilePath linkpath) {
    errno = 0;

    if (1) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error unlink(FilePath pathname) {
    errno = 0;

    if (1) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error unlinkat(int dirfd, FilePath pathname, int flags) {
    errno = 0;

    if (1) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error readlink(FilePath path, char *buf, u32 bufsiz) {
    errno = 0;

    if (1) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error readlinkat(int dirfd, FilePath pathname, char *buf, u32 bufsiz) {
    errno = 0;

    if (1) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


///
/// File System (Basic File Attributes)
///


Error umask(u32 mask) {
    errno = 0;

    if (::umask(mask)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error stat(FilePath path, FileInfo *info) {
    errno = 0;

    struct stat st;

    if (::stat(path.c_str(), &st)) {
        return Error::FAILURE;
    }

    time_init_dsn(&info->access_time, st.st_atim.tv_sec / 86400, st.st_atim.tv_sec % 86400, st.st_atim.tv_nsec);
    time_init_dsn(&info->modify_time, st.st_mtim.tv_sec / 86400, st.st_mtim.tv_sec % 86400, st.st_mtim.tv_nsec);
    time_init_dsn(&info->change_time, st.st_ctim.tv_sec / 86400, st.st_ctim.tv_sec % 86400, st.st_ctim.tv_nsec);
    info->dev = st.st_dev;
    info->ino = st.st_ino;
    info->mode = st.st_mode;
    info->nlink = st.st_nlink;
    info->uid = st.st_uid;
    info->gid = st.st_gid;
    info->rdev = st.st_rdev;
    info->size = st.st_size;
    info->blksize = st.st_blksize;
    info->blocks = st.st_blocks;
    return Error::SUCCESS;
}


Error lstat(FilePath path, FileInfo *info) {
    errno = 0;

    struct stat st;

    if (::lstat(path.c_str(), &st)) {
        return Error::FAILURE;
    }

    time_init_dsn(&info->access_time, st.st_atim.tv_sec / 86400, st.st_atim.tv_sec % 86400, st.st_atim.tv_nsec);
    time_init_dsn(&info->modify_time, st.st_mtim.tv_sec / 86400, st.st_mtim.tv_sec % 86400, st.st_mtim.tv_nsec);
    time_init_dsn(&info->change_time, st.st_ctim.tv_sec / 86400, st.st_ctim.tv_sec % 86400, st.st_ctim.tv_nsec);
    info->dev = st.st_dev;
    info->ino = st.st_ino;
    info->mode = st.st_mode;
    info->nlink = st.st_nlink;
    info->uid = st.st_uid;
    info->gid = st.st_gid;
    info->rdev = st.st_rdev;
    info->size = st.st_size;
    info->blksize = st.st_blksize;
    info->blocks = st.st_blocks;
    return Error::SUCCESS;
}


Error fstat(FileDescriptor fd, FileInfo *info) {
    errno = 0;

    struct stat st;

    if (::fstat(fd, &st)) {
        return Error::FAILURE;
    }

    time_init_dsn(&info->access_time, st.st_atim.tv_sec / 86400, st.st_atim.tv_sec % 86400, st.st_atim.tv_nsec);
    time_init_dsn(&info->modify_time, st.st_mtim.tv_sec / 86400, st.st_mtim.tv_sec % 86400, st.st_mtim.tv_nsec);
    time_init_dsn(&info->change_time, st.st_ctim.tv_sec / 86400, st.st_ctim.tv_sec % 86400, st.st_ctim.tv_nsec);
    info->dev = st.st_dev;
    info->ino = st.st_ino;
    info->mode = st.st_mode;
    info->nlink = st.st_nlink;
    info->uid = st.st_uid;
    info->gid = st.st_gid;
    info->rdev = st.st_rdev;
    info->size = st.st_size;
    info->blksize = st.st_blksize;
    info->blocks = st.st_blocks;
    return Error::SUCCESS;
}


Error chmod(FilePath path, u32 mode) {
    errno = 0;

    if (1) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error fchmod(FileDescriptor fd, u32 mode) {
    errno = 0;

    if (1) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error fchmodat(FileDescriptor dirfd, FilePath pathname, u32 mode, u32 flags) {
    errno = 0;

    if (1) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error chown(FilePath path, UserId owner, GroupId group) {
    errno = 0;

    if (1) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error lchown(FilePath path, UserId owner, GroupId group) {
    errno = 0;

    if (1) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error fchown(FileDescriptor fd, UserId owner, GroupId group) {
    errno = 0;

    if (1) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error fchownat(FileDescriptor dirfd, FilePath pathname, UserId owner, GroupId group, u32 flags) {
    errno = 0;

    if (1) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error futimens(FileDescriptor fd, const Time *times) {
    errno = 0;


}


Error utimensat(FileDescriptor fd, FilePath path, const Time *times, u32 flags) {
    errno = 0;


}


Error access(FilePath path, u32 mode) {
    errno = 0;


}


Error faccessat(FileDescriptor dirfd, FilePath pathname, u32 mode, u32 flags) {
    errno = 0;

    if (1) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


///
/// File System (Extended File Attributes)
///


Error getxattr(FilePath path, FilePath name, void *value, u32 size) {
    errno = 0;

    if (::getxattr(path.c_str(), name.c_str(), value, size) == -1) {
        switch (errno) {
        case E2BIG:
            lib_bug("platform::system::Linux", "The size of the attribute value is larger than the maximum size allowed; the attribute cannot be retrieved!");
            break;
        case ENODATA:
            lib_error("platform::system::Linux", "The named attribute does not exist, or the process has no access to this attribute!");
            break;
        case ENOTSUP:
            lib_error("platform::system::Linux", "Extended attributes are not supported by the filesystem, or are disabled!");
            break;
        case ERANGE:
            lib_error("platform::system::Linux", "The size of the value buffer is too small to hold the result!");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error lgetxattr(FilePath path, FilePath name, void *value, u32 size) {
    errno = 0;

    if (::lgetxattr(path.c_str(), name.c_str(), value, size) == -1) {
        switch (errno) {
        case E2BIG:
            lib_bug("platform::system::Linux", "The size of the attribute value is larger than the maximum size allowed; the attribute cannot be retrieved!");
            break;
        case ENODATA:
            lib_error("platform::system::Linux", "The named attribute does not exist, or the process has no access to this attribute!");
            break;
        case ENOTSUP:
            lib_error("platform::system::Linux", "Extended attributes are not supported by the filesystem, or are disabled!");
            break;
        case ERANGE:
            lib_error("platform::system::Linux", "The size of the value buffer is too small to hold the result!");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error fgetxattr(FileDescriptor fd, FilePath name, void *value, u32 size) {
    errno = 0;

    if (::fgetxattr(fd, name.c_str(), value, size) == -1) {
        switch (errno) {
        case E2BIG:
            lib_bug("platform::system::Linux", "The size of the attribute value is larger than the maximum size allowed; the attribute cannot be retrieved!");
            break;
        case ENODATA:
            lib_error("platform::system::Linux", "The named attribute does not exist, or the process has no access to this attribute!");
            break;
        case ENOTSUP:
            lib_error("platform::system::Linux", "Extended attributes are not supported by the filesystem, or are disabled!");
            break;
        case ERANGE:
            lib_error("platform::system::Linux", "The size of the value buffer is too small to hold the result!");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error setxattr(FilePath path, FilePath name, const void *value, u32 size, u32 flags) {
    errno = 0;

    if (::setxattr(path.c_str(), name.c_str(), value, size, flags)) {
        switch (errno) {
        case EDQUOT:
            lib_error("platform::system::Linux", "Disk quota limits meant that there is insufficient space remaining to store the extended attribute!");
            break;
        case EEXIST:
            lib_error("platform::system::Linux", "XATTR_CREATE was specified, and the attribute exists already!");
            break;
        case ENODATA:
            lib_error("platform::system::Linux", "XATTR_REPLACE was specified, and the attribute does not exist!");
            break;
        case ENOSPC:
            lib_error("platform::system::Linux", "There is insufficient space remaining to store the extended attribute!");
            break;
        case ENOTSUP:
            lib_error("platform::system::Linux", "The namespace prefix of name is not valid!");
            lib_error("platform::system::Linux", "Extended attributes are not supported by the filesystem, or are disabled!");
            break;
        case EPERM:
            lib_error("platform::system::Linux", "The file is marked immutable or append-only!");
            break;
        case ERANGE:
            lib_error("platform::system::Linux", "The size of name or value exceeds a filesystem-specific limit!");
            break;
        //In addition, the errors documented in stat(2) can also occur.
        }
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error lsetxattr(FilePath path, FilePath name, const void *value, u32 size, u32 flags) {
    errno = 0;

    if (::lsetxattr(path.c_str(), name.c_str(), value, size, flags)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error fsetxattr(FileDescriptor fd, FilePath name, const void *value, u32 size, u32 flags) {
    errno = 0;

    if (::fsetxattr(fd, name.c_str(), value, size, flags)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error listxattr(FilePath path, char *list, u32 size) {
    errno = 0;

    if (::listxattr(path.c_str(), list, size)) {
        switch (errno) {
        case E2BIG:
            lib_bug("platform::system::Linux", "The size of the attribute value is larger than the maximum size allowed; the attribute cannot be retrieved!");
            break;
        case ENOTSUP:
            lib_error("platform::system::Linux", "Extended attributes are not supported by the filesystem, or are disabled!");
            break;
        case ERANGE:
            lib_error("platform::system::Linux", "The size of the list buffer is too small to hold the result!");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error llistxattr(FilePath path, char *list, u32 size) {
    errno = 0;

    if (::llistxattr(path.c_str(), list, size)) {
        switch (errno) {
        case E2BIG:
            lib_bug("platform::system::Linux", "The size of the attribute value is larger than the maximum size allowed; the attribute cannot be retrieved!");
            break;
        case ENOTSUP:
            lib_error("platform::system::Linux", "Extended attributes are not supported by the filesystem, or are disabled!");
            break;
        case ERANGE:
            lib_error("platform::system::Linux", "The size of the list buffer is too small to hold the result!");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error flistxattr(FileDescriptor fd, char *list, u32 size) {
    errno = 0;

    if (::flistxattr(fd, list, size)) {
        switch (errno) {
        case E2BIG:
            lib_bug("platform::system::Linux", "The size of the attribute value is larger than the maximum size allowed; the attribute cannot be retrieved!");
            break;
        case ENOTSUP:
            lib_error("platform::system::Linux", "Extended attributes are not supported by the filesystem, or are disabled!");
            break;
        case ERANGE:
            lib_error("platform::system::Linux", "The size of the list buffer is too small to hold the result!");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error removexattr(FilePath path, FilePath name) {
    errno = 0;

    if (::removexattr(path.c_str(), name.c_str())) {
        switch (errno) {
        case ENODATA:
            lib_error("platform::system::Linux", "The named attribute does not exist, or the process has no access to this attribute!");
            break;
        case ENOTSUP:
            lib_error("platform::system::Linux", "Extended attributes are not supported by the filesystem, or are disabled!");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error lremovexattr(FilePath path, FilePath name) {
    errno = 0;

    if (::lremovexattr(path.c_str(), name.c_str())) {
        switch (errno) {
        case ENODATA:
            lib_error("platform::system::Linux", "The named attribute does not exist, or the process has no access to this attribute!");
            break;
        case ENOTSUP:
            lib_error("platform::system::Linux", "Extended attributes are not supported by the filesystem, or are disabled!");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error fremovexattr(FileDescriptor fd, FilePath name) {
    errno = 0;

    if (::fremovexattr(fd, name.c_str())) {
        switch (errno) {
        case ENODATA:
            lib_error("platform::system::Linux", "The named attribute does not exist, or the process has no access to this attribute!");
            break;
        case ENOTSUP:
            lib_error("platform::system::Linux", "Extended attributes are not supported by the filesystem, or are disabled!");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


///
/// File System (File Descriptor Manipulations)
///


Error ioctl(FileDescriptor fd, int request, ...) {
    errno = 0;

    return ::ioctl(fd, request);
}


Error fcntl(FileDescriptor fd, int cmd, int arg) {
    errno = 0;

    if (::fcntl(fd, cmd, arg)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error dup(FileDescriptor fd) {
    errno = 0;

    if (::dup(fd)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error dup2(FileDescriptor oldfd, FileDescriptor newfd) {
    errno = 0;

    if (::dup2(oldfd, newfd)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error flock(FileDescriptor fd, int operation) {
    errno = 0;

    if (::flock(fd, operation)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


///
/// File System (Read/Write)
///


Error read(FileDescriptor fd, void *buffer, u32 size) {
    errno = 0;

    if (::read(fd, buffer, size)) {
        switch (errno){
        case EAGAIN:
            lib_bug("platform::system::Linux", "The file descriptor has been marked nonblocking, and the read would block!");
            break;
        case EBADF:
            lib_bug("platform::system::Linux", "The file descriptor is invalid or is not open for reading!");
            break;
        case EFAULT:
            lib_bug("platform::system::Linux", "The buffer is outside accessible address space!");
            break;
        case EINTR:
            lib_error("platform::system::Linux", "The call was interrupted by a signal before any data was read!");
            break;
        case EINVAL:
            lib_bug("platform::system::Linux", "fd is attached to an object which is unsuitable for reading; or the file was opened with the O_DIRECT flag, and either the address specified in buf, the value specified in count, or the file offset is not suitably aligned.");
            lib_bug("platform::system::Linux", "fd was created via a call to timerfd_create() and the wrong size buffer was given to read(); see timerfd_create(2) for further information.");
            break;
        case EIO:
            lib_error("platform::system::Linux", "I/O error. This will happen for example when the process is in a background process group, tries to read from its controlling terminal, and either it is ignoring or blocking SIGTTIN or its process group is orphaned.  It may also occur when there is a low-level I/O error while reading from a disk or tape. A further possible cause of EIO on networked filesystems is when an advisory lock had been taken out on the file descriptor and this lock has been lost.");
            break;
        case EISDIR:
            lib_bug("platform::system::Linux", "fd refers to a directory!");
            break;
        default:
            lib_error("platform::system::Linux", "Unspecified error! ({:u})", errno);
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error readv(FileDescriptor fd, Buffer<u8> *buffers, u32 size) {
    errno = 0;

    struct iovec buffers[size];

    for (u32 i = 0; i < size; i++) {
        buffers[i].iov_base = buffers[i].data;
        buffers[i].iov_len = buffers[i].size;
    }

    if (::readv(fd, buffers, size)) {
        return Error::FAILURE;
    }
}


Error pread(FileDescriptor fd, void *buffer, u32 size, i64 offset) {
    errno = 0;

    if (::pread(fd, buffer, size, offset)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error preadv(FileDescriptor fd, Buffer<u8> *buffers, u32 size, i64 offset) {
    errno = 0;

    if (::preadv(fd, buffers, size, offset)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error write(FileDescriptor fd, const void *buffer, u32 size) {
    errno = 0;

    if (::write(fd, buffer, size)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error writev(FileDescriptor fd, const Buffer<u8> *buffer, u32 size) {
    errno = 0;

    if (::writev(fd, buffer, size)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error pwrite(FileDescriptor fd, const void *buffer, u32 size, i64 offset) {
    errno = 0;

    if (::pwrite(fd, buffer, size, offset)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error pwritev(FileDescriptor fd, const Buffer<u8> *buffer, u32 size, i64 offset) {
    errno = 0;

    if (::pwritev(fd, buffer, size, offset)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error lseek(FileDescriptor fd, i64 offset, u32 whence) {
    errno = 0;

    if (::lseek(fd, offset, whence)) {
        switch (errno) {
        case EBADF:
            lib_bug("platform::system::Linux", "Invalid file descriptor!");
            break;
        case EINVAL:
            lib_bug("platform::system::Linux", "whence is invalid.  Or: the resulting file offset would be negative, or beyond the end of a seekable device!");
            break;
        case ENXIO:
            lib_bug("platform::system::Linux", "whence is SEEK_DATA or SEEK_HOLE, and offset is beyond the end of the file, or whence is SEEK_DATA and offset is within a hole at the end of the file!");
            break;
        case EOVERFLOW:
            lib_error("platform::system::Linux", "The resulting file offset cannot be represented in an off_t!");
            break;
        case ESPIPE:
            lib_bug("platform::system::Linux", "fd is associated with a pipe, socket, or FIFO!");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error sendfile(FileDescriptor readfd, FileDescriptor writefd, const i64 *offset, u32 count) {
    errno = 0;
    off_t _offset = *offset;
    i32 sent = ::sendfile(readfd, writefd, &_offset, count);
    //*offset = _offset;

    if  (sent) {
        switch (errno) {
        case EAGAIN:
            lib_error("platform::system::Linux", "Nonblocking I/O has been selected using O_NONBLOCK and the write would block");
        case EBADF:
            lib_bug("platform::system::Linux", "The input file was not opened for reading or the output file was not opened for writing!");
            break;
        case EFAULT:
            lib_error("platform::system::Linux", "Bad address!");
            break;
        case EINVAL:
            if (readfd & O_APPEND) {
                lib_bug("platform::system::Linux", "readfd has the O_APPEND flag set. This is not currently supported by sendfile()!");
            } else {
                lib_error("platform::system::Linux", "Descriptor is not valid or locked, or an mmap()-like operation is not available for in_fd, or count is negative!");
            }

            break;
        case EIO:
            lib_error("platform::system::Linux", "Unspecified error while reading from in_fd!");
            break;
        case ENOMEM:
            lib_error("platform::system::Linux", "Insufficient memory to read from in_fd!");
            break;
        case EOVERFLOW:
            lib_bug("platform::system::Linux", "count is too large, the operation would result in exceeding the maximum size of either the input file or the output file!");
            break;
        case ESPIPE:
            lib_bug("platform::system::Linux", "offset is not NULL but the input file is not seekable!");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}














///
/// Network (Socket Operations)
///


Error socket(FileDescriptor *fd, u32 domain, u32 type, u32 protocol) noexcept {
    errno = 0;
    u32 result = ::socket(domain, type, protocol);

    if (result == -1) {
        switch (errno) {
        case EACCES:
            log_error("Permission to create a socket of the specified type and/or protocol is denied.");
            break;
        case EAFNOSUPPORT:
            log_bug("The implementation does not support the specified address family.");
            break;
        case EINVAL:
            log_bug("Unknown protocol, or protocol family not available. Invalid flags in type.");
            break;
        case EMFILE:
            log_error("The per-process limit on the number of open file descriptors has been reached.");
            break;
        case ENFILE:
            log_error("The system-wide limit on the total number of open files has been reached.");
            break;
        case ENOBUFS:
        case ENOMEM:
            log_error("Insufficient memory is available. The socket cannot be created until sufficient resources are freed.");
            break;
        case EPROTONOSUPPORT:
            log_bug("The protocol type or the specified protocol is not supported within this domain.");
            break;
        default:
            log_error("Other errors may be generated by the underlying protocol modules.");
            break;
        }

        return Error::FAILURE;
    }

    *fd = result;
    return Error::SUCCESS;
}


Error socketpair(FileDescriptor *fd1, FileDescriptor *fd2, u32 domain, u32 type, u32 protocol) noexcept {
    errno = 0;
    int fds[2];

    if (::socketpair(domain, type, protocol, fds) == -1) {
        switch (errno) {
        case EAFNOSUPPORT:
            log_bug("The implementation does not support the specified address family.");
            break;
        case EFAULT:
            log_bug("The address sv does not specify a valid part of the process address space.");
            break;
        case EMFILE:
            log_error("The per-process limit on the number of open file descriptors has been reached.");
            break;
        case ENFILE:
            log_error("The system-wide limit on the total number of open files has been reached.");
            break;
        case EOPNOTSUPP:
            log_bug("The specified protocol does not support creation of socket pairs.");
            break;
        case EPROTONOSUPPORT:
            log_bug("The specified protocol is not supported on this machine.");
            break;
        }

        return Error::FAILURE;
    }

    *fd1 = fds[0];
    *fd2 = fds[1];
    return Error::SUCCESS;
}


Error setsockopt(FileDescriptor fd, u32 level, u32 name, u32 value, u32 size) noexcept {
    errno = 0;

    if (::setsockopt(fd, level, name, &value, size)) {
        switch (errno) {
        case EBADF:
            log_bug("The argument sockfd is not a valid file descriptor.");
            break;
        case EFAULT:
            log_bug("The address pointed to by 'value' is not in a valid part of the process address space.");
            break;
        case EINVAL:
            log_error("optlen invalid in setsockopt(). In some cases this error can also occur for an invalid value in 'value'");
            break;
        case EPROTONOSUPPORT:
            log_bug("The option is unknown at the level indicated.");
            break;
        case ENOTSOCK:
            log_bug("The file descriptor sockfd does not refer to a socket.");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error getsockopt(FileDescriptor fd, u32 level, u32 name, void *value, u32 *size) noexcept {
    errno = 0;
    socklen_t optlen;

    if (::getsockopt(fd, level, name, value, &optlen)) {
        switch (errno) {
        case EBADF:
            log_bug("The argument 'fd' is not a valid file descriptor.");
            break;
        case EFAULT:
            log_bug("The address pointed to by optval is not in a valid part of the process address space or optlen is not in a valid part of the process address space.");
            break;
        case EINVAL:
            log_error("optlen invalid in setsockopt(). In some cases this error can also occur for an invalid value in optval");
            break;
        case EPROTONOSUPPORT:
            log_bug("The option is unknown at the level indicated.");
            break;
        case ENOTSOCK:
            log_bug("The file descriptor 'fd' does not refer to a socket.");
            break;
        }
    }

    *size = optlen;
    return Error::SUCCESS;
}


Error getsockname(FileDescriptor fd, SocketAddress *address, u32 *size) noexcept {
    errno = 0;

    if (::getsockname(fd, address, size)) {
        switch (errno) {
        case EBADF:
            log_bug("Invalid file descriptor!");
            break;
        case EFAULT:
            log_bug("The addr argument points to memory not in a valid part of the process address space.");
            break;
        case EINVAL:
            log_bug("addrlen is invalid (e.g., is negative).");
            break;
        case ENOBUFS:
            log_bug("Insufficient resources were available in the system to perform the operation.");
            break;
        case ENOTSOCK:
            log_bug("The file descriptor 'fd' does not refer to a socket.");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error getpeername(FileDescriptor fd, SocketAddress *address, u32 *size) noexcept {
    errno = 0;

    if (::getpeername(fd, address, size)) {
        switch (errno) {
        case :
            log_bug("");
            break;
        case :
            log_bug("");
            break;
        case :
            log_bug("");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error bind(FileDescriptor fd, SocketAddress *address, u32 *size) noexcept {
    errno = 0;

    if (::bind(fd, address, size)) {
        switch (errno) {
        case EACCES:
            log_bug("The address is protected, and the user is not the superuser.");
            break;
        case EADDRINUSE:
            log_bug("The given address is already in use.");
            break;
        case EBADF:
            log_bug("Invalid file descriptor!");
            break;
        case EINVAL:
            log_bug("The socket is already bound to an address.");
            log_bug("addrlen is wrong, or addr is not a valid address for this socket's domain.");
            break;
        case ENOTSOCK:
            log_bug("The file descriptor is not a socket!");
            break;

        // The following errors are specific to UNIX domain (AF_UNIX) sockets:

        case EACCES:
            log_bug("Search permission is denied on a component of the path prefix.");
            break;
        case EADDRNOTAVAIL:
            log_bug("A nonexistent interface was requested or the requested address was not local.");
            break;
        case EFAULT:
            log_bug("addr points outside the user's accessible address space.");
            break;
        case ELOOP:
            log_bug("Too many symbolic links were encountered in resolving addr.");
            break;
        case ENAMETOOLONG:
            log_bug("addr is too long!");
            break;
        case ENOENT:
            log_bug("A component in the directory prefix of the socket pathname does not exist.");
            break;
        case ENOMEM:
            log_bug("Insufficient kernel memory was available.");
            break;
        case ENOTDIR:
            log_bug("A component of the path prefix is not a directory.");
            break;
        case EROFS:
            log_bug("The socket inode would reside on a read-only filesystem.");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error listen(FileDescriptor fd, u32 max) noexcept {
    errno = 0;

    if (::listen(fd, max) == 0) {
        return Error::SUCCESS;
    }

    switch (errno) {
    case EADDRINUSE:
        log_error("Another socket is already listening on the same port!");
        log_error("(Internet domain sockets) The socket referred to by sockfd had not previously been bound to an address and, upon attempting to bind it to an ephemeral port, it was determined that all port numbers in the ephemeral port range are currently in use!");
        break;
    case EBADF:
        log_bug("Invalid file descriptor!");
        break;
    case ENOTSOCK:
        log_bug("The file descriptor is not a socket!");
        break;
    case EOPNOTSUPP:
        log_bug("The socket is not of a type that supports the listen() operation!");
        break;
    }

    return Error::FAILURE;
}


Error accept(FileDescriptor fd, SocketAddress *address, u32 *size) noexcept {
    errno = 0;

    if (::accept(fd, address, size)) {
        switch (errno) {
        case :
            log_bug("");
            break;
        case :
            log_bug("");
            break;
        case :
            log_bug("");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error accept4(FileDescriptor fd, SocketAddress *address, u32 *size, u32 flags) noexcept {
    if (::accept4(fd, address, size, flags)) {
        switch (errno) {
        case :
            log_bug("");
            break;
        case :
            log_bug("");
            break;
        case :
            log_bug("");
            break;
        }

        return Error::FAILURE;
    }

    return Error::SUCCESS;
}


Error connect(FileDescriptor fd, const SocketAddress *address, u32 size) noexcept {
    errno = 0;

    if (::connect(fd, address, size) == 0) {
        return Error::SUCCESS;
    }

    switch (errno) {
    case EACCES:
        log_bug("For UNIX domain sockets, which are identified by pathname: Write permission is denied on the socket file, or search permission is denied for one of the directories in the path prefix.");
        log_bug("The user tried to connect to a broadcast address without having the socket broadcast flag enabled or the connection request failed because of a local firewall rule.");
        log_bug("It can also be returned if an SELinux policy denied a connection (for example, if there is a policy saying that an HTTP proxy can only connect to ports associated with HTTP servers, and the proxy tries to connect to a different port).");
        break;
    case EPERM:
        log_bug("The user tried to connect to a broadcast address without having the socket broadcast flag enabled or the connection request failed because of a local firewall rule.");
        break;
    case EADDRINUSE:
        log_error("Local address is already in use.");
        break;
    case EADDRNOTAVAIL:
        log_error("(Internet domain sockets) The socket referred to by sockfd had not previously been bound to an address and, upon attempting to bind it to an ephemeral port, it was determined that all port numbers in the ephemeral port range are currently in use.");
        break;
    case EAFNOSUPPORT:
        log_bug("The passed address didn't have the correct address family in its sa_family field.");
        break;
    case EAGAIN:
        log_bug("For nonblocking UNIX domain sockets, the socket is nonblocking, and the connection cannot be completed immediately. For other socket families, there are insufficient entries in the routing cache.");
        break;
    case EALREADY:
        log_bug("The socket is nonblocking and a previous connection attempt has not yet been completed.");
        break;
    case EBADF:
        log_bug("sockfd is not a valid open file descriptor.");
        break;
    case ECONNREFUSED:
        log_error("A connect() on a stream socket found no one listening on the remote address.");
        break;
    case EFAULT:
        log_bug("The socket structure address is outside the user's address space.");
        break;
    case EINPROGRESS:
        log_debug("The socket is nonblocking and the connection cannot be completed immediately.  (UNIX domain sockets failed with EAGAIN instead.)  It is possible to select(2) or poll(2) for completion by selecting the socket for writing. After select(2) indicates writability, use getsockopt(2) to read the SO_ERROR option at level SOL_SOCKET to determine whether connect() completed successfully (SO_ERROR is zero) or unsuccessfully (SO_ERROR is one of the usual error codes listed here, explaining the reason for the failure).");
        break;
    case EINTR:
        log_error("The system call was interrupted by a signal that was caught");
        break;
    case EISCONN:
        log_debug("The socket is already connected.");
        break;
    case ENETUNREACH:
        log_error("Network is unreachable.");
        break;
    case ENOTSOCK:
        log_bug("The file descriptor sockfd does not refer to a socket.");
        break;
    case EPROTOTYPE:
        log_bug("The socket type does not support the requested communications protocol. This error can occur, for example, on an attempt to connect a UNIX domain datagram socket to a stream socket.");
        break;
    case ETIMEDOUT:
        log_error("Timeout while attempting connection. The server may be too busy to accept new connections. Note that for IP sockets the timeout may be very long when syncookies are enabled on the server.");
        break;
    }

    return Error::FAILURE;
}


void shutdown(FileDescriptor fd, u32 flags) noexcept {
    errno = 0;

    if (::shutdown(fd, flags)) {
        switch (errno) {
        case :
            log_bug("");
            break;
        case :
            log_bug("");
            break;
        case :
            log_bug("");
            break;
        }
    }
}


}
