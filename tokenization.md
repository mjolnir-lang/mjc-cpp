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

### Builtin Type Names

| Token       | After       | Variable | Function | Template |
| ----------- | ----------- | -------- | -------- | -------- |
| `bool`      |             | -        | -        | -        |
| `f16`       | `x1`,`x2`,`x4`,`x8`,`x16`    | -        | -        | -        |
| `f32`       | `x1`,`x2`,`x4`,`x8`            | -        | -        | -        |
| `f64`       | `x1`,`x2`,`x4`,`x8`            | -        | -        | -        |
| `f128`      | `x1`,`x2`,`x4`            | -        | -        | -        |
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

### Control Flow Keywords (Non-variable)

| Token       | Keyword | Variable | Function | Template |
| ----------- | ------- | -------- | -------- | -------- |
| `and`       | yes     | -        | yes      | yes      |
| `break`     | yes     | -        | yes      | yes      |
| `case`      | yes     | -        | yes      | yes      |
| `continue`  | yes     | -        | yes      | yes      |
| `else`      | yes     | -        | yes      | yes      |
| `fail`      | yes     | -        | yes      | yes      |
| `not`       | yes     | -        | yes      | yes      |
| `or`        | yes     | -        | yes      | yes      |
| `return`    | yes     | -        | yes      | yes      |
| `then`      | yes     | -        | yes      | yes      |
| `yield`     | yes     | -        | yes      | yes      |

### Control Flow Keywords (after expression)

Expressions cannot be else, and, or, then, case

| Token       | Keyword     | Variable | Function | Template |
| ----------- | ----------- | -------- | -------- | -------- |
| `for`       | # E         | yes      | yes      | yes      |
| `if`        | # E         | yes      | yes      | yes      |
| `in`        | `for` T V # | yes      | yes      | yes      |
| `match`     | # E         | yes      | yes      | yes      |
| `until`     | # E         | yes      | yes      | yes      |
| `while`     | # E         | yes      | yes      | yes      |

### Type Definition Keywords (Non-template)

| Token       | Keyword       | Variable | Function | Template |
| ----------- | ------------- | -------- | -------- | -------- |
| `bitfield`  | # `<`         | yes      | yes      | -        |
| `impl`      | # `<`         | yes      | yes      | -        |
| `where`     | # `<`         | yes      | yes      | -        |
| `enum`      | # `<`,T       | yes      | yes      | -        |
| `type`      | # `<`,T       | yes      | yes      | -        |
| `unit`      | # `<`,U       | yes      | yes      | -        |
| `union`     | # `<`,`{`,T,V | yes      | yes      | -        |

### Control Flow Keywords

| Token       | Keyword     | Variable | Function | Template |
| ----------- | ----------- | -------- | -------- | -------- |
| `asm`       | # `{`       | yes      | yes      | yes      |
| `do`        | # `{`       | yes      | yes      | yes      |
| `class`     | # `{`,T,V   | yes      | yes      | yes      |
| `import`    | # `{`,T,V   | yes      | yes      | yes      |
| `interface` | # `{`,T,V   | yes      | yes      | yes      |
| `struct`    | # `{`,T,V   | yes      | yes      | yes      |

### Operator Keywords

| Token       | Keyword     | Variable | Function | Template |
| ----------- | ----------- | -------- | -------- | -------- |
| `as`        | # T         | yes      | yes      | yes      |
| `const`     | # T         | yes      | yes      | yes      |
| `is`        | # T         | yes      | yes      | yes      |
| `mutable`   | # T         | yes      | yes      | yes      |
| `safe`      | # T         | yes      | yes      | yes      |

## Separators

| Token  | Name |
| ------ | --------- |
| `::`   | Shared Member Accessor  |
| `.`    | Member Accessor         |
| `,`    | Comma                   |
| `;`    | Semicolon               |
| `:`    | Colon                   |
| `(`    | Open Parenthesis        |
| `)`    | Close Parenthesis       |
| `[`    | Open Square Bracket     |
| `]`    | Close Square Bracket    |
| `{`    | Open Curly Brace        |
| `}`    | Close Curly Brace       |
| `<`    | Open Angle Bracket      |
| `>`    | Close Angle Bracket     |

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

| Before   | Token  | After    | Name     |
| -------- | ------ | -------- | -------- |
| `_`,`(`  | `~`    | `a`      | Invert   |
| `_`,`(`  | `-`    | `a`      | Negate   |
| `_`,`(`  | `*`    | `a`      | Deref    |
| `_`,`(`  | `&`    | `a`      | Ref      |
| `a`      | `++`   | `_`,`)`  | Inc         |
| `a`      | `--`   | `_`,`)`  | Dec         |
| `f`      | `&`    | `_`,`)`  | Function Ref         |
| `T`      | `*`    | `_`,`)`  | Pointer         |
| `T`      | `&`    | `_`,`)`  | Reference         |
| `T`      | `?`    | `_`,`)`  | Fallible         |
| `T`      | `!`    | `_`,`)`  | No Return |
| `_`,`(`  | `=`    | `_`,`)`  | Assign         |
| `_`,`(`  | `==`   | `_`,`)`  | Equal         |
| `_`,`(`  | `=>`   | `_`,`)`  | Lambda         |
| `_`,`(`  | `<`    | `_`,`)`  | Less Than         |
| `_`,`(`  | `<<`   | `_`,`)`  | Left Shift         |
| `_`,`(`  | `<<=`  | `_`,`)`  | Left Shift Assignment         |
| `_`,`(`  | `<=`   | `_`,`)`  |          |
| `_`,`(`  | `<=>`  | `_`,`)`  |          |
| `_`,`(`  | `>`    | `_`,`)`  |          |
| `_`,`(`  | `>>`   | `_`,`)`  |          |
| `_`,`(`  | `>>=`  | `_`,`)`  |          |
| `_`,`(`  | `>=`   | `_`,`)`  |          |
| `_`,`(`  | `*`    | `_`,`)`  |          |
| `_`,`(`  | `*=`   | `_`,`)`  |          |
| `_`,`(`  | `/`    | `_`,`)`  |          |
| `_`,`(`  | `/=`   | `_`,`)`  |          |
| `_`,`(`  | `%`    | `_`,`)`  |          |
| `_`,`(`  | `%=`   | `_`,`)`  |          |
| `_`,`(`  | `+`    | `_`,`)`  |          |
| `_`,`(`  | `+=`   | `_`,`)`  |          |
| `_`,`(`  | `-`    | `_`,`)`  |          |
| `_`,`(`  | `-=`   | `_`,`)`  |          |
| `_`,`(`  | `&`    | `_`,`)`  |          |
| `_`,`(`  | `&=`   | `_`,`)`  |          |
| `_`,`(`  | `\|`   | `_`,`)`  |          |
| `_`,`(`  | `\|=`  | `_`,`)`  |          |
| `_`,`(`  | `^`    | `_`,`)`  |          |
| `_`,`(`  | `^=`   | `_`,`)`  |          |
| `_`,`(`  | `!=`   | `_`,`)`  | Not Equal |

## Misc

| Before   | Token  | After    | Name |
| -------- | ------ | -------- | --------- |
|          | `#!`   |          | Shebang                 |
|          | `$`    | `_`      | Shell Statement         |
|          | `$`    | `a`,`{`  | Shell Variable          |
|          | `$`    | `(`      | Sub-shell Expression    |
| `_`,`(`  | `-`    | `a`      | Shell Short Option      |
| `_`,`(`  | `--`   | `a`      | Shell Long Option       |
|          | `@`    |          | Decorator               |

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
