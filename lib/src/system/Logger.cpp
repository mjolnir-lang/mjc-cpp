#include <system/logger/Logger.hpp>


Logger Logger::GLOBAL{};


String Logger::info(bool is_verbose) const noexcept {
    With<Mutex> lock(_mutex);
    String info;
    info.print(
        "Level:  {}\n"
        "Size:   {:.0V B}\n"
        "Usage:  {:.0V B} ({:.2f}%)\n"
        "Color:  {:b}\n"
        "Hidden: {:b}\n",
        _level.name(),
        _buffer.size(),
        _buffer.used(), (100.0 * _buffer.used()) / _buffer.size(),
        _has_color,
        _is_hidden
    );
    return info;
}


void Logger::vmessage(LoggerLevel level, StringView tag, StringView format, Slice<Printable> args) noexcept {
    static const StringView prefixes[] = {
        "Warning: ",
        "Error: ",
        "Fatal: ",
        "Bug: ",
        "\x1B[35;1mWarning:\x1B[m ",
        "\x1B[31;1mError:\x1B[m ",
        "\x1B[33;1mFatal:\x1B[m ",
        "\x1B[32;1mBug:\x1B[m ",
    };
    With<Mutex> lock(_mutex);

    if (_level <= level) {
        String message(level.id());

        if (!tag.is_empty()) {
            message.append(_has_color ? "\x1B[36;1m["_sv : "["_sv);
            message.append(tag);
            message.append(_has_color ? "]\x1B[m "_sv : "] "_sv);
        }

        i32 index = i32(level) - LoggerLevel::WARN;
        if (index >= 0) {
            if (_has_color) {
                index += 4;
            }

            message.append(prefixes[index]);
        }

        message.vprint(format, args);
        message.append('\n');

        if (!_is_hidden) {
            _stream->write(&message[1]);
        }

        _buffer.push(message);
    }
}


static
bool contains_pattern(StringView string, StringView pattern) noexcept {
    const u32 end = string.size() - pattern.size();

    for (u32 k = 0; string[k] < end; k++) {

        // Skip escape sequences.
        if (string[k] == '\x1B') {
            while (string[++k] != 'm');
            continue;
        }

        // Compare the pattern.
        for (u32 i = 0, j = 0; i <= pattern.size() && string[k + j]; i++, j++) {
            if (!pattern[i]) {
                return true;
            }

            // Skip escape sequences.
            if (string[k + j] == '\x1B') {
                while (string[k + j++] != 'm');
            }

            if (pattern[i] != string[k + j]) {
                break;
            }
        }
    }

    return false;
}


void Logger::dump(StringView pattern, LoggerLevel level, u32 max) noexcept {
    With<Mutex> lock(_mutex);
    StringBuffer::Iterator buffer_iterator = _buffer.iter();
    StringView string;
    u32 length;

    if (max && max < _buffer.size()) {
        StringView messages[max];
        u32 i = 0;
        bool is_full = false;

        while (!(string = buffer_iterator.next()).is_empty()) {
            if (
                string[0] >= static_cast<u32>(level) &&
                (pattern.is_empty() || contains_pattern(++string, pattern))
            ) {
                messages[i++] = string;

                if (i == max) {
                    i = 0;
                    is_full = true;
                }
            }
        }

        u32 rem;

        if (is_full) {
            rem = max;
        } else {
            i = 0;
            rem = i;
        }

        while (rem--) {
            _stream->write(messages[i++]);

            if (i == max) {
                i = 0;
            }
        }
    } else {
        while (!(string = buffer_iterator.next()).is_empty()) {
            if (
                string[0] >= static_cast<u32>(level) &&
                (pattern.is_empty() || contains_pattern(++string, pattern))
            ) {
                _stream->write(string);
            }
        }
    }
}
