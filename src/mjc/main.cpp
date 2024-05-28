//#include <mj/MjCompiler.hpp>
#include <mj/MjLexer.hpp>
//#include <mj/MjParser.hpp>


int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("Usage: mjc <src>\n");
        return 1;
    }

    Path src(argv[1]);
    Path build(src.parent_path() / "build");
    Path app(build / "app");

    if (!FileSystem::is_regular_file(src)) {
        printf("Invalid source file path: %s\n", src.c_str());
        return 1;
    }

    if (FileSystem::exists(build)) {
        //printf("Build directory already exists: '%s'\n", build.c_str());
        //return 1;
        FileSystem::remove_all(build);
    }

    FileSystem::create_directories(build);

    //MjParser parser(src);
    //MjProgram program = parser.parse();

    MjLexer lexer(src);
    lexer.parse();

    //for (const MjToken &token : lexer.tokens()) {
    //    StringView text = lexer.token_text(token);
    //    printf("%.*s\n", text.size(), text.data());
    //}

    return 0;
}
