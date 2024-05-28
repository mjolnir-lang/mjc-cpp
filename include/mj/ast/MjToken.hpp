#pragma once

#include <std/Enum.hpp>
#include <std/StringView.hpp>


template<class MjTokenType>
struct MjTokenTypeValues {

    // Misc
    static constexpr MjTokenType NONE{0}; // 
    static constexpr MjTokenType INDENT{1}; // [ \t]+
    static constexpr MjTokenType WHITESPACE{2}; // [ \t]+

    // Operators
    static constexpr MjTokenType AT{3};                    // @
    static constexpr MjTokenType LAMBDA{4};                // a => b

    // Reference Operators
    static constexpr MjTokenType POINTER{5};               // *a
    static constexpr MjTokenType NULLABLE_POINTER{6};      // ^a
    static constexpr MjTokenType REFERENCE{7};             // &a

    // Lifetime Operators
    static constexpr MjTokenType GLOBAL_LIFETIME{8};       // "
    static constexpr MjTokenType LOCAL_LIFETIME{9};        // '

    // Arithmetic Operators
    static constexpr MjTokenType INVERT{10};                // ~a
    static constexpr MjTokenType NEGATE{11};                // -a
    static constexpr MjTokenType INCREMENT{12};             // a++
    static constexpr MjTokenType DECREMENT{13};             // a--
    static constexpr MjTokenType SET{14};                   // a = b
    static constexpr MjTokenType RIGHT_SHIFT{15};           // a >> b
    static constexpr MjTokenType RIGHT_SHIFT_SET{16};       // a >>= b
    static constexpr MjTokenType LEFT_SHIFT{17};            // a << b
    static constexpr MjTokenType LEFT_SHIFT_SET{18};        // a <<= b
    static constexpr MjTokenType MULTIPLY{19};              // a * b
    static constexpr MjTokenType MULTIPLY_SET{20};          // a *= b
    static constexpr MjTokenType DIVIDE{21};                // a / b
    static constexpr MjTokenType DIVIDE_SET{22};            // a /= b
    static constexpr MjTokenType REMAINDER{23};             // a % b
    static constexpr MjTokenType REMAINDER_SET{24};         // a %= b
    static constexpr MjTokenType PLUS{25};                  // a + b
    static constexpr MjTokenType PLUS_SET{26};              // a += b
    static constexpr MjTokenType MINUS{27};                 // a - b
    static constexpr MjTokenType MINUS_SET{28};             // a -= b
    static constexpr MjTokenType BITWISE_AND{29};           // a & b
    static constexpr MjTokenType BITWISE_AND_SET{30};       // a &= b
    static constexpr MjTokenType BITWISE_OR{31};            // a | b
    static constexpr MjTokenType BITWISE_OR_SET{32};        // a |= b
    static constexpr MjTokenType BITWISE_XOR{33};           // a ^ b
    static constexpr MjTokenType BITWISE_XOR_SET{34};       // a ^= b
    static constexpr MjTokenType LOGICAL_AND{35};           // a && b
    static constexpr MjTokenType LOGICAL_AND_SET{36};       // a &&= b
    static constexpr MjTokenType LOGICAL_OR{37};            // a || b
    static constexpr MjTokenType LOGICAL_OR_SET{38};        // a ||= b
    static constexpr MjTokenType LOGICAL_XOR{39};           // a ^^ b
    static constexpr MjTokenType LOGICAL_XOR_SET{40};       // a ^^= b

    // Relational Operators
    static constexpr MjTokenType NOT{41};                   // !a
    static constexpr MjTokenType EQUAL{42};                 // a == b
    static constexpr MjTokenType NOT_EQUAL{43};             // a != b
    static constexpr MjTokenType SPACESHIP{44};             // a <=> b
    static constexpr MjTokenType LESS_THAN{45};             // a < b
    static constexpr MjTokenType LESS_THAN_OR_EQUAL{46};    // a <= b
    static constexpr MjTokenType GREATER_THAN{47};          // a > b
    static constexpr MjTokenType GREATER_THAN_OR_EQUAL{48}; // a >= b

    // Separators
    static constexpr MjTokenType SCOPE{49};                 // T::m
    static constexpr MjTokenType DOT{50};                   // a.m
    static constexpr MjTokenType COMMA{51};                 // ,
    static constexpr MjTokenType SEMICOLON{52};             // ;
    static constexpr MjTokenType COLON{53};                 // :
    static constexpr MjTokenType QUESTION{54};              // a ? b
    static constexpr MjTokenType FALLIBLE{55};              // T?

    static constexpr MjTokenType OPEN_CAST{156};     // (
    static constexpr MjTokenType CLOSE_CAST{157};    // )
    static constexpr MjTokenType OPEN_TYPE{158};     // (
    static constexpr MjTokenType CLOSE_TYPE{159};    // )
    static constexpr MjTokenType OPEN_PARENTHESIS{56};     // (
    static constexpr MjTokenType CLOSE_PARENTHESIS{57};    // )
    static constexpr MjTokenType OPEN_SQUARE_BRACKET{58};  // [
    static constexpr MjTokenType CLOSE_SQUARE_BRACKET{59}; // ]
    static constexpr MjTokenType OPEN_CURLY_BRACE{60};     // {
    static constexpr MjTokenType CLOSE_CURLY_BRACE{61};    // }
    static constexpr MjTokenType OPEN_ANGLE_BRACKET{62};   // <
    static constexpr MjTokenType CLOSE_ANGLE_BRACKET{63};  // >

    // Keywords
    static constexpr MjTokenType AS{64};         // as
    static constexpr MjTokenType ASM{65};        // asm
    static constexpr MjTokenType BREAK{66};      // break
    static constexpr MjTokenType BITFIELD{67};   // bitfield
    static constexpr MjTokenType CLASS{68};      // class
    static constexpr MjTokenType CONTINUE{69};   // continue
    static constexpr MjTokenType DO{70};         // do
    static constexpr MjTokenType ELSE{71};       // else
    static constexpr MjTokenType ENUM{72};       // enum
    static constexpr MjTokenType FAIL{73};       // fail
    static constexpr MjTokenType FOR{74};        // for
    static constexpr MjTokenType IF{75};         // if
    static constexpr MjTokenType IMPL{76};       // impl
    static constexpr MjTokenType IMPORT{77};     // import
    static constexpr MjTokenType IN{78};         // in
    static constexpr MjTokenType INTERFACE{79};  // interface
    static constexpr MjTokenType IS{80};         // is
    static constexpr MjTokenType LOOP{81};       // loop
    static constexpr MjTokenType MATCH{82};      // match
    static constexpr MjTokenType RETURN{83};     // return
    static constexpr MjTokenType STRUCT{84};     // struct
    static constexpr MjTokenType TYPE{85};       // type
    static constexpr MjTokenType UNION{86};      // union
    static constexpr MjTokenType UNIT{87};       // unit
    static constexpr MjTokenType UNTIL{88};      // until
    static constexpr MjTokenType VARIANT{89};    // variant
    static constexpr MjTokenType WHERE{90};      // where
    static constexpr MjTokenType WHILE{91};      // while
    static constexpr MjTokenType YIELD{92};      // yield

    // Type Qualifiers
    static constexpr MjTokenType CONST{93};    // const
    static constexpr MjTokenType MUTABLE{94};  // mutable
    static constexpr MjTokenType SAFE{95};     // safe
    static constexpr MjTokenType VOLATILE{96}; // volatile

    // Boolean Literals
    static constexpr MjTokenType TRUE{97}; // true
    static constexpr MjTokenType FALSE{98}; // false

    // Misc Literals
    static constexpr MjTokenType NULL_{99}; // null
    static constexpr MjTokenType UNINITIALIZED{100}; // uninitialized

    // String Literals
    static constexpr MjTokenType RAW_STRING_LITERAL{101}; // "'.*'"
    static constexpr MjTokenType STRING_LITERAL{102};     // "\\".*\\""
    static constexpr MjTokenType INTERPOLATED_STRING_LITERAL{103}; // "\\".*\\"" (with escape sequences)

    // Numeric Literals
    static constexpr MjTokenType U8_LITERAL{104};     // (number)u8
    static constexpr MjTokenType U16_LITERAL{105};    // (number)u16
    static constexpr MjTokenType U32_LITERAL{106};    // (number)u(32)
    static constexpr MjTokenType U64_LITERAL{107};    // (number)u64
    static constexpr MjTokenType U128_LITERAL{108};   // (number)u128
    static constexpr MjTokenType I8_LITERAL{109};     // (number)i8
    static constexpr MjTokenType I16_LITERAL{110};    // (number)i16
    static constexpr MjTokenType I32_LITERAL{111};    // (number)i(32)
    static constexpr MjTokenType I64_LITERAL{112};    // (number)i64
    static constexpr MjTokenType I128_LITERAL{113};   // (number)i128
    static constexpr MjTokenType F16_LITERAL{114};    // (number)f16
    static constexpr MjTokenType F32_LITERAL{115};    // (number)f(32)
    static constexpr MjTokenType F64_LITERAL{116};    // (number)f64
    static constexpr MjTokenType F80_LITERAL{117};    // (number)f80
    static constexpr MjTokenType F128_LITERAL{118};   // (number)f128

    static constexpr MjTokenType NUMERIC_LITERAL{119};          // (number)

    // Identifiers
    static constexpr MjTokenType INVALID_IDENTIFIER{120};
    static constexpr MjTokenType INVALID_MODULE{121};
    static constexpr MjTokenType ANNOTATION_NAME{123}; // "[a-z0-9][a-z0-9.+-]*"
    static constexpr MjTokenType VARIABLE_NAME{124}; // "[a-z0-9_]*[a-z][a-z0-9_]*"
    static constexpr MjTokenType FUNCTION_NAME{125}; // "[a-z0-9_]*[a-z][a-z0-9_]*(?=[(<])"
    static constexpr MjTokenType MODULE_NAME{126};   //
    static constexpr MjTokenType TYPE_NAME{127};     // '[A-Z0-9][A-Z0-9.+-]*[a-z][A-Za-z0-9.+-]*'
    static constexpr MjTokenType CONSTANT_NAME{128}; // "([A-Z0-9_]*[A-Z][A-Z0-9_]*|false|null|true|uninitialized)"

    // Comments
    static constexpr MjTokenType LINE_COMMENT{129};            // '//'
    static constexpr MjTokenType BLOCK_COMMENT{130};           // '///'
    static constexpr MjTokenType FORMATTED_LINE_COMMENT{131};  // '//' (with formatting)
    static constexpr MjTokenType FORMATTED_BLOCK_COMMENT{132}; // '///' (with formatting)

    // Units
    static constexpr MjTokenType UNIT_EXPRESSION{133}; // 

    // sub Tokens
    static constexpr MjTokenType NUMERIC_LITERAL_POSTFIX{134};  // (number)[fiu](8|16|32|64|128)
    static constexpr MjTokenType NUMERIC_LITERAL_PREFIX{135};   // 0[box](number)
    static constexpr MjTokenType CHARACTER_ESCAPE_SEQUENCE{136}; // "\\.*"
};


class MjTokenType : public Enum<MjTokenType, u16>, public MjTokenTypeValues<MjTokenType> {
private:
    static
    const struct Data {
        StringView name;
        StringView text;
    } DATA[1] {
        {"AT", "@"},
    };
public:


    ///
    /// Constructors
    ///


    constexpr
    explicit
    MjTokenType(u16 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    constexpr
    StringView name() const noexcept {
        return DATA[_id].name;
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
};


struct MjToken {
    u32 line = 0;
    u16 offset = 0;
    u8 size = 0;
    MjTokenType type = MjTokenType::NONE;


    MjToken() {}


    MjToken(
        MjTokenType type,
        u16 line,
        u16 offset,
        u8 size
    ) :
        line(line),
        offset(offset),
        size(size),
        type(type)
    {}


    bool operator==(const MjToken &other) const {
        return this->type == other.type;
    }


    bool operator==(MjToken &&other) const {
        return this->type == other.type;
    }


    bool operator!=(const MjToken &other) const {
        return this->type != other.type;
    }


    bool operator!=(MjToken &&other) const {
        return this->type != other.type;
    }
};
