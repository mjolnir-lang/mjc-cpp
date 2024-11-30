#pragma once

#include <core/Enum.hpp>


template<class FilePermission>
struct FilePermissionValues {
    static constexpr FilePermission NONE{0};
    static constexpr FilePermission ALL{0777};

    static constexpr FilePermission OWNER_READ{0400};
    static constexpr FilePermission OWNER_WRITE{0200};
    static constexpr FilePermission OWNER_EXECUTE{0100};
    static constexpr FilePermission OWNER_ALL{0700};

    static constexpr FilePermission GROUP_READ{0040};
    static constexpr FilePermission GROUP_WRITE{0020};
    static constexpr FilePermission GROUP_EXECUTE{0010};
    static constexpr FilePermission GROUP_ALL{0070};

    static constexpr FilePermission OTHER_READ{0040};
    static constexpr FilePermission OTHER_WRITE{0020};
    static constexpr FilePermission OTHER_EXECUTE{0010};
    static constexpr FilePermission OTHER_ALL{0070};

    static constexpr FilePermission U___{0000};
    static constexpr FilePermission U__X{0100};
    static constexpr FilePermission U_W_{0200};
    static constexpr FilePermission U_WX{0300};
    static constexpr FilePermission UR__{0400};
    static constexpr FilePermission UR_X{0500};
    static constexpr FilePermission URW_{0600};
    static constexpr FilePermission URWX{0700};

    static constexpr FilePermission G___{0000};
    static constexpr FilePermission G__X{0010};
    static constexpr FilePermission G_W_{0020};
    static constexpr FilePermission G_WX{0030};
    static constexpr FilePermission GR__{0040};
    static constexpr FilePermission GR_X{0050};
    static constexpr FilePermission GRW_{0060};
    static constexpr FilePermission GRWX{0070};

    static constexpr FilePermission O___{0000};
    static constexpr FilePermission O__X{0001};
    static constexpr FilePermission O_W_{0002};
    static constexpr FilePermission O_WX{0003};
    static constexpr FilePermission OR__{0004};
    static constexpr FilePermission OR_X{0005};
    static constexpr FilePermission ORW_{0006};
    static constexpr FilePermission ORWX{0007};
};


struct FilePermission : public Enum<u8>, public FilePermissionValues<FilePermission> {

    constexpr
    explicit
    FilePermission(u8 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    constexpr
    bool has(FilePermission bits) const noexcept {
        return (_id & bits) == bits;
    }
};
