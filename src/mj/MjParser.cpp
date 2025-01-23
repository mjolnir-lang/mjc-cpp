#include <mj/MjParser.hpp>

#include <mj/ast/MjBitfieldTypeDefinition.hpp>
#include <mj/ast/MjClassTypeDefinition.hpp>
#include <mj/ast/MjFunctionDefinition.hpp>

#include <mj/ast/MjImportDirective.hpp>

#include <mj/ast/MjBlockStatement.hpp>
#include <mj/ast/MjBreakStatement.hpp>
#include <mj/ast/MjContinueStatement.hpp>
#include <mj/ast/MjDoStatement.hpp>
#include <mj/ast/MjExpressionStatement.hpp>
#include <mj/ast/MjIfStatement.hpp>
#include <mj/ast/MjReturnStatement.hpp>
#include <mj/ast/MjUntilStatement.hpp>
#include <mj/ast/MjWhileStatement.hpp>
#include <mj/ast/MjYieldStatement.hpp>

#include <filesystem>


void MjParser::error(StringView message) noexcept {
    _errors.append(_token, message);
}


MjProgram MjParser::parse(const MjFile &file) noexcept {
    MjProgram program{file};
    program.parse_module();
    return program;
}















MjModule *MjParser::parse_module(std::filesystem::path path) noexcept {
    if (!std::filesystem::is_directory(path)) {
        error("Invalid module path! '{}'", path);
        return;
    }

    MjModule *mod = new MjModule();
    std::vector<std::filesystem::path> file_paths = std::filesystem::list_directory(path);

    // Verify module path.
    for (std::filesystem::path &path : file_paths) {
        if (std::filesystem::is_regular_file(path) && path.extension() == "mj") {
            parse_file(*mod, path);
        } else if (std::filesystem::is_directory(path)) {
            mod->modules().push_back(parse_module(path));
        }
    }


    // List files and directories.

    // list internal

    // list external

    // parse files
    for (std::filesystem::path &path : file_paths) {
        if (std::filesystem::is_regular_file(path) && path.extension() == "mj") {
            parse_file(*mod, path);
        }

        if (std::filesystem::is_directory(path) && path.filename() == "@internal") {
            std::vector<std::filesystem::path> file_paths = std::filesystem::list_directory(path);
        }
    }

    // parse submodules
    for (std::filesystem::path &path : file_paths) {
        if (std::filesystem::is_directory(path)) {
            mod->modules().push_back(parse_module(path));
        }
    }
}







MjItem *MjParser::parse_item() noexcept {
    //switch () {}
    return nullptr;
}









MjStatement *MjParser::parse_statement() noexcept {
    const MjToken *start = _token;
    MjStatement *statement = nullptr;

    switch (_token->kind()) {
    case MjTokenKind::OPEN_CURLY_BRACE: {
        MjBlockStatement *statement = new MjBlockStatement();

        while (true) {
            MjStatement *s = parse_statement();

            if (s == nullptr) {
                break;
            }

            statement->statements().append(s);
        }

        parse_token(MjTokenKind::CLOSE_CURLY_BRACE);
        statement->set_tokens(tokens_since(start));
        return statement;
    } case MjTokenKind::BREAK: {
        MjBreakStatement *statement = new MjBreakStatement();

        if (match_token(MjTokenKind::INDENT)) {
            MjExpression *depth = parse_expression();

            if (depth != nullptr) {
                if (depth->result_type() != MjBuiltinTypes::INT) {
                    error("Expected an expression!");
                } else {
                    statement->set_depth(depth);
                }
            }
        }

        statement->set_tokens(tokens_since(start));
        return statement;
    } case MjTokenKind::CONTINUE: {
        MjContinueStatement *statement = new MjContinueStatement();
        MjExpression *depth = parse_expression();
        statement->set_depth(depth);
        statement->set_tokens(tokens_since(start));
        return statement;
    } case MjTokenKind::CLASS: {
        MjClassDefinition *statement = new MjClassDefinition();

        // Consume the 'class' token.
        const MjToken *class_start = parse_token(MjTokenKind::CLASS);

        // Parse the name of the class type.
        const MjToken *class_name = parse_token(MjTokenKind::TYPE_NAME);

        if (class_name == nullptr) {
            error("Expected a type name after 'class'!");
            reset(start);
            return nullptr;
        }

        // Parse either a template argument list, or a template, or a partial specialization.
        if (parse_token(MjTokenKind::OPEN_ANGLE_BRACKET)) {
            MjTemplateArgumentList *template_argument_list = parse_template_argument_list();

            if (template_argument_list == nullptr) {
                // Non-template class type definitition.
            } else if (template_argument_list->is_pure()) {
                // Full class type template definition.
            } else if () {
                // Partial class type template definition.
            }
        }

        // Parse the optional inline variable declaration.
        if (match_token(MjTokenKind::VARIABLE_NAME) || match_token(MjTokenKind::CONSTANT_NAME)) {
            const MjToken *instance_name = parse_token();
        }

        // Parse the class type definition.
        while (true) {
            MjStatement *s = parse_statement();

            switch (s->type()) {
            case MjStatementType::STRUCTURE_DEFINITION:
                break;
            case MjStatementType::UNION_DEFINITION:
                break;
            case MjStatementType::CLASS_DEFINITION:
                break;
            case MjStatementType::ENUMERATION_DEFINITION:
                break;
            }

            statement->block_statements().append(s);
        }

        statement->set_tokens(tokens_since(start));
        return statement;
    } case MjTokenKind::DO: {
        if (!match_token(MjTokenKind::OPEN_CURLY_BRACE)) {
            error("Expected '{' after 'do'!");
            return nullptr;
        }

        MjStatement *body = parse_statement();
        Slice<const MjToken> tokens = Slice<const MjToken>(_token, 1);
        MjStatement *statement = new MjStatement(MjStatementType::DO);
    } case MjTokenKind::ELSE: {
        // should not get here!
        error("Keyword 'else' must follow 'if' block!");

        if (match_token(MjTokenKind::OPEN_CURLY_BRACE)) {
            parse_statement();
        }
    } case MjTokenKind::ENUM: {
        return parse_type_enumeration();
    } case MjTokenKind::FAIL: {
        return parse_fail_statement();
    } case MjTokenKind::FOR: {
        // 
    } case MjTokenKind::IF: {
        // Always succeeds.
        parse_token(MjTokenKind::OPEN_PARENTHESIS);

        MjExpression *condition = parse_expression();

        if (condition == nullptr) {
            error("Missing condition!");
            return nullptr;
        }

        if (!parse_token(MjTokenKind::CLOSE_PARENTHESIS)) {
            error("Missing ')'!");
            return nullptr;
        }

        MjStatement *if_block = parse_block_statement();

        if (if_block == nullptr) {
            error("Missing if block statement!");
            return nullptr;
        }

        MjStatement *else_block = nullptr;

        if (parse_token(MjTokenKind::ELSE)) {
            else_block = parse_block_statement();

            if (else_block == nullptr) {
                else_block = parse_if_statement();
            }

            if (else_block == nullptr) {
                error("Expected an 'if' statement or a 'block' statement after 'else'!");
                return nullptr;
            }
        }

        return &MjStatement(nullptr, condition, if_block, else_block);
    } case MjTokenKind::IMPL: {
        // 
    } case MjTokenKind::IMPORT: {
        // Scope dictates the import type (public/private)
        std::filesystem::path path(".");

        // Parse module imports
        while (parse_token(MjTokenKind::IMPORT)) {
            while (parse_token(MjTokenKind::SEMICOLON)) {
                const MjToken *token = parse_token();

                switch (token->kind) {
                case MjTokenKind::IDENTIFIER:
                    path.append(token->str());
                    break;
                case MjTokenKind::MINUS:
                    path.append('-', true);
                    break;
                case MjTokenKind::DOT:
                    path.append('/', true);
                    break;
                default:
                    error("Invalid module path!");
                    return nullptr;
                }
            }
        }

        MjModule mod(path);

        // Parse module global scope
        return new MjStatement(MjStatementType::IMPORT);
    } case MjTokenKind::INTERFACE: {
        // Only at module scope!
    } case MjTokenKind::MATCH: {
        // 

        // Parse all the cases.
        while () {
            ;
        }
    } case MjTokenKind::RETURN: {
        return new MjStatement(MjStatementType::RETURN, parse_expression());
    } case MjTokenKind::STRUCT: {
        // 
    } case MjTokenKind::TYPE: {
        skip_token();
        parse_token(MjTokenKind::OPEN_ANGLE_BRACKET);

        MjType *type = parse_type_expression();

        if (type == nullptr) {
            error("Missing type expression!");
        }

        parse_token(MjTokenKind::CLOSE_ANGLE_BRACKET);

        if (type == nullptr) {
            error("Missing type expression!");
        }

        const MjToken *type_name = parse_token(MjTokenKind::TYPE_NAME);

        if (type == nullptr) {
            error("Missing type expression!");
        }

        return new MjType(MjTypeType::ALIAS, type_name, type);
    } case MjTokenKind::UNION: {
        // 
    } case MjTokenKind::UNTIL: {
        // 
    } case MjTokenKind::VARIANT: {
        // 
    } case MjTokenKind::WHILE: {
        if (parse_token(MjTokenKind::OPEN_PARENTHESIS) == nullptr) {
            ;
        }

        MjExpression *loop_condition = parse_expression();

        if (parse_token(MjTokenKind::CLOSE_PARENTHESIS) == nullptr) {
            ;
        }

        MjStatement *loop_body = parse_block_statement();
        return new MjStatement(MjStatementType::WHILE, loop_condition, loop_body);
    } case MjTokenKind::YIELD: {
        MjExpression *return_value = parse_expression();

        if (return_value == nullptr) {
            ;
        }

        return new MjYieldStatement(return_value);
    }
    }

    // Check for an expression.
    return parse_expression();
}


















MjExpression *MjParser::parse_expression(u32 min_bp) {
    /// This is a Pratt parser implementation.
    ///
    /// We consider the binding power of an operator to convey both associativity and precedence.
    /// Binding power is the edge of a graph where both operators and terminals are the nodes.
    /// Terminals are bound to only one operator at a time and the greatest binding power
    /// wins.
    ///
    /// 
    MjExpression *lhs = nullptr;
    const MjToken *start = _token;

    switch (_token->kind()) {

    case MjTokenKind::OPEN_CAST: {
        parse_token();
        MjType *type = parse_type();
        parse_token(MjTokenKind::COLON);
        lhs = parse_expression();
        parse_token(MjTokenKind::CLOSE_CAST);
    }

    case MjTokenKind::TYPE_NAME: {
        MjType *type = parse_type();

        switch (_token->kind()) {
        case MjTokenKind::OPEN_PARENTHESIS: {
            MjFunctionParameterList *fpl = parse_function_parameter_list();
            lhs = new MjExpression(tokens_since(start), type, fpl);
            break;
        }

        case MjTokenKind::OPEN_CURLY_BRACE: {
            MjStatement *statement = parse_statement();
            lhs = new MjExpression(tokens_since(start), type, statement);
            break;
        }
        default:
            error("Expected '(', '{', or '::' after type name!");
        }

        break;
    }

    case MjTokenKind::MODULE_NAME: {
        MjType *type = parse_type();

        switch (_token->kind()) {
        case MjTokenKind::SCOPE: {
            lhs = new MjExpression(tokens_since(start), type);
            break;
        }
        default:
            error("Expected '::' after module name!");
        }

        break;
    }

    case MjTokenKind::UNINITIALIZED: {
        parse_token();
        lhs = new MjExpression(tokens_since(start), new MjVariable());
        break;
    }

    case MjTokenKind::TRUE:
    case MjTokenKind::FALSE:
    case MjTokenKind::NULL_: {
        parse_token();
        lhs = new MjExpression(tokens_since(start), new MjVariable());
        break;
    }

    case MjTokenKind::STRING_LITERAL:
    case MjTokenKind::RAW_STRING_LITERAL:
    case MjTokenKind::INTERPOLATED_STRING_LITERAL: {
        String string = token_text();
        MjVariable *string_literal = new MjStringLiteral(parse_token(), std::move(string));
        lhs = new MjExpression(tokens_since(start), string_literal);
        break;
    }

    case MjTokenKind::NUMERIC_LITERAL: {
        MjVariable *number_literal = new MjNumberLiteral(*parse_token());
        lhs = new MjExpression(tokens_since(start), number_literal);
        break;
    }

    case MjTokenKind::OPEN_PARENTHESIS: {
        parse_token();
        lhs = parse_expression();
        parse_token(MjTokenKind::CLOSE_PARENTHESIS);
        break;
    }

    case MjTokenKind::VARIABLE_NAME: {
        MjVariable *variable = new MjVariable(Slice<const MjToken>(parse_token(), 1));
        lhs = new MjExpression(tokens_since(start), variable);
        break;
    }

    case MjTokenKind::CONSTANT_NAME: {
        MjVariable *constant = new MjVariable(Slice<const MjToken>(parse_token(), 1));
        lhs = new MjExpression(tokens_since(start), constant);
        break;
    }

    case MjTokenKind::FUNCTION_NAME: {
        const MjToken *function_name = parse_token();
        MjTemplateArgumentList *template_argument_list = nullptr;
        MjFunctionArgumentList *function_argument_list = nullptr;

        if (_token->kind == MjTokenKind::OPEN_ANGLE_BRACKET) {
            template_argument_list = parse_template_argument_list();
        }

        if (_token->kind == MjTokenKind::OPEN_PARENTHESIS) {
            function_argument_list = parse_function_argument_list();
        }

        MjFunction *function = new MjFunction(tokens_since(start), function_name, template_argument_list);
        lhs = new MjExpression(tokens_since(start), function, function_argument_list);
        break;
    }

    default:
        // fallthrough
    }

    // 
    while (true) {
        if (_token->kind() == MjTokenKind::NONE) {
            break;
        }

        if (!_token->kind().is_operator()) {
            error("Expected an operator!");
            return nullptr;
        }

        MjOperatorKind op = MjOperatorKind::MULTIPLICATION;

        if (op.left_bp() < min_bp) {
            break;
        }

        parse_token();
        MjExpression *rhs = parse_expression(op.right_bp());
        lhs = new MjExpression(op, lhs, rhs);
    }

    return lhs;
}





























































MjTemplateParameterList *MjParser::parse_template_parameter_list() {
    if (!parse_token(MjTokenKind::OPEN_ANGLE_BRACKET)) {
        return nullptr;
    }

    MjTemplateParameterList *template_parameter_list;

    if (allocate(template_parameter_list)) {
        return nullptr;
    }

    do {
        if (!parse_type_expression()) {
            break;
        }
    } while (parse_token(MjTokenKind::COMMA));

    if (!parse_token(MjTokenKind::CLOSE_ANGLE_BRACKET)) {
        return nullptr;
    }

    return template_parameter_list;
}


MjTemplateArgument *MjParser::parse_template_argument() {
    MjTemplateArgument *template_argument = new MjTemplateArgument();

    if (parse_token(MjTokenKind::TYPE)) {
        if (!parse_type_name()) {
            error("Missing type name!");
        }

        if (parse_token(MjTokenKind::SET)) {
            if (parse_type_expression()) {
                error("Missing default type expression!");
            }
        }
    } else if (parse_type_expression()) {
        if (!parse_variable_name()) {
            error("Missing variable name!");
        }

        if (parse_token(MjTokenKind::SET)) {
            if (!parse_expression()) {
                error("Missing default expression!");
            }
        }
    } else {
        error("Invalid template argument!");
        // Look for another ',' or '>' to synchronize, but we might be missing those...
        // See what's next and go from there.
    }

    return template_argument;
}


MjTemplateArgumentList *MjParser::parse_template_argument_list() {
    MjTemplateArgumentList *template_argument_list = new MjTemplateArgumentList();

    if (!parse_token(MjTokenKind::OPEN_ANGLE_BRACKET)) {
        return nullptr;
    }

    do {
        if (parse_token(MjTokenKind::TYPE)) {
            if (!parse_type_name()) {
                error("Missing type name!");
            }

            if (parse_token(MjTokenKind::SET)) {
                if (parse_type_expression()) {
                    error("Missing default type expression!");
                }
            }
        } else if (parse_type_expression()) {
            if (!parse_variable_name()) {
                error("Missing variable name!");
            }

            if (parse_token(MjTokenKind::SET)) {
                if (!parse_expression()) {
                    error("Missing default expression!");
                }
            }
        } else {
            error("Invalid template argument!");
            // Look for another ',' or '>' to synchronize, but we might be missing those...
            // See what's next and go from there.
        }
    } while (parse_token(MjTokenKind::COMMA));

    if (!parse_token(MjTokenKind::CLOSE_ANGLE_BRACKET)) {
        return nullptr;
    }

    return template_argument_list;
}


MjFunctionParameterList *MjParser::parse_function_parameter_list() {

    if (!parse_token(MjTokenKind::OPEN_PARENTHESIS)) {
        return nullptr;
    }

    do {
        if (parse_type_expression()) {
        }
    } while (parse_token(MjTokenKind::COMMA));

    if (!parse_token(MjTokenKind::CLOSE_PARENTHESIS)) {
        restore(pos);
        return nullptr;
    }

    return nullptr;
}


MjFunctionArgumentList *MjParser::parse_function_argument_list() {

    if (!parse_token(MjTokenKind::OPEN_PARENTHESIS)) {
        return nullptr;
    }

    do {
        if (!parse_type_expression()) {
            break;
        }
    } while (parse_token(MjTokenKind::COMMA));

    if (!parse_token(MjTokenKind::CLOSE_PARENTHESIS)) {
        restore(pos);
        return nullptr;
    }

    return nullptr;
}


































































MjType *MjParser::parse_type_definition() noexcept {
    return nullptr;
}



MjBitfieldType *MjParser::parse_bitfield_type_definition() noexcept {
    parse_token(MjTokenKind::BITFIELD);
    const MjToken *name = parse_token(MjTokenKind::TYPE_NAME);
    //templates;
    parse_token(MjTokenKind::OPEN_ANGLE_BRACKET);

    //types;
    //members;
    //methods;

    // Scan the definition body.
    while (!parse_token(MjTokenKind::CLOSE_CURLY_BRACE)) {

        // Parse comment.
        field_comment = parse_comment();

        // Parse attributes.
        while (peek_token() == MjTokenKind::AT) {
            field_annotation = parse_annotation();

            if (!field_annotation) {
                return nullptr;
            }

            field_annotations.append(field_annotation);
        }

        // Parse field definition.
        if (parse_token(MjTokenKind::OPEN_SQUARE_BRACKET)) {

            // Parse field ID.
            MjExpression *field_id = parse_expression();

            if (!parse_token(MjTokenKind::CLOSE_SQUARE_BRACKET)) {
                error("Expected ']'!");
                break;
            }

            // Parse optional field type.
            field_type = parse_type_name();

            // Parse optional field name.
            field_name = parse_variable_name();

            // Parse optional field default value.
            if (parse_token(MjTokenKind::SET)) {
                field_value = parse_expression();
            }

            if (field_name == nullptr && field_value == nullptr) {
                error("Anonymous bitfield without default value!");
                break;
            }

            bitfield.fields.append({field_name, field_comment, field_annotations, field_type, field_value});
        } else {
            error("Expected a field definition!");
        }
    }

    return nullptr;
}


bool MjParser::verify_bitfield_type_definition(const MjBitfieldType &bitfield) noexcept {
    if (bitfield.) {

    }
    return true;
}


// Parse a class definition:
//
// - Parse the class type declaration (class Name<>)
// - Parse the class definition scope ({...})
//     - Parse import statements
//     - Parse type aliases
//     - Parse the member, shared, and implementation declarations (everything before '{', '=', or ';')
//     - Verify type references
//     - Parse the member, shared, and implementation definitions
MjClassType *MjParser::parse_class_type_definition() noexcept {
    parse_token(MjTokenKind::CLASS);
    const MjToken *name = parse_token(MjTokenKind::TYPE_NAME);
    //templates;
    parse_token(MjTokenKind::OPEN_ANGLE_BRACKET);

    //types;
    //members;
    //methods;

    // Scan the class.
    while (true) {
        const MjToken *token = peek_token();

        if (token->kind() == MjTokenKind::CLOSE_CURLY_BRACE) {
            break;
        } else if (token->kind() == MjTokenKind::SHARED) {
            ;
        } else if (token->kind() == MjTokenKind::IMPLEMENTS) {
            ;
        } else if (token->kind() == MjTokenKind::TYPE) {
            next_token();
            typevar = parse_variable();
            types.append(MjType(typevar.name, ));
        } else {
            type = parse_type();

            if (isinstance(type, MjFunctionType)) {
                methods.append(type);

                if (parse_token(MjTokenKind::OPEN_CURLY_BRACE)) {
                    depth = 1;

                    while (depth) {
                        token = next_token();

                        if (token->kind() == MjTokenKind::OPEN_CURLY_BRACE) {
                            depth += 1;
                        } else if (token->kind() == MjTokenKind::OPEN_CURLY_BRACE) {
                            depth -= 1;
                        }

                        method_body.append(token);
                    }
                } else if (token == MjTokenKind::SET) {
                    ;
                } else if (token == MjTokenKind::SEMICOLON) {
                    // Method declarations belong in interfaces!
                    raise SyntaxError("Classes may not contain method declarations!");
                }
            }

            members.append(type);
        }
    }
}


void MjParser::parse_interface_type_definition(MjType &type) {
}




MjStructureType *MjParser::parse_structure_type_definition() {
    if (!parse_token(MjTokenKind::STRUCT)) {
        return;
    }

    const MjToken *name = parse_token(MjTokenKind::TYPE_NAME);

    if (name != nullptr) {
        // Check for either a template argument list or a template parameter list.
        // If we find a template argument list, then this is a new structure type template or a partial specialization.
        // If we find a template parameter list, then this is a structure type template specialization.
        MjTemplateArgumentList *template_argument_list;

        if (template_argument_list != nullptr) {
            if (template_argument_list->is_partial_specialization()) {
                ;
            }
        } else {
            MjTemplateParameterList *template_parameter_list;
            if (template_parameter_list != nullptr) {
                ;
            }
        }
    }

    MjType structure_type = MjType(MjTypeType::STRUCTURE, name, comment, annotations);

    // Check for an optional inline instance declaration.
    const MjToken *instance_name = parse_token(MjTokenKind::VARIABLE_NAME);

    if (instance_name == nullptr) {
        instance_name = parse_token(MjTokenKind::CONSTANT_NAME);
    }

    // Parse the declaration body.
    if (!parse_token(MjTokenKind::OPEN_CURLY_BRACE)) {
        error("Missing opening curly brace!");
        return;
    }

    while (true) {
        MjItem *item = parse_item();

        if (!parse_token(MjTokenKind::OPEN_CURLY_BRACE)) {
            error("Missing opening curly brace!");
            return nullptr;
        }
    }

    // Parse the optional, inline instance variable declaration statement.
    if (instance_name != nullptr) {
        MjLocalVariable instance_variable(instance_name);
        MjVariableDeclarationStatement instance_declaration(instance_variable);
    }
}


void MjParser::parse_union_type_definition(MjType &type) {
}


void MjParser::parse_variant_type_definition(MjType &type) {
}


MjComment *MjParser::parse_comment() {
    bool is_formatted = false;

    switch (_token->kind()) {
    case MjTokenKind::FORMATTED_LINE_COMMENT:
        is_formatted = true;
        // fallthrough
    case MjTokenKind::LINE_COMMENT:
        return new MjComment(token_text().slice(3).data(), is_formatted);
    case MjTokenKind::FORMATTED_BLOCK_COMMENT:
        is_formatted = true;
        // fallthrough
    case MjTokenKind::BLOCK_COMMENT: {
        String text;

        do {
            text.append(token_text().slice(4).data(), token_text().slice(4).size());
            parse_token(MjTokenKind::INDENT);
        } while (parse_token(MjTokenKind::BLOCK_COMMENT) || parse_token(MjTokenKind::FORMATTED_BLOCK_COMMENT));

        return new MjComment(text, is_formatted);
    }
    default:
        return nullptr;
    }
}


void MjParser::parse_type_alias(MjType &type_alias) {
    if (!parse_token(MjTokenKind::TYPE)) {
        return;
    }

    MjTemplateArgumentList *template_argument_list = parse_template_argument_list();

    if (template_argument_list == nullptr) {
        return;
    }

    const MjToken *name = parse_token(MjTokenKind::TYPE_NAME);

    if (name == nullptr) {
        return;
    }

    type_alias = MjType(MjTypeType::ALIAS, name);
}


void MjParser::parse_type_alias_template(MjTypeTemplate &type_alias_definition) {
    if (!parse_token(MjTokenKind::TYPE)) {
        return;
    }

    MjTemplateArgumentList *template_argument_list = parse_template_argument_list();

    if (template_argument_list == nullptr) {
        return;
    }

    const MjToken *name = parse_token(MjTokenKind::TYPE_NAME);

    if (name == nullptr) {
        return;
    }

    MjTemplateParameterList *template_parameter_list = parse_template_parameter_list();

    if (template_parameter_list == nullptr) {
        return;
    }

    type_alias_definition = MjType(MjTypeTemplateType::ALIAS, name, template_parameter_list);
}


void MjParser::parse_type_enumeration(MjType &type) {
    MjType *type_enumeration = new MjType();
    parse_token(MjTokenKind::ENUM);
    parse_token(MjTokenKind::OPEN_ANGLE_BRACKET);
    MjType *index_type = parse_type_name();

    if (index_type == nullptr) {
        return nullptr;
    }

    MjVariable *index_variable = parse_variable_declaration();

    if (index_variable == nullptr) {
        ;
    }

    parse_token(MjTokenKind::CLOSE_ANGLE_BRACKET);
    const MjToken *name = parse_token(MjTokenKind::TYPE_NAME);
    return type_enumeration;
}


MjType *MjParser::parse_type_implementation() {
    MjTypeImplementation *type_implementation;
    return type_implementation;
}


MjAnnotation *MjParser::parse_annotation() {
    if (!parse_token(MjTokenKind::AT)) {
        return nullptr;
    }

    if (match_token(MjTokenKind::ANNOTATION_NAME)) {
        error("Expected annotation name after '@'!");
        return nullptr;
    }

    const MjToken *name = parse_token();

    if (!parse_token(MjTokenKind::OPEN_PARENTHESIS)) {
        return new MjAnnotation(name);
    }

    MjAnnotationArgumentList argument_list;

    do {
        if (!match_token(MjTokenKind::ANNOTATION_NAME)) {
            error("Expected annotation argument!");
            return nullptr;
        }

        argument_list.append(parse_token());

        if (parse_token(MjTokenKind::CLOSE_PARENTHESIS)) {
            break;
        }
    } while (!parse_token(MjTokenKind::COMMA));

    return new MjAnnotation(name, argument_list);
}


MjStatement *MjParser::parse_variable_declaration() {
    MjStatement *statement = new MjStatement();
    MjType *type = parse_type_expression();

    // Check for initialization.
    if (parse_token(MjTokenKind::SET)) {
        statement->set_initial_value(parse_expression());

        if (!parse_token(MjTokenKind::INDENT)) {
            // not the end of statement?
        }
    }

    return statement;
}
















MjUnit *MjParser::parse_unit_expression() {
    MjUnit &unit = _units.allocate();
    // parse an expression
    // operators: /*^+-()
    // identifiers + special unicode characters

    while (true) {
        if (ch >= '0' && ch <= '9') {
            ;// digit
        }
    }
    return unit;
}






bool MjParser::parse_unit_exponent() {
    u32 i = 0;

    if (_line[i] == '^') {
        i += 1;
        // ^-?[0-9]+(/[0-9]+)?
        for (u32 state = 0; state < 4;) {
            switch (state) {
            case 0: // -(?=\d)
                break;
            case 1: // \d+
                break;
            case 2: // /(?=\d)
                break;
            case 3: // \d+
                break;
            }
        }
    } else {

        // ⁻?[⁰¹²³⁴⁵⁶⁷⁸⁹]+(⸍[⁰¹²³⁴⁵⁶⁷⁸⁹]+)?
        for (u32 state = 0; state < 4;) {

            // Get the codepoint.
            if (i + 1u == _line.size()) {
                break;
            }

            u32 value = (_line[i] << 8) | _line[i + 1];
            i += 2;

            switch (value) {
            case 0xC2B2u: // '²'
            case 0xC2B3u: // '³'
            case 0xC2B9u: // '¹'
                value &= 0x37u;
                break;
            default:
                if (i == _line.size()) {
                    i -= 2;
                    break;
                }

                value = (value << 8) | _line[i];
                i += 1;

                switch (value) {
                case 0xE281B0u: // '⁰'
                case 0xE281B4u: // '⁴'
                case 0xE281B5u: // '⁵'
                case 0xE281B6u: // '⁶'
                case 0xE281B7u: // '⁷'
                case 0xE281B8u: // '⁸'
                case 0xE281B9u: // '⁹'
                    value &= 0x3Fu;
                    break;
                case 0xE281BBu: // '⁻'
                    value = '-';
                    break;
                case 0xE2B88Du: // '⸍'
                    value = '/';
                    break;
                default:
                    i -= 3;
                }
            }

            switch (state) {
            case 0: // -
                break;
            case 1: // [⁰¹²³⁴⁵⁶⁷⁸⁹]+
                break;
            case 2: // ⸍
                break;
            case 3: // [⁰¹²³⁴⁵⁶⁷⁸⁹]+
                break;
            }
        }
    }

    // -?[0-9]+(/[0-9]+)?
    for (u32 state = 0; state < 4;) {
        u32 value = 0;

        switch (state) {
        case 0: // -(?=\d)
            if (value == '-') {
            }

            state = 1;
            break;
        case 1: // \d+
            if (value - '0' >= 10) {
                state = 2;
            }

            break;
        case 2: // /(?=\d)
            if (value == '/') {
                state = 3;
            }

            break;
        case 3: // \d+
            break;
        }
    }

    if (value == '-' || value == '/') {
        // missing numerator or denominator of exponent.
        return false;
    }

    append_token(MjTokenKind::UNIT, i);
    return true;
}
