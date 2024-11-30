#pragma once

#include <core/Enum.hpp>
#include <core/StringView.hpp>


template<class MjTokenKind>
struct MjTokenKindValues {

    // Misc
    static constexpr MjTokenKind NONE{0}; // 
    static constexpr MjTokenKind INDENT{1}; // [ \t]+
    static constexpr MjTokenKind WHITESPACE{2}; // [ \t]+

    // Operators
    static constexpr MjTokenKind AT{3};                    // @
    static constexpr MjTokenKind LAMBDA{4};                // a => b

    // Reference Operators
    static constexpr MjTokenKind DEREFERENCE{5};           // *a
    static constexpr MjTokenKind NULLABLE_POINTER{6};      // ^a
    static constexpr MjTokenKind REFERENCE{7};             // &a
    static constexpr MjTokenKind FUNCTION_REFERENCE{8};    // f&

    // Lifetime Operators
    //static constexpr MjTokenKind GLOBAL_LIFETIME{8};       // "
    //static constexpr MjTokenKind LOCAL_LIFETIME{9};        // '

    // Arithmetic Operators
    static constexpr MjTokenKind INVERT{10};                // ~a
    static constexpr MjTokenKind NEGATE{11};                // -a
    static constexpr MjTokenKind INCREMENT{12};             // a++
    static constexpr MjTokenKind DECREMENT{13};             // a--
    static constexpr MjTokenKind SET{14};                   // a = b
    static constexpr MjTokenKind RIGHT_SHIFT{15};           // a >> b
    static constexpr MjTokenKind RIGHT_SHIFT_SET{16};       // a >>= b
    static constexpr MjTokenKind LEFT_SHIFT{17};            // a << b
    static constexpr MjTokenKind LEFT_SHIFT_SET{18};        // a <<= b
    static constexpr MjTokenKind MULTIPLY{19};              // a * b
    static constexpr MjTokenKind MULTIPLY_SET{20};          // a *= b
    static constexpr MjTokenKind DIVIDE{21};                // a / b
    static constexpr MjTokenKind DIVIDE_SET{22};            // a /= b
    static constexpr MjTokenKind REMAINDER{23};             // a % b
    static constexpr MjTokenKind REMAINDER_SET{24};         // a %= b
    static constexpr MjTokenKind PLUS{25};                  // a + b
    static constexpr MjTokenKind PLUS_SET{26};              // a += b
    static constexpr MjTokenKind MINUS{27};                 // a - b
    static constexpr MjTokenKind MINUS_SET{28};             // a -= b
    static constexpr MjTokenKind BITWISE_AND{29};           // a & b
    static constexpr MjTokenKind BITWISE_AND_SET{30};       // a &= b
    static constexpr MjTokenKind BITWISE_OR{31};            // a | b
    static constexpr MjTokenKind BITWISE_OR_SET{32};        // a |= b
    static constexpr MjTokenKind BITWISE_XOR{33};           // a ^ b
    static constexpr MjTokenKind BITWISE_XOR_SET{34};       // a ^= b
    static constexpr MjTokenKind LOGICAL_AND{35};           // a && b
    static constexpr MjTokenKind LOGICAL_OR{37};            // a || b

    // Relational Operators
    static constexpr MjTokenKind NOT{41};                   // !a
    static constexpr MjTokenKind EQUAL{42};                 // a == b
    static constexpr MjTokenKind NOT_EQUAL{43};             // a != b
    static constexpr MjTokenKind SPACESHIP{44};             // a <=> b
    static constexpr MjTokenKind LESS_THAN{45};             // a < b
    static constexpr MjTokenKind LESS_THAN_OR_EQUAL{46};    // a <= b
    static constexpr MjTokenKind GREATER_THAN{47};          // a > b
    static constexpr MjTokenKind GREATER_THAN_OR_EQUAL{48}; // a >= b

    // Separators
    static constexpr MjTokenKind SCOPE{49};                 // T::m
    static constexpr MjTokenKind DOT{50};                   // a.m
    static constexpr MjTokenKind COMMA{51};                 // ,
    static constexpr MjTokenKind SEMICOLON{52};             // ;
    static constexpr MjTokenKind COLON{53};                 // :
    static constexpr MjTokenKind QUESTION{54};              // a ? b
    static constexpr MjTokenKind HASH{55};                  // #
    static constexpr MjTokenKind DOLLAR_SIGN{56};           // $
    static constexpr MjTokenKind SHELL_COMMAND{57};         // [A-Za-z][A-Za-z0-9/:_-]
    static constexpr MjTokenKind SHELL_OPTION{58};          // -[A-Za-z][A-Za-z0-9_-]

    static constexpr MjTokenKind OPEN_CAST{156};     // (
    static constexpr MjTokenKind CLOSE_CAST{157};    // )
    static constexpr MjTokenKind OPEN_TYPE{158};     // (
    static constexpr MjTokenKind CLOSE_TYPE{159};    // )
    static constexpr MjTokenKind OPEN_PARENTHESIS{56};     // (
    static constexpr MjTokenKind CLOSE_PARENTHESIS{57};    // )
    static constexpr MjTokenKind OPEN_SQUARE_BRACKET{58};  // [
    static constexpr MjTokenKind CLOSE_SQUARE_BRACKET{59}; // ]
    static constexpr MjTokenKind OPEN_CURLY_BRACE{60};     // {
    static constexpr MjTokenKind CLOSE_CURLY_BRACE{61};    // }
    static constexpr MjTokenKind OPEN_ANGLE_BRACKET{62};   // <
    static constexpr MjTokenKind CLOSE_ANGLE_BRACKET{63};  // >

    // Keywords
    static constexpr MjTokenKind AS{64};         // as
    static constexpr MjTokenKind ASM{65};        // asm
    static constexpr MjTokenKind BREAK{66};      // break
    static constexpr MjTokenKind BITFIELD{67};   // bitfield
    static constexpr MjTokenKind CLASS{68};      // class
    static constexpr MjTokenKind CONTINUE{69};   // continue
    static constexpr MjTokenKind DO{70};         // do
    static constexpr MjTokenKind ELSE{71};       // else
    static constexpr MjTokenKind ENUM{72};       // enum
    static constexpr MjTokenKind FAIL{73};       // fail
    static constexpr MjTokenKind FOR{74};        // for
    static constexpr MjTokenKind IF{75};         // if
    static constexpr MjTokenKind IMPL{76};       // impl
    static constexpr MjTokenKind IMPORT{77};     // import
    static constexpr MjTokenKind IN{78};         // in
    static constexpr MjTokenKind INTERFACE{79};  // interface
    static constexpr MjTokenKind IS{80};         // is
    static constexpr MjTokenKind LOOP{81};       // loop
    static constexpr MjTokenKind MATCH{82};      // match
    static constexpr MjTokenKind RETURN{83};     // return
    static constexpr MjTokenKind STRUCT{84};     // struct
    static constexpr MjTokenKind TYPE{85};       // type
    static constexpr MjTokenKind UNION{86};      // union
    static constexpr MjTokenKind UNIT{87};       // unit
    static constexpr MjTokenKind UNTIL{88};      // until
    static constexpr MjTokenKind VARIANT{89};    // variant
    static constexpr MjTokenKind WHERE{90};      // where
    static constexpr MjTokenKind WHILE{91};      // while
    static constexpr MjTokenKind YIELD{92};      // yield

    // Type Qualifiers
    static constexpr MjTokenKind CONST{93};    // const
    static constexpr MjTokenKind MUTABLE{94};  // mutable
    static constexpr MjTokenKind SAFE{95};     // safe
    static constexpr MjTokenKind VOLATILE{96}; // volatile

    // Type Modifiers
    static constexpr MjTokenKind POINTER_TYPE_MODIFIER{140};   // T*
    static constexpr MjTokenKind REFERENCE_TYPE_MODIFIER{141}; // T&
    static constexpr MjTokenKind FALLIBLE_TYPE_MODIFIER{142};  // T?
    static constexpr MjTokenKind NO_RETURN_TYPE_MODIFIER{143}; // T!

    // Boolean Literals
    static constexpr MjTokenKind TRUE{97}; // true
    static constexpr MjTokenKind FALSE{98}; // false

    // Misc Literals
    static constexpr MjTokenKind NULL_{99}; // null
    static constexpr MjTokenKind UNINITIALIZED{100}; // uninitialized

    // String Literals
    static constexpr MjTokenKind RAW_STRING_LITERAL{101}; // "'.*'"
    static constexpr MjTokenKind STRING_LITERAL{102};     // "\\".*\\""
    static constexpr MjTokenKind INTERPOLATED_STRING_LITERAL{103}; // "\\".*\\"" (with escape sequences)

    // Numeric Literals
    static constexpr MjTokenKind U8_LITERAL{104};     // (number)u8
    static constexpr MjTokenKind U16_LITERAL{105};    // (number)u16
    static constexpr MjTokenKind U32_LITERAL{106};    // (number)u(32)
    static constexpr MjTokenKind U64_LITERAL{107};    // (number)u64
    static constexpr MjTokenKind U128_LITERAL{108};   // (number)u128
    static constexpr MjTokenKind I8_LITERAL{109};     // (number)i8
    static constexpr MjTokenKind I16_LITERAL{110};    // (number)i16
    static constexpr MjTokenKind I32_LITERAL{111};    // (number)i(32)
    static constexpr MjTokenKind I64_LITERAL{112};    // (number)i64
    static constexpr MjTokenKind I128_LITERAL{113};   // (number)i128
    static constexpr MjTokenKind F16_LITERAL{114};    // (number)f16
    static constexpr MjTokenKind F32_LITERAL{115};    // (number)f(32)
    static constexpr MjTokenKind F64_LITERAL{116};    // (number)f64
    static constexpr MjTokenKind F80_LITERAL{117};    // (number)f80
    static constexpr MjTokenKind F128_LITERAL{118};   // (number)f128

    static constexpr MjTokenKind NUMERIC_LITERAL{119};          // (number)

    // Identifiers
    static constexpr MjTokenKind INVALID_IDENTIFIER{120};
    static constexpr MjTokenKind INVALID_MODULE_NAME{121};
    static constexpr MjTokenKind ANNOTATION_NAME{123}; // "[a-z0-9][a-z0-9.+-]*"
    static constexpr MjTokenKind VARIABLE_NAME{124}; // "[a-z0-9_]*[a-z][a-z0-9_]*"
    static constexpr MjTokenKind FUNCTION_NAME{125}; // "[a-z0-9_]*[a-z][a-z0-9_]*(?=[(<])"
    static constexpr MjTokenKind MODULE_NAME{126};   //
    static constexpr MjTokenKind TYPE_NAME{127};     // '[A-Z0-9][A-Z0-9.+-]*[a-z][A-Za-z0-9.+-]*'
    static constexpr MjTokenKind CONSTANT_NAME{128}; // "([A-Z0-9_]*[A-Z][A-Z0-9_]*|false|null|true|uninitialized)"

    // Comments
    static constexpr MjTokenKind LINE_COMMENT{129};            // '//'
    static constexpr MjTokenKind BLOCK_COMMENT{130};           // '///'
    static constexpr MjTokenKind FORMATTED_LINE_COMMENT{131};  // '//' (with formatting)
    static constexpr MjTokenKind FORMATTED_BLOCK_COMMENT{132}; // '///' (with formatting)

    // Units
    static constexpr MjTokenKind UNIT_EXPRESSION{133}; // 

    // sub Tokens
    static constexpr MjTokenKind NUMERIC_LITERAL_POSTFIX{134};  // (number)[fiu](8|16|32|64|128)
    static constexpr MjTokenKind NUMERIC_LITERAL_PREFIX{135};   // 0[box](number)
    static constexpr MjTokenKind CHARACTER_ESCAPE_SEQUENCE{136}; // "\\.*"
    static constexpr MjTokenKind INVALID_ESCAPE_SEQUENCE{137}; // "\\.*"
};


class MjTokenKind : public Enum<u16>, public MjTokenKindValues<MjTokenKind> {
private:
    static
    constexpr
    struct Data {
        StringView name;
        StringView text;
        u32 flags = 0;
    } DATA[] {
        {"AT",                     "@"},
        {"LAMBDA",                 "=>"},
        {"DEREFERENCE",            "*"},
        {"NULLABLE_POINTER",       "^"},
        {"REFERENCE",              "&"},
        {"GLOBAL_LIFETIME",        "\""},
        {"LOCAL_LIFETIME",         "'"},
        {"INVERT",                 "~"},
        {"NEGATE",                 "-"},
        {"INCREMENT",              "++"},
        {"DECREMENT",              "--"},
        {"SET",                    "="},
        {"RIGHT_SHIFT",            ">>"},
        {"RIGHT_SHIFT_SET",        ">>="},
        {"LEFT_SHIFT",             "<<"},
        {"LEFT_SHIFT_SET",         "<<="},
        {"MULTIPLY",               "*"},
        {"MULTIPLY_SET",           "*="},
        {"DIVIDE",                 "/"},
        {"DIVIDE_SET",             "/="},
        {"REMAINDER",              "%"},
        {"REMAINDER_SET",          "%="},
        {"PLUS",                   "+"},
        {"PLUS_SET",               "+="},
        {"MINUS",                  "-"},
        {"MINUS_SET",              "-="},
        {"BITWISE_AND",            "&"},
        {"BITWISE_AND_SET",        "&="},
        {"BITWISE_OR",             "|"},
        {"BITWISE_OR_SET",         "|="},
        {"BITWISE_XOR",            "^"},
        {"BITWISE_XOR_SET",        "^="},
        {"LOGICAL_AND",            "&&"},
        {"LOGICAL_OR",             "||"},

        {"NOT",                    "!a"},
        {"EQUAL",                  "=="},
        {"NOT_EQUAL",              "!="},
        {"SPACESHIP",              "<=>"},
        {"LESS_THAN",              "<"},
        {"LESS_THAN_OR_EQUAL",     "<="},
        {"GREATER_THAN",           ">"},
        {"GREATER_THAN_OR_EQUAL",  ">="},

        {"SCOPE",                  "::"},
        {"DOT",                    "."},
        {"COMMA",                  ","},
        {"SEMICOLON",              ";"},
        {"COLON",                  ":"},
        {"QUESTION",               "?"},
        {"HASH",                   "#"},
        {"DOLLAR_SIGN",            "$"},
        {"SHELL_COMMAND",          nullptr},
        {"SHELL_OPTION",           nullptr},

        {"OPEN_CAST",              "("},
        {"CLOSE_CAST",             ")"},
        {"OPEN_TYPE",              "("},
        {"CLOSE_TYPE",             ")"},
        {"OPEN_PARENTHESIS",       "("},
        {"CLOSE_PARENTHESIS",      ")"},
        {"OPEN_SQUARE_BRACKET",    "["},
        {"CLOSE_SQUARE_BRACKET",   "]"},
        {"OPEN_CURLY_BRACE",       "{"},
        {"CLOSE_CURLY_BRACE",      "}"},
        {"OPEN_ANGLE_BRACKET",     "<"},
        {"CLOSE_ANGLE_BRACKET",    ">"},

        {"AS",                     "as"},
        {"ASM",                    "asm"},
        {"BREAK",                  "break"},
        {"BITFIELD",               "bitfield"},
        {"CLASS",                  "class"},
        {"CONTINUE",               "continue"},
        {"DO",                     "do"},
        {"ELSE",                   "else"},
        {"ENUM",                   "enum"},
        {"FAIL",                   "fail"},
        {"FOR",                    "for"},
        {"IF",                     "if"},
        {"IMPL",                   "impl"},
        {"IMPORT",                 "import"},
        {"IN",                     "in"},
        {"INTERFACE",              "interface"},
        {"IS",                     "is"},
        {"MATCH",                  "match"},
        {"RETURN",                 "return"},
        {"STRUCT",                 "struct"},
        {"TYPE",                   "type"},
        {"UNION",                  "union"},
        {"UNIT",                   "unit"},
        {"UNTIL",                  "until"},
        {"WHERE",                  "where"},
        {"WHILE",                  "while"},
        {"YIELD",                  "yield"},

        {"CONST",                  "const"},
        {"MUTABLE",                "mutable"},
        {"SAFE",                   "safe"},
        {"VOLATILE",               "volatile"},

        {"POINTER_TYPE_MODIFIER",   "*"},
        {"REFERENCE_TYPE_MODIFIER", "&"},
        {"NO_RETURN_TYPE_MODIFIER", "?"},
        {"FALLIBLE_TYPE_MODIFIER",  "!"},

        {"TRUE",                    "true"},
        {"FALSE",                   "false"},

        {"NULL",                    "null"},
        {"UNINITIALIZED",           "uninitialized"},

        {"RAW_STRING_LITERAL",          nullptr},
        {"STRING_LITERAL",              nullptr},
        {"INTERPOLATED_STRING_LITERAL", nullptr},

        {"U8_LITERAL",   "u8"},
        {"U16_LITERAL",  "u16"},
        {"U32_LITERAL",  "u32"},
        {"U64_LITERAL",  "u64"},
        {"U128_LITERAL", "u128"},
        {"I8_LITERAL",   "i8"},
        {"I16_LITERAL",  "i16"},
        {"I32_LITERAL",  "i32"},
        {"I64_LITERAL",  "i64"},
        {"I128_LITERAL", "i128"},
        {"F16_LITERAL",  "f16"},
        {"F32_LITERAL",  "f32"},
        {"F64_LITERAL",  "f64"},
        {"F80_LITERAL",  "f80"},
        {"F128_LITERAL", "f128"},

        {"NUMERIC_LITERAL",                  nullptr},

        {"INVALID_IDENTIFIER",               nullptr},
        {"INVALID_MODULE",                   nullptr},
        {"ANNOTATION_NAME",                  nullptr},
        {"VARIABLE_NAME",                    nullptr},
        {"FUNCTION_NAME",                    nullptr},
        {"MODULE_NAME",                      nullptr},
        {"TYPE_NAME",                        nullptr},
        {"CONSTANT_NAME",                    nullptr},

        {"LINE_COMMENT",                       "//"},
        {"BLOCK_COMMENT",                      "///"},
        {"FORMATTED_LINE_COMMENT",             "//"},
        {"FORMATTED_BLOCK_COMMENT",            "///"},

        {"UNIT_EXPRESSION",                  nullptr},

        {"NUMERIC_LITERAL_POSTFIX",          nullptr},
        {"NUMERIC_LITERAL_PREFIX",           nullptr},
        {"CHARACTER_ESCAPE_SEQUENCE",        nullptr},
    };
public:


    ///
    /// Constructors
    ///


    constexpr
    explicit
    MjTokenKind(u16 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    constexpr
    StringView name() const noexcept {
        return DATA[_id].name;
    }


    constexpr
    StringView text() const noexcept {
        return DATA[_id].text;
    }


    constexpr
    u32 size() const noexcept {
        return DATA[_id].text.size();
    }


    constexpr
    bool is_operator() const noexcept {
        return true;
    }


    constexpr
    bool is_keyword() const noexcept {
        return true;
    }


    constexpr
    bool is_identifier() const noexcept {
        return true;
    }


    constexpr
    bool is_literal() const noexcept {
        return true;
    }


    constexpr
    bool is_whitespace() const noexcept {
        return _id & (WHITESPACE | INDENT);
    }


    constexpr
    bool requires_leading_whitespace() const noexcept {
        return DATA[_id].flags & 1;
    }


    constexpr
    bool requires_trailing_whitespace() const noexcept {
        return DATA[_id].flags & 2;
    }


    constexpr
    bool is_fixed_size() const noexcept {
        return DATA[_id].text.is_empty();
    }


    constexpr
    bool is_pattern() const noexcept {
        return DATA[_id].text.is_empty();
    }


    constexpr
    bool requires_trailing_whitespace() const noexcept {
        return DATA[_id].flags & 2;
    }
};
