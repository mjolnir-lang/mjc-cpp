//#include <mj/MjCompiler.hpp>
//#include <mj/MjLexer.hpp>
//#include <mj/MjParser.hpp>

#include <system/ProgramCommand.hpp>
#include <system/Program.hpp>
#include <filesystem>


struct Args {
    std::filesystem::path build_dir;
    std::filesystem::path source_dir;
    std::filesystem::path output_file;
    std::vector<std::filesystem::path> include_dirs;

    StringView target_name;
    StringView arch_name;
    StringView cpu_name;

    bool debug;
    bool asm_only;
    bool obj_only;
    bool shared;
    bool color;
    bool no_color;
    bool interactive;
    bool quiet;
    bool verbose;
    bool dep;
} args;


Error compile() noexcept {
    //FilePath src(argv[1]);
    //FilePath build(src.parent_path() / "build");
    //FilePath app(build / "app");

    //if (!FileSystem::is_regular_file(src)) {
    //    Process::STDERR.print("Invalid source file path: %s\n", src.c_str());
    //    return Error::FAILURE;
    //}

    //if (FileSystem::exists(build)) {
        //printf("Build directory already exists: '%s'\n", build.c_str());
        //return Error::FAILURE;
        //FileSystem::remove_all(build);
    //}

    //FileSystem::create_directories(build);

    //MjParser parser(src);
    //MjProgram program = parser.parse();

    //MjLexer lexer(src);
    //lexer.parse();

    //for (const MjToken &token : lexer.tokens()) {
    //    StringView text = lexer.token_text(token);
    //    printf("%.*s\n", text.size(), text.data());
    //}

    return Error::SUCCESS;
}


const ProgramCommand program_cmd{
    "mjc",
    &compile,
    {
        ProgramOption('I', "include",     &args.include_dirs),
        ProgramOption('b', "build",       &args.build_dir),
        ProgramOption('o',                &args.output_file),
        ProgramOption('t', "target",      &args.target_name),
        ProgramOption(     "arch",        &args.arch_name),
        ProgramOption(     "cpu",         &args.cpu_name),
        ProgramOption('O',                &args.output_file),
        ProgramOption('g', "debug",       &args.debug),
        ProgramOption('c', "asm-only",    &args.asm_only),
        ProgramOption('S', "obj-only",    &args.obj_only),
        ProgramOption('m', "shared",      &args.shared),
        ProgramOption(     "color",       &args.color),
        ProgramOption(     "no-color",    &args.no_color),
        ProgramOption('i', "interactive", &args.interactive),
        ProgramOption('q', "quiet",       &args.quiet),
        ProgramOption('v', "verbose",     &args.verbose),
        ProgramOption(     "dep",         &args.dep),
    }, {
        ProgramArgument(&args.source_dir),
    },
    1,
    "Usage: mjc [options] [src]\n"
    "\n"
    "The Mjolnir compiler\n"
    "\n"
    "Compile modules and applications.\n"
    "\n"
    "Example: mjc -O size -o app -t x86-64 format/JSON\n"
    "\n"
    "Source Options:\n"
    "      --sysroot=PATH   The module root path (default: MJOLNIR_SYSROOT)\n"
    "  -I, --include=DIR    Add a module path to the search order (repeatable)\n"
    "  -b, --build=DIR      The build directory (default: SRC/build)\n"
    "  -o, --output=FILE    The output file (default: SRC/build/MOD[.mjo])\n"
    "\n"
    "Compilation Options:\n"
    "  -t, --target=NAME    The target platform name\n"
    "      --arch=NAME      The target architecture name\n"
    "      --cpu=NAME       The target cpu name\n"
    "  -O LEVEL             The optimization level (0, 1, 2, size)\n"
    "  -g, --debug          Build in debug mode\n"
    "  -c, --asm-only       Compile only. Do not assemble or link\n"
    "  -S, --obj-only       Compile and assemble. Do not link\n"
    "  -m, --shared         Compile as a shared module\n"
    "\n"
    "Output Options:\n"
    "      --color          Output color in console mode\n"
    "      --no-color       Do not output color\n"
    "  -i, --interactive    Run in interactive mode\n"
    "  -q, --quiet          Build in quiet mode\n"
    "  -v, --verbose        Build in verbose mode\n"
    "\n"
    "Miscellaneous:\n"
    "      --dep            Display the module dependency tree and exit\n"
    "      --help           Display this message and exit\n"
    "      --version        Display the application name and version and exit\n"
    "\n"
    "Arguments:\n"
    "  src                  The target path (default: <current directory>)\n",
    "mjc 0.0.0"
};


int main(int argc, const char *argv[]) {
    Vector<StringView> args;

    for (u32 i = 1; i < argc; ++i) {
        args.push_back(argv[i]);
    }

    return program_cmd.parse_and_run({args.data(), args.size()});
}
