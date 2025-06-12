#pragma once

#include <mj/ast/MjSourceFile.hpp>


// The parser consumes the output of the scanner and emits the AST components while controlling the parsing context.
class MjFormatter {
private:
    const MjSourceFile &_file;
public:


    static
    std::string format_file(const MjSourceFile &file) noexcept;


private:


    ///
    /// Constructors
    ///


    constexpr
    MjFormatter(const MjSourceFile &file) noexcept :
        _file(file)
    {}


    ///
    /// Token Formatting
    ///


    void print_tokens() noexcept;
};
