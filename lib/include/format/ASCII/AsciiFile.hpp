#pragma once

#include <filesystem/File.hpp>


class AsciiFile {
private:
    File _file;
public:


    constexpr
    AsciiFile(FilePath path) noexcept : _file(path) {}


    ///
    /// Properties
    ///


    /// Return true if the file was opened successfully.
    bool is_open() const {
        return _fd != -1 && _data != MAP_FAILED;
    }


    const Path &path() const {
        return _path;
    }


    const Vector<StringView> &lines() const {
        return _lines;
    }


    u32 size() const {
        return _lines.size();
    }


    StringView operator[](u32 index) const {
        return _lines[index];
    }


    const u8 *data() const {
        return _data;
    }


    ///
    /// Methods
    ///


    void write(Slice<const u8> data) noexcept {
        ;
    }


    void write(const u8 *data, u32 size) noexcept {
        write({data, size});
    }


    void write(u8 byte) noexcept {
        write({&byte, 1});
    }


private:


    // Scan the file and record the lines.
    void scan_lines() {
        Vector<StringView> lines;
        u32 offset = 0;

        for (u32 i = 0; i < _size; i++) {
            if (_data[i] == '\n' || _data[i] == '\r') {
                lines.emplace_back(&_data[offset], i - offset);

                if (_data[i] == '\r' && _data[i + 1] == '\n') {
                    i += 1;
                }

                offset = i + 1;
            }
        }

        lines.emplace_back(&_data[offset], _size - offset);
    }
};
