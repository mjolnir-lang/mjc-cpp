#pragma once

#include <core/Enum.hpp>


namespace platform {
namespace system {
inline namespace Linux {
inline namespace internal {


template<class PermissionFlags>
struct PermissionFlagsValues {
    static constexpr PermissionFlags IXOTH{1}; // others have execute permission
    static constexpr PermissionFlags IWOTH{2}; // others have write permission
    static constexpr PermissionFlags IROTH{4}; // others have read permission
    static constexpr PermissionFlags IRWXO{7}; // others have read, write, and execute permission
    static constexpr PermissionFlags IXGRP{8}; // group has execute permission
    static constexpr PermissionFlags IWGRP{16}; // group has write permission
    static constexpr PermissionFlags IRGRP{32}; // group has read permission
    static constexpr PermissionFlags IXUSR{64}; // user has execute permission
    static constexpr PermissionFlags IRWXG{56}; // group has read, write, and execute permission
    static constexpr PermissionFlags IWUSR{128}; // user has write permission
    static constexpr PermissionFlags IRUSR{256}; // user has read permission
    static constexpr PermissionFlags IRWXU{448}; // user (file owner) has read, write, and execute permission
    static constexpr PermissionFlags ISVTX{512}; // sticky bit
    static constexpr PermissionFlags ISGID{1024}; // set-group-ID bit
    static constexpr PermissionFlags ISUID{2048}; // set-user-ID bit
};


struct PermissionFlags : public Enum<u8>, public PermissionFlagsValues<PermissionFlags> {

    constexpr
    explicit
    PermissionFlags(u8 id) noexcept : Enum(id) {}
};


}
}
}
}
