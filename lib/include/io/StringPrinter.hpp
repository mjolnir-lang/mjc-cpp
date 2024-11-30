#pragma once

#include <io/internal/StringPrinterFormatOptions.hpp>
#include <io/internal/Printable.hpp>


template<class T>
class OutputStream;


class StringPrinter {
private:
    OutputStream<u8> &_output_stream;
    StringView _format_string;
    Slice<Printable> _args;
    StringPrinterFormatOptions _format;
    u32 _next_index = 0;
    u32 _bytes_written = 0;
public:


    ///
    /// Constructors
    ///


    constexpr
    StringPrinter(
        OutputStream<u8> &output_stream,
        StringView format_string,
        Slice<Printable> args
    ) noexcept :
        _output_stream(output_stream),
        _format_string(format_string),
        _args(args)
    {}


    ///
    /// Properties
    ///


    template<class T>
    const T &arg() const noexcept {
        return _args[_next_index].value<T>();
    }


    Slice<const Printable> args() const noexcept {
        return _args;
    }


    const StringPrinterFormatOptions &format() const noexcept {
        return _format;
    }


    u32 next_index() const noexcept {
        return _next_index;
    }


    ///
    /// Methods
    ///


    u32 print() noexcept;


    /// @brief Write all pending data.
    void flush() noexcept;


    /// @brief Begin writing a sequence of elements.
    /// @param data The elements to write
    /// @return 
    Error write(Slice<const u8> data) noexcept;


    /// @brief Write a sequence of bytes.
    /// @param data The bytes to write
    /// @param size The number of bytes to write
    /// @return 
    Error write(const u8 *data, u32 size = 1) noexcept {
        return write(Slice<const u8>(data, size));
    }


    /// @brief Write a byte.
    /// @param ch The byte to write
    /// @return 
    Error write(u8 ch) noexcept {
        return write(&ch);
    }


    /// @brief Write a string.
    /// @param string The string to write
    /// @return 
    Error write(StringView string) noexcept {
        return write(string.data(), string.size());
    }


    /// @brief Write a string up to the number of characters.
    /// @param string The string to write
    /// @param size The number of characters to write
    /// @return 
    Error write(StringView string, u32 size) noexcept {
        return write(string.data(), std::min(string.size(), size));
    }


    /// @brief Write a byte repeatedly.
    /// @param ch The byte to write
    /// @return 
    Error fill(u8 ch, u32 size) noexcept;


    /// @brief Print multiple values to the string using a format string.
    /// @param format The format string
    /// @param ... The format arguments
    /// @return 
    template<class... Args>
    Error print(StringView format, Args &&... args) noexcept {
        return vprint(format, {Printable(args)...});
    }


    Error vprint(StringView format, Slice<Printable> args) noexcept;


    Error print_char(u8 ch, u8 repeat_count, u32 width, u8 align, u8 fill_character = ' ') noexcept;


    Error print_string(StringView string, u32 width, u8 align, u8 fill_character = ' ') noexcept;


    Error print_u32(u32 value, bool is_negative = false) noexcept;


    Error print_u64(u64 value, bool is_negative = false) noexcept;


    Error print_i32(i32 value) noexcept {
        return print_u32(value < 0 ? -value : value, value < 0);
    }


    Error print_i64(i64 value) noexcept {
        return print_u64(value < 0 ? -value : value, value < 0);
    }


    Error print_f32(f32 value) noexcept;


    Error print_f64(f64 value) noexcept;
private:


    Error parse_format_options() noexcept;
};


template<class T>
struct Printer<Slice<T>> {

    static
    Error print(StringPrinter &out) noexcept {
        Slice<const T> slice = out.arg<Slice<const T>>();

        // Print metadata.
        if (out.format().has_alternate) {
            if (out.print("Slice<{}> ({})", Type::name<T>(), slice.size()).is_failure()) {
                return Error::FAILURE;
            }
        }

        if (out.write('[').is_failure()) {
            return Error::FAILURE;
        }

        for (u32 i = 0; i < slice.size();) {
            if (Printer<T>::print(out, out.format().extra, slice[i]).is_failure()) {
                return Error::FAILURE;
            }

            if (++i < slice.size() && out.write(", ").is_failure()) {
                return Error::FAILURE;
            }
        }

        return out.write(']');
    }
};
