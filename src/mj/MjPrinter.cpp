#include <mj/MjPrinter.hpp>


void MjPrinter::print(const MjVariable &variable) {

    if (variable.has_alignment()) {
        print(" #{:u}", variable.alignment());
    }

    if (variable.has_address()) {
        print(" @ 0x{:08X}", variable.address());
    }

    print(variable.type(), variable.name().text, variable.is_reference(), variable.is_mutable());

    if (variable.is_mutable()) {
        write("mutable ");
    }

    if (variable.is_reference()) {
        write("&");
    }

    if (variable.has_initializer()) {
        write(" = ");
    }

    write(";");
}


void MjPrinter::print(const MjMember &member) {
    print((MjVariable &) member);
}


void MjPrinter::print(const MjFunction &function) {
    print(function.type(), function.name().text, false, false);
}


void MjPrinter::print(const MjMethod &method) {
    print((MjFunction &) method);
}


void MjPrinter::print(const MjExpression &expression) {

}


void MjPrinter::print(const MjStatement &statement) {
    switch (statement.statement_type()) {
        case MjStatementType::BLOCK: print(dynamic_cast<const MjBlockStatement &>(statement)); break;
        case MjStatementType::BREAK: print(dynamic_cast<const MjBreakStatement &>(statement)); break;
        case MjStatementType::CONTINUE: print(dynamic_cast<const MjContinueStatement &>(statement)); break;
        case MjStatementType::DO: print(dynamic_cast<const MjDoStatement &>(statement)); break;
        case MjStatementType::DO_UNTIL: print(dynamic_cast<const MjDoUntilStatement &>(statement)); break;
        case MjStatementType::DO_WHILE: print(dynamic_cast<const MjDoWhileStatement &>(statement)); break;
        case MjStatementType::FOR: print(dynamic_cast<const MjForStatement &>(statement)); break;
        case MjStatementType::FOR_EACH: print(dynamic_cast<const MjForEachStatement &>(statement)); break;
        case MjStatementType::IF: print(dynamic_cast<const MjIfStatement &>(statement)); break;
        case MjStatementType::IMPORT: print(dynamic_cast<const MjImportStatement &>(statement)); break;
        case MjStatementType::MATCH: print(dynamic_cast<const MjMatchStatement &>(statement)); break;
        case MjStatementType::RETURN: print(dynamic_cast<const MjReturnStatement &>(statement)); break;
        case MjStatementType::UNTIL: print(dynamic_cast<const MjUntilStatement &>(statement)); break;
        case MjStatementType::WHILE: print(dynamic_cast<const MjWhileStatement &>(statement)); break;
        case MjStatementType::YIELD: print(dynamic_cast<const MjYieldStatement &>(statement)); break;
    }
}


void MjPrinter::print(const MjBlockStatement &block_statement) {
    newline();
    write("{");
    indent();

    for (const MjStatement *statement : block_statement.statements()) {
        print(*statement);
    }

    indent();
    newline();
    write("}");
}


void MjPrinter::print(const MjBreakStatement &break_statement) {
    newline();
    print("break {:u32};", break_statement.depth());
}


void MjPrinter::print(const MjContinueStatement &continue_statement) {
    newline();
    print("continue {:u32};", continue_statement.depth());
}


void MjPrinter::print(const MjDoStatement &do_statement) {
    newline();
    write("do ");
    print(do_statement.block());
}


void MjPrinter::print(const MjDoUntilStatement &do_until_statement) {
    newline();
    write("do ");
    print(do_until_statement.do_block());
    write(" until (");
    print(do_until_statement.condition());

    if (do_until_statement.until_block().statements().is_empty()) {
        write(");");
    } else {
        write(") ");
        print(do_until_statement.until_block());
    }
}


void MjPrinter::print(const MjDoWhileStatement &do_while_statement) {
    newline();
    write("do ");
    print(do_while_statement.do_block());
    write(" while (");
    print(do_while_statement.condition());

    if (do_while_statement.while_block().statements().is_empty()) {
        write(");");
    } else {
        write(") ");
        print(do_while_statement.while_block());
    }
}


void MjPrinter::print(const MjForStatement &for_statement) {
    newline();
    write("for (");
    print(for_statement.statement());
    write("; ");
    print(for_statement.condition());
    write("; ");
    print(for_statement.expression());
    write(") ");
    print(for_statement.block());
}


void MjPrinter::print(const MjForEachStatement &for_each_statement) {
    newline();
    write("for (");
    print(for_each_statement.statement());
    write(" in ");
    print(for_each_statement.expression());
    write(") ");
    print(for_each_statement.block());
}


void MjPrinter::print(const MjIfStatement &if_statement) {
    newline();
    write("if (");

    if (if_statement.has_init_statement()) {
        print(if_statement.init_statement());
        write("; ");
    }

    print(if_statement.condition());

    if (if_statement.if_block().statements().is_empty()) {
        write(");");
    } else {
        write(") ");
        print(if_statement.if_block());

        if (!if_statement.else_block().statements().is_empty()) {
            write(" else ");
            print(if_statement.else_block());
        }
    }
}


void MjPrinter::print(const MjImportStatement &import_statement) {
    newline();
    write("import ");
    print(import_statement.module());
}


void MjPrinter::print(const MjMatchStatement &match_statement) {
    newline();
    write("match (");
    print(match_statement.expression());
    write(")");

    for (const MjPatternStatement *pattern : match_statement.patterns()) {
        newline();
        print(pattern->expression());
        write(" => ");
        print(pattern->statement());
    }

    newline();
    write("}");
}


void MjPrinter::print(const MjReturnStatement &return_statement) {
    newline();
    write("return ");
    print(return_statement.expression());
    write(";");
}


void MjPrinter::print(const MjUntilStatement &until_statement) {
    newline();
    write("until (");
    print(until_statement.condition());

    if (until_statement.block().statements().is_empty()) {
        write(");");
    } else {
        write(") ");
        print(until_statement.block());
    }
}


void MjPrinter::print(const MjWhileStatement &while_statement) {
    newline();
    write("while (");
    print(while_statement.condition());

    if (while_statement.block().statements().is_empty()) {
        write(");");
    } else {
        write(") ");
        print(while_statement.block());
    }
}


void MjPrinter::print(const MjYieldStatement &statement) {
    newline();
    write("yield ");
    print(statement.value());
    write(";");
}


void MjPrinter::print(const MjType &type, const String *name, bool is_reference, bool is_mutable) {
    if (type.is_const()) {
        write("const ");
    }

    if (type.is_volatile()) {
        write("volatile ");
    }

    if (is_mutable) {
        write("mutable ");
    }

    if (is_reference) {
        write("&");
    }
}


void MjPrinter::print(const MjBitfieldType &bitfield_type) {

}


void MjPrinter::print(const MjClassType &class_type) {

    // Print the class declaration.
    newline();
    print("class {:s}", &class_type.name());

    if (!class_type.template_parameters().is_empty()) {

        // Write the template parameter list.
        write("<");
        bool once = true;

        for (MjTemplateParameter *type : class_type.template_parameters()) {
            if (once) once = false; else write(", ");
            print(*type);
        }

        write(">");
    }

    write(" {");
    indent();

    // Print the members.
    for (const MjMember *member : class_type.members()) {
        newline();
        print(*member);
    }

    // Print the constructors.
    for (const MjMethod *constructor : class_type.constructors()) {
        newline();
        print(*constructor);
    }

    // Print the destructors.
    newline();
    print(class_type.destructor());

    // Print the methods.
    for (const MjMethod *method : class_type.methods()) {
        newline();
        print(*method);
    }

    // Print the operators.
    for (const MjOperator *op : class_type.operators()) {
        newline();
        print(*op);
    }

    // Print the implementations.
    for (const MjImplementation *impl : class_type.implementations()) {
        newline();
        print(*impl);
    }

    // Print the type definitions.
    for (const MjType *type : class_type.member_types()) {
        newline();
        print(*type);
    }


    // shared/public/private


    undent();
    newline();
    write("}");
}


void MjPrinter::print(const MjEnumerationType &enumeration_type) {
    newline();
    write("enum<");
    print(enumeration_type.index_type());
    write("> ");
    print(enumeration_type.name());
    write(" {");
    indent();

    // Print the members.
    for (const MjMember *member : enumeration_type.members()) {
        newline();
        print(*member);
    }

    undent();
    newline();
    write("}");
}


void MjPrinter::print(const MjImplementation &implementation) {

}


void MjPrinter::print(const MjInterfaceType &interface_type) {

}


void MjPrinter::print(const MjStructureType &structure_type) {

    // Print the struct declaration.
    newline();
    write("struct ");

    if (!structure_type.is_anonymous()) {
        write(structure_type.name());

        if (!structure_type.template_parameters().is_empty()) {

            // Write the template parameter list.
            write("<");
            bool once = true;

            for (MjTemplateParameter *type : structure_type.template_parameters()) {
                if (once) once = false; else write(", ");
                print(*type);
            }

            write(">");
        }
    }

    write(" {");
    indent();

    for (MjMember *member : structure_type.members()) {
        newline();
        print(*member);
    }

    undent();
    newline();
    write("}");
}


void MjPrinter::print(const MjUnionType &union_type) {

    // Print the union declaration.
    newline();
    write("union ");

    if (!union_type.is_anonymous()) {
        write(union_type.name());

        if (!union_type.template_parameters().is_empty()) {

            // Write the template parameter list.
            write("<");
            bool once = true;

            for (MjTemplateParameter *type : union_type.template_parameters()) {
                if (once) once = false; else write(", ");
                print(*type);
            }

            write(">");
        }
    }

    write(" {");
    indent();

    for (MjMember *member : union_type.members()) {
        newline();
        print(*member);
    }

    undent();
    newline();
    write("}");
}


void MjPrinter::print(const MjVariantType &variant_type) {

    // Print the variant declaration.
    newline();
    write("variant ");

    if (!variant_type.is_anonymous()) {
        write(variant_type.name().text);

        if (!variant_type.template_parameters().is_empty()) {

            // Write the template parameter list.
            write("<");
            bool once = true;

            for (MjType *type : variant_type.template_parameters()) {
                if (once) once = false; else write(", ");
                print(*type);
            }

            write(">");
        }
    }

    write(" {");
    indent();

    for (MjMember *member : variant_type.members()) {
        newline();
        print(*member);
    }

    undent();
    newline();
    write("}");
}


// recursive base then self
void MjPrinter::print_left(const MjArrayType &array_type) {
    print(array_type.base());
}


// recursive self then base
void MjPrinter::print_right(const MjArrayType &array_type) {
    write("[");

    if (array_type.size()) {
        print(array_type.size());
    }

    write("]");
    print(array_type.base());
}


void MjPrinter::print_left(const MjBasicType &basic_type) {
    write(basic_type.name().text);

    if (!basic_type.template_parameters().is_empty()) {

        // Write the template parameter list.
        write("<");
        bool once = true;

        for (MjType *type : basic_type.template_parameters()) {
            if (once) once = false; else write(", ");
            print(*type);
        }

        write(">");
    }
}


void MjPrinter::print_right(const MjBasicType &basic_type) {

}


void MjPrinter::print(const MjModule &module) {
    // Single file.
}


void MjPrinter::print(const MjProgram &program) {
    // Multiple files.
}
