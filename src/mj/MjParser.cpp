#include <mj/MjParser.hpp>


void MjParser::error(StringView message) {
    _errors.emplace_back(_token, message);
}


MjProgram &MjParser::parse() {

    parse_module();

    return _program;
}


MjModule *MjParser::parse_module(const Path &path) {
    // Verify module path.

    // List files and directories.

    // list internal

    // list external

    // parse files

    // parse submodules
}


MjStatement *MjParser::parse_statement() {
    const MjToken *start = _token;
    MjStatement *statement = new MjStatement();

    switch (_token->type) {

    case MjTokenType::OPEN_CURLY_BRACE: {
        statement->set_type(MjStatementType::BLOCK);

        while (true) {
            MjStatement *s = parse_statement();

            if (s == nullptr) {
                break;
            }

            statement->block_statements().append(s);
        }

        parse_token(MjTokenType::CLOSE_CURLY_BRACE);
        statement->set_tokens(tokens_since(start));
        return statement;
    }

    case MjTokenType::BREAK: {
        statement->set_type(MjStatementType::BREAK);
        MjExpression depth = parse_expression();
        statement->set_depth(depth);
        statement->set_tokens(tokens_since(start));
        return statement;
    }

    case MjTokenType::CONTINUE: {
        statement->set_type(MjStatementType::CONTINUE);
        MjExpression depth = parse_expression();
        statement->set_depth(depth);
        statement->set_tokens(tokens_since(start));
        return statement;
    }

    case MjTokenType::CLASS: {
        statement->set_type(MjStatementType::CLASS_DEFINITION);

        // Consume the 'class' token.
        parse_token();

        // Parse the name of the class type.
        const MjToken *class_name = parse_token(MjTokenType::TYPE_NAME);

        if (class_name == nullptr) {
            error("Expected a type name after 'class'!");
            reset(start);
            return nullptr;
        }

        // Parse either a template argument list, or a template, or a partial specialization.
        if (parse_token(MjTokenType::OPEN_ANGLE_BRACKET)) {
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
        if (match_token(MjTokenType::VARIABLE_NAME) || match_token(MjTokenType::CONSTANT_NAME)) {
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
    }

    case MjTokenType::DO: {
        if (!match_token(MjTokenType::OPEN_CURLY_BRACE)) {
            error("Expected '{' after 'do'!");
            return nullptr;
        }

        MjStatement *body = parse_statement();
        Slice<const MjToken> tokens = Slice<const MjToken>(_token, 1);
        MjStatement *statement = new MjStatement(MjStatementType::DO);
    }

    case MjTokenType::ELSE: {
        // should not get here!
        error("Keyword 'else' must follow 'if' block!");

        if (match_token(MjTokenType::OPEN_CURLY_BRACE)) {
            parse_statement();
        }
    }

    case MjTokenType::ENUM: {
        return parse_type_enumeration();
    }

    case MjTokenType::FAIL: {
        return parse_fail_statement();
    }

    case MjTokenType::FOR: {
        // 
    }

    case MjTokenType::IF: {
        // Always succeeds.
        parse_token(MjTokenType::OPEN_PARENTHESIS);

        MjExpression *condition = parse_expression();

        if (condition == nullptr) {
            error("Missing condition!");
            return nullptr;
        }

        if (!parse_token(MjTokenType::CLOSE_PARENTHESIS)) {
            error("Missing ')'!");
            return nullptr;
        }

        MjStatement *if_block = parse_block_statement();

        if (if_block == nullptr) {
            error("Missing if block statement!");
            return nullptr;
        }

        MjStatement *else_block = nullptr;

        if (parse_token(MjTokenType::ELSE)) {
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
    }

    case MjTokenType::IMPL: {
        // 
    }

    case MjTokenType::IMPORT: {
        // Scope dictates the import type (public/private)
        Path path(".");

        // Parse module imports
        while (parse_token(MjTokenType::IMPORT)) {
            while (parse_token(MjTokenType::SEMICOLON)) {
                const MjToken *token = parse_token();

                switch (token->type) {
                case MjTokenType::IDENTIFIER:
                    path.append(token->str());
                    break;
                case MjTokenType::MINUS:
                    path.append('-', true);
                    break;
                case MjTokenType::DOT:
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
    }

    case MjTokenType::INTERFACE: {
        // Only at module scope!
    }

    case MjTokenType::MATCH: {
        // 

        // Parse all the cases.
        while () {
            ;
        }
    }

    case MjTokenType::RETURN: {
        return new MjStatement(MjStatementType::RETURN, parse_expression());
    }

    case MjTokenType::STRUCT: {
        // 
    }

    case MjTokenType::TYPE: {
        skip_token();
        parse_token(MjTokenType::OPEN_ANGLE_BRACKET);

        MjType *type = parse_type_expression();

        if (type == nullptr) {
            error("Missing type expression!");
        }

        parse_token(MjTokenType::CLOSE_ANGLE_BRACKET);

        if (type == nullptr) {
            error("Missing type expression!");
        }

        const MjToken *type_name = parse_token(MjTokenType::TYPE_NAME);

        if (type == nullptr) {
            error("Missing type expression!");
        }

        return new MjType(MjTypeType::ALIAS, type_name, type);
    }

    case MjTokenType::UNION: {
        // 
    }

    case MjTokenType::UNTIL: {
        // 
    }

    case MjTokenType::VARIANT: {
        // 
    }

    case MjTokenType::WHILE: {
        if (parse_token(MjTokenType::OPEN_PARENTHESIS) == nullptr) {
            ;
        }

        MjExpression *loop_condition = parse_expression();

        if (parse_token(MjTokenType::CLOSE_PARENTHESIS) == nullptr) {
            ;
        }

        MjStatement *loop_body = parse_block_statement();
        return new MjStatement(MjStatementType::WHILE, loop_condition, loop_body);
    }

    case MjTokenType::YIELD: {
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
    MjExpression *lhs = nullptr;
    const MjToken *start = _token;

    switch (_token->type) {

    case MjTokenType::OPEN_CAST: {
        parse_token();
        MjType *type = parse_type();
        parse_token(MjTokenType::COLON);
        lhs = parse_expression();
        parse_token(MjTokenType::CLOSE_CAST);
    }

    case MjTokenType::TYPE_NAME: {
        MjType *type = parse_type();

        switch (_token->type) {
        case MjTokenType::OPEN_PARENTHESIS: {
            MjFunctionParameterList *fpl = parse_function_parameter_list();
            lhs = new MjExpression(tokens_since(start), type, fpl);
            break;
        }

        case MjTokenType::OPEN_CURLY_BRACE: {
            MjStatement *statement = parse_statement();
            lhs = new MjExpression(tokens_since(start), type, statement);
            break;
        }
        default:
            error("Expected '(', '{', or '::' after type name!");
        }

        break;
    }

    case MjTokenType::MODULE_NAME: {
        MjType *type = parse_type();

        switch (_token->type) {
        case MjTokenType::SCOPE: {
            lhs = new MjExpression(tokens_since(start), type);
            break;
        }
        default:
            error("Expected '::' after module name!");
        }

        break;
    }

    case MjTokenType::UNINITIALIZED: {
        parse_token();
        lhs = new MjExpression(tokens_since(start), new MjVariable());
        break;
    }

    case MjTokenType::TRUE:
    case MjTokenType::FALSE:
    case MjTokenType::NULL_: {
        parse_token();
        lhs = new MjExpression(tokens_since(start), new MjVariable());
        break;
    }

    case MjTokenType::STRING_LITERAL:
    case MjTokenType::RAW_STRING_LITERAL:
    case MjTokenType::INTERPOLATED_STRING_LITERAL: {
        String string = token_text();
        MjVariable *string_literal = new MjStringLiteral(parse_token(), std::move(string));
        lhs = new MjExpression(tokens_since(start), string_literal);
        break;
    }

    case MjTokenType::NUMERIC_LITERAL: {
        MjVariable *number_literal = new MjNumberLiteral(*parse_token());
        lhs = new MjExpression(tokens_since(start), number_literal);
        break;
    }

    case MjTokenType::OPEN_PARENTHESIS: {
        parse_token();
        lhs = parse_expression();
        parse_token(MjTokenType::CLOSE_PARENTHESIS);
        break;
    }

    case MjTokenType::VARIABLE_NAME: {
        MjVariable *variable = new MjVariable(Slice<const MjToken>(parse_token(), 1));
        lhs = new MjExpression(tokens_since(start), variable);
        break;
    }

    case MjTokenType::CONSTANT_NAME: {
        MjVariable *constant = new MjVariable(Slice<const MjToken>(parse_token(), 1));
        lhs = new MjExpression(tokens_since(start), constant);
        break;
    }

    case MjTokenType::FUNCTION_NAME: {
        const MjToken *function_name = parse_token();
        MjTemplateArgumentList *template_argument_list = nullptr;
        MjFunctionArgumentList *function_argument_list = nullptr;

        if (_token->type == MjTokenType::OPEN_ANGLE_BRACKET) {
            template_argument_list = parse_template_argument_list();
        }

        if (_token->type == MjTokenType::OPEN_PARENTHESIS) {
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
        if (_token->type == MjTokenType::NONE) {
            break;
        }

        if (!_token->type.is_operator()) {
            error("Expected an operator!");
            return nullptr;
        }

        MjOperatorType op = MjOperatorType::MULTIPLICATION;

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
    if (!parse_token(MjTokenType::OPEN_ANGLE_BRACKET)) {
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
    } while (parse_token(MjTokenType::COMMA));

    if (!parse_token(MjTokenType::CLOSE_ANGLE_BRACKET)) {
        return nullptr;
    }

    return template_parameter_list;
}


MjTemplateArgumentList *MjParser::parse_template_argument_list() {
    if (!parse_token(MjTokenType::OPEN_ANGLE_BRACKET)) {
        return nullptr;
    }

    do {
        if (parse_token(MjTokenType::TYPE)) {
            if (!parse_type_name()) {
                error("Missing type name!");
            }

            if (parse_token(MjTokenType::SET)) {
                if (parse_type_expression()) {
                    error("Missing default type expression!");
                }
            }
        } else if (parse_type_expression()) {
            if (!parse_variable_name()) {
                error("Missing variable name!");
            }

            if (parse_token(MjTokenType::SET)) {
                if (!parse_expression()) {
                    error("Missing default expression!");
                }
            }
        } else {
            error("Invalid template argument!");
            // Look for another ',' or '>' to synchronize, but we might be missing those...
            // See what's next and go from there.
        }
    } while (parse_token(MjTokenType::COMMA));

    if (!parse_token(MjTokenType::CLOSE_ANGLE_BRACKET)) {
        return nullptr;
    }

    return true;
}


MjFunctionParameterList *MjParser::parse_function_parameter_list() {

    if (!parse_token(MjTokenType::OPEN_PARENTHESIS)) {
        return nullptr;
    }

    do {
        if (parse_type_expression()) {
        }
    } while (parse_token(MjTokenType::COMMA));

    if (!parse_token(MjTokenType::CLOSE_PARENTHESIS)) {
        restore(pos);
        return nullptr;
    }

    return nullptr;
}


MjFunctionArgumentList *MjParser::parse_function_argument_list() {

    if (!parse_token(MjTokenType::OPEN_PARENTHESIS)) {
        return nullptr;
    }

    do {
        if (!parse_type_expression()) {
            break;
        }
    } while (parse_token(MjTokenType::COMMA));

    if (!parse_token(MjTokenType::CLOSE_PARENTHESIS)) {
        restore(pos);
        return nullptr;
    }

    return nullptr;
}


































































void MjParser::parse_type_definition(MjType &type) {
    MjType &type = _types.allocate();
    return type;
}



void MjParser::parse_bitfield_type_definition(MjType &type) {

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
void MjParser::parse_class_type_definition(MjType &type) {
    parse_token(MjTokenType::CLASS);
    const MjToken *name = parse_token(MjTokenType::TYPE_NAME);
    //templates;
    parse_token(MjTokenType::OPEN_ANGLE_BRACKET);

    //types;
    //members;
    //methods;

    // Scan the class.
    while (true) {
        const MjToken *token = peek_token();

        if (token->type == MjTokenType::CLOSE_CURLY_BRACE) {
            break;
        } else if (token->type == MjTokenType::SHARED) {
            ;
        } else if (token->type == MjTokenType::IMPLEMENTS) {
            ;
        } else if (token->type == MjTokenType::TYPE) {
            next_token();
            typevar = parse_variable();
            types.append(MjType(typevar.name, ));
        } else {
            type = parse_type();

            if (isinstance(type, MjFunctionType)) {
                methods.append(type);

                if (parse_token(MjTokenType::OPEN_CURLY_BRACE)) {
                    depth = 1;

                    while (depth) {
                        token = next_token();

                        if (token == MjToken::OPEN_CURLY_BRACE) {
                            depth += 1;
                        } else if (token == MjToken::OPEN_CURLY_BRACE) {
                            depth -= 1;
                        }

                        method_body.append(token);
                    }
                } else if (token == MjTokenType::SET) {
                    ;
                } else if (token == MjTokenType::SEMICOLON) {
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




void MjParser::parse_structure_type_definition(MjType &type) {
    if (!parse_token(MjTokenType::STRUCT)) {
        return;
    }

    const MjToken *name = parse_token(MjTokenType::TYPE_NAME);

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
    const MjToken *instance_name = parse_token(MjTokenType::VARIABLE_NAME);

    if (instance_name == nullptr) {
        instance_name = parse_token(MjTokenType::CONSTANT_NAME);
    }

    // Parse the declaration body.
    if (!parse_token(MjTokenType::OPEN_CURLY_BRACE)) {
        error("Missing opening curly brace!");
        return;
    }

    while (true) {
        parse_class_type_definition(type);
        parse_structure_type_definition(type);
        parse_union_type_definition(type);
        parse_type_enumeration(type);
        parse_type_alias(type);

        if (!parse_token(MjTokenType::OPEN_CURLY_BRACE)) {
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

    switch (_token->type) {
    case MjTokenType::FORMATTED_LINE_COMMENT:
        is_formatted = true;
        // fallthrough
    case MjTokenType::LINE_COMMENT:
        return new MjComment(token_text().slice(3).data(), is_formatted);
    case MjTokenType::FORMATTED_BLOCK_COMMENT:
        is_formatted = true;
        // fallthrough
    case MjTokenType::BLOCK_COMMENT: {
        String text;

        do {
            text.append(token_text().slice(4).data(), token_text().slice(4).size());
            parse_token(MjTokenType::INDENT);
        } while (parse_token(MjTokenType::BLOCK_COMMENT) || parse_token(MjTokenType::FORMATTED_BLOCK_COMMENT));

        return new MjComment(text, is_formatted);
    }
    default:
        return nullptr;
    }
}


void MjParser::parse_type_alias(MjType &type_alias) {
    if (!parse_token(MjTokenType::TYPE)) {
        return;
    }

    MjTemplateArgumentList *template_argument_list = parse_template_argument_list();

    if (template_argument_list == nullptr) {
        return;
    }

    const MjToken *name = parse_token(MjTokenType::TYPE_NAME);

    if (name == nullptr) {
        return;
    }

    type_alias = MjType(MjTypeType::ALIAS, name);
}


void MjParser::parse_type_alias_template(MjTypeTemplate &type_alias_definition) {
    if (!parse_token(MjTokenType::TYPE)) {
        return;
    }

    MjTemplateArgumentList *template_argument_list = parse_template_argument_list();

    if (template_argument_list == nullptr) {
        return;
    }

    const MjToken *name = parse_token(MjTokenType::TYPE_NAME);

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
    parse_token(MjTokenType::ENUM);
    parse_token(MjTokenType::OPEN_ANGLE_BRACKET);
    MjType *index_type = parse_type_name();

    if (index_type == nullptr) {
        return nullptr;
    }

    MjVariable *index_variable = parse_variable_declaration();

    if (index_variable == nullptr) {
        ;
    }

    parse_token(MjTokenType::CLOSE_ANGLE_BRACKET);
    const MjToken *name = parse_token(MjTokenType::TYPE_NAME);
    return type_enumeration;
}


MjType *MjParser::parse_type_implementation() {
    MjTypeImplementation *type_implementation;
    return type_implementation;
}


MjAnnotation *MjParser::parse_annotation() {
    if (!parse_token(MjTokenType::AT)) {
        return nullptr;
    }

    if (match_token(MjTokenType::ANNOTATION_NAME)) {
        error("Expected annotation name after '@'!");
        return nullptr;
    }

    const MjToken *name = parse_token();

    if (!parse_token(MjTokenType::OPEN_PARENTHESIS)) {
        return new MjAnnotation(name);
    }

    MjAnnotationArgumentList argument_list;

    do {
        if (!match_token(MjTokenType::ANNOTATION_NAME)) {
            error("Expected annotation argument!");
            return nullptr;
        }

        argument_list.append(parse_token());

        if (parse_token(MjTokenType::CLOSE_PARENTHESIS)) {
            break;
        }
    } while (!parse_token(MjTokenType::COMMA));

    return new MjAnnotation(name, argument_list);
}


MjStatement *MjParser::parse_variable_declaration() {
    MjStatement *statement = new MjStatement();
    MjType *type = parse_type_expression();

    // Check for initialization.
    if (parse_token(MjTokenType::SET)) {
        statement->set_initial_value(parse_expression());

        if (!parse_token(MjTokenType::INDENT)) {
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

    append_token(MjTokenType::UNIT, i);
    return true;
}
