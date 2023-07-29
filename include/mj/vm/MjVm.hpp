#pragma once

#include "std/Common.hpp"


// Virtual Machine Return Codes
enum class MjVmError : u8 {
    NONE,
    ILLEGAL_INSTRUCTION,
    DIVIDE_BY_ZERO,
    MEMORY_ACCESS,
    FIRMWARE_ERROR,
    FIRMWARE_INVALID,
};


// Virtual machine external function return codes.
enum class MjCallResult : u8 {
    ABORT,
    ERROR,
    UPDATE
};


enum class MjVmOp : u8 {
    
    // Flow Control
    ABT = 0x00, // Abort
    RET = 0x01, // Return
    CAL = 0x02, // Call native function
    RUN = 0x03, // Call program function
    SCH = 0x04, // Schedule unconditionally
    SIF = 0x05, // Schedule if true
    SEL = 0x06, // Schedule if false
    SAF = 0x07, // Schedule after n cycles
    
    // Logical Unary Operations
    NOT = 0X08,
    
    // Bitwise Unary Operations
    BIT_INV = 0X09,
    
    // Arithmetic Unary Operations
    SETII = 0X0A,
    SETIF = 0X0B,
    SETFI = 0X0C,
    SETFF = 0X0D,
    NEGII = 0X0E,
    NEGIF = 0X0F,
    NEGFI = 0X10,
    NEGFF = 0X11,
    
    // Relational Binary Operations
    EQUII = 0X12,
    EQUIF = 0X13, // EQUFI
    EQUFF = 0X14,
    NEQII = 0X15,
    NEQIF = 0X16, // NEQFI
    NEQFF = 0X17,
    LESII = 0X18,
    LESIF = 0X19, // GTRFI
    LESFF = 0X1A,
    LEQII = 0X1B,
    LEQIF = 0X1C, // GEQFI
    LEQFF = 0X1D,
    GTRII = 0X1E,
    GTRIF = 0X1F, // LESFI
    GTRFF = 0X20,
    GEQII = 0X21,
    GEQIF = 0X22, // LEQFI
    GEQFF = 0X23,
    
    // Bitwise Binary Operations
    BIT_AND = 0X24, // AND
    BIT_OR  = 0X25, // OR
    BIT_XOR = 0X26, // XOR
    BIT_LSL = 0X27,
    BIT_ASR = 0X28,
    
    // Arithmetic Binary Operations
    ADDII = 0X29,
    ADDIF = 0X2A, // ADDFI
    ADDFF = 0X2B,
    SUBII = 0X2C,
    SUBIF = 0X2D,
    SUBFI = 0X2E,
    SUBFF = 0X2F,
    MULII = 0X30,
    MULIF = 0X31, // MULFI
    MULFF = 0X32,
    DIVII = 0X33,
    DIVIF = 0X34,
    DIVFI = 0X35,
    DIVFF = 0X36,
    REMII = 0X37,
    REMIF = 0X38,
    REMFI = 0X39,
    REMFF = 0X3A,
};


// An accessor for external objects.
struct MjVmObject {
    void *object;                                                    // The object address in external memory.
    MjCallResult (*destructor)(void *); // The object destructor.
    bool scheduled;                                         // The scheduled execution flag.
};


// A Virtual Machine Program.
struct MjProgram {
    struct {
        MjVmObject *data;    // The lsit of objects.
        u16 count;           // The number of signals.
    } objects; 
    struct {
        FlowVmSignal *data;  // The ordered list of program signals.
        u16 count;           // The number of signals.
    } signals; 
    struct {
        MjCallResult (**data)(value *, void *, value *); // The list of functions.
        u16 count;                            // The number of signals.
    } functions;
    u16 *code;         // The executable code.
    value *data;       // The initialized data.
    u32 size;          // The size of the full program.
    u32 code_size;     // The size of the program code.
    u16 data_size;     // The size of the program data.
    u8 id;             // The index of the program in internal storage.
};



/// The virtual machine. This is a memory to memory machine which supports
/// both integer and floating point operations, utilizes specialized peripheral
/// interface instructions for low cost highlevel functionality, automatically
/// schedules concurrent statements, and manages data dependancies between
/// concurrent and sequential blocks.
///
/// The machine will always execute functional statements with priorety to meet
/// timing requirements.
class MjVm {
private:
    static constexpr u32 FLOW_PROGRAM_NAME_MAX = 64;
public:


    MjVm() {}


    MjVmError stop();


    MjVmError reset();


    MjVmError update();
};
