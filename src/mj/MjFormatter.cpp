#include <mj/MjFormatter.hpp>


std::string MjFormatter::format_file(const MjSourceFile &file, const MjFormatterConfig &config) noexcept {
    MjFormatter formatter{file, config};
    formatter.print_tokens();
    return std::move(formatter._out);
}


void MjFormatter::print_tokens() noexcept {
    MjToken token = &_file.tokens().front();
    MjToken end = &_file.tokens().back();
    MjTokenKind last_token_kind = MjTokenKind::NONE;

    // Handle this case outside the loop since this condition can only be true on the first token.
    if (token.kind() == MjTokenKind::INDENT) {
        write(' ', _config.indent_width * token.indent());
        last_token_kind = token.kind();
        token += token.size();
    }

    while (token < end) {
        if (token.kind().has_whitespace(last_token_kind)) {
            write(' ');
        }

        if (token.kind() == MjTokenKind::INDENT) {
            write('\n');
            write(' ', _config.indent_width * token.indent());
        } else if (token.kind() == MjTokenKind::WHITESPACE) {
            write(' ', token.spaces());
        } else if (token.has_builtin_text()) {
            write(token.builtin_text());
        } else {
            write(_file.text_of(token));
        }

        last_token_kind = token.kind();
        token += token.size();
    }
}
