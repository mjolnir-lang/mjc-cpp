#pragma once

#include <core/Enum.hpp>
#include <core/Range.hpp>
#include <core/StringView.hpp>


template<class MjTokenStringKind>
struct MjTokenStringKindValues {
    static constexpr MjTokenStringKind NONE{0};
    static constexpr MjTokenStringKind LOWERCASE{1};
    static constexpr MjTokenStringKind UPPERCASE{2};
    static constexpr MjTokenStringKind MIXEDCASE{3};
    static constexpr MjTokenStringKind NUMBER_LITERALS{4};
    static constexpr MjTokenStringKind STRING_LITERALS{5};
    static constexpr MjTokenStringKind UNIT_EXPRESSIONS{6};
};


struct MjTokenStringKind : public Enum<u8>, public MjTokenStringKindValues<MjTokenStringKind> {

    constexpr
    explicit
    MjTokenStringKind(u8 id) noexcept : Enum(id) {}
};


struct MjNumberTokenInfo {
    u8 has_fraction : 1;
    u8 has_exponent : 1;
    u8 has_prefix   : 1; // NONE, 0x, 0o, 0b none
    u8 type_suffix  : 5; // f, f128, f16, f32, f64, f80, u, u128, u16, u32, u64, u8, i, i128, i16, i32, i64, i8
};


template<class MjTokenKind>
struct MjTokenKindValues {

    // The null value token
    static constexpr MjTokenKind NONE{0};

    // `.*`
    static constexpr MjTokenKind INVALID{1};

    // '` +`' - Tabs converted to spaces following tab rules
    /// Signifies the begining of a line
    /// Encoding: [line_index[7:0], line_index[15:8]]
    static constexpr MjTokenKind INDENT{2};

    // '` +`'
    /// An extra whitespace amount.
    /// Encoding: [width]
    static constexpr MjTokenKind WHITESPACE{3};


    ///
    /// Keywords
    ///


    static constexpr MjTokenKind AND{4};         // `and`
    static constexpr MjTokenKind AS{4};          // `as`
    static constexpr MjTokenKind ASM{5};         // `asm`
    static constexpr MjTokenKind BITFIELD{6};    // `bitfield`
    static constexpr MjTokenKind BREAK{7};       // `break`
    static constexpr MjTokenKind CASE{8};        // `case`
    static constexpr MjTokenKind CLASS{8};       // `class`
    static constexpr MjTokenKind CONTINUE{9};    // `continue`
    static constexpr MjTokenKind DO{10};         // `do`
    static constexpr MjTokenKind ELSE{11};       // `else`
    static constexpr MjTokenKind ENUM{12};       // `enum`
    static constexpr MjTokenKind FAIL{13};       // `fail`
    static constexpr MjTokenKind FOR{14};        // `for`
    static constexpr MjTokenKind IF{15};         // `if`
    static constexpr MjTokenKind IMPL{16};       // `impl`
    static constexpr MjTokenKind IMPORT{17};     // `import`
    static constexpr MjTokenKind IN{18};         // `in`
    static constexpr MjTokenKind INTERFACE{19};  // `interface`
    static constexpr MjTokenKind IS{20};         // `is`
    static constexpr MjTokenKind MATCH{22};      // `match`
    static constexpr MjTokenKind NOT{57};        // `not`
    static constexpr MjTokenKind OR{22};         // `or`
    static constexpr MjTokenKind RETURN{23};     // `return`
    static constexpr MjTokenKind STRUCT{24};     // `struct`
    static constexpr MjTokenKind TYPE{25};       // `type`
    static constexpr MjTokenKind THEN{25};       // `then`
    static constexpr MjTokenKind UNION{26};      // `union`
    static constexpr MjTokenKind UNIT{27};       // `unit`
    static constexpr MjTokenKind UNTIL{28};      // `until`
    static constexpr MjTokenKind WHERE{30};      // `where`
    static constexpr MjTokenKind WHILE{31};      // `while`
    static constexpr MjTokenKind YIELD{32};      // `yield`


    ///
    /// Type Qualifiers
    ///


    static constexpr MjTokenKind CONST{33};    // `const`
    static constexpr MjTokenKind MUTABLE{34};  // `mutable`
    static constexpr MjTokenKind SAFE{35};     // `safe`


    ///
    /// Literals
    ///


    static constexpr MjTokenKind TRUE{37};          // `true`
    static constexpr MjTokenKind FALSE{38};         // `false`
    static constexpr MjTokenKind NULL_{39};         // `null`
    static constexpr MjTokenKind UNINITIALIZED{40}; // `uninitialized`


    ///
    /// Identifiers
    ///


    static constexpr MjTokenKind INVALID_IDENTIFIER{41}; // `.*`
    static constexpr MjTokenKind ANNOTATION_NAME{42};    // `[a-z0-9][a-z0-9.+-]*`
    static constexpr MjTokenKind VARIABLE_NAME{43};      // `[a-z0-9_]*[a-z][a-z0-9_]*`
    static constexpr MjTokenKind FUNCTION_NAME{44};      // `[a-z0-9_]*[a-z][a-z0-9_]*(?=[(<&])`
    static constexpr MjTokenKind CONSTANT_NAME{45};      // `[A-Z0-9_]*[A-Z][A-Z0-9_]*`
    static constexpr MjTokenKind TYPE_NAME{46};          // `[A-Z0-9][A-Z0-9+-]*[a-z][A-Za-z0-9+-]*`
    static constexpr MjTokenKind NUMERIC_LITERAL{48};    // `<number>`
    static constexpr MjTokenKind UNIT_EXPRESSION{49};    // `(?:[A-Za-zµΩÅ°'\"]|\\^g|1/)[A-Za-z0-9⁰¹²³⁴⁵⁶⁷⁸⁹⁻⸍µΩÅ°'\"·^*/-]*`


    ///
    /// String Literals
    ///


    static constexpr MjTokenKind RAW_STRING_LITERAL{50};          // `'.*'`
    static constexpr MjTokenKind STRING_LITERAL{51};              // `".*"`
    static constexpr MjTokenKind INTERPOLATED_STRING_LITERAL{52}; // `".*"` (with escape sequences)


    ///
    /// Comments
    ///


    static constexpr MjTokenKind LINE_COMMENT{53};            // '// .*'
    static constexpr MjTokenKind FORMATTED_LINE_COMMENT{54};  // '// .*(`.*`.*)+' (with formatting)
    static constexpr MjTokenKind BLOCK_COMMENT{55};           // '/// .*'
    static constexpr MjTokenKind FORMATTED_BLOCK_COMMENT{56}; // '/// .*(`.*`.*)+' (with formatting)


    ///
    /// Prefix Operators
    ///


    static constexpr MjTokenKind INVERT{58};                 // `~a`
    static constexpr MjTokenKind NEGATE{59};                 // `-a`
    static constexpr MjTokenKind DEREFERENCE{60};            // `*a`
    static constexpr MjTokenKind REFERENCE{61};              // `&a`
    static constexpr MjTokenKind SHELL_SHORT_OPTION{62};     // `-a`
    static constexpr MjTokenKind SHELL_LONG_OPTION{63};      // `--a`


    ///
    /// Postfix Operators
    ///


    static constexpr MjTokenKind INCREMENT{64};               // `a++`
    static constexpr MjTokenKind DECREMENT{65};               // `a--`
    static constexpr MjTokenKind FUNCTION_REFERENCE{66};      // `f&`
    static constexpr MjTokenKind POINTER_TYPE_MODIFIER{67};   // `T*`
    static constexpr MjTokenKind REFERENCE_TYPE_MODIFIER{68}; // `T&`
    static constexpr MjTokenKind FALLIBLE_TYPE_MODIFIER{69};  // `T?`
    static constexpr MjTokenKind NO_RETURN_TYPE_MODIFIER{70}; // `T!`


    ///
    /// Infix Operators
    ///


    static constexpr MjTokenKind SET{71};                    // `a = b`
    static constexpr MjTokenKind EQUAL{72};                  // `a == b`
    static constexpr MjTokenKind LAMBDA{73};                 // `a => b`
    static constexpr MjTokenKind LESS_THAN{74};              // `a < b`
    static constexpr MjTokenKind LEFT_SHIFT{75};             // `a << b`
    static constexpr MjTokenKind LEFT_SHIFT_SET{76};         // `a <<= b`
    static constexpr MjTokenKind LESS_THAN_OR_EQUAL{77};     // `a <= b`
    static constexpr MjTokenKind SPACESHIP{78};              // `a <=> b`
    static constexpr MjTokenKind GREATER_THAN{79};           // `a > b`
    static constexpr MjTokenKind RIGHT_SHIFT{80};            // `a >> b`
    static constexpr MjTokenKind RIGHT_SHIFT_SET{81};        // `a >>= b`
    static constexpr MjTokenKind GREATER_THAN_OR_EQUAL{82};  // `a >= b`
    static constexpr MjTokenKind MULTIPLY{83};               // `a * b`
    static constexpr MjTokenKind MULTIPLY_SET{84};           // `a *= b`
    static constexpr MjTokenKind DIVIDE{85};                 // `a / b`
    static constexpr MjTokenKind DIVIDE_SET{86};             // `a /= b`
    static constexpr MjTokenKind REMAINDER{87};              // `a % b`
    static constexpr MjTokenKind REMAINDER_SET{88};          // `a %= b`
    static constexpr MjTokenKind PLUS{89};                   // `a + b`
    static constexpr MjTokenKind PLUS_SET{90};               // `a += b`
    static constexpr MjTokenKind MINUS{91};                  // `a - b`
    static constexpr MjTokenKind MINUS_SET{92};              // `a -= b`
    static constexpr MjTokenKind BITWISE_AND{93};            // `a & b`
    static constexpr MjTokenKind BITWISE_AND_SET{94};        // `a &= b`
    static constexpr MjTokenKind BITWISE_OR{95};             // `a | b`
    static constexpr MjTokenKind BITWISE_OR_SET{96};         // `a |= b`
    static constexpr MjTokenKind BITWISE_XOR{97};            // `a ^ b`
    static constexpr MjTokenKind BITWISE_XOR_SET{98};        // `a ^= b`
    static constexpr MjTokenKind NOT_EQUAL{101};             // `a != b`


    ///
    /// Separators
    ///


    static constexpr MjTokenKind SCOPE{104};                // `T::m`
    static constexpr MjTokenKind DOT{105};                  // `a.m`

    static constexpr MjTokenKind COMMA{106};                // `,`
    static constexpr MjTokenKind SEMICOLON{107};            // `;`
    static constexpr MjTokenKind COLON{108};                // `:`

    static constexpr MjTokenKind HASH{109};                 // `#`
    static constexpr MjTokenKind DOLLAR_SIGN{110};          // `$`
    static constexpr MjTokenKind AT{111};                   // `@`

    static constexpr MjTokenKind OPEN_PARENTHESIS{112};     // `(`
    static constexpr MjTokenKind CLOSE_PARENTHESIS{113};    // `)`
    static constexpr MjTokenKind OPEN_SQUARE_BRACKET{114};  // `[`
    static constexpr MjTokenKind CLOSE_SQUARE_BRACKET{115}; // `]`
    static constexpr MjTokenKind OPEN_CURLY_BRACE{116};     // `{`
    static constexpr MjTokenKind CLOSE_CURLY_BRACE{117};    // `}`
    static constexpr MjTokenKind OPEN_ANGLE_BRACKET{118};   // `<`
    static constexpr MjTokenKind CLOSE_ANGLE_BRACKET{119};  // `>`

    static constexpr MjTokenKind OPEN_CAST{120};     // `(`
    static constexpr MjTokenKind CLOSE_CAST{121};    // `)`
    static constexpr MjTokenKind OPEN_TYPE{122};     // `(`
    static constexpr MjTokenKind CLOSE_TYPE{123};    // `)`


    ///
    /// Lifetime Operators
    ///


    static constexpr MjTokenKind GLOBAL_LIFETIME{124}; // `[*&]"`
    static constexpr MjTokenKind LOCAL_LIFETIME{125};  // `[*&]'`


    ///
    /// Subtokens
    ///


    static constexpr MjTokenKind NUMERIC_LITERAL_PREFIX{126};    // `0[box]`
    static constexpr MjTokenKind NUMERIC_LITERAL_SUFFIX{127};    // `[fiu](8|16|32|64|128)`
    static constexpr MjTokenKind CHARACTER_ESCAPE_SEQUENCE{128}; // `\.*`
    static constexpr MjTokenKind INVALID_ESCAPE_SEQUENCE{129};   // `\.*`
};


/// The token ID value encoded in the token stream. Additional metadata is stored for builtin tokens
/// so that their string values do not have to be managed and their relative whitespace can be
/// encoded.
class MjTokenKind : public Enum<u8>, public MjTokenKindValues<MjTokenKind> {
private:
    static
    constexpr
    struct Data {
        StringView name;
        StringView text;
        struct Flags {
            u8 can_be_variable : 1;
            u8 can_be_template : 1;
            u8 can_be_function : 1;
            u8 keyword_always  : 1;
            u8 keyword_if_type : 1;
            u8 keyword_if_angle : 1;
            u8 keyword_if_brace : 1;
            u8 keyword_if_variable : 1;
            u8 keyword_if_expression : 1;
        } flags;
    } DATA[] {
        {"NONE",       nullptr},
        {"INVALID",    nullptr},
        {"INDENT",     nullptr},
        {"WHITESPACE", nullptr},

        {"AND",                    "and",               },
        {"AS",                     "as",                },
        {"ASM",                    "asm",               },
        {"BREAK",                  "break",             },
        {"BITFIELD",               "bitfield",          },
        {"CLASS",                  "class",             },
        {"CONTINUE",               "continue",          },
        {"DO",                     "do",                },
        {"ELSE",                   "else",              },
        {"ENUM",                   "enum",              },
        {"FAIL",                   "fail",              },
        {"FOR",                    "for",               },
        {"IF",                     "if",                },
        {"IMPL",                   "impl",              },
        {"IMPORT",                 "import",            },
        {"IN",                     "in",                },
        {"INTERFACE",              "interface",         },
        {"IS",                     "is",                },
        {"MATCH",                  "match",             },
        {"NOT",                    "not",               },
        {"OR",                     "or",                },
        {"RETURN",                 "return",            },
        {"STRUCT",                 "struct",            },
        {"TYPE",                   "type",              },
        {"UNION",                  "union",             },
        {"UNIT",                   "unit",              },
        {"UNTIL",                  "until",             },
        {"WHERE",                  "where",             },
        {"WHILE",                  "while",             },
        {"YIELD",                  "yield",             },

        {"CONST",                  "const",             },
        {"MUTABLE",                "mutable",           },
        {"SAFE",                   "safe",              },

        {"TRUE",                    "true",             },
        {"FALSE",                   "false",            },
        {"NULL",                    "null",             },
        {"UNINITIALIZED",           "uninitialized",    },

        {"INVALID_IDENTIFIER",      nullptr},
        {"ANNOTATION_NAME",         nullptr},
        {"VARIABLE_NAME",           nullptr},
        {"FUNCTION_NAME",           nullptr},
        {"CONSTANT_NAME",           nullptr},
        {"TYPE_NAME",               nullptr},
        {"MODULE_NAME",             nullptr},
        {"NUMERIC_LITERAL",         nullptr},
        {"UNIT_EXPRESSION",         nullptr},

        {"RAW_STRING_LITERAL",          nullptr},
        {"STRING_LITERAL",              nullptr},
        {"INTERPOLATED_STRING_LITERAL", nullptr},

        {"LINE_COMMENT",            nullptr},
        {"FORMATTED_LINE_COMMENT",  nullptr},
        {"BLOCK_COMMENT",           nullptr},
        {"FORMATTED_BLOCK_COMMENT", nullptr},

        {"INVERT",                 "~"},
        {"NEGATE",                 "-"},
        {"DEREFERENCE",            "*"},
        {"REFERENCE",              "&"},
        {"SHELL_SHORT_OPTION",     "-"},
        {"SHELL_LONG_OPTION",      "--"},

        {"INCREMENT",               "++"},
        {"DECREMENT",               "--"},
        {"FUNCTION_REFERENCE",      "&"},
        {"POINTER_TYPE_MODIFIER",   "*"},
        {"REFERENCE_TYPE_MODIFIER", "&"},
        {"FALLIBLE_TYPE_MODIFIER",  "?"},
        {"NO_RETURN_TYPE_MODIFIER", "!"},

        {"SET",                    "="},
        {"EQUAL",                  "=="},
        {"LAMBDA",                 "=>"},
        {"LESS_THAN",              "<"},
        {"LEFT_SHIFT",             "<<"},
        {"LEFT_SHIFT_SET",         "<<="},
        {"LESS_THAN_OR_EQUAL",     "<="},
        {"SPACESHIP",              "<=>"},
        {"GREATER_THAN",           ">"},
        {"RIGHT_SHIFT",            ">>"},
        {"RIGHT_SHIFT_SET",        ">>="},
        {"GREATER_THAN_OR_EQUAL",  ">="},
        {"DEREFERENCE",            "*"},
        {"NULLABLE_POINTER",       "^"},
        {"REFERENCE",              "&"},
        {"INVERT",                 "~"},
        {"NEGATE",                 "-"},
        {"INCREMENT",              "++"},
        {"DECREMENT",              "--"},
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

        {"NOT_EQUAL",              "!="},

        {"SCOPE",                  "::"},
        {"DOT",                    "."},
        {"COMMA",                  ","},
        {"SEMICOLON",              ";"},
        {"COLON",                  ":"},
        {"HASH",                   "#"},
        {"DOLLAR_SIGN",            "$"},
        {"AT",                     "@"},
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

        {"GLOBAL_LIFETIME",        "\""},
        {"LOCAL_LIFETIME",         "'"},

        {"NUMERIC_LITERAL_PREFIX",           nullptr},
        {"NUMERIC_LITERAL_SUFFIX",           nullptr},
        {"CHARACTER_ESCAPE_SEQUENCE",        nullptr},
    };
public:


    ///
    /// Shared
    ///


    static
    constexpr
    Range<MjTokenKind> reserved_names() noexcept {
        return Range<MjTokenKind>(AND, MjTokenKind(UNINITIALIZED + 1));
    }


    static
    constexpr
    Range<MjTokenKind> keywords() noexcept {
        return Range<MjTokenKind>(AND, MjTokenKind(YIELD + 1));
    }


    static
    constexpr
    Range<MjTokenKind> operators() noexcept {
        return Range<MjTokenKind>(INVERT, MjTokenKind(NOT_EQUAL + 1));
    }


    ///
    /// Constructors
    ///


    constexpr
    explicit
    MjTokenKind(u8 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    constexpr
    StringView name() const noexcept {
        return DATA[_id].name;
    }


    constexpr
    StringView builtin_text() const noexcept {
        return DATA[_id].text;
    }


    constexpr
    u32 size() const noexcept {
        return DATA[_id].text.size();
    }


    constexpr
    bool is_operator() const noexcept {
        return _id - INVALID < CLOSE_ANGLE_BRACKET - INVALID;
    }


    constexpr
    bool is_keyword() const noexcept {
        return _id - AS < YIELD - AS;
    }


    constexpr
    bool is_type_qualifier() const noexcept {
        return _id - CONST < VOLATILE - CONST;
    }


    constexpr
    bool is_identifier() const noexcept {
        return _id - INVALID_IDENTIFIER < TYPE_NAME - INVALID_IDENTIFIER;
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
    bool is_fixed_size() const noexcept {
        return DATA[_id].text.is_empty();
    }


    constexpr
    bool is_pattern() const noexcept {
        return DATA[_id].text.is_empty();
    }


    //constexpr
    //u8 encoded_size() const noexcept {
    //    return DATA[_id].flags & 3;
    //}


    constexpr
    u8 has_builtin_text() const noexcept {
        return;
    }


    constexpr
    MjTokenStringKind string_kind() const noexcept {
        return;
    }


    constexpr
    bool has_whitespace(MjTokenKind other) noexcept {
        return MjTokenKind::whitespace(*this, other);
    }


    /// Return true if there is canonical whitespace between the given tokens.
    //static
    //constexpr
    //bool whitespace(MjTokenKind a, MjTokenKind b) noexcept {
    //    return DATA[a].flags & DATA[b].flags;
    //}
};
