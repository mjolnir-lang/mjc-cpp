#include <core/String.hpp>


template<>
Error Printer<StringView>::print(StringPrinter &out) noexcept {
    return Printable(StringView(out.arg<String>())).print(out);
}
