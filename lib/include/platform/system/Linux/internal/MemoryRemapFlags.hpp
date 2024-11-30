#pragma once

#include <core/Enum.hpp>

namespace platform::system::Linux::internal {


static constexpr u32 MAP_HUGE_SHIFT = 26;
static constexpr u32 MAP_HUGE_2MB = 21 << MAP_HUGE_SHIFT;
static constexpr u32 MAP_HUGE_1GB = 30 << MAP_HUGE_SHIFT;

static constexpr void *MAP_FAILED = (void *) -1;


template<class MemoryRemapFlags>
struct MemoryRemapFlagsValues {
    static constexpr MemoryRemapFlags MAYMOVE{1 << 0};
    static constexpr MemoryRemapFlags FIXED{1 << 1};
    static constexpr MemoryRemapFlags DONTUNMAP{1 << 2};
};


struct MemoryRemapFlags : public Enum<u8>, public MemoryRemapFlagsValues<MemoryRemapFlags> {

    constexpr
    explicit
    MemoryRemapFlags(u8 id) noexcept : Enum(id) {}
};


}
