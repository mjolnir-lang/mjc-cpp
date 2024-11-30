#pragma once

#include <filesystem/File.hpp>
#include <platform/system/Linux/syscall/syscall.hpp>


namespace platform::system {


/// Close a file descriptor
Error close(File &file) {
    return Linux::syscall::close(file._fd);
}


/// Open and possibly create a file
Error create(FilePath path, FileAccessMode mode, FileAccessFlags flags) noexcept {
    path.append("\0");
    return Linux::syscall::creat(path, mode | flags);
}


/// Open and possibly create a file
Error open(FilePath path, FileAccessFlags flags, u32 mode) noexcept {
    return Linux::syscall::open(path, flags, mode);
}


/// Open and possibly create a file relative to a directory file descriptor
Error open(File &file, FilePath path, u32 flags, u32 mode) noexcept {
    return Linux::syscall::openat(file._fd, path, flags, mode);
}


/// Obtain handle for a pathname
Error name_to_handle_at(File &dir_file, FilePath path, File &handle, u32 *mount_id, u32 flags) noexcept {
    return Linux::syscall::name_to_handle_at(dir_file._fd, path, handle._fd, mount_id, flags);
}


/// Open file via a handle
Error open_by_handle_at(File &mount_file, File &handle, u32 flags) noexcept {
    return Linux::syscall::open_by_handle_at(mount_file._fd, handle._fd, flags);
}


/// Create an anonymous file
Error memfd_create();


/// Create a special or ordinary file
Error mknod();


/// Create a special or ordinary file relative to a directory file descriptor
Error mknodat();


/// Rename a file
Error rename(FilePath path, const FilePath &name);


/// Rename a file relative to directory file descriptors
Error rename(File &file, FilePath path, const FilePath &name);


/// Rename a file relative to directory file descriptors
Error rename();


/// Truncate a file to a specified length
Error truncate(FilePath path, u64 size);


/// Truncate a file to a specified length
Error truncate(File &file, u64 size);


/// Manipulate file space
Error allocate(File &file, u32 mode, u64 offset, u64 size);


}
