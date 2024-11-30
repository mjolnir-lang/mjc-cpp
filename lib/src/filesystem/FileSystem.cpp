#include <filesystem/FileSystem.hpp>


namespace FileSystem {


    FileSystemError open(File &file, const FilePath &path) noexcept {
        // Get the file size.
        struct stat st;

        if (stat(path.data(), &st) != 0) {
            return;
        }

        _size = st.st_size;

        // Open the file.
        _fd = ::open(path, O_RDWR, 0);

        if (_fd == -1) {
            return;
        }

        // Map the file.
        _data = reinterpret_cast<u8 *>(mmap(nullptr, _size, PROT_READ, MAP_PRIVATE, _fd, 0));

        if (_data == MAP_FAILED) {
            return;
        }
    }


}
