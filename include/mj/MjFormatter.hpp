#pragma once

#include <mj/ast/MjSourceFile.hpp>
#include <mj/MjFormatterConfig.hpp>

#include <filesystem>
#include <fstream>


// The parser consumes the output of the scanner and emits the AST components while controlling the parsing context.
class MjFormatter {
private:
    const MjSourceFile &_file;
    const MjFormatterConfig &_config;
    std::string _out;
public:


    static
    std::string format_file(const MjSourceFile &file, const MjFormatterConfig &config) noexcept;


private:


    ///
    /// Constructors
    ///


    constexpr
    MjFormatter(const MjSourceFile &file, const MjFormatterConfig &config = {}) noexcept :
        _file(file),
        _config(config)
    {}


    ///
    /// Token Formatting
    ///


    void print_tokens() noexcept;


    ///
    /// Text Control
    ///


    void write(StringView string) {
        _out.append(string.data(), string.size());
    }


    void write(u8 ch, u32 count) {
        _out.append(count, ch);
    }


    void write(u8 ch) {
        _out.push_back(ch);
    }
};
