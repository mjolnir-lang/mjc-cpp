#pragma once

#include <mj/ast/MjProgram.hpp>

#include <std/File.hpp>


// syntax errors (matching braces, termination, sequence)
class MjParseError {
private:
    MjToken _token;
    StringView _message;
public:


    MjParseError(
        MjToken token,
        StringView message
    ) :
        _token(token),
        _message(message)
    {}
};


// The parser consumes the output of the lexer and emits the AST components while controlling the parsing context.
class MjParser {
private:
    const File &_file;
    const Vector<MjToken> &_tokens;
    Vector<MjParseError> _errors;
    MjProgram _program;
    const MjToken *_token;
public:


    MjParser(
        const File &file,
        const Vector<MjToken> &tokens
    ) :
        _file(file),
        _tokens(tokens),
        _token(&_tokens[0])
    {}


    MjProgram &parse();
private:


    void error(StringView message);


    ///
    /// Token Parsing
    ///


    void reset(const MjToken *token) {
        _token = token;
    }


    void skip_token() {
        _token += 1;
    }


    StringView token_text() noexcept {
        return _file.lines()[_token->line].slice(_token->offset, _token->size);
    }


    const MjToken *peek_token(MjTokenType type) noexcept {
        return _token + 1;
    }


    const MjToken *parse_token() noexcept {
        return _token;
    }


    const MjToken *parse_token(MjTokenType type) noexcept {
        return _token->type == type ? _token : nullptr;
    }


    constexpr
    bool match_token(MjTokenType type) const noexcept {
        return _token->type == type;
    }


    constexpr
    Slice<const MjToken> tokens_since(const MjToken *start) const noexcept {
        return Slice<const MjToken>(start, u32(_token - start));
    }


    ///
    /// Structure Parsing
    ///


    /// @brief Parse a module
    /// @return 
    MjModule *parse_module(const Path &path);


    /// @brief Parse a file
    /// @return 
    void parse_file(MjModule &module, const Path &path);



    MjAnnotation *parse_annotation();


    MjComment *parse_comment();


    ///
    /// Type Declarations
    ///



    ///
    /// Type Definitions
    ///


    /// @brief Parse any type declaration
    /// @return 
    void parse_type_definition(MjType &type);


    /// @brief Parse a type enumeration.
    ///
    /// ```mj
    /// bitfield<BaseType> TypeName {
    ///     [n:m] field
    /// }
    /// ```
    ///
    /// @return 
    void parse_bitfield_type_definition(MjType &type);


    // Parse a class definition:
    //
    // - Parse the class type declaration (class Name<>)
    // - Parse the class definition scope ({...})
    //     - Parse import statements <-- IN PLACE!!!
    //     - Parse type aliases
    //     - Parse the member, shared, and implementation declarations (everything before '{', '=', or ';')
    //     - Verify type references
    //     - Parse the member, shared, and implementation definitions
    void parse_class_type_definition(MjType &type);


    void parse_interface_type_definition(MjType &type);


    void parse_structure_type_definition(MjType &type);


    void parse_union_type_definition(MjType &type);


    void parse_variant_type_definition(MjType &type);


    ///
    /// Meta Type Parsing Methods
    ///


    /// @brief Parse a type alias.
    ///
    /// ```mj
    /// type<TypeExpression> NewType
    /// ```
    ///
    /// @return 
    void parse_type_alias(MjType &type);


    /// @brief Parse a type alias template.
    ///
    /// ```mj
    /// type<TypeExpression> NewType<TemplateParameterList>
    /// ```
    ///
    /// @return 
    void parse_type_alias_template(MjTypeTemplate &type_template);


    /// @brief Parse a type enumeration.
    ///
    /// ```mj
    /// enum<IndexType> BaseType {
    ///     VAL
    ///     VAL = ...
    ///     [key] VAL
    ///     [key] VAL = ...
    /// }
    /// ```
    ///
    /// @return 
    void parse_type_enumeration(MjType &type);


    /// @brief Parse a type implementation.
    ///
    /// ```mj
    /// impl<InterfaceType> BaseType {
    ///     ...
    /// }
    /// ```
    ///
    /// @return 
    void parse_type_implementation(MjType &type);


    ///
    /// Type Expressions
    ///


    /// @brief Parse a type expression.
    MjType *parse_type_expression();


    /// @brief Parse a generic type name.
    ///
    /// ```mj
    /// TypeName<TypeArguments>
    /// TypeName<TypeParameters>
    /// ```
    MjType *parse_type_name();


    MjType *parse_type();


    ///
    /// Statements
    ///


    MjStatement *parse_statement();


    MjStatement *parse_variable_declaration();


    ///
    /// Expressions
    ///


    MjExpression *parse_expression(u32 min_bp = 0);


    ///
    /// Templates
    ///


    MjTemplateArgumentList *parse_template_argument_list();

    MjTemplateParameterList *parse_template_parameter_list();


    ///
    /// Type Templates
    ///


    ///
    /// Function Templates
    ///


    ///
    /// Functions
    ///


    MjFunctionArgumentList *parse_function_argument_list();

    MjFunctionParameterList *parse_function_parameter_list();
};
