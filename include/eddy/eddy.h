/** !
 * eddy main header
 * 
 * @author Jacob Smith
 * @file eddy/eddy.h
 */

// Include guard
#pragma once

// Standard library
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

// log
#include <log/log.h>

// dict
#include <dict/dict.h>

// array
#include <array/array.h>

// json
#include <json/json.h>

// base64
#include <base64/base64.h>

// stack
#include <stack/stack.h>

// Platform dependent macros
#ifdef _WIN64
#define DLLEXPORT extern __declspec(dllexport)
#else
#define DLLEXPORT
#endif

// Enumeration definitions
enum eddy_type {
    EDDY_TYPE_INV = 0,
    EDDY_TYPE_I32 = 1,
    EDDY_TYPE_U32 = 2,
    EDDY_TYPE_S32 = 3,
    EDDY_TYPE_I64 = 4,
    EDDY_TYPE_U64 = 5,
    EDDY_TYPE_S64 = 6,
    EDDY_TYPE_F32 = 7,
    EDDY_TYPE_F64 = 8
};

enum eddy_opcode
{
    EDDY_OP_INVALID,
    EDDY_OP_POP,
    EDDY_OP_PUSH,
    EDDY_OP_ADD,
    EDDY_OP_SUB,
    EDDY_OP_MUL,
    EDDY_OP_DIV
};

// Constant data
static const char *const eddy_type_strings[9] = 
{
    "invalid",
    "i32",
    "u32",
    "s32",
    "i64",
    "u64",
    "s64",
    "f32",
    "f64"
};

// Forward declarations
struct eddy_program_s;
struct eddy_instruction_s;

// Type definitions
typedef struct eddy_program_s eddy_program;
typedef struct eddy_op_s      eddy_op;

// Struct definitions
struct eddy_op_s
{
    enum eddy_opcode type;
    union 
    {
        struct
        {
            int to;
        } pop;
        
        struct 
        {
            int from;
        } push;
    };
};

struct eddy_program_s
{
    char  _name[255];
    char *p_program_text;
    stack *p_stack;
    struct
    {
        char _name[255];
        enum eddy_type _type;
    } input[8];
    struct
    {
        char _name[255];
        enum eddy_type _type;
    } output[4];
    eddy_op operations[256];
};

/** !
 *  Set up dependencies for eddy runtime
 * 
 * @param void
 * 
 * @return void
 */
DLLEXPORT void eddy_init ( void );

/** !
 * Return the size of a file IF buffer == 0 ELSE read a file into buffer
 * 
 * @param path path to the file
 * @param buffer buffer
 * @param binary_mode "wb" IF true ELSE "w"
 * 
 * @return 1 on success, 0 on error
 */
size_t load_file ( const char *path, void *buffer, bool binary_mode );