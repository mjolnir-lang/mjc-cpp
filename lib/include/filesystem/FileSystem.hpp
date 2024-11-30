#pragma once

#include <container/Vector.hpp>
#include <core/StringView.hpp>
#include <core/Error.hpp>

#include <filesystem>
#include <fstream>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>


#include <filesystem/File.hpp>
#include <filesystem/FilePermission.hpp>
#include <filesystem/FileType.hpp>
#include <filesystem/FileInfo.hpp>
#include <filesystem/FileSystemError.hpp>


namespace FileSystem {


    template<class CopyOptions>
    struct CopyOptionsValues {


        ///
        /// Options controlling copy_file() when the file already exists 
        ///


        /// Report an error (default behavior).
        static constexpr CopyOptions NONE{std::filesystem::copy_options::none};

        /// Keep the existing file, without reporting an error.
        static constexpr CopyOptions SKIP_EXISTING{std::filesystem::copy_options::skip_existing};

        /// Replace the existing file.
        static constexpr CopyOptions OVERWRITE_EXISTING{std::filesystem::copy_options::overwrite_existing};

        /// Replace the existing file only if it is older than the file being copied.
        static constexpr CopyOptions UPDATE_EXISTING{std::filesystem::copy_options::update_existing};


        ///
        /// Options controlling the effects of copy() on subdirectories
        ///


        /// Skip subdirectories (default behavior).
        static constexpr CopyOptions NONE{std::filesystem::copy_options::none};

        /// Recursively copy subdirectories and their content.
        static constexpr CopyOptions RECURSIVE{std::filesystem::copy_options::recursive};


        ///
        /// Options controlling the effects of copy() on symbolic links
        ///


        /// Follow symlinks (default behavior).
        static constexpr CopyOptions NONE{std::filesystem::copy_options::none};

        /// Copy symlinks as symlinks, not as the files they point to.
        static constexpr CopyOptions COPY_SYMLINKS{std::filesystem::copy_options::copy_symlinks};

        /// Ignore symlinks.
        static constexpr CopyOptions SKIP_SYMLINKS{std::filesystem::copy_options::skip_symlinks};


        ///
        /// Options controlling the kind of copying copy() does
        ///


        /// Copy file content (default behavior).
        static constexpr CopyOptions NONE{std::filesystem::copy_options::none};

        /// Copy the directory structure, but do not copy any non-directory files.
        static constexpr CopyOptions DIRECTORIES_ONLY{std::filesystem::copy_options::directories_only};

        /// Instead of creating copies of files, create symlinks pointing to the originals. Note: the source path must be an absolute path unless the destination path is in the current directory.
        static constexpr CopyOptions CREATE_SYMLINKS{std::filesystem::copy_options::create_symlinks};

        /// Instead of creating copies of files, create hardlinks that resolve to the same files as the originals. 
        static constexpr CopyOptions CREATE_HARD_LINKS{std::filesystem::copy_options::create_hard_links};
    };


    class CopyOptions : public Enum<std::filesystem::copy_options>, public CopyOptionsValues<CopyOptions> {
    public:


        constexpr
        explicit
        CopyOptions(std::filesystem::copy_options id) noexcept : Enum(id) {}
    };


    ///
    /// File Properties
    ///


    /// checks whether the given path refers to block device
    Result<bool, FileSystemError> is_block_file(FilePath &file_path) noexcept {
        std::error_code error_code;
        bool result = std::filesystem::is_block_file(file_path, error_code);
        return error_code ? FileSystemError(error_code.value()) : result;
    }


    /// checks whether the given path refers to a character device
    Result<bool, FileSystemError> is_character_file(FilePath &file_path) noexcept {
        std::error_code error_code;
        bool result = std::filesystem::is_character_file(file_path, error_code);
        return error_code ? FileSystemError(error_code.value()) : result;
    }


    /// checks whether the given path refers to a directory
    Result<bool, FileSystemError> is_directory(FilePath &file_path) noexcept {
        std::error_code error_code;
        bool result = std::filesystem::is_directory(file_path, error_code);
        return error_code ? FileSystemError(error_code.value()) : result;
    }


    /// checks whether the given path refers to an empty file or directory
    Result<bool, FileSystemError> is_empty(FilePath &file_path) noexcept {
        std::error_code error_code;
        bool result = std::filesystem::is_empty(file_path, error_code);
        return error_code ? FileSystemError(error_code.value()) : result;
    }


    /// checks whether the given path refers to a named pipe
    Result<bool, FileSystemError> is_pipe(FilePath &file_path) noexcept {
        std::error_code error_code;
        bool result = std::filesystem::is_fifo(file_path, error_code);
        return error_code ? FileSystemError(error_code.value()) : result;
    }


    /// checks whether the argument refers to an other file
    Result<bool, FileSystemError> is_other(FilePath &file_path) noexcept {
        std::error_code error_code;
        bool result = std::filesystem::is_other(file_path, error_code);
        return error_code ? FileSystemError(error_code.value()) : result;
    }


    /// checks whether the argument refers to a regular file
    Result<bool, FileSystemError> is_regular_file(FilePath &file_path) noexcept {
        std::error_code error_code;
        bool result = std::filesystem::is_regular_file(file_path, error_code);
        return error_code ? FileSystemError(error_code.value()) : result;
    }


    /// checks whether the argument refers to a named IPC socket
    Result<bool, FileSystemError> is_socket(FilePath &file_path) noexcept {
        std::error_code error_code;
        bool result = std::filesystem::is_socket(
            std::basic_string<char>(
                reinterpret_cast<char *>(file_path.data().data()),
                file_path.data().size()
            ),
            error_code
        );
        return error_code ? FileSystemError(error_code.value()) : result;
    }


    /// checks whether the argument refers to a symbolic link
    Result<bool, FileSystemError> is_symbolic_link(FilePath &file_path) noexcept {
        std::error_code error_code;
        bool result = std::filesystem::is_symlink(file_path, error_code);
        return error_code ? FileSystemError(error_code.value()) : result;
    }


    Result<bool, FileSystemError> is_same(const FilePath &a, const FilePath &b) noexcept {
        std::error_code error_code;
        bool result = std::filesystem::equivalent(a, b, error_code);
        return error_code ? FileSystemError(error_code.value()) : result;
    }


    /// checks whether file status is known
    bool is_status_known(FileStatus &file_status) noexcept {
        return std::filesystem::status_known(file_status);
    }


    Result<u64, FileSystemError> file_size(const FilePath &file_path) noexcept {
        std::error_code error_code;
        bool result = std::filesystem::file_size(file_path, error_code);
        return error_code ? FileSystemError(error_code.value()) : result;
    }


    Result<u32, FileSystemError> hard_link_count(const FilePath &link) noexcept {
        std::error_code error_code;
        u32 result = std::filesystem::hard_link_count(link, error_code);
        return error_code ? FileSystemError(error_code.value()) : result;
    }


    ///
    /// Copy Methods
    ///


    FileSystemError copy(const FilePath &dst, const FilePath &src) noexcept {
        std::error_code error_code;
        CopyOptions copy_options = CopyOptions::NONE;
        std::filesystem::copy(src, dst, copy_options, error_code);
        return FileSystemError(error_code.value());
    }


    FileSystemError copy_file(const FilePath &dst, const FilePath &src) noexcept {
        std::error_code error_code;
        CopyOptions copy_options = CopyOptions::NONE;
        std::filesystem::copy_file(src, dst, copy_options, error_code);
        return FileSystemError(error_code.value());
    }


    FileSystemError copy_symbolic_link(const FilePath &dst, const FilePath &src) noexcept {
        std::error_code error_code;
        std::filesystem::copy_symlink(src, dst, error_code);
        return FileSystemError(error_code.value());
    }


    FileSystemError resize_file(const FilePath &file_path, u64 size) noexcept {
        std::error_code error_code;
        std::filesystem::resize_file(file_path, size, error_code);
        return FileSystemError(error_code.value());
    }


    ///
    /// Create Methods
    ///


    FileSystemError create_directory(const FilePath &directory_path) noexcept {
        std::error_code error_code;
        std::filesystem::create_directory(directory_path, error_code);
        return FileSystemError(error_code.value());
    }


    FileSystemError create_symbolic_link(const FilePath &link, const FilePath &target) noexcept {
        std::error_code error_code;
        std::filesystem::create_symlink(target, link, error_code);
        return FileSystemError(error_code.value());
    }


    FileSystemError create_directory_symbolic_link(const FilePath &link, const FilePath &target) noexcept {
        std::error_code error_code;
        std::filesystem::create_directory_symlink(target, link, error_code);
        return FileSystemError(error_code.value());
    }


    FileSystemError create_hard_link(const FilePath &link, const FilePath &target) noexcept {
        std::error_code error_code;
        std::filesystem::create_hard_link(target, link, error_code);
        return FileSystemError(error_code.value());
    }


    FileSystemError symbolic_link_target(const FilePath &link, FilePath &target) noexcept {
        std::error_code error_code;
        target = std::move(std::filesystem::read_symlink(link, error_code));
        return FileSystemError(error_code.value());
    }


    ///
    /// Delete Methods
    ///


    /// @brief The file or empty directory identified by the path p is deleted as if by the POSIX remove. Symlinks are not followed (symlink is removed, not its target).
    /// @param target 
    /// @return 
    FileSystemError remove(const FilePath &target) noexcept {
        std::error_code error_code;
        std::filesystem::remove(target, error_code);
        return FileSystemError(error_code.value());
    }


    /// @brief Deletes the contents of p (if it is a directory) and the contents of all its subdirectories, recursively, then deletes p itself as if by repeatedly applying the POSIX remove. Symlinks are not followed (symlink is removed, not its target).
    /// @param target 
    /// @return 
    FileSystemError remove_all(const FilePath &target) noexcept {
        std::error_code error_code;
        std::filesystem::remove_all(target, error_code);
        return FileSystemError(error_code.value());
    }


    ///
    /// Open Methods
    ///


    FileSystemError open(File &file, const FilePath &path) noexcept;











    FileSystemError glob(const FilePath &glob, FilePath &path) noexcept {
        std::error_code error_code;
        std::filesystem::remove_all(target, error_code);

        for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(path, error_code)) {
            FilePath path = entry.path();
        }

        return FileSystemError(error_code.value());
    }
}
