/** !
 *  Include header for edy program
 * 
 * @file edy/program.h
 * @author Jacob Smith
 */

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

// edy
#include <edy/edy.h>

/** !
 *  Allocate memory for an edy program
 * 
 * @param pp_edy_program return
 * 
 * @return 1 on success, 0 on error
 */
int program_create ( edy_program **const pp_edy_program );

/** !
 *  Construct an edy program from a json value
 * 
 * @param pp_edy_program return
 * @param p_value the json value
 * 
 * @return 1 on success, 0 on error
 */
int load_program_as_json_value ( edy_program **const pp_edy_program, const json_value *const p_value );

/** !
 *  Write information about an edy program to standard out
 * 
 * @param p_edy_program the edy program
 * 
 * @return void
 */
void program_info ( const edy_program *const p_edy_program );

/** !
 *  Destory an edy program and its contents
 * 
 * @param pp_edy_program return
 * 
 * @return 1 on success, 0 on error
 */
int program_destroy ( edy_program **const pp_edy_program );