#include <core/StringView.hpp>


namespace UTF_8 {


    constexpr
    u32 size(u8 ch) {
        if ((ch & 0x80u) == 0x00u) {
            return 1;
        }

        if ((ch & 0xE0u) == 0xC0u) {
            return 2;
        }

        if ((ch & 0xF0u) == 0xE0u) {
            return 3;
        }

        if ((ch & 0xF8u) == 0xF0u) {
            return 4;
        }

        return 0;
    }
}
