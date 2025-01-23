#pragma once

#include <mj/ast/MjFile.hpp>


// The parser consumes the output of the scanner and emits the AST components while controlling the parsing context.
class MjFormatter {
private:
    const MjFile &_file;
public:


    static
    std::string format_file(const MjFile &file) noexcept;


private:


    ///
    /// Constructors
    ///


    constexpr
    MjFormatter(const MjFile &file) noexcept :
        _file(file)
    {}


    ///
    /// Token Formatting
    ///


    void print_tokens() noexcept;
};
