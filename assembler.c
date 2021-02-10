#include "stdio.h"
#include "stdlib.h"

#define true 1
#define false 0

#define ASSERT(EX) ((EX) ? true : *(volatile int*)0)
#define NOT_IMPLEMENTED ASSERT(!"NOT_IMPLEMENTED")
#define INVALID_DEFAULT_CASE ASSERT(!"INVALID_DEFAULT_CASE")

#define ARRAY_COUNT(ARR) (sizeof(ARR) / sizeof((ARR)[0]))

typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

typedef signed __int8  i8;
typedef signed __int16 i16;
typedef signed __int32 i32;
typedef signed __int64 i64;

typedef u8 bool;

typedef u64 umm;
typedef i64 imm;

#define U8_MAX 0xFF
#define U16_MAX 0xFFFF
#define U32_MAX 0xFFFFFFFF
#define U64_MAX 0xFFFFFFFFFFFFFFFF

enum INSTRUCTION_KIND
{
    Instruction_Addressing_None_Start = 0,
    Instruction_TAX = 0,
    Instruction_TAY,
    Instruction_TSX,
    Instruction_TXA,
    Instruction_TXS,
    Instruction_TYA,
    Instruction_DEX,
    Instruction_DEY,
    Instruction_INX,
    Instruction_INY,
    Instruction_PHA,
    Instruction_PHP,
    Instruction_PLA,
    Instruction_SEC,
    Instruction_SED,
    Instruction_SEI,
    Instruction_CLC,
    Instruction_CLD,
    Instruction_CLI,
    Instruction_CLV,
    Instruction_NOP,
    Instruction_PLP,
    Instruction_RTI,
    Instruction_RTS,
    Instruction_BRK,
    Instruction_Addressing_None_End = Instruction_BRK,
    
    Instruction_Addressing_Acc_Start = Instruction_BRK,
    Instruction_ASL,
    Instruction_LSR,
    Instruction_ROL,
    Instruction_ROR,
    Instruction_Addressing_Acc_End = Instruction_ROR,
    
    Instruction_Addressing_Rel_Start = Instruction_ROR,
    Instruction_BCC,
    Instruction_BCS,
    Instruction_BEQ,
    Instruction_BMI,
    Instruction_BNE,
    Instruction_BPL,
    Instruction_BVC,
    Instruction_BVS,
    Instruction_Addressing_Rel_End = Instruction_BVS,
    
    Instruction_ADC,
    Instruction_AND,
    Instruction_BIT,
    Instruction_CMP,
    Instruction_CPX,
    Instruction_CPY,
    Instruction_DEC,
    Instruction_EOR,
    Instruction_INC,
    Instruction_JMP,
    Instruction_JSR,
    Instruction_LDA,
    Instruction_LDX,
    Instruction_LDY,
    Instruction_ORA,
    Instruction_SBC,
    Instruction_STA,
    Instruction_STX,
    Instruction_STY,
    
    INSTRUCTION_KIND_COUNT
};

enum ADDRESSING_MODE
{
    Addressing_None,
    Addressing_Immediate,
    Addressing_ZeroPage,
    Addressing_ZeroPage_X,
    Addressing_ZeroPage_Y,
    Addressing_Absolute,
    Addressing_Absolute_X,
    Addressing_Absolute_Y,
    Addressing_Indirect,
    Addressing_Indirect_X,
    Addressing_Indirect_Y,
    
    ADDRESSING_MODE_COUNT
};

#define ERRR 0xFF
u8 OpcodeTable[INSTRUCTION_KIND_COUNT][ADDRESSING_MODE_COUNT] = {
    // None
    [Instruction_TAX] = { 0xAA, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_TAY] = { 0xA8, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_TSX] = { 0xBA, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_TXA] = { 0x8A, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_TXS] = { 0x9A, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_TYA] = { 0x98, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_DEX] = { 0xCA, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_DEY] = { 0x88, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_INX] = { 0xE8, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_INY] = { 0xC8, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_PHA] = { 0x48, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_PHP] = { 0x08, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_PLA] = { 0x68, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_SEC] = { 0x38, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_SED] = { 0xF8, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_SEI] = { 0x78, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_CLC] = { 0x18, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_CLD] = { 0xD8, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_CLI] = { 0x58, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_CLV] = { 0xB8, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_NOP] = { 0xEA, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_PLP] = { 0x28, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_RTI] = { 0x40, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_RTS] = { 0x60, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_BRK] = { 0x00, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    
    // Accumulator
    [Instruction_ASL] = { 0x0A, ERRR, 0x06, 0x16, ERRR, 0x0E, 0x1E, ERRR, ERRR, ERRR, ERRR },
    [Instruction_LSR] = { 0x4A, ERRR, 0x46, 0x56, ERRR, 0x4E, 0x5E, ERRR, ERRR, ERRR, ERRR },
    [Instruction_ROL] = { 0x2A, ERRR, 0x26, 0x36, ERRR, 0x2E, 0x3E, ERRR, ERRR, ERRR, ERRR },
    [Instruction_ROR] = { 0x6A, ERRR, 0x66, 0x76, ERRR, 0x6E, 0x7E, ERRR, ERRR, ERRR, ERRR },
    
    // Relative
    [Instruction_BCC] = { 0x90, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_BCS] = { 0xB0, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_BEQ] = { 0xF0, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_BMI] = { 0x30, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_BNE] = { 0xD0, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_BPL] = { 0x10, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_BVC] = { 0x50, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_BVS] = { 0x70, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR, ERRR },
    
    [Instruction_ADC] = { ERRR, 0x69, 0x65, 0x75, ERRR, 0x6D, 0x7D, 0x79, ERRR, 0x61, 0x71 },
    [Instruction_AND] = { ERRR, 0x29, 0x25, 0x35, ERRR, 0x2D, 0x3D, 0x39, ERRR, 0x21, 0x31 },
    [Instruction_BIT] = { ERRR, ERRR, 0x24, ERRR, ERRR, 0x2C, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_CMP] = { ERRR, 0xC9, 0xC5, 0xD5, ERRR, 0xCD, 0xDD, 0xD9, ERRR, 0xC1, 0xD1 },
    [Instruction_CPX] = { ERRR, 0xE0, 0xE4, ERRR, ERRR, 0xEC, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_CPY] = { ERRR, 0xC0, 0xC4, ERRR, ERRR, 0xCC, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_DEC] = { ERRR, ERRR, 0xC6, 0xD6, ERRR, 0xCE, 0xDE, ERRR, ERRR, ERRR, ERRR },
    [Instruction_EOR] = { ERRR, 0x49, 0x45, 0x55, ERRR, 0x4D, 0x5D, 0x59, ERRR, 0x41, 0x51 },
    [Instruction_INC] = { ERRR, ERRR, 0xE6, 0xF6, ERRR, 0xEE, 0xFE, ERRR, ERRR, ERRR, ERRR },
    [Instruction_JMP] = { ERRR, ERRR, ERRR, ERRR, ERRR, 0x4C, ERRR, ERRR, 0x6C, ERRR, ERRR },
    [Instruction_JSR] = { ERRR, ERRR, ERRR, ERRR, ERRR, 0x20, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_LDA] = { ERRR, 0xA9, 0xA5, 0xB5, ERRR, 0xAD, 0xBD, 0xB9, ERRR, 0xA1, 0xB1 },
    [Instruction_LDX] = { ERRR, 0xA2, 0xA6, ERRR, 0xB6, 0xAE, ERRR, 0xBE, ERRR, ERRR, ERRR },
    [Instruction_LDY] = { ERRR, 0xA0, 0xA4, 0xB4, ERRR, 0xAC, 0xBC, ERRR, ERRR, ERRR, ERRR },
    [Instruction_ORA] = { ERRR, 0x09, 0x05, 0x15, ERRR, 0x0D, 0x1D, 0x19, ERRR, 0x01, 0x11 },
    [Instruction_SBC] = { ERRR, 0xE9, 0xE5, 0xF5, ERRR, 0xED, 0xFD, 0xF9, ERRR, 0xE1, 0xF1 },
    [Instruction_STA] = { ERRR, ERRR, 0x85, 0x95, ERRR, 0x8D, 0x9D, 0x99, ERRR, 0x81, 0x91 },
    [Instruction_STX] = { ERRR, ERRR, 0x86, ERRR, 0x96, 0x8E, ERRR, ERRR, ERRR, ERRR, ERRR },
    [Instruction_STY] = { ERRR, ERRR, 0x84, 0x94, ERRR, 0x8C, ERRR, ERRR, ERRR, ERRR, ERRR },
};

typedef struct Memory_State
{
    u8* data;
    umm push_index;
} Memory_State;

void
PushByte(Memory_State* memory_state, u8 byte)
{
    ASSERT(memory_state->push_index < (1 << 16));
    memory_state->data[memory_state->push_index++] = byte;
}

bool
IsWhitespace(u8 c)
{
    return (c == ' '  || c == '\t' ||
            c == '\v' || c == '\r' ||
            c == '\n');
}

bool
IsDigit(u8 c)
{
    return (c >= '0' && c <= '9');
}

bool
IsHexDigit(u8 c)
{
    return (IsDigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'));
}

u8
HexDigitValue(u8 c)
{
    return (IsDigit(c) ? c - '0' : 10 + (c >= 'A' && c <= 'F' ? c - 'A' : c - 'a'));
}

typedef struct String
{
    u8* data;
    umm size;
} String;

typedef struct Label_Note
{
    String name;
    umm address;
    umm line_number;
} Label_Note;

typedef struct Label_Note_Array
{
    Label_Note* data;
    umm size;
    umm capacity;
} Label_Note_Array;

typedef struct Argument
{
    u8 addressing_mode;
    u8 is_multi_byte;
    u8 first_byte;
    u8 second_byte;
} Argument;

bool
StringCompare(String s0, String s1)
{
    if (s0.size == s1.size)
    {
        while (s0.size != 0 && *s0.data == *s1.data)
        {
            s0.data += 1;
            s0.size -= 1;
            
            s1.data += 1;
            s1.size -= 1;
        }
    }
    
    return (s0.size == 0 && s1.size == 0);
}

bool
ParseArgument(String* input, u32 line_number, Argument* argument)
{
    bool encountered_errors = false;
    
    *argument = (Argument){0};
    
    while (IsWhitespace(*input->data))
    {
        ++input->data;
        --input->size;
    }
    
    if (*input->data == '#')
    {
        ++input->data;
        --input->size;
        
        argument->addressing_mode = Addressing_Immediate;
        argument->is_multi_byte   = false;
        
        if (*input->data == '$')
        {
            ++input->data;
            --input->size;
            
            if (!IsHexDigit(input->data[0]) || input->size < 2 || !IsHexDigit(input->data[1])) encountered_errors = true;
            else
            {
                argument->first_byte = HexDigitValue(input->data[0]) << 4 | HexDigitValue(input->data[1]);
                input->data += 2;
                input->size -= 2;
            }
        }
        
        else
        {
            if (!IsDigit(input->data[0]) || input->size < 2 || !IsDigit(input->data[1])) encountered_errors = true;
            else
            {
                argument->first_byte = HexDigitValue(input->data[0]) * 10 + HexDigitValue(input->data[1]);
                input->data += 2;
                input->size -= 2;
            }
        }
    }
    
    else if (*input->data == '$')
    {
        ++input->data;
        --input->size;
        
        if (!IsHexDigit(input->data[0]) || input->size < 2 || !IsHexDigit(input->data[1])) encountered_errors = true;
        else
        {
            argument->first_byte = HexDigitValue(input->data[0]) << 4 | HexDigitValue(input->data[1]);
            
            input->data += 2;
            input->size -= 2;
            
            if (IsHexDigit(*input->data))
            {
                if (!IsHexDigit(input->data[0]) || input->size < 2 || !IsHexDigit(input->data[1])) encountered_errors = true;
                else
                {
                    argument->is_multi_byte = true;
                    argument->second_byte   = HexDigitValue(input->data[0]) << 4 | HexDigitValue(input->data[1]);
                    
                    input->data += 2;
                    input->size -= 2;
                }
            }
            
            else argument->is_multi_byte = false;
            
            if (!encountered_errors)
            {
                if (*input->data == ',')
                {
                    if (input->size < 2 || input->data[1] != 'X' && input->data[1] != 'Y') encountered_errors = true;
                    else
                    {
                        if (argument->is_multi_byte) argument->addressing_mode = (input->data[1] == 'X' ? Addressing_Absolute_X : Addressing_Absolute_Y);
                        else                         argument->addressing_mode = (input->data[1] == 'X' ? Addressing_ZeroPage_X : Addressing_ZeroPage_Y);
                        input->data += 2;
                        input->size -= 2;
                    }
                }
                
                else
                {
                    if (argument->is_multi_byte) argument->addressing_mode = Addressing_Absolute;
                    else                         argument->addressing_mode = Addressing_ZeroPage;
                }
            }
        }
    }
    
    else if (*input->data == '(')
    {
        ++input->data;
        --input->size;
        
        if (*input->data != '$') encountered_errors = true;
        else
        {
            ++input->data;
            --input->size;
            
            if (!IsHexDigit(input->data[0]) || input->size < 2 || !IsHexDigit(input->data[1])) encountered_errors = true;
            else
            {
                argument->first_byte    = HexDigitValue(input->data[0]) << 4 | HexDigitValue(input->data[1]);
                argument->is_multi_byte = false;
                
                input->data += 2;
                input->size -= 2;
                
                if (*input->data == ')')
                {
                    if (input->size < 3 || input->data[1] != ',' || input->data[2] != 'Y') encountered_errors = true;
                    else
                    {
                        argument->addressing_mode = Addressing_Indirect_Y;
                        input->data += 3;
                        input->size -= 3;
                    }
                }
                
                else
                {
                    if (input->size < 3 || input->data[0] != ',' || input->data[1] != 'X' || input->data[2] != ')') encountered_errors = true;
                    else
                    {
                        argument->addressing_mode = Addressing_Indirect_X;
                        input->data += 3;
                        input->size -= 3;
                    }
                }
            }
        }
    }
    
    else encountered_errors = true;
    
    if (encountered_errors) printf("ERROR(%d): Invalid argument format\n", line_number);
    
    return !encountered_errors;
}

bool
ParseInstruction(String input, u32 line_number, Memory_State* memory_state, Label_Note_Array* label_correction_array)
{
    bool encountered_errors = false;
    
    char instruction_name[4] = {0};
    for (umm i = 0; i < 3; ++i)
    {
        if (input.size == 0)
        {
            printf("ERROR(%d): Missing instruction at non empty line\n", line_number);
            encountered_errors = true;
            break;
        }
        
        else
        {
            instruction_name[i] = *input.data;
            input.data         += 1;
            input.size         -= 1;
        }
    }
    
    if (!encountered_errors)
    {
        u8 instruction = 0;
        
        if      (strcmp(instruction_name, "ADC") == 0) instruction = Instruction_ADC;
        else if (strcmp(instruction_name, "AND") == 0) instruction = Instruction_AND;
        else if (strcmp(instruction_name, "ASL") == 0) instruction = Instruction_ASL;
        else if (strcmp(instruction_name, "BCC") == 0) instruction = Instruction_BCC;
        else if (strcmp(instruction_name, "BCS") == 0) instruction = Instruction_BCS;
        else if (strcmp(instruction_name, "BEQ") == 0) instruction = Instruction_BEQ;
        else if (strcmp(instruction_name, "BIT") == 0) instruction = Instruction_BIT;
        else if (strcmp(instruction_name, "BMI") == 0) instruction = Instruction_BMI;
        else if (strcmp(instruction_name, "BNE") == 0) instruction = Instruction_BNE;
        else if (strcmp(instruction_name, "BPL") == 0) instruction = Instruction_BPL;
        else if (strcmp(instruction_name, "BRK") == 0) instruction = Instruction_BRK;
        else if (strcmp(instruction_name, "BVC") == 0) instruction = Instruction_BVC;
        else if (strcmp(instruction_name, "BVS") == 0) instruction = Instruction_BVS;
        else if (strcmp(instruction_name, "CLC") == 0) instruction = Instruction_CLC;
        else if (strcmp(instruction_name, "CLD") == 0) instruction = Instruction_CLD;
        else if (strcmp(instruction_name, "CLI") == 0) instruction = Instruction_CLI;
        else if (strcmp(instruction_name, "CLV") == 0) instruction = Instruction_CLV;
        else if (strcmp(instruction_name, "CMP") == 0) instruction = Instruction_CMP;
        else if (strcmp(instruction_name, "CPX") == 0) instruction = Instruction_CPX;
        else if (strcmp(instruction_name, "CPY") == 0) instruction = Instruction_CPY;
        else if (strcmp(instruction_name, "DEC") == 0) instruction = Instruction_DEC;
        else if (strcmp(instruction_name, "DEX") == 0) instruction = Instruction_DEX;
        else if (strcmp(instruction_name, "DEY") == 0) instruction = Instruction_DEY;
        else if (strcmp(instruction_name, "EOR") == 0) instruction = Instruction_EOR;
        else if (strcmp(instruction_name, "INC") == 0) instruction = Instruction_INC;
        else if (strcmp(instruction_name, "INX") == 0) instruction = Instruction_INX;
        else if (strcmp(instruction_name, "INY") == 0) instruction = Instruction_INY;
        else if (strcmp(instruction_name, "JMP") == 0) instruction = Instruction_JMP;
        else if (strcmp(instruction_name, "JSR") == 0) instruction = Instruction_JSR;
        else if (strcmp(instruction_name, "LDA") == 0) instruction = Instruction_LDA;
        else if (strcmp(instruction_name, "LDX") == 0) instruction = Instruction_LDX;
        else if (strcmp(instruction_name, "LDY") == 0) instruction = Instruction_LDY;
        else if (strcmp(instruction_name, "LSR") == 0) instruction = Instruction_LSR;
        else if (strcmp(instruction_name, "NOP") == 0) instruction = Instruction_NOP;
        else if (strcmp(instruction_name, "ORA") == 0) instruction = Instruction_ORA;
        else if (strcmp(instruction_name, "PHA") == 0) instruction = Instruction_PHA;
        else if (strcmp(instruction_name, "PHP") == 0) instruction = Instruction_PHP;
        else if (strcmp(instruction_name, "PLA") == 0) instruction = Instruction_PLA;
        else if (strcmp(instruction_name, "PLP") == 0) instruction = Instruction_PLP;
        else if (strcmp(instruction_name, "ROL") == 0) instruction = Instruction_ROL;
        else if (strcmp(instruction_name, "ROR") == 0) instruction = Instruction_ROR;
        else if (strcmp(instruction_name, "RTI") == 0) instruction = Instruction_RTI;
        else if (strcmp(instruction_name, "RTS") == 0) instruction = Instruction_RTS;
        else if (strcmp(instruction_name, "SBC") == 0) instruction = Instruction_SBC;
        else if (strcmp(instruction_name, "SEC") == 0) instruction = Instruction_SEC;
        else if (strcmp(instruction_name, "SED") == 0) instruction = Instruction_SED;
        else if (strcmp(instruction_name, "SEI") == 0) instruction = Instruction_SEI;
        else if (strcmp(instruction_name, "STA") == 0) instruction = Instruction_STA;
        else if (strcmp(instruction_name, "STX") == 0) instruction = Instruction_STX;
        else if (strcmp(instruction_name, "STY") == 0) instruction = Instruction_STY;
        else if (strcmp(instruction_name, "TAX") == 0) instruction = Instruction_TAX;
        else if (strcmp(instruction_name, "TAY") == 0) instruction = Instruction_TAY;
        else if (strcmp(instruction_name, "TSX") == 0) instruction = Instruction_TSX;
        else if (strcmp(instruction_name, "TXA") == 0) instruction = Instruction_TXA;
        else if (strcmp(instruction_name, "TXS") == 0) instruction = Instruction_TXS;
        else if (strcmp(instruction_name, "TYA") == 0) instruction = Instruction_TYA;
        else
        {
            printf("ERROR(%d): Unknown instruction\n", line_number);
            encountered_errors = true;
        }
        
        if (!encountered_errors)
        {
            if (instruction >= Instruction_Addressing_None_Start && instruction <= Instruction_Addressing_None_End)
            {
                PushByte(memory_state, OpcodeTable[instruction][Addressing_None]);
                if (instruction == Instruction_BRK) PushByte(memory_state, 0);
            }
            
            else if (instruction >= Instruction_Addressing_Acc_Start && instruction <= Instruction_Addressing_Acc_End)
            {
                while (IsWhitespace(*input.data))
                {
                    ++input.data;
                    --input.size;
                }
                
                if (*input.data == 'A')
                {
                    PushByte(memory_state, OpcodeTable[instruction][Addressing_None]);
                }
                
                else
                {
                    Argument argument;
                    if (!ParseArgument(&input, line_number, &argument)) encountered_errors = true;
                    else
                    {
                        if (OpcodeTable[instruction][argument.addressing_mode] == ERRR)
                        {
                            printf("ERROR(%d): Unsupported addressing mode\n", line_number);
                            encountered_errors = true;
                        }
                        
                        else
                        {
                            PushByte(memory_state, OpcodeTable[instruction][argument.addressing_mode]);
                            
                            PushByte(memory_state, argument.first_byte);
                            if (argument.is_multi_byte) PushByte(memory_state, argument.second_byte);
                        }
                    }
                }
            }
            
            else if (instruction >= Instruction_Addressing_Rel_Start && instruction <= Instruction_Addressing_Rel_End)
            {
                PushByte(memory_state, OpcodeTable[instruction][Addressing_None]);
                PushByte(memory_state, 0);
                
                while (IsWhitespace(*input.data))
                {
                    ++input.data;
                    --input.size;
                }
                
                String label = {
                    .data = input.data,
                    .size = 0
                };
                
                while ((*input.data >= 'A' && *input.data <= 'Z') || (*input.data >= 'a' && *input.data <= 'z') || IsDigit(*input.data) || *input.data == '_')
                {
                    ++input.data;
                    --input.size;
                    label.size += 1;
                }
                
                if (label_correction_array->size == label_correction_array->capacity)
                {
                    printf("ERROR(%d): Too many label used\n", line_number);
                    encountered_errors = true;
                }
                
                else
                {
                    label_correction_array->data[label_correction_array->size++] = (Label_Note){
                        .name        = label,
                        .address     = memory_state->push_index - 1,
                        .line_number = line_number
                    };
                }
            }
            
            else
            {
                Argument argument;
                if (!ParseArgument(&input, line_number, &argument)) encountered_errors = true;
                else
                {
                    if (OpcodeTable[instruction][argument.addressing_mode] == ERRR)
                    {
                        printf("ERROR(%d): Unsupported addressing mode\n", line_number);
                        encountered_errors = true;
                    }
                    
                    else
                    {
                        PushByte(memory_state, OpcodeTable[instruction][argument.addressing_mode]);
                        
                        PushByte(memory_state, argument.first_byte);
                        if (argument.is_multi_byte) PushByte(memory_state, argument.second_byte);
                    }
                }
            }
            
            if (!encountered_errors)
            {
                while (!encountered_errors && input.size != 0)
                {
                    if (!IsWhitespace(*input.data))
                    {
                        printf("ERROR(%d): Trailing characters\n", line_number);
                        encountered_errors = true;
                    }
                    
                    else
                    {
                        ++input.data;
                        --input.size;
                    }
                }
            }
        }
    }
    
    return !encountered_errors;
}
#undef ERRR

__declspec(dllexport) bool
ParseProgram(const char* filename, u8 program_memory[(1 << 16)])
{
    bool encountered_errors = false;
    
    Memory_State memory_state = {
        .data       = program_memory,
        .push_index = 0
    };
    
    for (umm i = 0; i < ARRAY_COUNT(program_memory); ++i) program_memory[i] = 0;
    
    FILE* file = fopen(filename, "rb");
    
    int size     = 0;
    char* buffer = 0;
    
    if (file != 0)
    {
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        rewind(file);
        
        buffer = malloc(size + 1);
    }
    
    if (file == 0 || fread(buffer, 1, size, file) != size)
    {
        printf("ERROR: Failed to read file\n");
        encountered_errors = true;
    }
    
    else
    {
        buffer[size] = 0;
        
        Label_Note_Array label_array;
        label_array.capacity = 1024;
        label_array.size     = 0;
        label_array.data = malloc(sizeof(Label_Note_Array) * label_array.capacity);
        
        Label_Note_Array label_correction_array;
        label_correction_array.capacity = 1024;
        label_correction_array.size     = 0;
        label_correction_array.data = malloc(sizeof(Label_Note_Array) * label_correction_array.capacity);
        
        char* cursor = buffer;
        u32 line_number  = 0;
        
        while (!encountered_errors)
        {
            while (*cursor != 0)
            {
                if (*cursor == '\n')
                {
                    line_number += 1;
                    cursor      += 1;
                }
                
                else if (IsWhitespace(*cursor))
                {
                    cursor += 1;
                }
                
                else if (*cursor == ';')
                {
                    while (*cursor != 0 && *cursor != '\n') ++cursor;
                }
                
                else break;
            }
            
            char* line_start = cursor;
            
            bool encountered_colon = false;
            while (*cursor != 0 && *cursor != '\r' && *cursor != '\n' && *cursor != ';')
            {
                if (*cursor == ':')
                {
                    encountered_colon = true;
                    break;
                }
                
                else cursor += 1;
            }
            
            char* line_end = cursor;
            
            if (*line_start == 0) break;
            else
            {
                String line = {
                    .data = (u8*)line_start,
                    .size = line_end - line_start
                };
                
                if (encountered_colon)
                {
                    // NOTE(soimn): Skip colon
                    ++cursor;
                    
                    for (umm i = 0; !encountered_errors && i < label_array.size; ++i)
                    {
                        if (StringCompare(line, label_array.data[i].name) == 0)
                        {
                            printf("ERROR(%d): Duplicate label\n", line_number);
                            encountered_errors = true;
                        }
                    }
                    
                    if (!encountered_errors)
                    {
                        if (label_array.size == label_array.capacity)
                        {
                            printf("ERROR(%d): Too many labels\n", line_number);
                            encountered_errors = true;
                        }
                        
                        else
                        {
                            label_array.data[label_array.size++] = (Label_Note){
                                .name    = line,
                                .address = memory_state.push_index
                            };
                        }
                    }
                }
                
                else if (!ParseInstruction(line, line_number, &memory_state, &label_correction_array))
                {
                    encountered_errors = true;
                }
            }
        }
        
        if (!encountered_errors)
        {
            for (umm i = 0; i < label_correction_array.size; ++i)
            {
                umm source_address = label_correction_array.data[i].address;
                
                imm dest_address = -1;
                for (umm j = 0; j < label_array.size; ++j)
                {
                    if (StringCompare(label_correction_array.data[i].name, label_array.data[j].name))
                    {
                        dest_address = label_array.data[j].address;
                        break;
                    }
                }
                
                if (dest_address == -1)
                {
                    printf("ERROR(%d): Unknown label\n", (u32)label_correction_array.data[i].line_number);
                    encountered_errors = true;
                }
                
                else
                {
                    memory_state.data[source_address] = (i8)(dest_address - (source_address + 1));
                }
            }
        }
    }
    
    free(buffer);
    
    return !encountered_errors;
}
