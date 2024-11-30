#pragma once

#include <filesystem/FilePath.hpp>

#include <filesystem>


class DirectoryIterator {
private:
    std::filesystem::directory_iterator _it;
public:


    DirectoryIterator(std::filesystem::directory_iterator &&it) noexcept : _it(it) {}
};


class Directory {
private:
    FilePath _file_path;
public:


    Directory(const FilePath &file_path) noexcept : _file_path(file_path) {}


    DirectoryIterator begin() const noexcept {
        std::error_code error_code;
        std::filesystem::directory_iterator it(_file_path, error_code);

        if (error_code.value()) {
            return std::filesystem::directory_iterator();
        }

        return it;
    }


    DirectoryIterator end() const noexcept {
        return std::filesystem::directory_iterator();
    }
};
