#pragma once

#include <io/InputStream.hpp>
#include <io/OutputStream.hpp>


template<class T>
class Stream {
public:
    struct VTable {
        Function<u32(const void *)> space;
        Function<bool(const void *)> is_full;
        Function<void(void *)> flush;
        Function<u32(void *, Slice<const T>)> write;
        Function<u32(const void *)> size;
        Function<bool(const void *)> is_empty;
        Function<void(const void *)> clear;
        Function<u32(void *, Slice<T>)> read;
        Function<u32(void *, Slice<T>)> peek;
        Function<u32(void *, u32)> skip;
    };
private:
    void *_inst;
    const VTable &_vtable;
public:


    ///
    /// Constructors
    ///


    constexpr
    Stream(void *inst, const VTable &vtable) noexcept : _inst(inst), _vtable(vtable) {}


    ///
    /// Type Casts
    ///


    constexpr
    operator const InputStream<T>() const noexcept {
        return InputStream<T>(const_cast<Stream<T> *>(this), _vtable_input_stream);
    }


    constexpr
    operator InputStream<T>() noexcept {
        return InputStream<T>(this, _vtable_input_stream);
    }


    constexpr
    operator const OutputStream<T>() const noexcept {
        return OutputStream<T>(const_cast<Stream<T> *>(this), _vtable_output_stream);
    }


    constexpr
    operator OutputStream<T>() noexcept {
        return OutputStream<T>(this, _vtable_output_stream);
    }


    ///
    /// Properties
    ///


    /// @brief Get the number of elements available to be written.
    /// @return The number of elements available to be written
    u32 space() const noexcept {
        return _vtable.space(_inst);
    }


    /// @brief Get the number of elements able to be written.
    /// @return The number of elements able to be written
    bool is_full() const noexcept {
        return _vtable.is_full(_inst);
    }


    ///
    /// Methods
    ///


    /// @brief Write all pending data.
    void flush() noexcept {
        return _vtable.flush(_inst);
    }


    /// @brief Begin writing a sequence of elements.
    /// @param data The elements to write
    /// @return The number of elements written
    u32 write(Slice<const T> data) noexcept {
        return _vtable.write(_inst, data);
    }


    /// @brief Begin writing a sequence of elements.
    /// @param data The elements to write
    /// @param size The number of elements to write
    /// @return The number of elements written
    u32 write(const T *data, u32 size = 1) noexcept {
        return write(Slice<const T>(data, size));
    }


    /// @brief Write a sequence of bytes.
    /// @param data The bytes to write
    /// @param size The number of bytes to write
    /// @return The number of bytes written
    u32 write(const u8 *data, u32 size = 1) noexcept {
        return write(Slice<const u8>(data, size));
    }


    /// @brief Write a byte.
    /// @param ch The byte to write
    /// @return The number of bytes written
    u32 write(u8 ch) noexcept {
        return write(&ch);
    }


    /// @brief Write a string.
    /// @param string The string to write
    /// @return The number of characters written
    u32 write(StringView string) noexcept {
        return write(string.data(), string.size());
    }


    /// @brief Write a string up to the number of characters.
    /// @param string The string to write
    /// @param size The number of characters to write
    /// @return The number of characters written
    u32 write(StringView string, u32 size) noexcept {
        return write(string.data(), std::min(string.size(), size));
    }


    /// @brief Write a byte repeatedly.
    /// @param ch The byte to write
    /// @return The number of bytes written
    u32 fill(u8 ch, u32 size) noexcept {
        for (u32 i = 0; i < size; ++i) {
            write(&ch);
        }

        return size;
    }


    ///
    /// Printing Methods
    ///


    /// @brief Print multiple values to the string using a format string.
    /// @param format The format string
    /// @param ... The format arguments
    /// @return The number of characters printed
    template<class... Args>
    u32 print(StringView format, Args &&... args) noexcept {
        return vprint(format, {PrintArg(args)...});
    }


    /// @brief Print multiple values to the end of the string using a format string.
    /// @param format The format string
    /// @param args The format arguments
    /// @return The number of characters printed
    u32 vprint(StringView format, std::initializer_list<PrintArg> args) noexcept;


    u32 print_char(u8 ch, u8 repeat_count, u32 width, u8 align, u8 fill_character = ' ') noexcept;


    u32 print_string(StringView string, u32 width, u8 align, u8 fill_character = ' ') noexcept;


    u32 print_u32(const PrintFormat &format, u32 value, bool is_negative = false) noexcept;


    u32 print_u64(const PrintFormat &format, u64 value, bool is_negative = false) noexcept;


    u32 print_i32(const PrintFormat &format, i32 value) noexcept {
        return print_u32(format, static_cast<u32>(value), value < 0);
    }


    u32 print_i64(const PrintFormat &format, i64 value) noexcept {
        return print_u64(format, static_cast<u64>(value), value < 0);
    }


    u32 print_f32(const PrintFormat &format, f32 value) noexcept;


    u32 print_f64(const PrintFormat &format, f64 value) noexcept;
private:


    static
    const typename InputStream<T>::VTable _vtable_input_stream;

    static
    const typename OutputStream<T>::VTable _vtable_output_stream;
};


template<class T>
inline
const typename InputStream<T>::VTable Stream<T>::_vtable_input_stream{
    .space{&Stream<T>::space},
    .is_full{[](const void *) { return false; }},
    .flush{[](void *) {}},
    .write{[](void *inst, Slice<const T> data) {
        reinterpret_cast<Stream<T> *>(inst)->append(data);
        return data.size();
    }},
};


template<class T>
inline
const typename OutputStream<T>::VTable Stream<T>::_vtable_output_stream{
    .space{&Stream<T>::space},
    .is_full{[](const void *) { return false; }},
    .flush{[](void *) {}},
    .write{[](void *inst, Slice<const T> data) {
        reinterpret_cast<Stream<T> *>(inst)->append(data);
        return data.size();
    }},
};
