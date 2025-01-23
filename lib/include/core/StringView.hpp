#pragma once

#include <core/Slice.hpp>
#include <format/ASCII/Ascii.hpp>


class Parsable;
class StringPrinter;
class StringParser;


/// @brief A value type which describes a constant contiguous sequence of bytes.
///
/// Functions which accept a string or byte sequence should implement the following overload signatures:
///
/// - func(StringView string);
/// - func(const u8 *data, u32 size);
/// - func(StringView string, u32 size); // for C++ string literals only...
///
class StringView {
private:
    Slice<const u8> _data;
public:


    ///
    /// Constructors
    ///


    /// @brief Create an empty StringView.
    constexpr
    StringView() noexcept {}


    /// @brief Create an empty StringView from a nullptr.
    constexpr
    StringView(std::nullptr_t) noexcept : _data(nullptr) {}


    /// @brief Create a slice from an initializer list.
    /// @param data The initializer list to reference.
    //constexpr
    //StringView(std::initializer_list<u8> data) noexcept : _data(data) {}


    /// @brief Create a StringView from an array.
    /// @param data The C string to copy
    template<u32 SIZE>
    constexpr
    StringView(const u8 (&data)[SIZE]) noexcept : _data(data, SIZE - 1) {}


    /// @brief Create a StringView from a byte array.
    /// @param data The C string to copy
    /// @param size The size of the string
    constexpr
    StringView(const u8 *data, u32 size) noexcept : _data(data, size) {}


    /// @brief Create a StringView from a slice.
    /// @param data The C string to copy
    /// @param size The size of the string
    constexpr
    StringView(Slice<const u8> data) noexcept : _data(data) {}


    /// @brief Create a StringView from a null-terminated, C-style, string.
    /// @param data The C string to copy
    static
    constexpr
    StringView from_c_str(const u8 *data) noexcept {
        return {data, Ascii::c_str_size(data)};
    }


    ///
    /// Type Casts
    ///


    constexpr
    operator Slice<const u8>() const noexcept {
        return _data;
    }


    constexpr
    operator const u8 *() const noexcept {
        return _data;
    }


    ///
    /// Operators
    ///


    /// @brief Access the first character of the string.
    constexpr
    const u8 &operator*() const noexcept {
        return *_data;
    }


    /// @brief Access a character of the string by index.
    /// @param i The index of the character
    constexpr
    const u8 &operator[](u32 index) const noexcept {
        return _data[index];
    }


    constexpr
    StringView &operator++() noexcept {
        ++_data;
        return *this;
    }


    constexpr
    StringView &operator--() noexcept {
        --_data;
        return *this;
    }


    constexpr
    StringView operator++(int) noexcept {
        return _data++;
    }


    constexpr
    StringView operator--(int) noexcept {
        return _data--;
    }


    /// @brief Increment reference.
    /// @param size The amount to increment
    constexpr
    void operator+=(u32 size) noexcept {
        _data += size;
    }


    /// @brief Increment reference.
    /// @param size The amount to increment
    constexpr
    void operator-=(u32 size) noexcept {
        _data -= size;
    }


    /// @brief Increment reference.
    /// @param size The amount to increment
    constexpr
    void operator>>=(u32 size) noexcept {
        _data >>= size;
    }


    /// @brief Increment reference.
    /// @param size The amount to increment
    constexpr
    void operator<<=(u32 size) noexcept {
        _data <<= size;
    }


    ///
    /// Properties
    ///


    /// @brief Get the equivalent C string.
    /// @return The C string
    constexpr
    const u8 *data() const noexcept {
        return _data.data();
    }


    /// @brief Get the string size.
    /// @return The size of the string
    constexpr
    u32 size() const noexcept {
        return _data.size();
    }


    /// @brief Return true if the string is empty.
    /// @return true if the string is empty
    constexpr
    bool is_empty() const noexcept {
        return _data.is_empty();
    }


    ///
    /// Constant Methods
    ///


    /// @brief Return a slice of the string from an index through the end of the string.
    /// @param index The index of the first character
    constexpr
    StringView slice(u32 start) const noexcept {
        return _data.tail(start);
    }


    /// @brief Return a slice of the string.
    /// @param index The index of the first character
    /// @param size The number of characters to copy
    constexpr
    StringView slice(u32 start, u32 end) const noexcept {
        return _data.slice(start, end);
    }




    /// @brief Return a reference to the elements from the beginning of the string to the given end
    /// index.
    /// @param end The index past the last element
    constexpr
    StringView head(u32 end) const noexcept {
        return slice(0, end);
    }


    /// @brief Return a reference to the elements from the given start index through the end of the
    /// slice.
    /// @param start The index of the first element
    constexpr
    StringView tail(u32 start) const noexcept {
        return slice(start, _data.size());
    }





    constexpr
    StringView shift_left(u32 offset) noexcept {
        return _data.shift_left(offset);
    }


    constexpr
    bool starts_with(u8 value) const noexcept {
        return _data.starts_with(value);
    }


    constexpr
    bool starts_with(StringView other) const noexcept {
        return _data.starts_with(other);
    }


    constexpr
    bool starts_with(const u8 *other, u32 size) const noexcept {
        return _data.starts_with(other, size);
    }


    constexpr
    bool ends_with(u8 value) const noexcept {
        return _data.ends_with(value);
    }


    constexpr
    bool ends_with(StringView other) const noexcept {
        return _data.ends_with(other);
    }


    constexpr
    bool ends_with(const u8 *other, u32 size) const noexcept {
        return _data.ends_with(other, size);
    }


    constexpr
    bool contains(u8 value) const noexcept {
        return _data.contains(value);
    }


    constexpr
    bool contains(StringView other) const noexcept {
        return _data.contains(other);
    }


    constexpr
    bool contains(const u8 *other, u32 size) const noexcept {
        return _data.contains(other, size);
    }


    /// @brief Compare the first string with the second string.
    /// @param other The other string
    /// @return 0 if the strings are equal, positive if the first string is
    /// greater than the second string, and negative if the first string is
    /// less than the second string
    constexpr
    i32 compare(StringView other) const noexcept {
        return _data.compare(other);
    }


    /// @brief Compare the first string with the second string up to the
    /// maximum number of characters.
    /// @param other The second string
    /// @return 0 if the strings are equal, positive if the first string is
    /// greater than the second string, and negative if the first string is
    /// less than the second string
    constexpr
    i32 compare(const u8 *data, u32 size) const noexcept {
        return compare(StringView(data, size));
    }


    /// @brief Return true if the strings are equal.
    /// @param other The other string
    constexpr
    bool is_equal(StringView other) const noexcept {
        return _data.is_equal(other);
    }


    /// @brief Test if the strings are equal up to the maximum number of
    /// characters.
    /// @param data The second string
    /// @return true if the strings are equal
    constexpr
    bool is_equal(const u8 *data, u32 size) const noexcept {
        return is_equal(StringView(data, size));
    }


    /// @brief Count the characters from the beginning of the string which are
    /// contained in the character set.
    /// @param set The character set
    /// @return The number of characters
    constexpr
    u32 count(u8 ch) const noexcept {
        return _data.count(ch);
    }


    /// @brief Count the characters from the beginning of the string which are
    /// contained in the character set.
    /// @param set The character set
    /// @return The number of characters
    constexpr
    u32 count(StringView substring) const noexcept {
        return _data.count(substring);
    }


    /// @brief Count the characters from the beginning of the string which are
    /// contained in the character set.
    /// @param set The character set
    /// @return The number of characters
    constexpr
    u32 count_all_of(StringView bytes) const noexcept {
        return _data.count_all_of(bytes);
    }


    /// @brief Count the characters from the beginning of the string which are
    /// not contained in the character set.
    /// @param set The character set
    /// @return The number of characters
    constexpr
    u32 count_not_of(StringView bytes) const noexcept {
        return _data.size() - _data.count_all_of(bytes);
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



    constexpr
    const u8 *begin() const noexcept {
        return _data.begin();
    }


    constexpr
    const u8 *end() const noexcept {
        return _data.end();
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
        return parse(format, {Parsable(args)...});
    }


    /// @brief Parse a u64 value from a string accounting for numerical base prefixes and scientific
    /// representation.
    /// @param value The parsed value.
    /// @param base The numeric base to use.
    /// @return The number of bytes parsed on success, and 0 on failure.
    u32 parse_u64(u64 &value, u8 base = 0) const noexcept;


    /// @brief Parse an i64 value from a string accounting for numerical base prefixes and scientific
    /// representation.
    /// @param value The parsed value.
    /// @param base The numeric base to use.
    /// @return The number of bytes parsed on success, and 0 on failure.
    u32 parse_i64(i64 &value, u8 base = 0) const noexcept;


    /// @brief Parse an f64 value from a string accounting for numerical base prefixes and scientific
    /// representation.
    /// @param value The parsed value.
    /// @return The number of bytes parsed on success, and 0 on failure.
    u32 parse_f64(f64 &value) const noexcept;


    static
    u32 print(StringPrinter &stream_printer) noexcept;


    static
    Error parse(StringParser &string_parser) noexcept;
private:


    /// @brief Parse multiple values from the string using a format string.
    /// @param format The format string
    /// @param ... The format arguments
    /// @return The number of characters parsed
    u32 parse(StringView format, std::initializer_list<Parsable> args) const noexcept;



};


///
/// Relational Operators
///


/// @brief Return true if the contents of the slices are equal.
constexpr
bool operator==(StringView lhs, StringView rhs) noexcept {
    return lhs.is_equal(rhs);
}


/// @brief Return true if the contents of the slices are not equal.
constexpr
bool operator!=(StringView lhs, StringView rhs) noexcept {
    return !lhs.is_equal(rhs);
}


/// @brief Return true if the contents of lhs are lexigraphically less than the contents of rhs.
constexpr
bool operator<(StringView lhs, StringView rhs) noexcept {
    return lhs.compare(rhs) < 0;
}


/// @brief Return true if the contents of lhs are lexigraphically less than or equal to the
/// contents of rhs.
constexpr
bool operator<=(StringView lhs, StringView rhs) noexcept {
    return lhs.compare(rhs) <= 0;
}


/// @brief Return true if the contents of lhs are lexigraphically greater than the contents of rhs.
constexpr
bool operator>(StringView lhs, StringView rhs) noexcept {
    return lhs.compare(rhs) > 0;
}


/// @brief Return true if the contents of lhs are lexigraphically greater than or equal to the
/// contents of rhs.
constexpr
bool operator>=(StringView lhs, StringView rhs) noexcept {
    return lhs.compare(rhs) >= 0;
}


///
/// Arithmetic Operators
///


/// @brief Increment the data pointer and decrement the size of the given slice by the given amount.
/// @param size The amount by which to increment
constexpr
StringView operator+(StringView slice, u32 size) noexcept {
    slice += size;
    return slice;
}


/// @brief Decrement the data pointer and increment the size of the given slice by the given amount.
/// @param size The amount by which to decrement
constexpr
StringView operator-(StringView slice, u32 size) noexcept {
    slice -= size;
    return slice;
}


/// @brief Shift the data of the given slice to the right by the given amount.
/// @param size The amount by which to shift
constexpr
StringView operator>>(StringView slice, u32 size) noexcept {
    slice >>= size;
    return slice;
}


/// @brief Shift the data of the given slice to the left by the given amount.
/// @param size The amount by which to shift
constexpr
StringView operator<<(StringView slice, u32 size) noexcept {
    slice <<= size;
    return slice;
}


// This must be here to avoid dependency cycles.
//#include <std/StringParser.hpp>
//#include <std/StringPrinter.hpp>


///
/// StringView extends the Type namespace with Type::name<T>()
///

/*
#include <source_location>


namespace Type {


    template<class T>
    constexpr
    StringView name() noexcept;


    template<>
    constexpr
    StringView name<void>() noexcept {
        return "void";
    }


    namespace internal {
        using type_name_prober = void;


        template<typename T>
        constexpr
        StringView wrapped_type_name() noexcept {
            return std::source_location::current().function_name();
        }


        constexpr
        u32 wrapped_type_name_prefix_length() noexcept {
            return wrapped_type_name<type_name_prober>().index_of_first(name<type_name_prober>()).value();
        }


        constexpr
        u32 wrapped_type_name_suffix_length() noexcept {
            return wrapped_type_name<type_name_prober>().size()
                - wrapped_type_name_prefix_length()
                - name<type_name_prober>().size();
        }
    }


    template<class T>
    constexpr
    StringView name() noexcept {
        constexpr auto wrapped_name = internal::wrapped_type_name<T>();
        constexpr auto prefix_length = internal::wrapped_type_name_prefix_length();
        constexpr auto suffix_length = internal::wrapped_type_name_suffix_length();
        constexpr auto type_name_length = wrapped_name.length() - prefix_length - suffix_length;
        return wrapped_name.substr(prefix_length, type_name_length);
    }
};
*/
