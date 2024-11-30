#pragma once

#include <core/Common.hpp>
#include <string>

using String = std::basic_string<u8>;


/*
#include <container/Vector.hpp>


class String {
private:
    Vector<u8> _data;
public:


    ///
    /// Constructors
    ///


    constexpr
    String() noexcept {}


    /// @brief Create an empty string.
    /// @param null The nullptr argument
    constexpr
    String(std::nullptr_t) noexcept {}


    /// @brief Create a string from a byte sequence.
    /// @param data The byte sequence to copy
    String(std::initializer_list<u8> data) noexcept : _data(data) {}


    /// @brief Create a string from a byte sequence.
    /// @param data The byte sequence to copy
    /// @param size The number of characters to copy
    String(const u8 *data, u32 size) noexcept : _data(data, size) {}


    /// @brief Create a string from a byte sequence.
    /// @param data The byte sequence to copy
    String(StringView data) noexcept : _data(data.data(), data.size()) {}


    /// @brief Create a String from a byte array.
    /// @param data The C string to copy
    /// @param size The size of the string
    String(StringView data, u32 size) noexcept : _data(data, size) {}


    /// @brief Create a string from another string.
    /// @param other The string to copy
    explicit
    String(u32 size, u8 ch = 0) noexcept : _data(size, ch) {}


    constexpr
    String(Vector<u8> &&vector) noexcept : _data(std::move(vector)) {}


    //String(const Vector<u8> &vector) noexcept : _data(vector) {}


    ///
    /// Type Casts
    ///


    constexpr
    operator const OutputStream<u8>() const noexcept {
        return _data;
    }


    constexpr
    operator OutputStream<u8>() noexcept {
        return _data;
    }


    operator Vector<u8>() && noexcept {
        return std::move(_data);
    }


    constexpr
    operator StringView() const noexcept {
        return _data.slice();
    }


    constexpr
    operator Slice<const u8>() const noexcept {
        return _data;
    }


    constexpr
    operator Slice<u8>() noexcept {
        return _data;
    }


    constexpr
    operator const u8 *() const noexcept {
        return _data;
    }


    constexpr
    operator u8 *() noexcept {
        return _data;
    }


    ///
    /// Operator Overloads
    ///


    /// @brief Access the first character of the string.
    constexpr
    const u8 &operator*() const noexcept {
        return *_data;
    }


    /// @brief Access the first character of the string.
    constexpr
    u8 &operator*() noexcept {
        return *_data;
    }


    /// @brief Access a character of the string by index.
    /// @param index The index of the character
    constexpr
    const u8 &operator[](u32 index) const noexcept {
        return _data[index];
    }


    /// @brief Access a character of the string by index.
    /// @param index The index of the character
    constexpr
    u8 &operator[](u32 index) noexcept {
        return _data[index];
    }


    ///
    /// Properties
    ///


    /// @brief Return a pointer to the string data.
    const char *c_str() noexcept {
        if (_data[_data.size() - 1] != 0) {
            _data.append(0);
        }

        return reinterpret_cast<char *>(_data.data());
    }


    /// @brief Return a pointer to the string data.
    constexpr
    const u8 *data() const noexcept {
        return _data.data();
    }


    /// @brief Return a pointer to the string data.
    constexpr
    u8 *data() noexcept {
        return _data.data();
    }


    /// @brief Return the available space in the string data.
    constexpr
    u32 space() const noexcept {
        return _data.space();
    }


    /// @brief Return the size of the string data.
    constexpr
    u32 size() const noexcept {
        return _data.size();
    }


    /// @brief Return the size of the allocated space for the string data.
    constexpr
    u32 capacity() const noexcept {
        return _data.capacity();
    }


    /// @brief Return true if the string is empty.
    constexpr
    bool is_empty() const noexcept {
        return _data.is_empty();
    }


    ///
    /// Constant Methods
    ///


    /// @brief Return a slice of the whole string.
    StringView slice() const noexcept {
        return _data.slice();
    }


    /// @brief Return a slice of the string.
    /// @param start The index of the first character
    StringView slice(u32 start) const noexcept {
        return _data.slice(start);
    }


    /// @brief Return a slice of the string.
    /// @param start The index of the first character
    /// @param end The index after the last character
    StringView slice(u32 start, u32 end) const noexcept {
        return _data.slice(start, end);
    }


    /// @brief Test if the strings are equal.
    /// @param other The second string
    /// @return true if the strings are equal
    bool is_equal(StringView other) const noexcept {
        return _data.is_equal(other);
    }


    /// @brief Test if the strings are equal up to the maximum number of
    /// characters.
    /// @param other The second string
    /// @return true if the strings are equal
    bool is_equal(const u8 *data, u32 size) const noexcept {
        return _data.is_equal(data, size);
    }


    /// @brief Compare the first string with the second string.
    /// @param other The second string
    /// @return 0 if the strings are equal, positive if the first string is
    /// greater than the second string, and negative if the first string is
    /// less than the second string
    i32 compare(StringView other) const noexcept {
        return _data.compare(other);
    }


    /// @brief Compare the first string with the second string up to the
    /// maximum number of characters.
    /// @param other The second string
    /// @return 0 if the strings are equal, positive if the first string is
    /// greater than the second string, and negative if the first string is
    /// less than the second string
    i32 compare(const u8 *data, u32 size) const noexcept {
        return _data.compare(data, size);
    }


    ///
    /// Index Of
    ///


    /// @brief Return the index of the first matching character in the string
    /// or the size of the string if no matching character was found.
    /// @param ch The character for which to search
    constexpr
    Result<u32> index_of_first(u8 ch) const noexcept {
        return _data.index_of_first(ch);
    }


    /// @brief Return the index of the first matching substring in the string
    /// or nullptr if one could not be found.
    /// @param substring The substring for which to search
    /// @return The index of the first matching substring or just past the end of this string.
    constexpr
    Result<u32> index_of_first(StringView substring) const noexcept {
        return _data.index_of_first(substring);
    }


    /// @brief Return the index of the first matching substring in the string
    /// or nullptr if one could not be found.
    /// @param substring The substring for which to search
    /// @return The index of the first matching substring or just past the end of this string.
    constexpr
    Result<u32> index_of_first(const u8 *substring, u32 size) const noexcept {
        return index_of_first(StringView(substring, size));
    }


    /// @brief Return the index of the last matching character in the string
    /// or U32_MAX if one could not be found.
    /// @param ch The character for which to search
    /// @return The pointer to the last matching character or nullptr
    constexpr
    Result<u32> index_of_last(u8 ch) const noexcept {
        return _data.index_of_last(ch);
    }


    /// @brief Return the index of the last matching substring in the string
    /// or U32_MAX if one could not be found.
    /// @param substring The substring for which to search
    /// @return The pointer to the last matching substring or nullptr
    constexpr
    Result<u32> index_of_last(StringView substring) const noexcept {
        return _data.index_of_last(substring);
    }


    /// @brief Return the index of the last matching substring in the string
    /// or U32_MAX if one could not be found.
    /// @param substring The substring for which to search
    /// @return The pointer to the last matching substring or nullptr
    constexpr
    Result<u32> index_of_last(const u8 *substring, u32 size) const noexcept {
        return _data.index_of_last(substring, size);
    }


    ///
    /// Find
    ///


    /// @brief Return the index of the first matching character in the string
    /// or the size of the string if no matching character was found.
    /// @param ch The character for which to search
    constexpr
    const u8 *find_first(u8 ch) const noexcept {
        return _data.find_first(ch);
    }


    /// @brief Return the index of the first matching substring in the string
    /// or nullptr if one could not be found.
    /// @param substring The substring for which to search
    /// @return The index of the first matching substring or just past the end of this string.
    constexpr
    StringView find_first(StringView substring) const noexcept {
        return _data.find_first(substring);
    }


    /// @brief Return the index of the first matching substring in the string
    /// or nullptr if one could not be found.
    /// @param substring The substring for which to search
    /// @return The index of the first matching substring or just past the end of this string.
    constexpr
    StringView find_first(const u8 *substring, u32 size) const noexcept {
        return find_first(StringView(substring, size));
    }


    /// @brief Return the index of the last matching character in the string
    /// or U32_MAX if one could not be found.
    /// @param ch The character for which to search
    /// @return The pointer to the last matching character or nullptr
    constexpr
    const u8 *find_last(u8 ch) const noexcept {
        return _data.find_last(ch);
    }


    /// @brief Return the index of the last matching substring in the string
    /// or U32_MAX if one could not be found.
    /// @param substring The substring for which to search
    /// @return The pointer to the last matching substring or nullptr
    constexpr
    StringView find_last(StringView substring) const noexcept {
        return _data.find_last(substring);
    }


    /// @brief Return the index of the last matching substring in the string
    /// or U32_MAX if one could not be found.
    /// @param substring The substring for which to search
    /// @return The pointer to the last matching substring or nullptr
    constexpr
    StringView find_last(const u8 *substring, u32 size) const noexcept {
        return _data.find_last(substring, size);
    }


    ///
    /// Mutable Methods
    ///


    /// @brief Clear the string.
    void clear() noexcept {
        _data.clear();
    }


    /// @brief Resize the string.
    /// This may invalidate all references to the string data.
    /// @param size The requested size
    /// @param ch The fill character
    void resize(u32 size, u8 ch = 0) noexcept {
        _data.resize(size, ch);
    }


    /// @brief Increase or reduce the size of the string data allocated.
    /// This may invalidate all references to the string data.
    /// @param size The requested allocated capacity
    void reserve(u32 size) noexcept {
        _data.reserve(size);
    }


    /// @brief Reduce the allocated capacity to the string size.
    void trim() noexcept {
        _data.trim();
    }


    /// @brief Append a character to the end of the string repeatedly.
    /// This may invalidate all references to the string data.
    /// @param ch The character to append
    void append(u8 ch) noexcept {
        _data.append(ch);
    }


    /// @brief Append a byte sequence to the end of the string.
    /// This may invalidate all references to the string data.
    /// @param data The byte sequence to append
    /// @param size The number of bytes to append
    void append(const u8 *data, u32 size) noexcept {
        _data.append(data, size);
    }


    /// @brief Append a string to the end of the string.
    /// This may invalidate all references to the string data.
    /// @param data The string to append
    void append(StringView data) noexcept {
        _data.append(data);
    }


    /// @brief Insert a character into the string at an arbitrary index.
    /// This may invalidate all references to the string data.
    /// @param index The index at which to insert
    /// @param ch The character to insert
    void insert(u32 index, u8 ch) noexcept {
        _data.insert(index, ch);
    }


    /// @brief Insert a byte sequence into the string at an arbitrary index.
    /// This may invalidate all references to the string data.
    /// @param index The index at which to insert
    /// @param data The byte sequence to insert
    /// @param size The number of characters to insert
    void insert(u32 index, const u8 *data, u32 size) noexcept {
        _data.insert(index, data, size);
    }


    /// @brief Insert a string into the string at an arbitrary index.
    /// This may invalidate all references to the string data.
    /// @param index The index at which to insert
    /// @param data The string to insert
    void insert(u32 index, StringView data) noexcept {
        _data.insert(index, data);
    }


    /// @brief Erase a range of characters from the string.
    /// @param index The index of the first character to erase
    /// @param size The number of characters to erase
    void remove(u32 index, u32 size = 1) noexcept {
        _data.remove(index, size);
    }


    ///
    /// Printing Methods
    ///


    Error printer(StringPrinter &out) const noexcept {
        return Error::SUCCESS;
    }


    ///
    /// Parsing Methods
    ///


    /// @brief Parse multiple values from the formattable object using a format string.
    /// @param format The format string
    /// @param ... The format arguments
    /// @return The number of format arguments parsed
    template<class... Args>
    u32 parse(StringView format, Args &&... args) const noexcept {
        return StringView(*this).parse(format, {Parsable(args)...});
    }


    /// @brief Parse a u64 value from a string accounting for numerical base prefixes and scientific
    /// representation.
    /// @param value The parsed value.
    /// @param base The numeric base to use.
    /// @return The number of bytes parsed on success, and 0 on failure.
    u32 parse_u64(u64 &value, u8 base = 0) const noexcept {
        return StringView(*this).parse_u64(value, base);
    }


    /// @brief Parse an i64 value from a string accounting for numerical base prefixes and scientific
    /// representation.
    /// @param value The parsed value.
    /// @param base The numeric base to use.
    /// @return The number of bytes parsed on success, and 0 on failure.
    u32 parse_i64(i64 &value, u8 base = 0) const noexcept {
        return StringView(*this).parse_i64(value, base);
    }


    /// @brief Parse an f64 value from a string accounting for numerical base prefixes and scientific
    /// representation.
    /// @param value The parsed value.
    /// @return The number of bytes parsed on success, and 0 on failure.
    u32 parse_f64(f64 &value) const noexcept {
        return StringView(*this).parse_f64(value);
    }
};
*/
