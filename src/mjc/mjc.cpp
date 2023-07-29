#include "mj/compiler/MjCompiler.hpp"
#include "mj/parser/MjScanner.hpp"
#include "mj/parser/MjParser.hpp"

#include "std/File.hpp"


int main(int argc, const char *argv[]) {
    if (argc < 3) {
        printf("usage: mjc <src> <out>");
        return 1;
    }

    Path src(argv[1]);
    Path app(argv[2]);

    if (!std::filesystem::is_regular_file(src)) {
        printf("Invalid source file path: %s\n", src.c_str());
        return 1;
    }

    if (!std::filesystem::is_directory(app.parent_path())) {
        printf("Invalid output path: %s\n", app.parent_path().c_str());
        return 1;
    }

    Path build(app.parent_path() / "build");

    if (std::filesystem::exists(build)) {
        printf("Build directory alreay exists: {build}");
        //return 1
        std::filesystem::remove_all(build);
    }

    printf("src:   %s\n", src);
    printf("app:   %s\n", app);
    printf("build: %s\n", build);

    std::filesystem::create_directories(build);

    MjParser parser(src);
    MjProgram program = parser.parse();
    program.export_source(build);
    return 0;
}
