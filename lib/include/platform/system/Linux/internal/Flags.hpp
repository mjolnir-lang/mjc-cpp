#pragma once

#include <core/Enum.hpp>


using DateTime = u64;
using Time = u64;


namespace platform::system::Linux::internal {


//enum os_prot_flag {
//    OS_PROT_NONE      = 0, // prevents access to memory
//    OS_PROT_READ      = 1, // allows reading of memory
//    OS_PROT_WRITE     = 2, // allows memory to be modified
//    OS_PROT_EXEC      = 4, // allows execution of memory
//    OS_PROT_SEM       = 0, // allows memory to be used in atomic operations
//    OS_PROT_GROWSUP   = 33554432, // sets protection mode upward (for arcitectures that have stack that grows upward)
//    OS_PROT_GROWSDOWN = 16777216, // sets protection mode downward (useful for stack memory)
//};


//enum os_map_flag {
//    OS_MAP_SHARED          = 1, // allows other processes to use this mapping
//    OS_MAP_SHARED_VALIDATE = 3, // same as MAP_SHARED but ensures all flags are valid
//    OS_MAP_PRIVATE         = 2, // prevents other processes from using this mapping
//    OS_MAP_32BIT           = 64, // tells the kernel to locate mapping in the first 2 GB of RAM
//    OS_MAP_ANONYMOUS       = 32, // lets the mapping not be backed by any file (thus ignoring `fd`)
//    OS_MAP_ANON            = 32, //
//    OS_MAP_                = 0, //
//    OS_MAP_                = 0, //
//    OS_MAP_                = 0, //
//    OS_MAP_FIXED           = 16, // treats addr argument as an actual address and not a hint
//    OS_MAP_FIXED_NOREPLACE = 1048576, // same as MAP_FIXED but prevents clobbering existing mapped ranges
//    OS_MAP_GROWSDOWN       = 256, // tells the kernel to expand mapping downward in RAM (useful for stacks)
//    OS_MAP_HUGETB          = 262144, // forces use of huge pages in mapping
//    OS_MAP_HUGE_1MB        = 0, // use with MAP_HUGETB to set 1 MB pages
//    OS_MAP_HUGE_2MB        = 0, // use with MAP_HUGETB to set 2 MB pages
//    OS_MAP_LOCKED          = 8192, // maps the region to be locked (similar behavior to mlock)
//    OS_MAP_NONBLOCK        = 65536, // prevents read-ahead for this mapping
//    OS_MAP_NORESERVE       = 16384, // prevents allocation of swap space for this mappining
//    OS_MAP_POPULATE        = 32768, // tells the kernel to populate page tables for this mapping (causing read-ahead)
//    OS_MAP_STACK           = 131072, // tells the kernel to allocate address suitable for use in a stack
//    OS_MAP_UNINITIALIZED   = 0, // prevents clearing of anonymous pages
//};


///
static constexpr u32 MAP_HUGE_SHIFT = 26;
static constexpr u32 MAP_HUGE_2MB = 21 << MAP_HUGE_SHIFT;
static constexpr u32 MAP_HUGE_1GB = 30 << MAP_HUGE_SHIFT;

// /
static constexpr void *MAP_FAILED = (void *) -1;


template<class MemoryRemapFlags>
struct MemoryRemapFlagsValues {
    static constexpr MemoryRemapFlags MAYMOVE{1};
    static constexpr MemoryRemapFlags FIXED{2};
    static constexpr MemoryRemapFlags DONTUNMAP{4};
};


struct MemoryRemapFlags : public Enum<u8>, public MemoryRemapFlagsValues<MemoryRemapFlags> {

    constexpr
    explicit
    MemoryRemapFlags(u8 id) noexcept : Enum(id) {}
};


/// A file descriptor
using FileDescriptor = i32;

/// A Process ID
using ProcessId = i32;

/// A User ID
using UserId = i32;

/// A Group ID
using GroupId = i32;

/// A Thread ID
using ThreadId = i32;


using FileHandle = struct file_handle;


struct FileInfo {
    DateTime access_time; // Time of last access
    DateTime modify_time; // Time of last modification
    DateTime change_time; // Time of last status change
    u64 dev;              // ID of device containing file
    u64 ino;              // Inode number
    u32 mode;             // File type and mode
    u64 nlink;            // Number of hard links
    UserId uid;           // User ID of owner
    GroupId gid;          // Group ID of owner
    u64 rdev;             // Device ID (if special file)
    u64 size;             // Total size, in bytes
    u64 blksize;          // Block size for filesystem I/O
    u64 blocks;           // Number of 512B blocks allocated
};


struct DirectoryEntry {
    u32 ino;     // Inode number
    u32 offset;  // Offset to next linux_dirent
    u16 size;    // Length of this linux_dirent
    u8 name[0]; // Filename (null-terminated) length is actually (size - 2 - offsetof(struct linux_dirent, name))
};


union EpollData {
    void *ptr;
    FileDescriptor fd;
    u32 u32;
    u64 u64;
};


struct EpollEvent {
    u32 events; // Epoll events
    EpollData data; // User data variable
};


}
