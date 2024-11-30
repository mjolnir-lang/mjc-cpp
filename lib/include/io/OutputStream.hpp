#pragma once

#include <io/StringPrinter.hpp>


/// @brief A stream endpoint which can be written to.
template<class T>
class OutputStream {
public:
    struct VTable {
        Function<u32(const void *)> space;
        Function<bool(const void *)> is_full;
        Function<void(void *)> flush;
        Function<u32(void *, Slice<const T>)> write;
    };
private:
    void *_inst;
    const VTable &_vtable;
public:


    constexpr
    OutputStream(void *inst, const VTable &vtable) noexcept : _inst(inst), _vtable(vtable) {}


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
};


/// `OutputStream<u8>` is a specialization of `OutputStream<T>` with additional methods for
/// consuming `String` and `u8` objects.
template<>
class OutputStream<u8> {
public:
    struct VTable {
        Function<u32(const void *)> space;
        Function<bool(const void *)> is_full;
        Function<void(void *)> flush;
        Function<u32(void *, Slice<const u8>)> write;
    };
private:
    void *_inst;
    const VTable &_vtable;
public:


    constexpr
    OutputStream(void *inst, const VTable &vtable) noexcept : _inst(inst), _vtable(vtable) {}


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
    u32 write(Slice<const u8> data) noexcept {
        return _vtable.write(_inst, data);
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
        return vprint(format, {Printable(args)...});
    }


    /// @brief Print multiple values to the end of the string using a format string.
    /// @param format The format string
    /// @param args The format arguments
    /// @return The number of characters printed
    u32 vprint(StringView format, Slice<Printable> args) noexcept {
        return StringPrinter(*this, format, args).print();
    }
};
