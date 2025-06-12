#include <mj/ast/MjSourceFile.hpp>

#include <fstream>



Error MjSourceFile::load(std::filesystem::path file_path) noexcept {

    // Open file in binary mode and position the cursor at the end to determine file size
    std::basic_ifstream<u8> file_stream(file_path, std::ios::binary | std::ios::ate);

    if (!file_stream.is_open()) {
        return Error::FAILURE;
    }

    // Get file size
    std::streamsize file_size = file_stream.tellg();

    if (file_size < 0) {
        return Error::FAILURE;
    }

    _path = file_path;

    // Resize the vector to hold the file content
    _size = u32(file_size) + 1;
    _data.resize(_size);

    // Rewind the cursor to the beginning and read the data into the vector
    file_stream.seekg(0, std::ios::beg);

    if (!file_stream.read(_data.data(), file_size)) {
        return Error::FAILURE;
    }

    _data[_size - 1] = 0;
    return Error::SUCCESS;
}
