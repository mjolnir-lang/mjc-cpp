#include <c/CPrinter.hpp>






void CPrinter::print_type_declaration(const CType &type) {
    switch (type.type()) {
    case CTypeType::VOID:
    case CTypeType::ARRAY:
    case CTypeType::POINTER:
    case CTypeType::FUNCTION:
    case CTypeType::ENUMERATION:
    case CTypeType::STRUCTURE:
        print_structure_type_declaration(type);
    default:
    }
}


void CPrinter::print_type_definition(const CType &type) {
}


void CPrinter::print_type_name(const CType &type) {
}






void CPrinter::print_structure_type_declaration(const CStructureType &type) {
    print(
        "typedef struct {} {};\n"
        "struct {} {{\n",
        type.name(),
        type.name(),
        type.name()
    );
    indent();

    for () {
        ;
    }

    undent();
    write("}};\n");
}


void CPrinter::print_structure_type_definition(const CStructureType &type) {
}


void CPrinter::print_structure_type_name(const CStructureType &type) {
}
