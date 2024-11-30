#pragma once

#include <filesystem/File.hpp>

#include <filesystem>


class DirectoryIterator {
private:
    std::filesystem::directory_iterator _it;
public:


    DirectoryIterator(std::filesystem::directory_iterator &&it) noexcept : _it(it) {}
};


class Directory {
private:
    File _file;
public:


    Directory(const FilePath &path) noexcept : _file(path) {}

    Directory(File &&file) noexcept : _file(file) {}

    Directory(const File &file) noexcept : _file(file) {}



    DirectoryIterator begin() const noexcept {
        std::error_code error_code;
        std::filesystem::directory_iterator it(_file.path(), error_code);

        if (error_code.value()) {
            return std::filesystem::directory_iterator();
        }

        return it;
    }


    DirectoryIterator end() const noexcept {
        return std::filesystem::directory_iterator();
    }
};
