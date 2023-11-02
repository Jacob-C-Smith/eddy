/** !
 * edy runtime 
 * 
 * @author Jacob Smith
 * @file main.c
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
#include <edy/program.h>

// Entry point
int main ( int argc, const char *const argv[] )
{

    // Argument check
    //if ( argc != 2 ) goto print_usage;

    // Initialized data
    // const char *const program_path = argv[1];
    const char *const program_path = "example_program.json";
    size_t program_file_size = load_file(program_path, 0, false);
    char *program_file_content = realloc(0, program_file_size * sizeof(char) + 1);
    json_value *p_program_file_json = 0;
    edy_program *p_edy_program = (void *) 0;

    // Initialize the edy runtime dependencies
    edy_init();

    // Load the edy schema
    if ( load_file(program_path, program_file_content, false) == 0 ) goto failed_to_read_file;

    // Parse the edy schema file into a json value
    if ( parse_json_value(program_file_content, 0, &p_program_file_json) == 0 ) goto failed_to_parse_file_text;

    // Parse the json object into an edy program
    if ( load_program_as_json_value(&p_edy_program, p_program_file_json) == 0 ) goto failed_to_load_edy_program;

    // Write a description of the program to standard out
    program_info(p_edy_program);

    // Free the program
    if ( program_destroy(&p_edy_program) == 0 ) goto failed_to_free_program;

    // Clean up resources
    free_json_value(p_program_file_json);
    (void)realloc(program_file_content, 0);

    // Success
    return EXIT_SUCCESS;

    // Error handling
    {

        // Argument errors
        {

            print_usage:

                // Print a usage message
                printf("Usage: edy program_file.sced\n");

                // Error handling
                return EXIT_FAILURE;
        }

        // edy errors
        {
            failed_to_load_edy_program:

                // Write an error message to standard out 
                log_error("[edy] Failed to load edy program in call to function \"%s\"\n", __FUNCTION__);

                // Error
                return EXIT_FAILURE;
            
            failed_to_free_program:

                // Write an error message to standard out 
                log_error("[edy] Failed to free edy program in call to function \"%s\"\n", __FUNCTION__);

                // Error
                return EXIT_FAILURE;
                
        }

        // json errors
        {
            failed_to_parse_file_text:
                log_error("[edy] Failed to parse json text in call to function \"%s\"\n", __FUNCTION__);

                // Error
                return EXIT_FAILURE;
        }

        // Standard library
        {
            failed_to_read_file:
                log_error("[edy] Failed to read file \"%s\" in call to function \"%s\"\n", program_path, __FUNCTION__);

                // Error
                return EXIT_FAILURE;
        }
    }
}