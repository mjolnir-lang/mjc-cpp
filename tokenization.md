# Tokenization

## Tokens

- keywords
  - control - fun
    - `break`
    - `continue`
    - `fail`
    - `return`
    - `yield`
  - parameterized - var, fun (non-template)
    - `bitfield`
    - `enum`
    - `impl`
    - `type`
    - `union`
    - `unit`
    - `where`
  - control - var, fun
    - `for`
    - `if`
    - `match`
    - `until`
    - `while`
  - type qualifiers - var, fun
    - `const`
    - `mutable`
    - `safe`
    - `volatile`
  - type names - never
    - `bool`
    - `f16`
    - `f32`
    - `f64`
    - `f128`
    - `i8`
    - `i16`
    - `i32`
    - `i64`
    - `i128`
    - `u8`
    - `u16`
    - `u32`
    - `u64`
    - `u128`
    - `void`
  - declarations - var, fun
    - `asm`
    - `class`
    - `do`
    - `else`
    - `import`
    - `interface`
    - `struct`
    - `union`
  - operators - var, fun
    - `as`
    - `is`
- literals
  - numbers
    - base prefixes
      - NONE decimal
      - `0x` hexadecimal
      - `0o` octal
      - `0b` binary
    - type suffixes
    - exponents
      - `e[+-]\d+` decimal
      - `p[+-]\d+` hexadecimal
    - fractions
      - `.\d+` decimal
      - `.\h+` hexadecimal
  - strings
    - raw
    - interpolated
  - booleans
    - `true`
    - `false`
  - deferred initialization
    - `uninitialized`
  - null pointer
    - `null`
- operators
  - prefix
  - suffix
  - infix

## Keywords

| Token       | Keyword     | Variable | Function | Template |
| ----------- | ----------- | -------- | -------- | -------- |
| `bool`      |             | -        | -        | -        |
| `f16`       |             | -        | -        | -        |
| `f32`       |             | -        | -        | -        |
| `f64`       |             | -        | -        | -        |
| `f128`      |             | -        | -        | -        |
| `i8`        |             | -        | -        | -        |
| `i16`       |             | -        | -        | -        |
| `i32`       |             | -        | -        | -        |
| `i64`       |             | -        | -        | -        |
| `i128`      |             | -        | -        | -        |
| `u8`        |             | -        | -        | -        |
| `u16`       |             | -        | -        | -        |
| `u32`       |             | -        | -        | -        |
| `u64`       |             | -        | -        | -        |
| `u128`      |             | -        | -        | -        |
| `void`      |             | -        | -        | -        |
| `break`     |             | -        | yes      | yes      |
| `continue`  |             | -        | yes      | yes      |
| `fail`      |             | -        | yes      | yes      |
| `return`    |             | -        | yes      | yes      |
| `yield`     |             | -        | yes      | yes      |
| `bitfield`  | `<`         | yes      | yes      | -        |
| `impl`      | `<`         | yes      | yes      | -        |
| `where`     | `<`         | yes      | yes      | -        |
| `enum`      | `<`,T       | yes      | yes      | -        |
| `type`      | `<`,T       | yes      | yes      | -        |
| `unit`      | `<`,U       | yes      | yes      | -        |
| `union`     | `<`,`{`,T,V | yes      | yes      | -        |
| `for`       | `\s(`       | yes      | yes      | yes      |
| `if`        | `\s(`       | yes      | yes      | yes      |
| `match`     | `\s(`       | yes      | yes      | yes      |
| `until`     | `\s(`       | yes      | yes      | yes      |
| `while`     | `\s(`       | yes      | yes      | yes      |
| `asm`       | `{`         | yes      | yes      | yes      |
| `do`        | `{`         | yes      | yes      | yes      |
| `else`      | `{`         | yes      | yes      | yes      |
| `class`     | `{`,T,V     | yes      | yes      | yes      |
| `import`    | `{`,T,V     | yes      | yes      | yes      |
| `interface` | `{`,T,V     | yes      | yes      | yes      |
| `struct`    | `{`,T,V     | yes      | yes      | yes      |
| `as`        | T           | yes      | yes      | yes      |
| `const`     | T           | yes      | yes      | yes      |
| `is`        | T           | yes      | yes      | yes      |
| `mutable`   | T           | yes      | yes      | yes      |
| `safe`      | T           | yes      | yes      | yes      |
| `volatile`  | T           | yes      | yes      | yes      |

## Operators

Operator Kind

- Terminal
  - Before - Any
  - After - Any
- Infix
  - Before - Whitespace/Newline
  - After - Whitespace/Newline
- Prefix
  - Before - Whitespace/Newline/Prefix/Separator
  - After - Prefix
- Postfix
  - Before - Postfix
  - After - Whitespace/Newline/Postfix/Separator

| Before   | Token  | After    | Name |
| -------- | ------ | -------- | -------- |
| `\s`,`(` | `!`    | `a`      | Not                |
| `\s`,`(` | `~`    | `a`      | Invert             |
| `\s`,`(` | `-`    | `a`      | Negate             |
| `\s`,`(` | `*`    | `a`      | Deref              |
| `\s`,`(` | `&`    | `a`      | Ref                |
| `a`      | `++`   | `\s`,`)` |          |
| `a`      | `--`   | `\s`,`)` |          |
| `f`      | `&`    | `\s`,`)` |          |
| `T`      | `*`    | `\s`,`)` |          |
| `T`      | `&`    | `\s`,`)` |          |
| `T`      | `?`    | `\s`,`)` |          |
| `T`      | `!`    | `\s`,`)` |          |
| `\s`,`(` | `=`    | `\s`,`)` |          |
| `\s`,`(` | `==`   | `\s`,`)` |          |
| `\s`,`(` | `=>`   | `\s`,`)` |          |
| `\s`,`(` | `<`    | `\s`,`)` |          |
| `\s`,`(` | `<<`   | `\s`,`)` |          |
| `\s`,`(` | `<<=`  | `\s`,`)` |          |
| `\s`,`(` | `<=`   | `\s`,`)` |          |
| `\s`,`(` | `<=>`  | `\s`,`)` |          |
| `\s`,`(` | `>`    | `\s`,`)` |          |
| `\s`,`(` | `>>`   | `\s`,`)` |          |
| `\s`,`(` | `>>=`  | `\s`,`)` |          |
| `\s`,`(` | `>=`   | `\s`,`)` |          |
| `\s`,`(` | `*`    | `\s`,`)` |          |
| `\s`,`(` | `*=`   | `\s`,`)` |          |
| `\s`,`(` | `/`    | `\s`,`)` |          |
| `\s`,`(` | `/=`   | `\s`,`)` |          |
| `\s`,`(` | `%`    | `\s`,`)` |          |
| `\s`,`(` | `%=`   | `\s`,`)` |          |
| `\s`,`(` | `+`    | `\s`,`)` |          |
| `\s`,`(` | `+=`   | `\s`,`)` |          |
| `\s`,`(` | `-`    | `\s`,`)` |          |
| `\s`,`(` | `-=`   | `\s`,`)` |          |
| `\s`,`(` | `&`    | `\s`,`)` |          |
| `\s`,`(` | `&=`   | `\s`,`)` |          |
| `\s`,`(` | `\|`   | `\s`,`)` |          |
| `\s`,`(` | `\|=`  | `\s`,`)` |          |
| `\s`,`(` | `^`    | `\s`,`)` |          |
| `\s`,`(` | `^=`   | `\s`,`)` |          |
| `\s`,`(` | `&&`   | `\s`,`)` |          |
| `\s`,`(` | `\|\|` | `\s`,`)` |          |
| `\s`,`(` | `!=`   | `\s`,`)` |          |
| `\s`,`(` | `?`    | `\s`,`)` |          |
| `\s`,`(` | `:`    | `\s`,`)` |          |

## Separators

| Before   | Token  | After    | Name |
| -------- | ------ | -------- | --------- |
| `T`      | `::`   | `m`,`T`  | Shared Member Accessor  |
| `a`      | `.`    | `m`      | Member Accessor         |
|          | `,`    |          | Comma                   |
|          | `;`    |          | Semicolon               |
|          | `:`    |          | Colon                   |
|          | `#!`   |          | Shebang                 |
|          | `$`    | `\s`     | Shell Statement         |
|          | `$`    | `a`,`{`  | Shell Variable          |
|          | `$`    | `(`      | Sub-shell Expression    |
| `\s`,`(` | `-`    | `a`      | Shell Short Option      |
| `\s`,`(` | `--`   | `a`      | Shell Long Option       |
|          | `@`    |          | Decorator               |
|          | `(`    |          | Open Parenthesis        |
|          | `)`    |          | Close Parenthesis       |
|          | `[`    |          | Open Square Bracket     |
|          | `]`    |          | Close Square Bracket    |
|          | `{`    |          | Open Curly Brace        |
|          | `}`    |          | Close Curly Brace       |
|          | `<`    |          | Open Angle Bracket      |
|          | `>`    |          | Close Angle Bracket     |

## Names

- Any Case
  - Module Name
- Pascal Case
  - Type Name
- Upper Snake Case
  - Constant Name
- Lower Snake Case
  - Variable Name
  - Function Name
  - Annotation Name
  - Shell Option Name
