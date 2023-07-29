#pragma once

#include "mj/ast/MjToken.hpp"

#include "std/Vector.hpp"
#include "std/Queue.hpp"
#include "std/List.hpp"
#include "std/String.hpp"
#include "std/File.hpp"


enum class State : u32 {
    DECLARATION = 1 << 0,
    COMMENT     = 1 << 1,
    ANNOTATION  = 1 << 2,
    TEMPLATE    = 1 << 3,
    STRING      = 1 << 4,
    RAW_STRING  = 1 << 5,
    LAST_CAN_BE_TEMPLATE = 1 << 3,
    LAST_CAN_BE_MODULE = 1 << 3,
};


class MjLexer {
private:
    static const Vector<MjTokenInfo> OPERATORS; // The operator token parse info
    static const Vector<MjTokenInfo> KEYWORDS[10];  // The keyword token parse info
private:
    File &file_;
    Queue<MjToken> tokens_;
    Queue<State> states_;
    String line_;
    const MjToken *token_ = nullptr;
    State state_ = State::DECLARATION;
    u32 ln = 1;
    u32 ch = 0;
public:


    MjLexer(
        const Path &path
    ) :
        file_(System::open(path, "r"))
    {
        if (!file_.is_open()) {
            System::out.print("Invalid source file path! '{:s}'", path);
        }

        tokens_.append(OPERATORS);
        tokens_.append(KEYWORDS);
        line_ = file_.read_line();
        token_ = scan();
    }


    const Path &file_path() const {
        return file_.path();
    }


    u32 line_number() const {
        return ln;
    }


    u32 column_number() const {
        return ch;
    }


    const MjToken make_token(StringView text, MjTokenType type) {
        return tokens_.get(text, MjToken(text, type));
    }


    const MjToken &scan();


    const MjToken *peek() const {
        return token_;
    }


    const MjToken *next() {
        const MjToken *token = this->token_;
        this->token_ = scan();
        return token;
    }


    const MjToken *next_if_any(MjTokenType type) {
        return token_->type == type ? next() : nullptr;
    }


    bool next_if(const MjToken &token) {
        return *this->token_ == token ? next() : nullptr;
    }


    void expect(const MjToken &token) {
        if (next() != token) {
            //raise SyntaxError(f"{this.path}:{this.ln}:{this.ch}: Expected: '{token.text}'");
        }
    }


    const MjToken *expect_any(MjTokenType type) {
        if (next().type != type) {
            //raise SyntaxError(f"{this.path}:{this.ln}:{this.ch}: Expected: '{type}'")
        }

        return token;
    }


    /// @brief Return true if the token is the first in the line.
    /// This is used for tracking indentation as a parsing hint for handling errors.
    bool next_is_first() {
        return false;
    }


private:


    void push_state(State state) {
        states_.push(state_);
        state_ = state;
    }


    void pop_state() {
        state_ = states_.front();
        states_.pop();
    }


    const MjToken parse() {
        u32 codepoint;

        // Handle whitespace, newline, and indentation.
        if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') {
            consume_whitespace();
            u32 line = 0; // The line number (1 indexed)
            u32 indent = 0; // True if this is the first token in the line
            u32 column = 0; // The column number in characters
            u32 byte_offset = 0; // The line size in bytes.
            bool is_newline = 0; // True if this is the first token in the line
        }

        switch (ch) {
        case '>':
            if (state_ == State::TEMPLATE) {
                return MjToken::CA;
            }

            if (ch == '>') {
                return MjToken::ASR;
            }

            if (ch != '>') {
                return MjToken::LES;
            }

            if (ch == '>') {
                return MjToken::LSR_SET;
            }

            return MjToken::GTR;
        case '>>>':
            return MjToken::LSR;
        case '>>=':
            return MjToken::ASR_SET;
        case '<':
            if (state_ == State::LAST_CAN_BE_TEMPLATE) {
                return MjToken::OA;
            }

            return MjToken::LES;
        case '<<':
            return MjToken::LSL;
        case '<<=':
            return MjToken::LSL_SET;
        case '::':
            return MjToken::SCOPE;
        case '->':
            return MjToken::PTR;
        case '++':
            return MjToken::INC;
        case '--':
            return MjToken::DEC;
        case '&&':
            return MjToken::LAND;
        case '^^':
            return MjToken::LXOR;
        case '||':
            return MjToken::LOR;
        case '*=':
            return MjToken::MUL_SET;
        case '/=':
            return MjToken::DIV_SET;
        case '%=':
            return MjToken::REM_SET;
        case '+=':
            return MjToken::ADD_SET;
        case '-=':
            return MjToken::SUB_SET;
        case '&=':
            return MjToken::AND_SET;
        case '^=':
            return MjToken::XOR_SET;
        case '|=':
            return MjToken::OR_SET;
        case '<=':
            return MjToken::LEQ;
        case '>=':
            return MjToken::GEQ;
        case '==':
            return MjToken::EQU;
        case '!=':
            return MjToken::NEQ;
        case '.':
            return MjToken::DOT;
        case '!':
            return MjToken::NOT;
        case '~':
            return MjToken::INV;
        case '*':
            return MjToken::MUL;
        case '/':
            return MjToken::DIV;
        case '%':
            return MjToken::REM;
        case '+':
            return MjToken::ADD;
        case '-':
            return MjToken::SUB;
        case '&':
            return MjToken::AND;
        case '^':
            return MjToken::XOR;
        case '|':
            return MjToken::OR;
        case '=':
            return MjToken::SET;
        case '?':
            return MjToken::QUESTION;
        case ':':
            return MjToken::COLON;
        case ';':
            return MjToken::SEMICOLON;
        case ',':
            return MjToken::COMMA;
        case '(':
            return MjToken::OP;
        case ')':
            return MjToken::CP;
        case '[':
            // push scope '['
            return MjToken::OS;
        case ']':
            // This is the end of a subscript operator, slice operator, bitfield operator, or array type specifier.
            // pop scope if within an '['
            return MjToken::CS;
        case '{':
            return MjToken::OB;
        case '}':
            return MjToken::CB;
        case '@':
            // push scope '@' pop scope at newline.
            push_state(State::ANNOTATION);
            return MjToken::AT;
        default:
            StringView text;

            if (text.size() > 10) {
                return MjToken::IDENT;
            }

            for (MjTokenInfo keyword : KEYWORDS[text.size()]) {
                if (text == keyword.token.text) {
                    return keyword.token;
                }
            }

            return MjToken::IDENT;
        }
    }

    /// @annotation(...)
    void consume_annotation() {
        if (state_ != State::DECLARATION || ch != '@') {
            return;
        }

        consume_variable_name();
        consume_parameter_list();
    }


    /// [A-Za-z0-9_][A-Za-z0-9_.+-]+(?=::)
    void consume_module_name() {
        u32 ch = file_.peek();

        if (!(
            (ch >= '0' && ch <= '9') ||
            (ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z') ||
            ch == '_'
        )) {
            return;
        }

        do {
            ch = file_.peek();
        } while (
            (ch >= '0' && ch <= '9') ||
            (ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z') ||
            ch == '_' || 
            ch == '.' || 
            ch == '+' || 
            ch == '-'
        );

        consume_whitespace();
        consume_comment();

        if (ch == ':' && ch == ':') {
            file_.peek();
        }
    }


    /// (false|null|true)
    void consume_constant_literal() {

    }


    /// [0-9_]*[A-Z][A-Z0-9_]+
    void consume_constant_variable_name() {
        u32 ch = file_.peek();

        if (!(
            (ch >= '0' && ch <= '9') ||
            (ch >= 'A' && ch <= 'Z') ||
            ch == '_'
        )) {
            return;
        }

        do {
            ch = file_.peek();
        } while (
            (ch >= '0' && ch <= '9') ||
            (ch >= 'A' && ch <= 'Z') ||
            ch == '_'
        );
    }


    /// [0-9]*[a-z_][a-z0-9_]*
    void consume_variable_name() {
        do {
            ch = file_.peek();
        } while ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || ch == '_');
    }


    /// [A-Za-z0-9_][A-Za-z0-9_.+-]+(?=::)
    void consume_function_name() {
        consume_variable_name();

        if (ch == '<') {
            // template
        }

        if (ch == '(') {
            // function
        } else {
            // variable
        }
    }


    /// ([iu](?:8|16|32|64|128)|f(?:16|32|64|80|128)|bool|void|[A-Z](?:[A-Z0-9]*[a-z][A-Za-z0-9-]*)?)
    void consume_type_name() {
        if (ch == "bool") {
            // fundamental type
        } else if (ch == "void") {
            // fundamental type
        } else if (ch == 'i' || ch == 'u' || ch == 'f') {
            // fundamental type
        } else if (
            (ch >= 'A' && ch <= 'Z')
        ) {
            // user defined type
        }

        if (ch == '\'') {
            consume_unit_expression();
        }
    }


    /// [A-Za-z0-9_][A-Za-z0-9_.+-]+(?=::)
    void consume_type_expression() {
    }


    /// [A-Za-zµΩÅ°'"]|\^g|1/)[A-Za-zµΩÅ°'"^]*
    void consume_unit_name() {
        u32 ch = file_.peek();

        while (ch != EOF) {
            if (
                (ch >= 'A' && ch <= 'Z') ||
                (ch >= 'a' && ch <= 'z') ||
                ch == 'µ' ||
                ch == 'Ω' ||
                ch == '°' || ch == '\'' || ch == '"'
            ) {
                ;
            }
        }
    }


    /// [A-Za-zµΩÅ°'"]|\^g|1/)[A-Za-z0-9⁰¹²³⁴⁵⁶⁷⁸⁹⁻⸍µΩÅ°'"·^*/-]*
    void consume_unit_expression() {
        u32 ch = file_.peek();

        while (ch != EOF) {
            consume_unit_name();
            if (
                (ch >= '0' && ch <= '9') ||
                ch == '*' || ch == '/' || ch == '^' || ch == '-' || ch == '·' ||
                ch == '⁰' ||
                ch == '¹' ||
                ch == '²' ||
                ch == '³' ||
                ch == '⁴' ||
                ch == '⁵' ||
                ch == '⁶' ||
                ch == '⁷' ||
                ch == '⁸' ||
                ch == '⁹' ||
                ch == '⁻' ||
                ch == '⸍'
            ) {
                ;
            }
        }
    }


    /// 
    /// (
    ///     \d+(?:\.\d+)?(?:([Ee])[+-]?\d+)?(f(?:16|32|64|80|128)?|[iu](?:8|16|32|64|128)?|x)?
    ///     (0x)[0-9A-Fa-f']+(?:\\.\\h+)?(?:([Pp])[+-]\\d+)?(f(?:16|32|64|80|128)?|[iu](?:8|16|32|64|128)?)?
    ///     (0o)[0-7']+([iu](?:8|16|32|64|128)?)?
    ///     (0b)[01']+([iu](?:8|16|32|64|128)?)?
    /// ) \b(\s+(?:[A-Za-zµΩ°'"]|\^g|1/)[A-Za-z0-9⁰¹²³⁴⁵⁶⁷⁸⁹⁻⸍µΩ°'\"·^*/-]*)?
    ///
    void consume_numeric_literal() {
        
        // Unit expression has priority after a numeric literal.
        consume_unit_expression();
    }


    /// "(\\"|[^"])*"
    void consume_string_literal() {
        if (file_.peek() != '"') {
            return;
        }

        do {
            ;
            // \\(["0nrt\\]|x\h\h|u\h\h\h\h) "constant.character.escape.mj"
            // \\(x\h*|u\h*|.) "invalid.illegal.mj"
        } while (file_.peek() != '"');
    }


    /// '[^']*'
    void consume_raw_string_literal() {
        if (file_.peek() != '\'') {
            return;
        }

        do {
            ;
        } while (file_.peek() != '\'');
    }


    /// [A-Za-z0-9_][A-Za-z0-9_.+-]+(?=::)
    void consume_function_declaration() {
        // type variable <params, args> (params, args)
    }


    /// [A-Za-z0-9_][A-Za-z0-9_.+-]+(?=::)
    void consume_keyword() {

        /// Semantic Keywords (followed by template parameter list)
        if (
            token->text == "bitfield" ||
            token->text == "enum" ||
            token->text == "impl" ||
            token->text == "type" ||
            token->text == "variant" ||
            token->text == "where"
        ) {
            return;
        }

        /// Semantic Keywords (followed by scope)
        if (
            token->text == "asm" ||
            token->text == "catch" ||
            token->text == "do" ||
            token->text == "else" ||
            token->text == "try"
        ) {
            return;
        }

        /// Semantic Keywords (\w+<...>)
        if (
            token->text == "bitfield"
        ) {
            return;
        }

        /// Semantic Keywords (\w+<...>)
        if (
            token->text == "bitfield"
        ) {
            return;
        }

        // Pure keywords.
        if (
            token->text == "as" ||
            token->text == "break" ||
            token->text == "continue" ||
            token->text == "fail" ||
            token->text == "in" ||
            token->text == "is" ||
            token->text == "return" ||
            token->text == "yield"
        ) {
            return;
        }

        if (consume_identifier()) {
            return;
        }
    }
};
