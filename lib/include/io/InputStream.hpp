#pragma once

#include <core/StringView.hpp>
#include <core/Function.hpp>


/// InputStream
///
/// A readable object must expose an interface for reading a sequence of elements.
///
/// Read operations may store data at addresses or directly into String objects.
///
/// There are three types of primary read operations:
/// - read() - Consume and store.
/// - peek() - Read without consuming.
/// - skip() - Read without storing.
///
/// There are two secondary read operations:
/// - _until() - Read until a matching element is read or the maximum number of elements have been
///     read.
/// - _while() - Read while the elements match a given element or the maximum number of elements
///     have been read.
template<class T>
class InputStream {
public:
    struct VTable {
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


    constexpr
    InputStream(void *inst, const VTable &vtable) noexcept : _inst(inst), _vtable(vtable) {}


    ///
    /// Properties
    ///


    /// @brief Get the number of elements available to be read immediately.
    /// @return The number of elements available to be read
    u32 size() const noexcept {
        return _vtable.size(_inst);
    }


    /// @brief Return true if no elements are available to be read.
    /// @return true if no elements are available to be read
    bool is_empty() const noexcept {
        return _vtable.is_empty(_inst);
    }


    ///
    /// Methods
    ///


    /// @brief Clear all readable elements.
    void clear() noexcept {
        return _vtable.clear(_inst);
    }


    ///
    /// Read Methods
    ///


    u32 read(Slice<T> data) noexcept {
        return _vtable.read(_inst, data);
    }


    /// @brief Read a sequence of elements.
    /// @param buffer The buffer into which to read
    /// @param size The number of elements to read
    /// @return The number of elements read
    u32 read(T *data, u32 size = 1) noexcept {
        return read(Slice<T>(data, size));
    }







    /// @brief Read a sequence of elements until either a match is found or the buffer is full.
    /// @param buffer The buffer into which to read
    /// @param size The number of elements to read
    /// @param match The element after which to stop reading
    /// @return The number of elements read
    u32 read_until(T *buffer, u32 size, const T &match) {
        u32 n = 0;

        while (n < size && peek(&buffer[n]) > 0 && buffer[n] != match) {
            skip();
            n += 1;
        }

        return n;
    }


    /// @brief Read a sequence of elements until either a match is found or the buffer is full.
    /// @param buffer The buffer into which to read
    /// @param size The number of elements to read
    /// @param match The element after which to stop reading
    /// @return The number of elements read
    u32 read_while(T *buffer, u32 size, const T &match) {
        u32 n = 0;

        while (n < size && peek(&buffer[n]) > 0 && buffer[n] == match) {
            skip();
            n += 1;
        }

        return n;
    }


    ///
    /// Peek Methods
    ///


    /// @brief Read a sequence of elements without consuming it.
    /// @param buffer The buffer into which to read
    /// @param size The number of elements to read
    /// @return The number of elements read
    u32 peek(Slice<T> data) const {
        return _vtable.peek(_inst, data);
    }


    /// @brief Read a sequence of elements without consuming it.
    /// @param buffer The buffer into which to read
    /// @param size The number of elements to read
    /// @return The number of elements read
    u32 peek(T *buffer, u32 size = 1) const {
        return peek(Slice<T>(buffer, size));
    }


    /// @brief Read a sequence of elements without consuming it until either a match is found or
    /// the buffer is full.
    /// @param buffer The buffer into which to read
    /// @param size The number of elements to read
    /// @param match The element after which to stop reading
    /// @return The number of elements read
    u32 peek_until(T *buffer, u32 size, const T &match) const {

    }


    /// @brief Read a sequence of elements without consuming it until either a match is found or
    /// the buffer is full.
    /// @param buffer The buffer into which to read
    /// @param size The number of elements to read
    /// @param match The element after which to stop reading
    /// @return The number of elements read
    u32 peek_while(T *buffer, u32 size, const T &match) const {

    }


    ///
    /// Skip Methods
    ///


    /// @brief Read a sequence of elements without storing it.
    /// @param size The number of elements to read
    /// @return The number of elements read
    u32 skip(u32 size = 1) {
        return _vtable.skip(_inst, size);
    }


    /// @brief Read a sequence of elements without storing it until either a match is found or the
    /// buffer is full.
    /// @param size The number of elements to read
    /// @param match The element after which to stop reading
    /// @return The number of elements read
    u32 skip_until(u32 size, const T &match) {
        T buffer;
        u32 n = 0;

        while (n < size && peek(&buffer) > 0 && buffer != match) {
            skip();
            n += 1;
        }

        return n;
    }


    /// @brief Read a sequence of elements without storing it until either a match is found or the
    /// buffer is full.
    /// @param size The number of elements to read
    /// @param match The element after which to stop reading
    /// @return The number of elements read
    u32 skip_while(u32 size, const T &match) {
        T buffer;
        u32 n = 0;

        while (n < size && peek(&buffer) > 0 && buffer == match) {
            skip();
            n += 1;
        }

        return n;
    }
};
