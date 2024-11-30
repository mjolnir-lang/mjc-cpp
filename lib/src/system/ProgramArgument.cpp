#include <system/ProgramArgument.hpp>
#include <system/logger/Logger.hpp>


void ProgramArgument::reset() {
    if (_type.is_slice()) {
        _value.slice_capacity = 0;
        return;
    }

    if (_type.is_vector()) {
        return;
    }

    switch (_type) {
    case ProgramArgumentType::BOOL:
        set_value<bool>(_value.default_value.value<bool>());
        break;
    case ProgramArgumentType::ENUM:
        set_value<u32>(_value.default_value.value<u32>());
        break;
    case ProgramArgumentType::FUNC:
        /// TODO: Alternatively use a user-provided copy function to copy the default value instead
        /// of parsing a default string.
        _parser.parser(_value.default_value.value<StringView>(), _data, 0);
        break;
    case ProgramArgumentType::STR:
        set_value<StringView>(_value.default_value.value<StringView>());
        break;
    case ProgramArgumentType::SIZE:
        set_value<size_t>(_value.default_value.value<size_t>());
        break;
    case ProgramArgumentType::U8:
        set_value<u8>(_value.default_value.value<u8>());
        break;
    case ProgramArgumentType::U16:
        set_value<u16>(_value.default_value.value<u16>());
        break;
    case ProgramArgumentType::U32:
        set_value<u32>(_value.default_value.value<u32>());
        break;
    case ProgramArgumentType::U64:
        set_value<u64>(_value.default_value.value<u64>());
        break;
    case ProgramArgumentType::I8:
        set_value<i8>(_value.default_value.value<i8>());
        break;
    case ProgramArgumentType::I16:
        set_value<i16>(_value.default_value.value<i16>());
        break;
    case ProgramArgumentType::I32:
        set_value<i32>(_value.default_value.value<i32>());
        break;
    case ProgramArgumentType::I64:
        set_value<i64>(_value.default_value.value<i64>());
        break;
    case ProgramArgumentType::F32:
        set_value<f32>(_value.default_value.value<f32>());
        break;
    case ProgramArgumentType::F64:
        set_value<f64>(_value.default_value.value<f64>());
    }
}


Error ProgramArgument::parse(StringView str) {

    // This function will never be called when the index would be out of bounds.
    u32 index = 0;

    if (_type.is_list()) {
        index = _value.slice_capacity++;
    }

    switch (_type.element_type()) {
    case ProgramArgumentType::STR: {
        set_value(index, str);
        return Error::SUCCESS;
    }
    case ProgramArgumentType::ENUM: {
        for (u32 value = 0; value < _parser.value_set.size(); ++value) {
            if (str == _parser.value_set[value]) {
                set_value(value);
                return Error::SUCCESS;
            }
        }

        log_error("Invalid choice! '{}'", str);
        return Error::FAILURE;
    }
    case ProgramArgumentType::FUNC: {
        if (_parser.parser(str, _data, index).is_failure()) {
            log_error("Invalid choice! '{}'", str);
            return Error::FAILURE;
        }

        return Error::SUCCESS;
    }
    case ProgramArgumentType::SIZE: {
        if (str.parse("{}", value<size_t>(index))) {
            log_error("Invalid argument format!");
            return Error::FAILURE;
        }

        return Error::SUCCESS;
    }
    case ProgramArgumentType::BOOL: {
        if (_type.is_vector()) {
            reinterpret_cast<Vector<bool> *>(_data)->resize(index);
        }

        set_value(index, true);
        return Error::SUCCESS;
    }
    case ProgramArgumentType::U8: {
        u8 value;

        if (str.parse("{}", value)) {
            log_error("Invalid argument format!");
            return Error::FAILURE;
        }

        if (_type.is_vector()) {
            reinterpret_cast<Vector<u8> *>(_data)->append(value);
        } if (_type.is_slice()) {
            (*reinterpret_cast<Slice<u8> *>(_data))[index] = value;
        }

        return Error::SUCCESS;
    }
    case ProgramArgumentType::U16: {
        if (str.parse("{}", value<u16>(index))) {
            log_error("Invalid argument format!");
            return Error::FAILURE;
        }

        return Error::SUCCESS;
    }
    case ProgramArgumentType::U32: {
        if (str.parse("{}", value<u32>(index))) {
            log_error("Invalid argument format!");
            return Error::FAILURE;
        }

        return Error::SUCCESS;
    }
    case ProgramArgumentType::U64: {
        if (str.parse("{}", value<u64>(index))) {
            log_error("Invalid argument format!");
            return Error::FAILURE;
        }

        return Error::SUCCESS;
    }
    case ProgramArgumentType::I8: {
        if (str.parse("{}", value<i8>(index))) {
            log_error("Invalid argument format!");
            return Error::FAILURE;
        }

        return Error::SUCCESS;
    }
    case ProgramArgumentType::I16: {
        if (str.parse("{}", value<i16>(index))) {
            log_error("Invalid argument format!");
            return Error::FAILURE;
        }

        return Error::SUCCESS;
    }
    case ProgramArgumentType::I32: {
        if (str.parse("{}", value<i32>(index))) {
            log_error("Invalid argument format!");
            return Error::FAILURE;
        }

        return Error::SUCCESS;
    }
    case ProgramArgumentType::I64: {
        if (str.parse("{}", value<i64>(index))) {
            log_error("Invalid argument format!");
            return Error::FAILURE;
        }

        return Error::SUCCESS;
    }
    case ProgramArgumentType::F32: {
        if (str.parse("{}", value<f32>(index))) {
            log_error("Invalid argument format!");
            return Error::FAILURE;
        }

        return Error::SUCCESS;
    }
    case ProgramArgumentType::F64: {
        if (str.parse("{}", value<f64>(index))) {
            log_error("Invalid argument format!");
            return Error::FAILURE;
        }

        return Error::SUCCESS;
    }
    default: {
        log_bug("Invalid argument type!");
        return Error::FAILURE;
    }
    }

    return Error::SUCCESS;
}
