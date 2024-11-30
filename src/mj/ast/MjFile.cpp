#include <mj/ast/MjFile.hpp>

#include <fstream>



Error MjFile::load(std::filesystem::path file_path) noexcept {

    // Open file in binary mode and position the cursor at the end to determine file size
    std::basic_ifstream<u8> ifstream(file_path, std::ios::binary | std::ios::ate);

    if (!ifstream.is_open()) {
        return Error::FAILURE;
    }

    // Get file size
    std::streamsize file_size = ifstream.tellg();

    if (file_size < 0) {
        return Error::FAILURE;
    }

    _path = file_path;

    // Resize the vector to hold the file content
    _data.reserve(file_size);

    // Rewind the cursor to the beginning and read the data into the vector
    ifstream.seekg(0, std::ios::beg);

    if (!ifstream.read(_data.data(), file_size)) {
        return Error::FAILURE;
    }

    return Error::SUCCESS;
}
