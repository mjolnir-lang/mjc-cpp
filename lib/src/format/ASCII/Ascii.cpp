#include <format/ASCII/Ascii.hpp>


Error Ascii::parse_digit(u8 ch, u8 &digit, u32 base) noexcept {
    if (ch - '0' < 10) {
        digit = ch - '0';
        return Error::SUCCESS;
    }

    if ((ch | 0x20u) - ('a' - 10) < base) {
        digit = (ch | 0x20u) - ('a' - 10);
        return Error::SUCCESS;
    }

    return Error::FAILURE;
}
