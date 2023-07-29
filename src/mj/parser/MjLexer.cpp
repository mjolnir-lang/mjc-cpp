#include "mj/MjLexer.hpp"


const MjToken MjToken::EOT("EOF", MjTokenType::EOT);
const MjToken MjToken::LSR_SET(">>>=", MjTokenType::OPERATOR);
const MjToken MjToken::LSR(">>>", MjTokenType::OPERATOR);
const MjToken MjToken::LSL_SET("<<=", MjTokenType::OPERATOR);
const MjToken MjToken::ASR_SET(">>=", MjTokenType::OPERATOR);
const MjToken MjToken::LSL("<<", MjTokenType::OPERATOR);
const MjToken MjToken::ASR(">>", MjTokenType::OPERATOR);
const MjToken MjToken::SCOPE("::", MjTokenType::OPERATOR);
const MjToken MjToken::PTR("->", MjTokenType::OPERATOR);
const MjToken MjToken::INC("++", MjTokenType::OPERATOR);
const MjToken MjToken::DEC("--", MjTokenType::OPERATOR);
const MjToken MjToken::LAND("&&", MjTokenType::OPERATOR);
const MjToken MjToken::LXOR("^^", MjTokenType::OPERATOR);
const MjToken MjToken::LOR("||", MjTokenType::OPERATOR);
const MjToken MjToken::MUL_SET("*=", MjTokenType::OPERATOR);
const MjToken MjToken::DIV_SET("/=", MjTokenType::OPERATOR);
const MjToken MjToken::REM_SET("%=", MjTokenType::OPERATOR);
const MjToken MjToken::ADD_SET("+=", MjTokenType::OPERATOR);
const MjToken MjToken::SUB_SET("-=", MjTokenType::OPERATOR);
const MjToken MjToken::AND_SET("&=", MjTokenType::OPERATOR);
const MjToken MjToken::XOR_SET("^=", MjTokenType::OPERATOR);
const MjToken MjToken::OR_SET("|=", MjTokenType::OPERATOR);
const MjToken MjToken::LEQ("<=", MjTokenType::OPERATOR);
const MjToken MjToken::GEQ(">=", MjTokenType::OPERATOR);
const MjToken MjToken::EQU("==", MjTokenType::OPERATOR);
const MjToken MjToken::NEQ("!=", MjTokenType::OPERATOR);
const MjToken MjToken::LES("<", MjTokenType::OPERATOR);
const MjToken MjToken::GTR(">", MjTokenType::OPERATOR);
const MjToken MjToken::DOT(".", MjTokenType::OPERATOR);
const MjToken MjToken::NOT("!", MjTokenType::OPERATOR);
const MjToken MjToken::INV("~", MjTokenType::OPERATOR);
const MjToken MjToken::MUL("*", MjTokenType::OPERATOR);
const MjToken MjToken::DIV("/", MjTokenType::OPERATOR);
const MjToken MjToken::REM("%", MjTokenType::OPERATOR);
const MjToken MjToken::ADD("+", MjTokenType::OPERATOR);
const MjToken MjToken::SUB("-", MjTokenType::OPERATOR);
const MjToken MjToken::AND("&", MjTokenType::OPERATOR);
const MjToken MjToken::XOR("^", MjTokenType::OPERATOR);
const MjToken MjToken::OR("|", MjTokenType::OPERATOR);
const MjToken MjToken::SET("=", MjTokenType::OPERATOR);
const MjToken MjToken::QUESTION("?", MjTokenType::OPERATOR);
const MjToken MjToken::COLON(":", MjTokenType::OPERATOR);
const MjToken MjToken::SEMICOLON(";", MjTokenType::OPERATOR);
const MjToken MjToken::COMMA(",", MjTokenType::OPERATOR);
const MjToken MjToken::OP("(", MjTokenType::OPERATOR);
const MjToken MjToken::CP(")", MjTokenType::OPERATOR);
const MjToken MjToken::OS("[", MjTokenType::OPERATOR);
const MjToken MjToken::CS("]", MjTokenType::OPERATOR);
const MjToken MjToken::OB("{", MjTokenType::OPERATOR);
const MjToken MjToken::CB("}", MjTokenType::OPERATOR);
const MjToken MjToken::AT("@", MjTokenType::OPERATOR);
const MjToken MjToken::AS("as", MjTokenType::KEYWORD);
const MjToken MjToken::ASM("asm", MjTokenType::KEYWORD);
const MjToken MjToken::BREAK("break", MjTokenType::KEYWORD);
const MjToken MjToken::CLASS("class", MjTokenType::KEYWORD);
const MjToken MjToken::CONST("const", MjTokenType::KEYWORD);
const MjToken MjToken::CONTINUE("continue", MjTokenType::KEYWORD);
const MjToken MjToken::DO("do", MjTokenType::KEYWORD);
const MjToken MjToken::ELSE("else", MjTokenType::KEYWORD);
const MjToken MjToken::ENUM("enum", MjTokenType::KEYWORD);
const MjToken MjToken::FAIL("fail", MjTokenType::KEYWORD);
const MjToken MjToken::FOR("for", MjTokenType::KEYWORD);
const MjToken MjToken::IF("if", MjTokenType::KEYWORD);
const MjToken MjToken::IMPLEMENTS("implements", MjTokenType::KEYWORD);
const MjToken MjToken::IMPORT("import", MjTokenType::KEYWORD);
const MjToken MjToken::IN("in", MjTokenType::KEYWORD);
const MjToken MjToken::INTERFACE("interface", MjTokenType::KEYWORD);
const MjToken MjToken::IS("is", MjTokenType::KEYWORD);
const MjToken MjToken::LOOP("loop", MjTokenType::KEYWORD);
const MjToken MjToken::MATCH("match", MjTokenType::KEYWORD);
const MjToken MjToken::RETURN("return", MjTokenType::KEYWORD);
const MjToken MjToken::SHARED("shared", MjTokenType::KEYWORD);
const MjToken MjToken::STRUCT("struct", MjTokenType::KEYWORD);
const MjToken MjToken::TYPE("type", MjTokenType::KEYWORD);
const MjToken MjToken::UNION("union", MjTokenType::KEYWORD);
const MjToken MjToken::UNTIL("until", MjTokenType::KEYWORD);
const MjToken MjToken::VOID("void", MjTokenType::KEYWORD);
const MjToken MjToken::VARIANT("variant", MjTokenType::KEYWORD);
const MjToken MjToken::VOLATILE("volatile", MjTokenType::KEYWORD);
const MjToken MjToken::WHEN("when", MjTokenType::KEYWORD);
const MjToken MjToken::WHILE("while", MjTokenType::KEYWORD);
const MjToken MjToken::YIELD("yield", MjTokenType::KEYWORD);
const MjToken MjToken::PLACEHOLDER("_", MjTokenType::IDENTIFIER);
const MjToken MjToken::THIS("this", MjTokenType::IDENTIFIER);
const MjToken MjToken::FALSE("false", MjTokenType::IDENTIFIER);
const MjToken MjToken::TRUE("true", MjTokenType::IDENTIFIER);
const MjToken MjToken::NONE("null", MjTokenType::IDENTIFIER);
const MjToken MjToken::U8("u8", MjTokenType::IDENTIFIER);
const MjToken MjToken::U16("u16", MjTokenType::IDENTIFIER);
const MjToken MjToken::U32("u32", MjTokenType::IDENTIFIER);
const MjToken MjToken::U64("u64", MjTokenType::IDENTIFIER);
const MjToken MjToken::I8("i8", MjTokenType::IDENTIFIER);
const MjToken MjToken::I16("i16", MjTokenType::IDENTIFIER);
const MjToken MjToken::I32("i32", MjTokenType::IDENTIFIER);
const MjToken MjToken::I64("i64", MjTokenType::IDENTIFIER);
const MjToken MjToken::F32("f32", MjTokenType::IDENTIFIER);
const MjToken MjToken::F64("f64", MjTokenType::IDENTIFIER);
const MjToken MjToken::STRING("String", MjTokenType::IDENTIFIER);
const MjToken MjToken::BOOL("bool", MjTokenType::IDENTIFIER);
const MjToken MjToken::OA          = LES;
const MjToken MjToken::CA          = GTR;



const Vector<MjTokenInfo> MjLexer::OPERATORS{
    {">>>=",       MjToken::LSR_SET},
    {">>>",        MjToken::LSR},
    {"<<=",        MjToken::LSL_SET},
    {">>=",        MjToken::ASR_SET},
    {"<<",         MjToken::LSL},
    {">>",         MjToken::ASR},
    {"::",         MjToken::SCOPE},
    {"->",         MjToken::PTR},
    {"++",         MjToken::INC},
    {"--",         MjToken::DEC},
    {"&&",         MjToken::LAND},
    {"^^",         MjToken::LXOR},
    {"||",         MjToken::LOR},
    {"*=",         MjToken::MUL_SET},
    {"/=",         MjToken::DIV_SET},
    {"%=",         MjToken::REM_SET},
    {"+=",         MjToken::ADD_SET},
    {"-=",         MjToken::SUB_SET},
    {"&=",         MjToken::AND_SET},
    {"^=",         MjToken::XOR_SET},
    {"|=",         MjToken::OR_SET},
    {"<=",         MjToken::LEQ},
    {">=",         MjToken::GEQ},
    {"==",         MjToken::EQU},
    {"!=",         MjToken::NEQ},
    {"<",          MjToken::LES},
    {">",          MjToken::GTR},
    {".",          MjToken::DOT},
    {"!",          MjToken::NOT},
    {"~",          MjToken::INV},
    {"*",          MjToken::MUL},
    {"/",          MjToken::DIV},
    {"%",          MjToken::REM},
    {"+",          MjToken::ADD},
    {"-",          MjToken::SUB},
    {"&",          MjToken::AND},
    {"^",          MjToken::XOR},
    {"|",          MjToken::OR},
    {"=",          MjToken::SET},
    {"?",          MjToken::QUESTION},
    {":",          MjToken::COLON},
    {";",          MjToken::SEMICOLON},
    {",",          MjToken::COMMA},
    {"(",          MjToken::OP},
    {")",          MjToken::CP},
    {"[",          MjToken::OS},
    {"]",          MjToken::CS},
    {"{",          MjToken::OB},
    {"}",          MjToken::CB},
    {"@",          MjToken::AT},
};


const Vector<MjTokenInfo> MjLexer::KEYWORDS[10] = {
    {
        {"_", MjToken::PLACEHOLDER},
    },
    {
        {"as", MjToken::AS},
        {"do", MjToken::DO},
        {"i8", MjToken::I8},
        {"if", MjToken::IF},
        {"in", MjToken::IN},
        {"is", MjToken::IS},
        {"u8", MjToken::U8},
    },
    {
        {"asm", MjToken::ASM},
        {"f16", MjToken::F16},
        {"f32", MjToken::F32},
        {"f64", MjToken::F64},
        {"f80", MjToken::F80},
        {"for", MjToken::FOR},
        {"i16", MjToken::I16},
        {"i32", MjToken::I32},
        {"i64", MjToken::I64},
        {"u16", MjToken::U16},
        {"u32", MjToken::U32},
        {"u64", MjToken::U64},
    },
    {
        {"bool", MjToken::BOOL},
        {"else", MjToken::ELSE},
        {"enum", MjToken::ENUM},
        {"f128", MjToken::F128},
        {"fail", MjToken::FAIL},
        {"i128", MjToken::I128},
        {"impl", MjToken::IMPL},
        {"null", MjToken::NONE},
        {"safe", MjToken::SAFE},
        {"true", MjToken::TRUE},
        {"type", MjToken::TYPE},
        {"u128", MjToken::U128},
        {"unit", MjToken::UNIT},
        {"void", MjToken::VOID},
    },
    {
        {"break", MjToken::BREAK},
        {"class", MjToken::CLASS},
        {"const", MjToken::CONST},
        {"false", MjToken::FALSE},
        {"match", MjToken::MATCH},
        {"union", MjToken::UNION},
        {"until", MjToken::UNTIL},
        {"while", MjToken::WHERE},
        {"while", MjToken::WHILE},
        {"yield", MjToken::YIELD},
    },
    {
        {"import", MjToken::IMPORT},
        {"return", MjToken::RETURN},
        {"struct", MjToken::STRUCT},
    },
    {
        {"mutable", MjToken::MUTABLE},
        {"variant", MjToken::VARIANT},
    },
    {
        {"continue", MjToken::CONTINUE},
        {"volatile", MjToken::VOLATILE},
    },
    {
        {"interface", MjToken::INTERFACE},
    },
    {
        {"implements", MjToken::IMPLEMENTS},
    }
};






// patterns = {
//     (Tokens.NONE,   re.compile("null")),
//     (Tokens.FALSE,  re.compile("false")),
//     (Tokens.TRUE,   re.compile("true")),
//     (Tokens.I32,    re.compile("([1-9][0-9]*|0[0-7]*|0x[0-9A-Fa-f]+)([IiUu](?:8|16|32|64)?)?")),
//     (Tokens.F64,    re.compile("([1-9][0-9]*(?:.[0-9]+(?:[Ee][+-]?[0-9]+)?)?|0[0-7]*(?:.[0-7]+(?:[Ee][+-]?[0-7]+)?)?|0x[0-9A-Fa-f]+(?:.[0-9A-Fa-f]+(?:[Ee][+-]?[0-9]+)?)?)([Ff](?:32|64)?)?")),
//     (Tokens.STRING, re.compile("\"((?:\\[\"tnreb]|[^\"\n])*)\"|'([^'\\n]*)'")),
//     (Tokens.THIS,   re.compile("([A-Za-z_]\\w*)")),
// };


const MjToken &MjLexer::scan() {
    while (true) {
        ch += whitespace.match(line[ch:]).end();

        if (ch == line.size()) {
            line = file->read_line();
            ln += 1;
            ch = 0;
        } else {
            break;
        }
    }

    line = this->line[ch:];
    // print(line)

    if (line.begins_with("//")) {
        String text = nullptr;

        while (line.begins_with("//")) {
            text.append(line.slice(1));
        }

        return make_token(text, MjTokenType::COMMENT);
    }

    for (const MjTokenInfo &op : OPERATORS) {
        if (line.is_equal(op.string, op.string.size())) {
            ch += op.string.size();
            return op.token;
        }
    }

    for (pattern : patterns) {
        match = pattern[1].match(line);

        if (match) {
            //print(match)
            ch += match.end();
            StringView text = match[1];
            StringView last = match[match.lastindex];

            if (pattern[0] == MjToken::I32) {
                if (last == "u8") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                if (last == "u16") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                if (last == "u32" or last == "u") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                if (last == "u64") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                if (last == "i8") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                if (last == "i16") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                if (last == "i32" or last == "i") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                if (last == "i64") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                return make_token(text, MjTokenType::NUMBER);
            } else if (pattern[0] == MjToken::F64) {
                if (last == "f32" or last == "f") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                if (last == "f64") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                return make_token(text, MjTokenType::NUMBER);
            } else if (pattern[0] == MjToken::STRING) {
                return make_token(text, MjTokenType::STRING);
            } else if (pattern[0] == MjToken::THIS) {
                return make_token(text, MjTokenType::IDENTIFIER);
            }

            return make_token(pattern[0], MjTokenType::IDENTIFIER);
        }
    }

    return MjToken::EOT;
}






const MjToken &MjLexer::consume_unit_expression() {
    consume_whitespace();

    // handle indentation and empty lines

    // handle line and block comments (preceding or trailing)


    // we have a semantic state machine
    // parse according to precedence rules

    while (true) {
        ch += whitespace.match(line[ch:]).end();

        if (ch == line.size()) {
            line = file->read_line();
            ln += 1;
            ch = 0;
        } else {
            break;
        }
    }

    line = this->line[ch:];
    // print(line)

    if (line.begins_with("//")) {
        String text = nullptr;

        while (line.begins_with("//")) {
            text.append(line.slice(1));
        }

        return make_token(text, MjTokenType::COMMENT);
    }

    for (const MjTokenInfo &op : OPERATORS) {
        if (line.is_equal(op.string, op.string.size())) {
            ch += op.string.size();
            return op.token;
        }
    }

    for (pattern : patterns) {
        match = pattern[1].match(line);

        if (match) {
            //print(match)
            ch += match.end();
            StringView text = match[1];
            StringView last = match[match.lastindex];

            if (pattern[0] == MjToken::I32) {
                if (last == "u8") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                if (last == "u16") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                if (last == "u32" or last == "u") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                if (last == "u64") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                if (last == "i8") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                if (last == "i16") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                if (last == "i32" or last == "i") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                if (last == "i64") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                return make_token(text, MjTokenType::NUMBER);
            } else if (pattern[0] == MjToken::F64) {
                if (last == "f32" or last == "f") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                if (last == "f64") {
                    return make_token(text, MjTokenType::NUMBER);
                }

                return make_token(text, MjTokenType::NUMBER);
            } else if (pattern[0] == MjToken::STRING) {
                return make_token(text, MjTokenType::STRING);
            } else if (pattern[0] == MjToken::THIS) {
                return make_token(text, MjTokenType::IDENTIFIER);
            }

            return make_token(pattern[0], MjTokenType::IDENTIFIER);
        }
    }

    return MjToken::EOT;
}






void MjLexer::scan_span(const MjToken &inc, const MjToken &dec) {
    Vector<const MjToken *> tokens;
    size_t i = 1;

    while (token && i) {
        tokens.append(token);

        if (token == inc) {
            i += 1;
        } else if (token == dec) {
            i -= 1;
        }
    }

    if (i) {
        raise SyntaxError("End of file reached while scanning span!");
    }

    return tokens;
}
