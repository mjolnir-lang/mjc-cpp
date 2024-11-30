#pragma once

#include <platform/system/Linux/internal/FileDescriptor.hpp>
#include <platform/system/Linux/internal/FileAccessMode.hpp>
#include <platform/system/Linux/internal/FileAccessFlags.hpp>
#include <platform/system/Linux/internal/OpenFlags.hpp>
#include <platform/system/Linux/internal/PermissionFlags.hpp>
#include <platform/system/Linux/internal/ProcessId.hpp>
#include <platform/system/Linux/internal/SeekFlags.hpp>

#include <filesystem/FilePath.hpp>
#include <container/Buffer.hpp>

namespace platform::system::Linux::syscall {


///
/// File Operation System Calls
///


///
/// File System (File Operations)
///


/// (  3) Close a file descriptor
Error close(FileDescriptor fd);


/// ( 85) Open and possibly create a file
Error creat(const u8 *path, u32 mode);


/// (  2) Open and possibly create a file
Error open(const u8 *path, u32 flags, u32 mode);


/// (257) Open and possibly create a file relative to a directory file descriptor
Error openat(FileDescriptor fd, const u8 *path, u32 flags, u32 mode);


/// (303) Obtain handle for a pathname
Error name_to_handle_at(FileDescriptor dirfd, const u8 *path, FileHandle *handle, int *mount_id, u32 flags);


/// (304) Open file via a handle
Error open_by_handle_at(FileDescriptor mount_fd, FileHandle *handle, u32 flags);


/// (319) Create an anonymous file
Error memfd_create();


/// (133) Create a special or ordinary file
Error mknod();


/// (259) Create a special or ordinary file relative to a directory file descriptor
Error mknodat();


/// ( 82) Rename a file
Error rename(FilePath path, const u8 *name);


/// (264) Rename a file relative to directory file descriptors
Error renameat(FileDescriptor fd, FilePath path, const u8 *name);


/// (316) Rename a file relative to directory file descriptors
Error renameat2();


/// ( 76) Truncate a file to a specified length
Error truncate(FilePath path, u64 size);


/// ( 77) Truncate a file to a specified length
Error ftruncate(FileDescriptor fd, u64 size);


/// (285) Manipulate file space
Error fallocate(FileDescriptor fd, u32 mode, u64 offset, u64 size);


///
/// File System (Directory Operations)
///


/// ( 83) Create a directory
/// Attempts to create a directory named pathname.
///
/// The argument mode specifies the mode for the new directory.
/// It is modified by the process's umask in the usual
/// way: in the absence of a default ACL, the mode of the created
/// directory is (mode & ~umask & 0777).  Whether other mode bits are
/// honored for the created directory depends on the operating
/// system.  For Linux, see NOTES below.
///
/// The newly created directory will be owned by the effective user
/// ID of the process.  If the directory containing the file has the
/// set-group-ID bit set, or if the filesystem is mounted with BSD
/// group semantics (mount -o bsdgroups or, synonymously mount -o
/// grpid), the new directory will inherit the group ownership from
/// its parent; otherwise it will be owned by the effective group ID
/// of the process.
///
/// If the parent directory has the set-group-ID bit set, then so
/// will the newly created directory.
Error mkdir(FilePath path);


/// (258) Create a directory relative to a directory file descriptor
Error mkdirat();


/// ( 84) Delete a directory
Error rmdir();


/// ( 79) Get current working directory
Error getcwd();


/// ( 80) Change working directory
Error chdir();


/// ( 81) Change working directory
Error fchdir();


/// (161) Change root directory
Error chroot();


/// ( 78) Get directory entries
Error getdents();


/// (217) Get directory entries
Error getdents64();


/// (212) Return a directory entry's path
Error lookup_dcookie();


///
/// File System (Link Operations)
///


Error link();           // ( 86) Create a hard link to a file
Error linkat();         // (265) Create a hard link to a file relative to directory file descriptors
Error symlink();        // ( 88) Create a symbolic link to a file
Error symlinkat();      // (266) Create a symbolic link to a file relative to a directory file descriptor
Error unlink();         // ( 87) Delete a name and possibly the file it refers to
Error unlinkat();       // (263) Delete a name and possibly the file it refers to relative to a directory file descriptor
Error readlink();       // ( 89) Read value of a symbolic link
Error readlinkat();     // (267) Read value of a symbolic link relative to a directory file descriptor


///
/// File System (Basic File Attributes)
///


/// ( 95) Set file mode creation mask
Error umask();


/// (  4) Get file metadata
Error stat();


/// (  6) Get link metadata
Error lstat();


/// (  5) Get file metadata
Error fstat();


/// (262) Get file metadata relative to a directory file descriptor
Error fstatat();


/// ( 90) Change permissions of a file
Error chmod();


/// ( 91) Change permissions of a file
Error fchmod();


/// (268) Change permissions of a file relative to a directory file descriptor
Error fchmodat();


/// ( 92) Change ownership of a file
Error chown();


/// ( 94) Change ownership of a link
Error lchown();


/// ( 93) Change ownership of a file
Error fchown();


/// (260) Change ownership of a file relative to a directory file descriptor
Error fchownat();


/// (280) Change file timestamps with nanosecond precision
Error futimens(FileDescriptor fd, const Time *times);


/// (280) Change file timestamps with nanosecond precision
Error utimensat(FileDescriptor fd, FilePath path, const Time *times, u32 flags);


/// ( 21) Check real user's permissions for a file
Error access(FilePath path, u32 mode);


/// (269) Check real user's permissions for a file relative to a directory file descriptor
Error faccessat(FileDescriptor fd, FilePath path, u32 mode, u32 flags);


///
/// File System (Extended File Attributes)
///


/// (191) Retrieve an extended attribute value
Error getxattr(FilePath path, FilePath name, void *value, u32 size);


/// (192) Retrieve an extended attribute value
Error lgetxattr(FilePath path, FilePath name, void *value, u32 size);


/// (193) Retrieve an extended attribute value
Error fgetxattr(FileDescriptor fd, FilePath name, void *value, u32 size);


/// (188) Set an extended attribute value
Error setxattr(FilePath path, FilePath name, const void *value, u32 size, u32 flags);


/// (189) Set an extended attribute value
Error lsetxattr(FilePath path, FilePath name, const void *value, u32 size, u32 flags);


/// (190) Set an extended attribute value
Error fsetxattr(FileDescriptor fd, FilePath name, const void *value, u32 size, u32 flags);


/// (194) List extended attribute names
Error listxattr(FilePath path, char *list, u32 size);


/// (195) List extended attribute names
Error llistxattr(FilePath path, char *list, u32 size);


/// (196) List extended attribute names
Error flistxattr(FileDescriptor fd, char *list, u32 size);


/// (197) Remove an extended attribute
Error removexattr(FilePath path, FilePath name);


/// (198) Remove an extended attribute
Error lremovexattr(FilePath path, FilePath name);


/// (199) Remove an extended attribute
Error fremovexattr(FileDescriptor fd, FilePath name);


///
/// File System (File Descriptor Manipulations)
///


/// ( 16) Control device
Error ioctl(FileDescriptor fd, int request, ...);


/// ( 72) Manipulate file descriptor
Error fcntl(FileDescriptor fd, int cmd, int arg);


/// ( 32) Duplicate a file descriptor
Error dup(FileDescriptor fd);


/// ( 33) Duplicate a file descriptor
Error dup2(FileDescriptor oldfd, FileDescriptor newfd);


/// (292) Duplicate a file descriptor
Error dup3();


/// ( 73) Apply or remove an advisory lock on an open file
Error flock(FileDescriptor fd, int operation);


///
/// File System (Read/Write)
///


/// (  0) Read from a file descriptor
Error read(FileDescriptor fd, void *buffer, u32 size);


/// ( 19) Read data into multiple buffers
Error readv(FileDescriptor fd, Buffer<u8> *buffers, u32 size);


/// ( 17) Read from a file descriptor at a given offset
Error pread(FileDescriptor fd, void *buffer, u32 size, i64 offset);


/// (295) Read data into multiple buffers
Error preadv(FileDescriptor fd, Buffer<u8> *buffers, u32 size, i64 offset);


/// (  1) Write to a file descriptor
Error write(FileDescriptor fd, const void *buffer, u32 size);


/// ( 20) Write data into multiple buffers
Error writev(FileDescriptor fd, const Buffer<u8> *buffers, u32 size);


/// ( 18) Write to a file descriptor at a given offset
Error pwrite(FileDescriptor fd, const void *buffer, u32 size, i64 offset);


/// (296) Write data into multiple buffers
Error pwritev(FileDescriptor fd, const Buffer<u8> *buffers, u32 size, i64 offset);


/// (  8) Reposition read/write file offset
Error lseek(FileDescriptor fd, i64 offset, u32 whence);


/// ( 40) Transfer data between file descriptors
Error sendfile(FileDescriptor readfd, FileDescriptor writefd, const i64 *offset, u32 size);


///
/// File System (Synchronized I/O)
///


/// ( 75) Synchronize a file's in-core state with storage device
Error fdatasync(FileDescriptor fd);


/// ( 74) Synchronize a file's in-core state with storage device
Error fsync(FileDescriptor fd);


/// ( 26) Synchronize a file with a memory map
Error msync(void *addr, u32 size, u32 flags);


/// (277) Sync a file segment with disk
Error sync_file_range(FileDescriptor fd, u64 offset, u64 size, u32 flags);


/// (162) Commit buffer cache to disk
void sync(void);


/// (306) Commit buffer cache to disk
Error syncfs(FileDescriptor fd);


///
/// File System (Asynchronous I/O)
///


struct IoEvent {
    u64 data; // The data field from the AioCb
    u64 obj;  // The AioTransfer this event came from
    i64 res;  // The result code
    i64 res2; // The secondary result
};


struct IoCb {
    u64 data;     // The data copied into the data field of AioEvent upon I/O completion
#ifdef LITTLE_ENDIAN
    u32 key;      // An internal field used by the kernel (Do not modify this field after an io_submit() call!)
    u32 rw_flags; // The R/W flags passed with structure
#else
    u32 rw_flags; // The R/W flags passed with structure
    u32 key;      // An internal field used by the kernel (Do not modify this field after an io_submit() call!)
#endif
    u16 command;  // The IO operation to be performed
    i16 priority; // The request priority
    FileDescriptor fd;        // The file descriptor used for the transfer
    u64 buffer;   // The buffer to transfer
    u64 size;     // The number of bytes to transfer
    i64 offset;   // The offset of the file descriptor at which to transfer
    u64 signal;   // The signal to raise upon completion
    u32 flags;    //
    FileDescriptor resfd;     // The file descriptor to signal upon completion
};


/// (206) Create an asynchronous I/O context.
Error io_setup(u32 nr_events, u64 *context);


/// (207) Destroy an asynchronous I/O context.
Error io_destroy(u64 context);


/// (209) Submit asynchronous I/O blocks for processing.
Error io_submit(u64 context, u32 nr, IoCb **iocb);


/// (210) Cancel an outstanding asynchronous I/O operation.
Error io_cancel(u64 context, IoCb *iocb, IoEvent *result);


/// (208) Read asynchronous I/O events from the completion queue.
Error io_getevents(u64 context, u32 min_nr, u32 nr, IoEvent *events, const Time *timeout);


///
/// File System (Multiplexed I/O)
///


class SelectFd {
private:
    u64 _words[16]; // 1024 bits
public:


    /// This macro clears (removes all file descriptors from) set.
    /// It should be employed as the first step in initializing a
    /// file descriptor set.
    constexpr
    SelectFd() noexcept {}


    /// This macro adds the file descriptor fd to set.  Adding a
    /// file descriptor that is already present in the set is a
    /// no-op, and does not produce an error.
    constexpr
    void set(FileDescriptor fd) noexcept {
        _words[fd >> 6] |= 1u << (fd & 0x3Fu);
    }


    /// This macro removes the file descriptor fd from set.
    /// Removing a file descriptor that is not present in the set
    /// is a no-op, and does not produce an error.
    constexpr
    void clear(FileDescriptor fd) noexcept {
        _words[fd >> 6] &= ~(1u << (fd & 0x3Fu));
    }


    /// select() modifies the contents of the sets according to
    /// the rules described below.  After calling select(), the
    /// FD_ISSET() macro can be used to test if a file descriptor
    /// is still present in a set.  FD_ISSET() returns nonzero if
    /// the file descriptor fd is present in set, and zero if it
    /// is not.
    constexpr
    bool is_set(FileDescriptor fd) const noexcept {
        return _words[fd >> 6] & (1u << (fd & 0x3Fu));
    }
};


struct PollFd {
    FileDescriptor fd;       // File descriptor to poll
    u16 events;  // Types of events poller cares about
    u16 revents; // Types of events that actually occurred
};




/// ( 23) Synchronous I/O multiplexing
Error select(u32 nfds, SelectFd *read_fds, SelectFd *write_fds, SelectFd *except_fds, const Time *timeout);


/// (270) Synchronous I/O multiplexing
Error pselect(u32 nfds, SelectFd *read_fds, SelectFd *write_fds, SelectFd *except_fds, const Time *timeout, const sigset_t *sigmask);


/// (  7) Wait for some event on a file descriptor
Error poll(const PollFd *pollfds, u32 size, const Time *timeout);


/// (271) Wait for some event on a file descriptor
Error ppoll(const PollFd *pollfds, u32 size, const Time *timeout, const sigset_t *sigmask);


/// (213) Open an epoll file descriptor.
Error epoll_create(void);


/// (291) Open an epoll file descriptor.
Error epoll_create1(u32 flags);


/// (233) Control interface for an epoll descriptor
Error epoll_ctl(FileDescriptor epfd, u32 op, FileDescriptor fd, struct epoll_event *event);


/// (232) Wait for an I/O event on an epoll file descriptor
Error epoll_wait(FileDescriptor epfd, struct epoll_event *events, u32 maxevents, const Time *timeout);


/// (281) Wait for an I/O event on an epoll file descriptor
Error epoll_pwait(FileDescriptor epfd, struct epoll_event *events, u32 maxevents, const Time *timeout, const sigset_t *sigmask);


///
/// File System (File Event Monitoring)
///


/// (253) Initialize an inotify instance
Error inotify_init();


/// (294) Initialize an inotify instance
Error inotify_init1();


/// (254) Add a watch to an initialized inotify instance
Error inotify_add_watch();


/// (255) Remove an existing watch from an inotify instance
Error inotify_rm_watch();


/// (300) Create and initialize fanotify group
Error fanotify_init();


/// (301) Add, remove, or modify an fanotify mark on a filesystem object
Error fanotify_mark();


///
/// File System (Misc)
///


/// (221) Predeclare an access pattern for file data
Error fadvise64();


/// (187) Perform file readahead into page cache
Error readahead();


/// (318) Obtain a series of random bytes
Error getrandom();


///
/// File System (System Wide Privileged)
///


/// (155) Change the root file system
Error pivot_root(FilePath new_root, FilePath put_old);


/// (167) Start swapping to file/device
Error swapon(FilePath path, u32 flags);


/// (168) Stop swapping to file/device
Error swapoff(FilePath path);


/// (165) Mount file system
Error mount(FilePath source, FilePath target, FilePath filesystemtype, u64 mountflags, const void *data);


/// (166) Unmount file system
Error umount2(FilePath target, u32 flags);


/// (180) Syscall interface to kernel nfs daemon
Error nfsservctl(u32 cmd, struct nfsctl_arg *argp, union nfsctl_res *resp);


///
/// File System (System Wide Unprivileged)
///


typedef struct fs_info {
    u64 total_blocks;   // Total data blocks in filesystem
    u64 free_blocks;    // Free blocks in filesystem
    u64 avail_blocks;   // Free blocks available to unprivileged user
    u64 total_files;    // Total inodes in filesystem
    u64 free_inodes;    // Free inodes in filesystem
    u32 id[2];          // Filesystem ID
    u32 type;           // Type of filesystem (see below)
    u32 block_size;     // Optimal transfer block size
    u32 max_file_name_size;  // Maximum length of filenames
    u32 fragment_size;   // Fragment size (since Linux 2.6)
    u32 mount_flags;     // Mount flags of filesystem (since Linux 2.6.36)
} FsInfo;


/// (137) Get file system statistics
Error statfs(FilePath path, FsInfo *info);


/// (138) Get file system statistics
Error fstatfs(FileDescriptor fd, FsInfo *info);

































///
/// Network (Socket Operations)
///


#define SOCKET_SHUTDOWN_RD    0
#define SOCKET_SHUTDOWN_WR    1
#define SOCKET_SHUTDOWN_RDWR  2


struct SocketAddress {
    u16 family;  // address family and length
    u8 data[14]; // Address data
};


template<class SocketType>
struct SocketTypeValues {

    /// Provides sequenced, reliable, two-way, connection-based byte streams.
    /// An out-of-band data transmission mechanism may be supported.
    static constexpr SocketType STREAM{SOCK_STREAM};

    /// Supports datagrams (connectionless, unreliable messages of a fixed maximum length).
    static constexpr SocketType DATAGRAM{SOCK_DGRAM};

    /// Provides a sequenced, reliable, two-way connection-based data transmission path for
    /// datagrams of fixed maximum length; a consumer is required to read an entire packet with
    /// each input system call.
    static constexpr SocketType SEQPACKET{SOCK_SEQPACKET};

    /// Provides raw network protocol access.
    static constexpr SocketType RAW{SOCK_RAW};

    /// Provides a reliable datagram layer that does not guarantee ordering.
    static constexpr SocketType RDM{SOCK_RDM};
};


struct SocketType : public Enum<u8>, public SocketTypeValues<SocketType> {

    explicit
    constexpr
    SocketType(u8 id) noexcept : Enum(id) {}


    bool is_nonblocking() const noexcept {
        return _id & SOCK_NONBLOCK;
    }


    bool is_cloexec() const noexcept {
        return _id & SOCK_CLOEXEC;
    }
};


/// ( 41) Create an endpoint for communication
///
/// On success, a file descriptor for the new socket is returned.
Error socket(FileDescriptor *fd, u32 domain, u32 type, u32 protocol) noexcept;


/// ( 53) Create a pair of connected sockets
///
/// The socketpair() call creates an unnamed pair of connected
/// sockets in the specified domain, of the specified type, and using
/// the optionally specified protocol.  For further details of these
/// arguments, see socket(2).
///
/// The file descriptors used in referencing the new sockets are
/// returned in sv[0] and sv[1].  The two sockets are
/// indistinguishable.
Error socketpair(FileDescriptor *fd1, FileDescriptor *fd2, u32 domain, u32 type, u32 protocol) noexcept;


/// ( 54) Set options on sockets
Error setsockopt(FileDescriptor fd, u32 level, u32 name, u32 value, u32 size) noexcept;


/// ( 55) Get options on sockets
Error getsockopt(FileDescriptor fd, u32 level, u32 name, void *value, u32 *size) noexcept;


/// ( 51) Get socket name
///
/// getsockname() returns the current address to which the socket
/// sockfd is bound, in the buffer pointed to by addr.  The addrlen
/// argument should be initialized to indicate the amount of space
/// (in bytes) pointed to by addr.  On return it contains the actual
/// size of the socket address.
///
/// The returned address is truncated if the buffer provided is too
/// small; in this case, addrlen will return a value greater than was
/// supplied to the call.
Error getsockname(FileDescriptor fd, SocketAddress *address, u32 *size) noexcept;


/// ( 52) Get name of connected peer socket
Error getpeername(FileDescriptor fd, SocketAddress *address, u32 *size) noexcept;


/// ( 49) Bind a name to a socket
Error bind(FileDescriptor fd, SocketAddress *address, u32 *size) noexcept;


/// ( 50) Listen for connections on a socket
Error listen(FileDescriptor fd, u32 max) noexcept;


/// ( 43) Accept a connection on a socket
Error accept(FileDescriptor fd, SocketAddress *address, u32 *size) noexcept;


/// (288) Accept a connection on a socket
Error accept4(FileDescriptor fd, SocketAddress *address, u32 *size, u32 flags) noexcept;


/// ( 42) Initiate a connection on a socket
Error connect(FileDescriptor fd, const SocketAddress *address, u32 size) noexcept;


/// ( 48) Shut down part of a full-duplex connection
void shutdown(FileDescriptor fd, u32 flags) noexcept;



























///
/// Process Management System Calls
///

Error clone();                    // ( 56) Create a child process
Error fork();                     // ( 57) Create a child process
Error vfork();                    // ( 58) Create a child process and block parent
Error execve();                   // ( 59) Execute program
Error execveat();                 // (322) Execute program relative to a directory file descriptor
Error exit();                     // ( 60) Terminate the calling process
Error exit_group();               // (231) Terminate all threads in a process
Error wait4();                    // ( 61) Wait for process to change state
Error waitid();                   // (247) Wait for process to change state
Error getpid();                   // ( 39) Get process ID
Error getppid();                  // (110) Get parent process ID
Error gettid();                   // (186) Get thread ID
Error setsid();                   // (112) Set session ID
Error getsid();                   // (124) Get session ID
Error setpgid();                  // (109) Set process group ID
Error getpgid();                  // (121) Get process group ID
Error getpgrp();                  // (111) Get the process group ID of the calling process
Error setuid();                   // (105) Set real user ID
Error getuid();                   // (102) Get real user ID
Error setgid();                   // (106) Set real group ID
Error getgid();                   // (104) Get real group ID
Error setresuid();                // (117) Set real, effective and saved user IDs
Error getresuid();                // (118) Get real, effective and saved user IDs
Error setresgid();                // (119) Set real, effective and saved group IDs
Error getresgid();                // (120) Get real, effective and saved group IDs
Error setreuid();                 // (113) Set real and/or effective user ID
Error setregid();                 // (114) Set real and/or effective group ID
Error setfsuid();                 // (122) Set user ID used for file system checks
Error setfsgid();                 // (123) Set group ID used for file system checks
Error geteuid();                  // (107) Get effective user ID
Error getegid();                  // (108) Get effective group ID
Error setgroups();                // (116) Set list of supplementary group IDs
Error getgroups();                // (115) Get list of supplementary group IDs
Error setns();                    // (308) Reassociate thread with a namespace
Error setrlimit();                // (160) Set resource limits
Error getrlimit();                // ( 97) Get resource limits
Error prlimit();                  // (302) Set and get the resource limits of an arbitrary process
Error getrusage();                // ( 98) Get resource usage
Error sched_setattr();            // (314) Set scheduling policy and attributes
Error sched_getattr();            // (315) Get scheduling policy and attributes
Error sched_setscheduler();       // (144) Set scheduling policy/parameters
Error sched_getscheduler();       // (145) Get scheduling policy/parameters
Error sched_setparam();           // (142) Set scheduling parameters
Error sched_getparam();           // (143) Get scheduling parameters
Error sched_setaffinity();        // (203) Set a process's CPU affinity mask
Error sched_getaffinity();        // (204) Get a process's CPU affinity mask
Error sched_get_priority_max();   // (146) Get static priority range (max value)
Error sched_get_priority_min();   // (147) Get static priority range (min value)
Error sched_rr_get_interval();    // (148) Get the SCHED_RR interval for the named process
Error sched_yield();              // ( 24) Yield the processor
Error setpriority();              // (141) Set program scheduling priority
Error getpriority();              // (140) Get program scheduling priority
Error ioprio_set();               // (251) Set I/O scheduling class and priority
Error ioprio_get();               // (252) Get I/O scheduling class and priority
Error brk();                      // ( 12) Change data segment size
Error mmap();                     // (  9) Map files or devices into memory
Error munmap();                   // ( 11) Unmap files or devices into memory
Error mremap();                   // ( 25) Remap a virtual memory address
Error mprotect();                 // ( 10) Set protection on a region of memory
Error madvise();                  // ( 28) Give advice about use of memory
Error mlock();                    // (149) Lock part of the calling process's virtual address space into RAM
Error mlock2();                   // (325) Lock part of the calling process's virtual address space into RAM
Error mlockall();                 // (151) Lock all of the calling process's virtual address space into RAM
Error munlock();                  // (150) Unlock part of the calling process's virtual address space into RAM
Error munlockall();               // (152) Unlock all of the calling process's virtual address space into RAM
Error mincore();                  // ( 27) Determine whether pages are resident in memory
Error membarrier();               // (324) Issue memory barriers on a set of threads
Error modify_ldt();               // (154) Reads or writes the local descriptor table (ldt) for a process
Error capset();                   // (126) Set capabilities of thread(s)
Error capget();                   // (125) Get capabilities of thread(s)
Error set_thread_area();          // (205) Set a thread local storage (TLS) area
Error get_thread_area();          // (211) Get a thread-local storage (TLS) area
Error set_tid_address();          // (218) Set pointer to thread ID
Error arch_prctl();               // (158) Set architecture-specific thread state
Error uselib();                   // (134) Load shared library
Error prctl();                    // (157) Operations on a process
Error seccomp();                  // (317) Operate on Secure Computing state of the process
Error ptrace();                   // (101) Process trace
Error process_vm_readv();         // (310) Transfers data from the remote process to the local process
Error process_vm_writev();        // (311) Transfers data from the local process to the remote process
Error kcmp();                     // (312) Compare two processes to determine if they share a kernel resource
Error unshare();                  // (272) Disassociate parts of the process execution context



///
/// Time
///


Error time();             // (201) Get time in seconds
Error settimeofday();     // (164) Set time
Error gettimeofday();     // ( 96) Get time
Error clock_settime();    // (227) Set the time of the specified clock
Error clock_gettime();    // (228) Get the time of the specified clock
Error clock_getres();     // (229) Get resolution of the specified clock
Error clock_adjtime();    // (305) Tune the specified clock
Error clock_nanosleep();  // (230) Do high-resolution sleep using the specified clock
Error timer_create();     // (222) Create a POSIX per-process timer
Error timer_delete();     // (226) Delete a POSIX per-process timer
Error timer_settime();    // (223) Arm/disarm POSIX per-process timer
Error timer_gettime();    // (224) Fetch state of POSIX per-process timer
Error timer_getoverrun(); // (225) Get overrun count for a POSIX per-process timer
Error alarm();            // ( 37) Set an alarm clock for delivery of a signal
Error setitimer();        // ( 38) Set value of an interval timer
Error getitimer();        // ( 36) Get value of an interval timer
Error timerfd_create();   // (283) Creates a new file descriptors based timer object
Error timerfd_settime();  // (286) Arm/disarm the timer referred to by the file descriptor
Error timerfd_gettime();  // (287) Get current setting of the timer referred to by the file descriptor
Error adjtimex();         // (159) Tune kernel clock
Error nanosleep();        // ( 35) High-resolution sleep
Error times();            // (100) Get process times


}
