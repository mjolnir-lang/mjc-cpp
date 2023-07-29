#include "mj/MjParser.hpp"


MjProgram MjParser::parse() {
    //MjScanner scanner(src);

    //token = scanner.next()
    //while token:
        //print(str(token))
        //print(token.text, end="")
        //print("\n" if token.text and token.text in "{};" else " ", end="")
        //token = scanner.next()

    return MjProgram();
}


MjModule &MjParser::parse_module() {
    Path path(".");

    // Parse module imports
    while (*scanner_.next() == MjToken::IMPORT) {
        while (*scanner_.next() != MjToken::SEMICOLON) {
            const MjToken *token = scanner_.expect_any(MjTokenType::IDENTIFIER);

            if (token) {
                path.append(token->str());
            } else if (*token == MjToken::SUB) {
                path.append('-', true);
            } else if (*token == MjToken::DOT) {
                path.append('/', true);
            }
        }
    }

    MjModule mod(path);

    // Parse module global scope
    mod.scope = parse_scope();
    return mod;
}


MjImportStatement &MjParser::parse_import_statement() {
    Path path(".");

    // Parse module imports
    while (*scanner_.next() == MjToken::IMPORT) {
        while (*scanner_.next() != MjToken::SEMICOLON) {
            const MjToken *token = scanner_.expect_any(MjTokenType::IDENTIFIER);

            if (token) {
                path.append(token->str());
            } else if (*token == MjToken::SUB) {
                path.append('-', true);
            } else if (*token == MjToken::DOT) {
                path.append('/', true);
            }
        }
    }

    MjModule mod(path);

    // Parse module global scope
    MjImportStatement &import_statement = import_statements_.allocate();
    return import_statement;
}


MjStatement &MjParser::parse_expression() {
    MjExpression &expression = expressions_.allocate();
    return expression;
}


MjStatement &MjParser::parse_statement() {
    const MjToken &token = *scanner_.next();

    // Check for statement and type declaration keywords.

    if (token == MjToken::BREAK) {
        const MjToken *depth = scanner_.expect_any(MjTokenType::NUMBER);
        return MjBreakStatement(depth);
    }

    if (token == MjToken::CONTINUE) {
        const MjToken *depth = scanner_.expect_any(MjTokenType::NUMBER);
        return MjContinueStatement(depth);
    }

    if (token == MjToken::CLASS) {
        return MjClassDeclaration();
    }

    if (token == MjToken::DO) {
        // 
        return MjDoStatement();
        return MjDoUntilStatement();
        return MjDoWhileStatement();
    }

    if (token == MjToken::ELSE) {
        // should not get here!
    }

    if (token == MjToken::ENUM) {
        return MjEnumerationDeclaration();
    }

    if (token == MjToken::FAIL) {
        // 
    }

    if (token == MjToken::FOR) {
        // 
    }

    if (token == MjToken::IF) {
        // 
        return MjIfStatement();
        return MjIfElseStatement();
    }

    if (token == MjToken::IMPLEMENTS) {
        // 
    }

    if (token == MjToken::IMPORT) {
        // Scope dictates the import type (public/private)
    }

    if (token == MjToken::INTERFACE) {
        // Only at module scope!
    }

    if (token == MjToken::MATCH) {
        // 

        // Parse all the cases.
        while () {
            ;
        }
    }

    if (token == MjToken::RETURN) {
        // 
    }

    if (token == MjToken::SHARED) {
        // 
    }

    if (token == MjToken::STRUCT) {
        // 
    }

    if (token == MjToken::TYPE) {
        // 
    }

    if (token == MjToken::UNION) {
        // 
    }

    if (token == MjToken::UNTIL) {
        // 
    }

    if (token == MjToken::VARIANT) {
        // 
    }

    if (token == MjToken::WHILE) {
        // 
    }

    if (token == MjToken::YIELD) {
        // 
    }

    // Check for a variable declaration.
    if (token.is_type()) {
        ;
    }

    // Check for an expression.
    return parse_expression();
}


MjType &MjParser::parse_type() {
    MjType &type = types_.allocate();
    return type;
}


MjUnit &MjParser::parse_unit() {
    MjUnit &unit = units_.allocate();
    // parse an expression
    // operators: */^+-()
    // identifiers + special unicode characters

    while (true) {
        if (ch >= '0' && ch <= '9') {
            ;// digit
        }
    }
    return unit;
}


MjBitfieldType &MjParser::parse_bitfield_definition() {

}


// Parse a class definition:
//
// - Parse the class type declaration (class Name<>)
// - Parse the class definition scope ({...})
//     - Parse import statements <-- IN PLACE!!!
//     - Parse type aliases
//     - Parse the member, shared, and implementation declarations (everything before '{', '=', or ';')
//     - Verify type references
//     - Parse the member, shared, and implementation definitions
MjClassType &MjParser::parse_class_definition() {
    scanner_.expect(MjToken::CLASS);
    MjType &type = parse_type();
    MjToken &name = scanner.expect_any(MjTokenType::IDENTIFIER);
    templates;
    scanner_.expect(MjToken::OA);

    types;
    members;
    methods;

    // Scan the class.
    while (true) {
        MjToken token = scanner.peek();

        if (token == MjToken::CB) {
            break;
        } else if (token == MjToken::SHARED) {
            ;
        } else if (token == MjToken::IMPLEMENTS) {
            ;
        } else if (token == MjToken::TYPE) {
            scanner_.next();
            typevar = parse_variable();
            types.append(MjType(typevar.name, ));
        } else {
            type = parse_type();

            if (isinstance(type, MjFunctionType)) {
                methods.append(type);

                if (*scanner_.next() == MjToken::OB) {
                    depth = 1;

                    while (depth) {
                        token = scanner.next();

                        if (token == Tokens.OB) {
                            depth += 1;
                        } else if (token == Tokens.CB) {
                            depth -= 1;
                        }

                        method_body.append(token);
                    }
                } else if (token == MjToken::SET) {
                    ;
                } else if (token == MjToken::SEMICOLON) {
                    // Method declarations belong in interfaces!
                    raise SyntaxError("Classes may not contain method declarations!");
                }
            }

            members.append(type);
        }
    }

    MjClassType &class_definition = class_definitions_.allocate(

    );

    return class_definition;
}


MjEnumerationType &MjParser::parse_enumeration_definition() {

    MjEnumerationType &enumeration_definition = enumeration_definitions_.allocate(

    );
    scanner.expect(MjToken::ENUM);
    scanner.expect(MjToken::OA);
    MjType &index_type = parse_type();
    scanner.expect(MjToken::CA);
    MjToken &name = scanner.expect_any(MjTokenType::IDENTIFIER);
    return enumeration_definition;
}


MjInterfaceType &MjParser::parse_interface_definition() {

    MjInterfaceType &interface_definition = interface_definitions_.allocate(

    );

    return interface_definition;
}


MjStructureType &MjParser::parse_structure_type() {

    // Parse the structure declaration.
    scanner_.expect(MjToken::STRUCT);
    MjStructureType this(name, type);
    MjType type = parse_type();
    MjToken *name = scanner.expect_any(MjTokenType::IDENTIFIER);

    // Parse the structure definition.
    while (1) {
        switch ((uintptr_t) scanner.peek()) {
        case (uintptr_t) &MjToken::SHARED:
            break;
        case (uintptr_t) &MjToken::IMPLEMENTS:
            break;
        case (uintptr_t) &MjToken::CLASS:
            types_.append(parse_class_type());
            break;
        case (uintptr_t) &MjToken::STRUCT:
            types_.append(parse_structure_type());
            break;
        case (uintptr_t) &MjToken::UNION:
            types_.append(parse_union_type());
            break;
        case (uintptr_t) &MjToken::ENUM:
            types_.append(parse_enumeration_type());
            break;
        case (uintptr_t) &MjToken::TYPE:
            types_.append(parse_type_alias());
            break;
        default:
            return nullptr;
        }
    }

    return this;
}


MjUnionType &MjParser::parse_union_definition() {

}


MjVariantType &MjParser::parse_variant_definition() {

}


MjComment &MjParser::parse_comment() {

}

MjAnnotation &MjParser::parse_annotation() {

}
