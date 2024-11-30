#pragma once

#include <system/ProgramOption.hpp>
#include <system/internal/ProgramCommandCallback.hpp>


/// @brief A command.
class ProgramCommand {
private:
    // If the command is the top level command, then this instead contains the
    // message to be printed if the '--version' option is given. The
    // '--version' option is only specially handled for top level commands.
    StringView _name;
    StringView _help; // The usage message printed when '--help' is given
    StringView _version; // The version message printed when '--version' is given
    ProgramCommandCallback _callback; // The callback function
    Slice<ProgramCommand> _cmds; // The list of subcommands
    Slice<ProgramOption> _opts; // The list of optional arguments
    Slice<ProgramArgument> _args; // The list of positional arguments
    u32 _args_required; // The number of required positional arguments
public:


    /// @brief Create a command with no options and no arguments
    constexpr
    ProgramCommand(
        StringView name,
        ProgramCommandCallback callback,
        StringView help = nullptr,
        StringView version = nullptr
    ) :
        _name(name),
        _help(help),
        _version(version),
        _callback(callback),
        _args_required(0)
    {}


    /// @brief Create a command with options.
    constexpr
    ProgramCommand(
        StringView name,
        ProgramCommandCallback callback,
        Slice<ProgramOption> opts,
        StringView help = nullptr,
        StringView version = nullptr
    ) :
        _name(name),
        _help(help),
        _version(version),
        _callback(callback),
        _opts(opts),
        _args_required(0)
    {}


    /// @brief Create a command with arguments.
    constexpr
    ProgramCommand(
        StringView name,
        ProgramCommandCallback callback,
        Slice<ProgramArgument> args,
        u32 args_required,
        StringView help = nullptr,
        StringView version = nullptr
    ) :
        _name(name),
        _help(help),
        _version(version),
        _callback(callback),
        _args(args),
        _args_required(args_required)
    {}


    /// @brief Create a command with options and arguments.
    constexpr
    ProgramCommand(
        StringView name,
        ProgramCommandCallback callback,
        Slice<ProgramOption> opts,
        Slice<ProgramArgument> args,
        u32 args_required,
        StringView help = nullptr,
        StringView version = nullptr
    ) :
        _name(name),
        _help(help),
        _version(version),
        _callback(callback),
        _opts(opts),
        _args(args),
        _args_required(args_required)
    {}


    /// @brief Create a command group.
    constexpr
    ProgramCommand(
        StringView name,
        Slice<ProgramCommand> cmds,
        StringView help = nullptr,
        StringView version = nullptr
    ) :
        _name(name),
        _help(help),
        _version(version),
        _callback(nullptr),
        _cmds(cmds),
        _args_required(0)
    {}


    ///
    /// Properties
    ///


    constexpr
    StringView name() const noexcept {
        return _name;
    }


    /// Return the list of subcommands.
    constexpr
    bool is_group() const noexcept {
        return _cmds;
    }


    /// Return the list of subcommands.
    constexpr
    Slice<ProgramCommand> cmds() noexcept {
        return _cmds;
    }


    ///
    /// Methods
    ///


    /// @brief Reset all sub-commands, optional arguments, and positional arguments to unset state.
    void reset();


    /// @brief Reset all optional and positional arguments to their default values.
    void apply_defaults();


    /// @brief Parse a command and its arguments from a string.
    /// @param cmd The command to parse
    /// @param args The command string
    ProgramCommand *parse(Slice<StringView> args) const noexcept;


    Error run() const noexcept {
        return _callback();
    }


    Error parse_and_run(Slice<StringView> args) const noexcept {
        const ProgramCommand *cmd = parse(args);

        if (cmd == nullptr) {
            return Error::FAILURE;
        }

        return cmd->run();
    }


    /// @brief Return a list of valid completions for a partial command string.
    /// @param cmd The command
    /// @param strs The list of string arguments
    Vector<StringView> complete(Slice<StringView> args);
};
