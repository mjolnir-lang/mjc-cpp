#pragma once

#include "mj/ast/MjAnnotation.hpp"
#include "mj/ast/MjNamespace.hpp"
#include "mj/ast/MjModule.hpp"
#include "mj/ast/MjStatement.hpp"
#include "mj/ast/MjModule.hpp"
#include "mj/ast/MjProgram.hpp"
#include "mj/ast/MjType.hpp"

#include "mj/MjLexer.hpp"


// The parser consumes the output of the lexer and emits the AST components while controlling the parsing context.
class MjParser {
private:
    MjNamespace global_;
    MjNamespace active_;
    MjLexer lexer_;
public:


    MjParser(MjLexer lexer) : lexer_(lexer) {}


    MjProgram parse();


    MjModule &parse_module();


    MjStatement &parse_expression();


    MjStatement &parse_statement();


    MjAnnotation &parse_annotation();
    MjComment &parse_comment();


    /// Type Declarations



    /// Type Definitions


    MjType &parse_type();


    MjBitfieldType &parse_bitfield_definition();


    // Parse a class definition:
    //
    // - Parse the class type declaration (class Name<>)
    // - Parse the class definition scope ({...})
    //     - Parse import statements <-- IN PLACE!!!
    //     - Parse type aliases
    //     - Parse the member, shared, and implementation declarations (everything before '{', '=', or ';')
    //     - Verify type references
    //     - Parse the member, shared, and implementation definitions
    MjClassType &parse_class_definition();


    MjEnumerationType &parse_enumeration_definition();


    MjInterfaceType &parse_interface_definition();


    MjStructureType &parse_structure_type();


    MjUnionType &parse_union_definition();


    MjVariantType &parse_variant_definition();



    /// Type Expressions


    MjType &parse_type_expression();





    MjImportStatement &parse_import_statement();
};
