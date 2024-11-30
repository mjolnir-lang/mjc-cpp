#pragma once

#include <core/String.hpp>


class FilePath {
private:
    String _data;
public:


    ///
    /// Constructors
    ///


    constexpr
    FilePath() noexcept : _data() {}


    constexpr
    FilePath(const FilePath &path) noexcept : _data(path._data) {}


    FilePath(StringView string) noexcept : _data(string) {}


    FilePath(String string) noexcept : _data(std::move(string)) {}


    ///
    /// Type Casts
    ///


    constexpr
    operator StringView() const noexcept {
        return _data;
    }


    constexpr
    operator String &() noexcept {
        return _data;
    }


    ///
    /// Properties
    ///


    const char *c_str() noexcept {
        return _data.c_str();
    }


    constexpr
    StringView data() const noexcept {
        return _data;
    }


    constexpr
    String &data() noexcept {
        return _data;
    }


    /// Return true if the path is absolute.
    constexpr
    bool is_absolute() const noexcept {
        return false;
    }


    /// Return true if the path is relative.
    constexpr
    bool is_relative() const noexcept {
        return false;
    }


    /// Return true if the path is a UNC share.
    constexpr
    bool is_unc_share() const noexcept {
        return false;
    }


    constexpr
    bool is_windows() const noexcept {
        return false;
    }


    constexpr
    bool is_posix() const noexcept {
        return false;
    }


    FilePath unc_share() const noexcept {
        return "";
    }


    u8 drive_letter() const noexcept {
        return 0;
    }


    u8 drive_letter() const noexcept {
        return 0;
    }


    u8 drive_letter() const noexcept {
        return 0;
    }


    FilePath root_directory() const noexcept {
        return _data;
    }


    StringView root_name() const noexcept {
        if ("//s/s") {
            return "UNC share";
        }
        return _data;
    }


    /// Return the root path.
    ///
    /// If the path is relative, return an empty path.
    /// If the path is absolute, return the root directory, UNC share, or drive letter with the
    /// directory separator.
    FilePath root_path() const noexcept {
        u32 end = _data.size();
        while (end > 0 && _data[--end] != '/');
        return _data.slice(start, end);
    }


    /// Return the parent file path.
    FilePath parent_path() const noexcept {
        u32 end = _data.size();
        while (end > 0 && _data[--end] != '/');
        return _data.slice(0, end);
    }


    StringView stem() const noexcept {
        u32 end = _data.size();
        while (end > 0 && _data[--end] != '.');
        u32 start = end;
        while (start > 0 && _data[--start] != '/');
        return _data.slice(start, end);
    }


    /// A string representing the final path component, excluding the drive and root, if any
    StringView file_name() const noexcept {
        u32 start = _data.size();
        while (start > 0 && _data[--start] != '/');
        return _data.slice(start);
    }


    StringView file_extension() const noexcept {
        u32 start = _data.size();

        while (start > 0 && _data[--start] != '.') {
            if (_data[start] != '/') {
                return nullptr;
            }
        }

        return _data.slice(start, _data.size());
    }


    ///
    /// Methods
    ///


    void append(StringView string) noexcept {
        _data.append(string);
    }


    void clear() noexcept {
        _data.clear();
    }
};
