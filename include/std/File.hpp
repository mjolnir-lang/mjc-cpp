#pragma once

#include <std/Vector.hpp>
#include <std/StringView.hpp>
#include <std/Error.hpp>

#include <filesystem>
#include <fstream>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>


namespace FileSystem = std::filesystem;


using FileStream = std::fstream;


using Path = std::filesystem::path;


class File {
private:
    Vector<StringView> lines_;
    Path path_;
    const u8 *data_ = reinterpret_cast<u8 *>(MAP_FAILED);
    i32 fd_ = -1;
    u32 size_ = 0;
public:


    /// Open a file.
    File(Path path) :
        path_(path)
    {

        // Get the file size.
        struct stat st;

        if (stat(path.c_str(), &st) != 0) {
            return;
        }

        size_ = st.st_size;

        // Open the file.
        fd_ = open(path.c_str(), O_RDWR, 0);

        if (fd_ == -1) {
            return;
        }

        // Map the file.
        data_ = reinterpret_cast<u8 *>(mmap(nullptr, size_, PROT_READ, MAP_PRIVATE, fd_, 0));

        if (data_ == MAP_FAILED) {
            return;
        }

        // Initialize the line data.
        scan_lines();
    }


    ~File() {
        if (fd_ != -1) {
            if (data_ != MAP_FAILED) {
                munmap(const_cast<u8 *>(data_), size_);
            }

            close(fd_);
        }
    }


    ///
    /// Properties
    ///


    /// Return true if the file was opened successfully.
    bool is_open() const {
        return fd_ != -1 && data_ != MAP_FAILED;
    }


    const Path &path() const {
        return path_;
    }


    const Vector<StringView> &lines() const {
        return lines_;
    }


    u32 size() const {
        return lines_.size();
    }


    StringView operator[](u32 index) const {
        return lines_[index];
    }


    const u8 *data() const {
        return data_;
    }
private:


    // Scan the file and record the lines.
    void scan_lines() {
        u32 offset = 0;

        for (u32 i = 0; i < size_; i++) {
            if (data_[i] == '\n' || data_[i] == '\r') {
                lines_.emplace_back(&data_[offset], i - offset);

                if (data_[i] == '\r' && data_[i + 1] == '\n') {
                    i += 1;
                }

                offset = i + 1;
            }
        }

        lines_.emplace_back(&data_[offset], size_ - offset);
    }
};
