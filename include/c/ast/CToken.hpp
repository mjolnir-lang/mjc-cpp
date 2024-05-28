#pragma once

#include <std/Common.hpp>


enum class CTokenType : u16 {

    // Misc
    GROUP_MASK = 0xFF << 8,
    NONE       = 0,
    INDENT     = 1, // [ \t]+
    WHITESPACE = 2, // [ \t]+

    // Operators
    OPERATOR  = 1 << 8,

    OP_SCOPE,     // ::
    OP_DOT,       // .

    OP_LAMBDA,    // =>

    OP_AT,        // @

    OP_PTR,       // *
    OP_NPTR,      // ^
    OP_REF,       // &
    OP_GLT,       // "
    OP_LLT,       // '
    OP_FAIL,      // ?

    OP_INC,       // ++
    OP_DEC,       // --

    OP_SHR_SET,   // >>=
    OP_SHL_SET,   // <<=
    OP_MUL_SET,   // *=
    OP_DIV_SET,   // /=
    OP_REM_SET,   // %=
    OP_ADD_SET,   // +=
    OP_SUB_SET,   // -=
    OP_AND_SET,   // &=
    OP_XOR_SET,   // ^=
    OP_OR_SET,    // |=
    OP_LAND_SET,  // &&=
    OP_LXOR_SET,  // ^^=
    OP_LOR_SET,   // ||=

    OP_SHR,       // >>
    OP_SHL,       // <<
    OP_MUL,       // *
    OP_DIV,       // /
    OP_REM,       // %
    OP_ADD,       // +
    OP_SUB,       // -
    OP_AND,       // &
    OP_XOR,       // ^
    OP_OR,        // |
    OP_LAND,      // &&
    OP_LXOR,      // ^^
    OP_LOR,       // ||

    OP_SET,       // =

    OP_EQU,       // ==
    OP_NEQ,       // !=
    OP_SPS,       // <=>
    OP_LES,       // <
    OP_LEQ,       // <=
    OP_GTR,       // >
    OP_GEQ,       // >=

    OP_NOT,       // !
    OP_INV,       // ~

    OP_QUESTION,  // ?
    OP_COLON,     // :

    OP_SEMICOLON, // ;
    OP_COMMA,     // ,

    OP_OP,        // (
    OP_CP,        // )
    OP_OS,        // [
    OP_CS,        // ]
    OP_OB,        // {
    OP_CB,        // }
    OP_OA,        // <
    OP_CA,        // >

    // Keywords
    KEYWORD    = 2 << 8,
    KW_AS,         // as
    KW_ASM,        // asm
    KW_BREAK,      // break
    KW_BITFIELD,   // bitfield
    KW_CLASS,      // class
    KW_CONTINUE,   // continue
    KW_DO,         // do
    KW_ELSE,       // else
    KW_ENUM,       // enum
    KW_FAIL,       // fail
    KW_FOR,        // for
    KW_IF,         // if
    KW_IMPL,       // impl
    KW_IMPORT,     // import
    KW_IN,         // in
    KW_INTERFACE,  // interface
    KW_IS,         // is
    KW_LOOP,       // loop
    KW_MATCH,      // match
    KW_RETURN,     // return
    KW_STRUCT,     // struct
    KW_TYPE,       // type
    KW_UNION,      // union
    KW_UNIT,       // unit
    KW_UNTIL,      // until
    KW_VARIANT,    // variant
    KW_WHERE,      // where
    KW_WHILE,      // while
    KW_YIELD,      // yield

    // Language Defined Types
    TYPE = 7 << 8,
    ID_TYPE, // '[A-Z0-9][A-Z0-9.+-]*[a-z][A-Za-z0-9.+-]*'
    TY_BOOL, // bool
    TY_F16,  // f16
    TY_F32,  // f32
    TY_F64,  // f64
    TY_F80,  // f80
    TY_F128, // f128
    TY_I8,   // i8
    TY_I16,  // i16
    TY_I32,  // i32
    TY_I64,  // i64
    TY_I128, // i128
    TY_U8,   // u8
    TY_U16,  // u16
    TY_U32,  // u32
    TY_U64,  // u64
    TY_U128, // u128
    TY_VOID, // void

    // Strings
    STRING = 5 << 8,
    LT_STRING_LITERAL,     // "\\".*\\""
    LT_RAW_STRING_LITERAL, // "'.*'"

    // Numbers
    NUMERIC_LITERAL = 4 << 8,
    LT_U8,     // 
    LT_U16,    // 
    LT_U32,    // 
    LT_U64,    // 
    LT_U128,   // 
    LT_I8,     // 
    LT_I16,    // 
    LT_I32,    // 
    LT_I64,    // 
    LT_I128,   // 
    LT_F16,    // 
    LT_F32,    // 
    LT_F64,    // 
    LT_F80,    // 
    LT_F128,   // 

    // Constants
    CONSTANTS = 10 << 8,
    ID_CONSTANT, // "[A-Z0-9_]*[A-Z][A-Z0-9_]*"
    LT_NULL,   // null
    LT_FALSE,  // false
    LT_TRUE,   // true
    LT_UNINITIALIZED, // uninitialized

    // Identifiers
    IDENTIFIER = 3 << 8,
    ID_VARIABLE, // "[a-z0-9_]*[a-z][a-z0-9_]*"
    ID_FUNCTION, // "[a-z0-9_]*[a-z][a-z0-9_]*(?=[(<])"
    ID_MODULE, // "\b[A-Za-z0-9][A-Za-z0-9.+-]+(?=::)"

    // Comments
    COMMENT = 6 << 8,
    CO_LINE,  // '//'
    CO_BLOCK, // '///'
    CO_SPAN,  // '`.*`'

    QUALIFIER = 9 << 8,
    QU_CONST,    // const
    QU_MUTABLE,  // mutable
    QU_SAFE,     // safe
    QU_VOLATILE, // volatile

    // Units
    UNIT = 8 << 8,
};


inline
CTokenType operator&(CTokenType a, CTokenType b) {
    return static_cast<CTokenType>(static_cast<u16>(a) & static_cast<u16>(b));
}


inline
CTokenType operator|(CTokenType a, CTokenType b) {
    return static_cast<CTokenType>(static_cast<u16>(a) | static_cast<u16>(b));
}


struct CToken {
    u32 line = 0;
    u16 offset = 0;
    u8 size = 0;
    CTokenType type = CTokenType::NONE;


    CToken() {}


    CToken(
        CTokenType type,
        u16 line,
        u16 offset,
        u8 size
    ) :
        line(line),
        offset(offset),
        size(size),
        type(type)
    {}


    bool is_operator() const {
        return (type & CTokenType::GROUP_MASK) == CTokenType::OPERATOR;
    }


    bool is_keyword() const {
        return (type & CTokenType::GROUP_MASK) == CTokenType::KEYWORD;
    }


    bool is_identifier() const {
        return (type & CTokenType::GROUP_MASK) == CTokenType::IDENTIFIER;
    }


    bool is_number() const {
        return (type & CTokenType::GROUP_MASK) == CTokenType::NUMERIC_LITERAL;
    }


    bool is_string() const {
        return (type & CTokenType::GROUP_MASK) == CTokenType::STRING;
    }


    bool is_comment() const {
        return (type & CTokenType::GROUP_MASK) == CTokenType::COMMENT;
    }


    bool operator==(const CToken &other) const {
        return this->type == other.type;
    }


    bool operator==(CToken &&other) const {
        return this->type == other.type;
    }


    bool operator!=(const CToken &other) const {
        return this->type != other.type;
    }


    bool operator!=(CToken &&other) const {
        return this->type != other.type;
    }
};
