#pragma once

#include <core/Enum.hpp>


namespace platform {
namespace system {
inline namespace Linux {
inline namespace internal {


template<class SeekFlags>
struct SeekFlagsValues {
    static constexpr SeekFlags SET{0}; // offset is the absolute offset position in the file
    static constexpr SeekFlags CUR{1}; // offset is the current offset location plus offset
    static constexpr SeekFlags END{2}; // offset is the file size plus offset
    static constexpr SeekFlags DATA{3}; // set offset to next location greater or equal to offset that contains data
    static constexpr SeekFlags HOLE{4}; // set offset to next hole in file great or equal to offset
};


struct SeekFlags : public Enum<u8>, public SeekFlagsValues<SeekFlags> {

    constexpr
    explicit
    SeekFlags(u8 id) noexcept : Enum(id) {}
};


}
}
}
}
