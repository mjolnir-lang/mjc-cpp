#include <c/CPrinter.hpp>


void CPrinter::print(const CStructure &structure) {
    print(
        "typedef struct {} {};\n"
        "struct {} {{\n",
        structure.name(),
        structure.name(),
        structure.name()
    );
    indent();

    for () {
        ;
    }

    undent();
    write("}};\n");
}
