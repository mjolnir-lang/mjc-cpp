#pragma once

#include <system/internal/ProgramArgumentType.hpp>
#include <system/internal/ProgramArgumentValue.hpp>
#include <system/internal/ProgramArgumentParser.hpp>
#include <container/Vector.hpp>


/// @brief A program argument.
class ProgramArgument {
private:

    /// @brief An argument copying function.
    using ProgramArgumentCopier = Function<void(void *, const void *)>;

    // The parsed value
    void *_data;

    union Value {
        // The default value
        ProgramArgumentValue default_value;
        u32 slice_capacity;

        constexpr Value(ProgramArgumentValue default_value) noexcept : default_value(default_value) {}
        constexpr Value(u32 slice_capacity) noexcept : slice_capacity(slice_capacity) {}
    } _value;

    union Parser {
        Slice<StringView> value_set;
        ProgramArgumentParser parser;

        constexpr Parser(Slice<StringView> value_set) noexcept : value_set(value_set) {}
        constexpr Parser(ProgramArgumentParser parser) noexcept : parser(parser) {}
    } _parser;

    // The argument type
    ProgramArgumentType _type;

    // The flag set when the argument is assigned
    bool _is_set = false;
public:


    ///
    /// Constructors
    ///


    /// @brief Create a positional argument.
    /// @param value The parsed value address
    /// @param default_value The value assigned when the argument is unspecified.
    template<class T>
    constexpr
    ProgramArgument(T *value, T default_value = T()) noexcept :
        _data(value),
        _value(default_value),
        _parser(&StringView::parse<T>),
        _type(arg_type<T>()),
    {}


    /// @brief Create a positional argument.
    /// @param value The parsed value address
    /// @param default_value The default value if unset.
    constexpr
    ProgramArgument(StringView *value, Slice<StringView> value_set, u32 default_value = 0) noexcept :
        _data(value),
        _value(default_value),
        _parser(value_set),
        _type(ProgramArgumentType::ENUM)
    {}


    /// @brief Create a positional argument.
    /// @param value The parsed value address
    /// @param default_value The default value if unset.
    template<class T>
    constexpr
    ProgramArgument(T *value, ProgramArgumentParser parser, T default_value = T()) noexcept :
        _data(value),
        _value(default_value),
        _parser(parser, []() { *value = *default_value; }),
        _type(ProgramArgumentType::FUNC)
    {}


    /// @brief Create a positional argument list.
    /// @param values The parsed value address
    /// @param count The number of parsed values
    /// @param size The maximum number of values to parse
    template<class T>
    constexpr
    ProgramArgument(Slice<T> *values) noexcept :
        _data(values),
        _value(values->size()),
        _type(arg_type<T>() | ProgramArgumentType::SLICE)
    {}


    /// @brief Create a positional argument list.
    /// @param value The parsed value address
    constexpr
    ProgramArgument(Slice<StringView> *values, Slice<StringView> value_set) noexcept :
        _data(values),
        _value(values->size()),
        _parser(value_set),
        _type(ProgramArgumentType::ENUM | ProgramArgumentType::SLICE)
    {}


    /// @brief Create a positional argument list.
    /// @param value The parsed value address
    template<class T>
    constexpr
    ProgramArgument(Slice<T> *values, ProgramArgumentParser parser) noexcept :
        _data(values),
        _value(values->size()),
        _parser(parser),
        _type(ProgramArgumentType::FUNC | ProgramArgumentType::SLICE)
    {}


    /// @brief Create a positional argument list.
    /// @param values The parsed value address
    /// @param count The number of parsed values
    /// @param size The maximum number of values to parse
    template<class T>
    constexpr
    ProgramArgument(Vector<T> *values) noexcept :
        _data(values),
        _value(0),
        _type(arg_type<T>() | ProgramArgumentType::VECTOR)
    {}


    /// @brief Create a positional argument list.
    /// @param value The parsed value address
    constexpr
    ProgramArgument(Vector<StringView> *values, Slice<StringView> value_set) noexcept :
        _data(values),
        _value(0),
        _parser(value_set),
        _type(ProgramArgumentType::ENUM | ProgramArgumentType::VECTOR)
    {}


    /// @brief Create a positional argument list.
    /// @param value The parsed value address
    template<class T>
    constexpr
    ProgramArgument(Vector<T> *values, ProgramArgumentParser parser) noexcept :
        _data(values),
        _value(0),
        _parser(parser),
        _type(ProgramArgumentType::FUNC | ProgramArgumentType::VECTOR)
    {}


    ///
    /// Properties
    ///


    /// @brief Return true if the argument is set.
    constexpr
    bool is_set() const noexcept {
        return _type.is_list() ? values<u8>().size() > 0 : _is_set;
    }


    /// @brief Return true if the argument is a list.
    constexpr
    bool is_list() const noexcept {
        return _type.is_list();
    }


    /// @brief Return true if the argument list is full.
    constexpr
    bool is_full() const noexcept {
        if (_type.is_slice()) {
            return values<u8>().size() == _value.slice_capacity;
        }

        return !_type.is_vector();
    }


    /// @brief Return the argument type.
    constexpr
    ProgramArgumentType type() const noexcept {
        return _type;
    }


    /// @brief Return the argument values.
    template<class T>
    Slice<const T> values() const noexcept {
        if (_type.is_slice()) {
            return *reinterpret_cast<Slice<const T> *>(_data);
        }

        if (_type.is_vector()) {
            return *reinterpret_cast<Vector<const T> *>(_data);
        }

        return nullptr;
    }


    /// @brief Return the argument values.
    template<class T>
    Slice<T> values() noexcept {
        if (_type.is_slice()) {
            return *reinterpret_cast<Slice<T> *>(_data);
        }

        if (_type.is_vector()) {
            return *reinterpret_cast<Vector<T> *>(_data);
        }

        return nullptr;
    }


    /// @brief Return the argument value.
    template<class T>
    const T *value() const noexcept {
        return reinterpret_cast<const T *>(_data);
    }


    /// @brief Return the argument value.
    template<class T>
    T *value() noexcept {
        return reinterpret_cast<T *>(_data);
    }


    /// @brief Return the argument value.
    template<class T>
    const T *value(u32 index) const noexcept {
        return &reinterpret_cast<const T *>(_data)[index];
    }


    /// @brief Return the argument value.
    template<class T>
    T *value(u32 index) noexcept {
        return &reinterpret_cast<T *>(_data)[index];
    }


    ///
    /// Methods
    ///


    /// @brief Reset the argument value.
    void reset() noexcept;


    /// @brief Set the argument value.
    template<class T>
    Error append_value(T value) noexcept {
        if (_type.is_slice()) {
            if (values<u8>().size() == _value.slice_capacity) {
                return Error::FAILURE;
            }

            Slice<T> &slice = *reinterpret_cast<Slice<T> *>(_data);
            slice[slice.size()] = value;
            ++slice;
            return Error::SUCCESS;
        }

        if (_type.is_vector()) {
            reinterpret_cast<Vector<T> *>(_data)->append(value);
            return Error::SUCCESS;
        }
    }


    /// @brief Set the argument value.
    template<class T>
    void set_value(T value) noexcept {
        *reinterpret_cast<T *>(_data) = value;
    }


    /// @brief Set the argument value at the given index in the argument values list.
    template<class T>
    void set_value(u32 index, T value) noexcept {
        reinterpret_cast<T *>(_data)[index] = value;
    }


    /// @brief Parse the argument value from a string.
    /// @param string The string to parse
    /// @return true if the argument could not be parsed
    Error parse(StringView string) noexcept;
private:


    template<class T>
    static
    constexpr
    ProgramArgumentType arg_type() noexcept {
        if constexpr (std::is_same_v<T, StringView>) {
            return ProgramArgumentType::STR;
        } else if constexpr (std::is_same_v<T, size_t>) {
            return ProgramArgumentType::SIZE;
        } else if constexpr (std::is_same_v<T, bool>) {
            return ProgramArgumentType::BOOL;
        } else if constexpr (std::is_same_v<T, u8>) {
            return ProgramArgumentType::U8;
        } else if constexpr (std::is_same_v<T, u16>) {
            return ProgramArgumentType::U16;
        } else if constexpr (std::is_same_v<T, u32>) {
            return ProgramArgumentType::U32;
        } else if constexpr (std::is_same_v<T, u64>) {
            return ProgramArgumentType::U64;
        } else if constexpr (std::is_same_v<T, i8>) {
            return ProgramArgumentType::I8;
        } else if constexpr (std::is_same_v<T, i16>) {
            return ProgramArgumentType::I16;
        } else if constexpr (std::is_same_v<T, i32>) {
            return ProgramArgumentType::I32;
        } else if constexpr (std::is_same_v<T, i64>) {
            return ProgramArgumentType::I64;
        } else if constexpr (std::is_same_v<T, f32>) {
            return ProgramArgumentType::F32;
        } else if constexpr (std::is_same_v<T, f64>) {
            return ProgramArgumentType::F64;
        } else {
            static_assert(false, "Invalid argument type!");
        }
    }
};
