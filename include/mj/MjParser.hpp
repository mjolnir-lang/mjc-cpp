#pragma once

#include <mj/ast/MjFile.hpp>
#include <mj/ast/MjProgram.hpp>
#include <mj/ast/MjTypeAlias.hpp>
#include <mj/ast/MjTypeTemplate.hpp>
#include <mj/ast/MjClassType.hpp>
#include <mj/ast/MjBitfieldType.hpp>
#include <mj/ast/MjStructureType.hpp>
#include <mj/ast/MjUnionType.hpp>
#include <mj/ast/MjTypeEnumeration.hpp>
#include <mj/ast/MjTypeImplementation.hpp>
#include <mj/ast/MjInterfaceType.hpp>

//#include <mj/internal/MjParserError.hpp>

#include <filesystem>


// syntax errors (matching braces, termination, sequence)
class MjParseError {
private:
    MjToken _token;
    StringView _message;
public:


    MjParseError(MjToken token, StringView message) noexcept :
        _token(token),
        _message(message)
    {}
};


// The parser consumes the output of the lexer and emits the AST components while controlling the parsing context.
class MjParser {
private:
    const MjFile &_file;
    Vector<MjParseError> _errors;
    MjProgram _program;
    const MjToken *_token;
public:


    static    
    MjProgram parse(const MjFile &file) noexcept;


private:


    MjParser(const MjFile &file) noexcept :
        _file(file),
        _token(&_file.tokens()[0])
    {}


    void error(StringView message) noexcept;


    ///
    /// Token Parsing
    ///


    void reset(const MjToken *token) noexcept {
        _token = token;
    }


    void skip_token() noexcept {
        _token += 1;
    }


    StringView token_text() noexcept {
        return _file.line(_token->line).slice(_token->offset, _token->size);
    }


    const MjToken *peek_token() noexcept {
        return _token + 1;
    }


    const MjToken *peek_token(MjTokenKind type) noexcept {
        const MjToken *token = _token + 1;
        return token->kind == type ? token : nullptr;
    }


    const MjToken *parse_token() noexcept {
        return _token;
    }


    const MjToken *parse_token(MjTokenKind type) noexcept {
        return _token->kind == type ? _token : nullptr;
    }


    constexpr
    bool match_token(MjTokenKind type) const noexcept {
        return _token->kind == type;
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
    MjModule *parse_module(std::filesystem::path path) noexcept;


    /// @brief Parse a file
    /// @return 
    void parse_file(MjModule &module, std::filesystem::path path) noexcept;


    /// @brief Parse an item.
    /// @return 
    MjItem *parse_item() noexcept;


    /// @brief Parse an item.
    /// @return 
    MjDirective *parse_directive() noexcept;


    MjAnnotation *parse_annotation() noexcept;


    MjComment *parse_comment() noexcept;


    ///
    /// Type Declarations
    ///



    ///
    /// Type Definitions
    ///


    /// @brief Parse any type declaration
    /// @return 
    MjType *parse_type_definition() noexcept;


    /// @brief Parse a type enumeration.
    ///
    /// ```mj
    /// bitfield<BaseType> TypeName {
    ///     [n:m] field
    /// }
    /// ```
    ///
    /// @return 
    void parse_bitfield_type_definition(MjType &type) noexcept;


    // Parse a class definition:
    //
    // - Parse the class type declaration (class Name<>)
    // - Parse the class definition scope ({...})
    //     - Parse import statements <-- IN PLACE!!!
    //     - Parse type aliases
    //     - Parse the member, shared, and implementation declarations (everything before '{', '=', or ';')
    //     - Verify type references
    //     - Parse the member, shared, and implementation definitions
    MjClassType *parse_class_type_definition() noexcept;


    MjInterfaceType *parse_interface_type_definition() noexcept;


    MjStructureType *parse_structure_type_definition() noexcept;


    MjUnionType *parse_union_type_definition() noexcept;


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
    MjTypeAlias *parse_type_alias() noexcept;


    /// @brief Parse a type alias template.
    ///
    /// ```mj
    /// type<TypeExpression> NewType<TemplateParameterList>
    /// ```
    ///
    /// @return 
    void parse_type_alias_template() noexcept;


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
    void parse_type_enumeration(MjType &type) noexcept;


    /// @brief Parse a type implementation.
    ///
    /// ```mj
    /// impl<InterfaceType> BaseType {
    ///     ...
    /// }
    /// ```
    ///
    /// @return 
    void parse_type_implementation(MjType &type) noexcept;


    ///
    /// Type Expressions
    ///


    /// @brief Parse a type expression.
    MjType *parse_type_expression() noexcept;


    /// @brief Parse a generic type name.
    ///
    /// ```mj
    /// TypeName<TypeArguments>
    /// TypeName<TypeParameters>
    /// ```
    MjType *parse_type_name() noexcept;


    MjType *parse_type() noexcept;


    ///
    /// Statements
    ///


    MjStatement *parse_statement() noexcept;


    MjStatement *parse_variable_declaration() noexcept;


    ///
    /// Expressions
    ///


    MjExpression *parse_expression(u32 min_bp = 0) noexcept;


    ///
    /// Templates
    ///


    MjTemplateArgument *parse_template_argument() noexcept;


    MjTemplateArgumentList *parse_template_argument_list() noexcept;

    MjTemplateParameterList *parse_template_parameter_list() noexcept;


    ///
    /// Type Templates
    ///


    ///
    /// Function Templates
    ///


    ///
    /// Functions
    ///


    MjFunctionArgumentList *parse_function_argument_list() noexcept;

    MjFunctionParameterList *parse_function_parameter_list() noexcept;
};
