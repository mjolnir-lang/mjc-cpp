#pragma once

#include <filesystem/FilePath.hpp>


class File {
private:
    Vector<StringView> _lines;
    FilePath _path;
    const u8 *_data = reinterpret_cast<u8 *>(MAP_FAILED);
    i32 _fd = -1;
    u32 _size = 0;
public:


    constexpr
    File(FilePath path) noexcept : _path(path) {

        // Get the file size.
        struct stat st;

        if (stat(path.c_str(), &st) != 0) {
            return;
        }

        _size = st.st_size;

        // Open the file.
        _fd = FileSystem::open(path.c_str(), O_RDWR, 0);

        if (_fd == -1) {
            return;
        }

        // Map the file.
        _data = reinterpret_cast<u8 *>(mmap(nullptr, _size, PROT_READ, MAP_PRIVATE, _fd, 0));

        if (_data == MAP_FAILED) {
            return;
        }

        // Initialize the line data.
        scan_lines();
    }


    ~File() {
        if (_fd != -1) {
            if (_data != MAP_FAILED) {
                munmap(const_cast<u8 *>(_data), _size);
            }

            close(_fd);
        }
    }


    ///
    /// Properties
    ///


    /// Return true if the file was opened successfully.
    bool is_open() const noexcept {
        return _fd != -1 && _data != MAP_FAILED;
    }


    const Path &path() const noexcept {
        return _path;
    }


    const Vector<StringView> &lines() const noexcept {
        return _lines;
    }


    u32 size() const noexcept {
        return _lines.size();
    }


    StringView operator[](u32 index) const noexcept {
        return _lines[index];
    }


    const u8 *data() const noexcept {
        return _data;
    }


    ///
    /// Methods
    ///


    void write(Slice<const u8> data) noexcept noexcept {
        ;
    }


    void write(const u8 *data, u32 size) noexcept noexcept {
        write({data, size});
    }


    void write(u8 byte) noexcept noexcept {
        write({&byte, 1});
    }


private:


    // Scan the file and record the lines.
    void scan_lines() {
        u32 offset = 0;

        for (u32 i = 0; i < _size; i++) {
            if (_data[i] == '\n' || _data[i] == '\r') {
                _lines.emplace_back(&_data[offset], i - offset);

                if (_data[i] == '\r' && _data[i + 1] == '\n') {
                    i += 1;
                }

                offset = i + 1;
            }
        }

        _lines.emplace_back(&_data[offset], _size - offset);
    }
};
