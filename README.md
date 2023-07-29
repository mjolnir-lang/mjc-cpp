# Mjolnir C++ Libraries

## Data Formats and Interfaces (API)

- `token` - Token
- `ast` - Abstract Syntax Tree (parser -> compiler/transpiler/jit/vm)
- `asm` - Assmebly
- `bc` - Byte Code
- `ir` - Intermediate Representation (Platform Agnostic ASM)
- `ir-asm` - IR Human Readable ASM
- `ir-o` - IR Memory Object Layout
- `ir-bc` - IR Byte Code

## Libraries

The Mjolnir libraries are module aby design for independent use in multiple tools.

- `MjScanner` - Scanner
- `MjParser` - Parser
- `MjAnnotator` - Annotator
- `MjLinter` - Linter (same as annotator?)
- `MjCompiler` - Compiler
  - `x86`
  - `x86_64`
  - `arm`
  - `aarch64`
- `MjTranspiler` - Compiler
  - `MjCTranspiler` - Mjolnir to C transpiler
  - `MjCppTranspiler` - Mjolnir to C++ transpiler
  - `MjRustTranspiler` - Mjolnir to Rust transpiler
  - `MjPythonTranspiler` - Mjolnir to Python transpiler
- `linker` - Linker
  - static (compile time)
  - dynamic (run time)
- `MjFormatter` - Source Code Formatter
- `object viewer` - Object Viewer (`.mjo`, `.mjso`, `.mjpo`)

## Tools

The Standard Mjolnir tools are used to manage every aspect of the developer experience.

- `mjc` - Compiler (Disassembler, Optimizer, Assembler, Parser)
- `mjca` - Code Analyzer (Linter?, Compiler?)
- `mjdb` - Debugger (VS Code) (Native and/or VM, Profiler, Object/Memory Viewer, Resource Monitor)
- `mjls` - Language Server (VS Code) (Formatter, Linter, Debugger?, Compiler?)
- `mjvm` - Virtual Machine (JIT, Interpreter, and/or VM)

## File Types

- `.mj` - Source Code
- `.mjpo` - Parsed Object/Pre-tokenized Source Object/Package/Partial Object
- `.mjo` - Object (Byte Code, Static Linkage)
- `.mjso` - Shared Object (Byte Code, Dynamic Linkage)

## AST Purposes

The AST must support including CST metadata as part of formatting, linting, editing, and error reporting.

- compiling
  - fully valid
- linting
  - file/line/column metadata
  - whitespace/tabs/new lines
  - partial syntax
- formatting
  - everything from linting
- editing
  - mutable nodes
- analysing
  - high level preservation

syntax analysis
error reporting

Use relative line numbers for nested syntax elements.
Use line number deltas for interactive editing.

Format on save?
