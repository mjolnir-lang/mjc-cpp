#include <system/ProgramCommand.hpp>
#include <system/logger/Logger.hpp>


void ProgramCommand::reset() {
    for (ProgramOption &opt : _opts) {
        opt.arg().reset();
    }

    for (ProgramArgument &arg : _args) {
        arg.reset();
    }
}


void ProgramCommand::apply_defaults() {
    if () {
        return;
    }

    for (ProgramOption &opt : _opts) {
        opt.arg().reset();
    }

    for (ProgramArgument &arg : _args) {
        arg.reset();
    }
}


ProgramCommand *ProgramCommand::parse(Slice<StringView> args) {
    u32 a = 0;
    bool is_parsing = true;
    ProgramCommand *cmd = this;
    cmd->reset();

    for (StringView str = *args++; str; str = *args++) {
        ProgramArgument *arg = nullptr;
        log_debug("next: '{:s}'", str);

        if (is_parsing && str[0] == '-' && str[1] != '\0' && !Char::is_digit(str[1])) {
            if (str[1] == '-') {
                if (str[2] == '\0') {
                    is_parsing = false;
                    continue;
                }

                StringView opt_str = str.slice(2);
                u32 n = 0;
                for (; opt_str[n] && opt_str[n] != '='; n++);

                // Check for '--help' option.
                if (opt_str.head(n) == "help") {
                    if (opt_str[n]) {
                        log_warn("Unused argument for option! '--{:.*s}'", n, opt_str);
                    }

                    if (!cmd->_help.is_empty()) {
                        System::out.write(cmd->_help);
                    }

                    return nullptr;
                }

                // Look for a matching long option
                u32 i = 0;

                for (; i < cmd->_opts.size(); i++) {
                    ProgramOption &opt = cmd->_opts[i];

                    if (opt_str == opt.long_name().head(n)) {
                        if (opt.arg().type() == ProgramArgumentType::BOOL) {
                            if (opt_str[n]) {
                                log_warn("Unused argument for option! '--{:.*s}'", n, opt_str);
                            }

                            opt.arg().set_value<bool>(true);
                            log_debug("option: '--{:s}'", *opt_str);
                            break;
                        }

                        str = opt_str[n] ? opt_str.slice(n + 1) : *args++;

                        if (!str) {
                            log_error("Missing argument for option! '--{:.*s}'", n, opt_str);
                            return nullptr;
                        }

                        arg = &opt.arg();
                        log_debug("option: '--{:.*s}', '{:s}'", n, opt_str, str);
                        break;
                    }
                }

                if (i == cmd->_opts.size()) {
                    log_error("Unknown option! '--{:.*s}'", n, opt_str);
                    return nullptr;
                }
            } else {

                // Look for a matching short option or short option list
                StringView opt_str = str.slice(1);
                bool is_option_list = opt_str[0] && opt_str[1];

                do {
                    u32 i = 0;

                    for (; i < cmd->_opts.size(); i++) {
                        ProgramOption &opt = cmd->_opts[i];

                        if (*opt_str == opt.short_name()) {
                            if (opt.arg().type() == ProgramArgumentType::BOOL) {
                                opt.arg().set_value<bool>(true);
                                log_debug("option: '-{:c}'", *opt_str);
                                break;
                            } else if (*(opt_str - 1) == '-') {
                                is_option_list = false;
                            }

                            if (is_option_list) {
                                log_error("Non-boolean option cannot be specified in a short option list! '-{:c}'", *opt_str);
                                return nullptr;
                            }

                            str = opt_str[1] ? opt_str.slice(1) : *args++;

                            if (!str) {
                                log_error("Missing argument for option! '-{:c}'", *opt_str);
                                return nullptr;
                            }

                            arg = &opt.arg();
                            log_debug("option: '-{:c}', '{:s}'", *opt_str, str);
                            break;
                        }
                    }

                    if (i == cmd->_opts.size()) {
                        log_error("Unknown option! '-{:c}'", *opt_str);
                        return nullptr;
                    }

                    opt_str += 1;
                } while (is_option_list && *opt_str);
            }
        } else if (cmd->_cmds.size()) {

            // Parse the next string as a subcommand.
            bool found = false;

            for (ProgramCommand &c : cmd->_cmds) {
                if (c._name == str) {
                    cmd = &c;
                    found = true;
                    break;
                }
            }

            if (!found) {

                // Check for 'help' subcommand.
                if (str == "help" && cmd->_help) {
                    System::out.write(cmd->_help);
                    return nullptr;
                }

                log_error("Unknown subcommand! '{:s}'", str);
                return nullptr;
            }

            // Reset the optional and positional argument values.
            cmd->reset();

            // Reset the positional argument counter.
            a = 0;
            log_debug("cmd: '{:s}'", cmd->_name);
            continue;
        } else if (a < cmd->_args.size()) {

            // Parse the next string as a positional argument.
            arg = &cmd->_args[a];

            if (!arg->is_list() || *arg->_count == arg->_max - 1) {
                a += 1;
            }

            log_debug("arg: '{:s}': {:u}", cmd->_name, a - 1);
        } else {
            a += 1;
        }

        // Check for successful conversion.
        if (arg && arg->parse(str)) {
            log_error("Failed to parse argument! '{:s}'", str);
            return nullptr;
        }
    }

    // Check for missing program arguments.
    if (cmd->_cmds.size()) {
        log_error("Missing subcommand!");
        return nullptr;
    }

    // Handle the case where an incomplete positional argument list has not incremented 'a'.
    if (a < cmd->_args.size() && cmd->_args[a].is_list() && *cmd->_args[a].count < cmd->_args[a].max - 1) {
        a += 1;
    }

    i32 n = static_cast<i32>(cmd->_args_required) - a;

    if (n > 0) {
        log_error("Missing {:i} required positional argument{:s}!", n, n == 1 ? "" : "s");
        return nullptr;
    }

    n = static_cast<i32>(a) - cmd->_args.size();

    if (n > 0) {
        log_warn("Ignored {:i} unsupported positional argument{:s}!", n, n == 1 ? "" : "s");
    }

    return cmd;
}


Vector<StringView> ProgramCommand::complete(Slice<StringView> args) {
    Vector<StringView> matches;
    /*
    ProgramArgument *arg = nullptr;
    StringView str = *strs++;
    size_t a = 0;
    bool is_parsing = true;

    for (; (&str)[1]; str = *strs++) {
        arg = nullptr;

        if (is_parsing && str[0] == '-' && str[1] != '\0' && !Char::is_digit(str[1])) {
            if (str[1] == '-') {
                if (str[2] == '\0') {
                    is_parsing = false;
                    continue;
                }

                StringView opt_str = str + 2;
                size_t opt_size = 0;
                for (; opt_str[opt_size] && opt_str[opt_size] != '='; opt_size++);

                for (size_t i = 0; i < cmd->_opts_size; i++) {
                    ProgramOption &opt = cmd->_opts[i];

                    if (opt.long_name && Str::is_equal(opt_str, opt.long_name, opt_size)) {
                        if (opt.arg.type == ProgramArgumentType::BOOL) {
                            *reinterpret_cast<bool *>(opt.arg.value) = true;
                            //lib_debug("option: '--{:s}'", *opt_str);
                            break;
                        }

                        str = opt_str[opt_size] ? &opt_str[opt_size + 1] : *strs++;

                        if (!str) {
                            if (opt.arg.type == ProgramArgumentType::ENUM) {
                                for (const u8 *const *enums = *reinterpret_cast<const u8 *const *>(opt.arg.def); *enums; enums++) {
                                    if (Str::is_equal(str, *enums, str_size)) {
                                        matches.push_back(*enums);
                                    }
                                }
                            }

                            return nullptr;
                        }

                        arg = &opt.arg;
                        break;
                    }
                }
            } else {

                // Look for a matching short option or short option list
                StringView opt_str = str + 1;
                bool is_option_list = opt_str[0] && opt_str[1];

                do {
                    size_t i = 0;

                    for (; i < cmd->_opts_size; i++) {
                        ProgramOption &opt = cmd->_opts[i];

                        if (opt.short_name && *opt_str == opt.short_name) {
                            if (opt.arg.type == ProgramArgumentType::BOOL) {
                                break;
                            } else if (*(opt_str - 1) == '-') {
                                is_option_list = false;
                            }

                            if (is_option_list) {
                                console.error("Non-boolean option cannot be specified in a short option list! '-{:c}'", *opt_str);
                                return nullptr;
                            }

                            str = opt_str[1] ? &opt_str[1] : *strs++;

                            if (!str) {
                                console.error("Missing argument for option! '-{:c}'", *opt_str);
                                return nullptr;
                            }

                            arg = &opt.arg;
                            //lib_debug("option: '-{:c}', '{:s}'", *opt_str, str);
                            break;
                        }
                    }

                    if (i == cmd->_opts_size) {
                        console.error("Unknown option! '-{:c}'", *opt_str);
                        return nullptr;
                    }

                    opt_str += 1;
                } while (is_option_list && *opt_str);
            }
        } else if (cmd->_cmds) {

            if (is_last) {
                if (*str == '\0') {
                    // list of all commands
                } else {
                    // list of matching commands
                }

                return nullptr;
            }

            // Parse the next string as a subcommand.
            bool found = false;

            for (size_t i = 0; i < cmd->_cmds_size; i++) {
                if (Str::is_equal(cmd->_cmds[i].name, str)) {
                    cmd = &cmd->_cmds[i];
                    found = true;
                    break;
                }
            }

            if (!found) {
                return nullptr;
            }

            // Reset the positional argument counter.
            a = 0;
            continue;
        } else if (cmd->_args && a < cmd->_args_size) {

            // Parse the next string as a positional argument.
            arg = &cmd->_args[a];

            if (!arg->_count || *arg->_count == arg->_max - 1) {
                a += 1;
            }
        } else {
            a += 1;
        }
    }

    if (*str) {
        size_t str_size = Str::size(str);

        if (is_parsing && str[0] == '-' && !Char::is_digit(str[1])) {
            if (str[1] == '-') {
                str += 2;
                str_size -= 2;

                if (*str == '\0') {
                    matches.push_back("--");
                }

                if (Str::is_equal(str, "help", str_size)) {
                    matches.push_back("help");
                }

                for (size_t i = 0; i < cmd->_opts_size; i++) {
                    ProgramOption &opt = cmd->_opts[i];

                    if (opt.long_name &&Str::is_equal(opt.long_name, str, str_size)) {
                        matches.push_back(opt.long_name);
                    }
                }
            } else if (str[1] == '\0') {
                str += 1;
                str_size -= 1;
                matches.push_back("-");

                for (size_t i = 0; i < cmd->_opts_size; i++) {
                    ProgramOption &opt = cmd->_opts[i];

                    if (opt.short_name && *str == opt.short_name) {
                        matches.push_back("-");//opt.short_name);
                    }
                }
            }
        } else if (cmd->_cmds) {
            if (Str::is_equal(str, "help", str_size)) {
                matches.push_back("help");
            }

            for (size_t i = 0; i < cmd->_cmds_size; i++) {
                if (Str::is_equal(cmd->_cmds[i].name, str, str_size)) {
                    matches.push_back(cmd->_cmds[i].name);
                }
            }
        } else if (cmd->_args && a < cmd->_args_size && cmd->_args[a].type == ProgramArgumentType::ENUM) {
            for (const u8 *const *enums = reinterpret_cast<const u8 *const *>(cmd->_args[a].def); *enums; enums++) {
                if (Str::is_equal(*enums, str, str_size)) {
                    matches.push_back(*enums);
                }
            }
        }
    } else if (cmd->_cmds) {
        if (Str::is_equal(str, "help")) {
            matches.push_back("help");
        }

        for (size_t i = 0; i < cmd->_cmds_size; i++) {
            matches.push_back(cmd->_cmds[i].name);
        }
    } else if (cmd->_args && a < cmd->_args_size && cmd->_args[a].type == ProgramArgumentType::ENUM) {
        for (const u8 *const *enums = reinterpret_cast<const u8 *const *>(cmd->_args[a].def); *enums; enums++) {
            matches.push_back(*enums);
        }
    }
    */
    return matches;
}
