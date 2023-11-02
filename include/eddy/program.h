/** !
 *  Include header for eddy program
 * 
 * @file eddy/program.h
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

// eddy
#include <eddy/eddy.h>

/** !
 *  Allocate memory for an eddy program
 * 
 * @param pp_eddy_program return
 * 
 * @return 1 on success, 0 on error
 */
int program_create ( eddy_program **const pp_eddy_program );

/** !
 *  Construct an eddy program from a json value
 * 
 * @param pp_eddy_program return
 * @param p_value the json value
 * 
 * @return 1 on success, 0 on error
 */
int load_program_as_json_value ( eddy_program **const pp_eddy_program, const json_value *const p_value );

/** !
 *  Write information about an eddy program to standard out
 * 
 * @param p_eddy_program the eddy program
 * 
 * @return void
 */
void program_info ( const eddy_program *const p_eddy_program );

/** !
 *  Destory an eddy program and its contents
 * 
 * @param pp_eddy_program return
 * 
 * @return 1 on success, 0 on error
 */
int program_destroy ( eddy_program **const pp_eddy_program );