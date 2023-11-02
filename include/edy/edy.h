/** !
 * edy main header
 * 
 * @author Jacob Smith
 * @file edy/edy.h
 */

// Include guard
#pragma once

// Standard library
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

// log submodule
#include <log/log.h>

// dict submodule
#include <dict/dict.h>

// array submodule
#include <array/array.h>

// json submodule
#include <json/json.h>

// base64 submodule
#include <base64/base64.h>

// Enumeration definitions
enum edy_type {
    EDY_TYPE_INV = 0,
    EDY_TYPE_I32 = 1,
    EDY_TYPE_U32 = 2,
    EDY_TYPE_S32 = 3,
    EDY_TYPE_I64 = 4,
    EDY_TYPE_U64 = 5,
    EDY_TYPE_S64 = 6,
    EDY_TYPE_F32 = 7,
    EDY_TYPE_F64 = 8
};

// Constant data
static const char *const edy_type_strings[9] = 
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
struct edy_program_s;

// Type definitions
typedef struct edy_program_s edy_program;

// Struct definitions
struct edy_program_s
{
    char  _name[255];
    char *p_program_text;
    struct {
        char _name[255];
        enum edy_type _type;
    } input[4];
    struct {
        char _name[255];
        enum edy_type _type;
    } output[4];
};

/** !
 *  Set up dependencies for edy runtime
 * 
 * @param void
 * 
 * @return void
 */
void edy_init ( void );

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