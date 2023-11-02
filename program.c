/** !
 *  Defines functions for working with edy programs
 * 
 * @file program.c
 * @author Jacob Smith
*/

// Include 
#include <edy/program.h>

dict *p_edy_type_lut;

void init_type_lut (void)
{

    // Construct the type LUT
    dict_construct(&p_edy_type_lut, 32, 0);

    // Populate the type LUT
    for (size_t i = 0; i < 9; i++) dict_add(p_edy_type_lut, edy_type_strings[i], i);

    // Done
    return;
}

int program_create ( edy_program **const pp_edy_program )
{

    // Argument check
    if ( pp_edy_program == (void *) 0 ) goto no_edy_program;

    // Initialized data
    edy_program *p_edy_program = realloc(0, sizeof(edy_program));

    // Error check
    if ( p_edy_program == (void *) 0 ) goto no_mem;

    // Zero set
    memset(p_edy_program, 0, sizeof(edy_program));

    // Return a pointer to the caller
    *pp_edy_program = p_edy_program;

    // Success
    return 1;

    // Error handling
    {
        
        // Argument check
        {
            no_edy_program:
                #ifndef NDEBUG
                    log_error("[edy] [program] Null pointer provided for parameter \"pp_edy_program\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Standard library errors
        {
            no_mem:
                #ifndef NDEBUG
                    printf("[edy] [program] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int load_program_as_json_value ( edy_program **const pp_edy_program, const json_value *const p_value )
{

    // Argument check
    if ( pp_edy_program == (void *) 0        ) goto no_edy_program;
    if ( p_value        == (void *) 0        ) goto wrong_type;
    if ( p_value->type  != JSON_VALUE_OBJECT ) goto wrong_type;

    // Initialized data
    edy_program *p_edy_program = 0;
    const dict *const p_dict = p_value->object;
    const json_value *const p_name   = dict_get(p_dict, "name"),
                     *const p_source = dict_get(p_dict, "source"),
                     *const p_input  = dict_get(p_dict, "input"),
                     *const p_output = dict_get(p_dict, "output");

    // Error check
    if ( ! ( p_name && p_source && p_input && p_output ) ) goto missing_properties;

    // Type checks
    if ( p_name->type   != JSON_VALUE_STRING ) goto wrong_name_type;
    if ( p_source->type != JSON_VALUE_STRING ) goto wrong_source_type;
    if ( p_input->type  != JSON_VALUE_ARRAY  ) goto wrong_input_type;
    if ( p_output->type != JSON_VALUE_ARRAY  ) goto wrong_output_type;

    // Allocate memory for the edy program
    if ( program_create(&p_edy_program) == 0 ) goto failed_to_allocate_edy_program;

    // Copy the program name
    strncpy(p_edy_program->_name, p_name->string, 255);

    // Copy the source code
    {

        // Initialized data
        size_t len = strlen(p_source->string);

        // Allocate memory for the program text
        p_edy_program->p_program_text = calloc(len + 1, sizeof(char));

        // Decode the program text
        base64_decode(p_source->string, len, p_edy_program->p_program_text);
    }

    // Parse the input
    {

        // Initialized data
        const array *const p_array = p_input->list;
        size_t len = array_size(p_array);

        // Iterate over each value in the array
        for (size_t i = 0; i < len; i++)
        {
            
            // Initialized data
            json_value *i_value = 0;

            // Get the value indexed by the iterator
            array_index(p_array, i, &i_value);

            // Error check
            if ( i_value == (void *)0 ) goto wrong_input_element_type;

            // Type check
            if ( i_value->type != JSON_VALUE_OBJECT ) goto wrong_input_element_type;

            // Parse the input 
            {

                // Initialized data
                const dict *const p_dict = i_value->object;
                const json_value *const p_name = dict_get(p_dict, "name"),
                                 *const p_type = dict_get(p_dict, "type");
                
                // Error check
                if ( !( p_name && p_type ) ) goto missing_input_properties;

                // Type check
                if ( p_name->type != JSON_VALUE_STRING ) goto wrong_input_name_type;
                if ( p_type->type != JSON_VALUE_STRING ) goto wrong_input_type_type;

                // Copy the name of the input
                strncpy(p_edy_program->input[i]._name, p_name->string, 255);

                // Store the type of the input
                p_edy_program->input[i]._type = dict_get(p_edy_type_lut, p_type->string);
            }
        }
    }

    // Parse the output
    {

        // Initialized data
        const array *const p_array = p_output->list;
        size_t len = array_size(p_array);

        // Iterate over each value in the array
        for (size_t i = 0; i < len; i++)
        {
            
            // Initialized data
            json_value *i_value = 0;

            // Get the value indexed by the iterator
            array_index(p_array, i, &i_value);

            // Error check
            if ( i_value == (void *)0 ) goto wrong_output_element_type;

            // Type check
            if ( i_value->type != JSON_VALUE_OBJECT ) goto wrong_output_element_type;

            // Parse the output 
            {

                // Initialized data
                const dict *const p_dict = i_value->object;
                const json_value *const p_name = dict_get(p_dict, "name"),
                                 *const p_type = dict_get(p_dict, "type");
                
                // Error check
                if ( !( p_name && p_type ) ) goto missing_output_properties;

                // Type check
                if ( p_name->type != JSON_VALUE_STRING ) goto wrong_output_name_type;
                if ( p_type->type != JSON_VALUE_STRING ) goto wrong_output_type_type;

                // Copy the name of the output
                strncpy(p_edy_program->output[i]._name, p_name->string, 255);

                // Store the type of the output
                p_edy_program->output[i]._type = dict_get(p_edy_type_lut, p_type->string);
            }
        }
    }

    // Return a pointer to the caller
    *pp_edy_program = p_edy_program;

    // Success
    return 1;

    wrong_input_name_type:
    wrong_input_type_type:
    missing_output_properties:
    wrong_output_name_type:
    wrong_output_type_type:
    wrong_name_type:
    wrong_source_type:
    wrong_input_type:
    wrong_input_element_type:
    wrong_output_element_type:
    wrong_output_type:

    // Error
    return 0;

    // Error handling
    {
        
        // Argument check
        {
            no_edy_program:
                #ifndef NDEBUG
                    log_error("[edy] [program] Null pointer provided for parameter \"pp_edy_program\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // edy errors
        {
            failed_to_allocate_edy_program:
                #ifndef NDEBUG
                    log_error("[edy] [program] Failed to allocate memory for edy program in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // json errors
        {
            missing_properties:
                #ifndef NDEBUG
                    log_error("[edy] Not enough properties to construct program in call to function \"%s\"\nRefer to edyschema: https://edy.g10.app/program.json \n", __FUNCTION__);
                #endif

                // Error
                return EXIT_FAILURE;

            missing_input_properties:
                #ifndef NDEBUG
                    log_error("[edy] Not enough properties to construct program input in call to function \"%s\"\nRefer to edyschema: https://edy.g10.app/program.json \n", __FUNCTION__);
                #endif

                // Error
                return EXIT_FAILURE;

            wrong_type:
                #ifndef NDEBUG
                    log_error("[edy] Expected json value to be of type [ object ] in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return EXIT_FAILURE;

        }

        // Standard library errors
        {
            no_mem:
                #ifndef NDEBUG
                    log_error("[edy] [program] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

void program_info ( const edy_program *const p_edy_program )
{

    // Argument check
    if ( p_edy_program == (void *) 0 ) goto no_edy_program;

    // Log the name
    log_info(" - %s - \n", p_edy_program->_name);

    log_info("input: \n", p_edy_program->_name);

    // Log the inputs
    for (size_t i = 0; i < 4; i++)
        if ( p_edy_program->input[i]._type != EDY_TYPE_INV )
            log_info("\t[%d] %s: %s\n", i, p_edy_program->input[i]._name, edy_type_strings[p_edy_program->input[i]._type]);
    
    log_info("output: \n", p_edy_program->_name);

    // Log the outputs
    for (size_t i = 0; i < 4; i++)
        if ( p_edy_program->output[i]._type != EDY_TYPE_INV )
            log_info("\t[%d] %s: %s\n", i, p_edy_program->output[i]._name, edy_type_strings[p_edy_program->output[i]._type]);
    
    // Log the source code
    log_info("source:\n------------------------------\n%s\n------------------------------\n", p_edy_program->p_program_text);
    
    no_edy_program:

    // Done
    return;
}

int program_destroy ( edy_program **const pp_edy_program )
{

    // Argument check
    if ( pp_edy_program == (void *) 0 ) goto no_program;

    // Initialized data
    edy_program *p_edy_program = *pp_edy_program;

    // No more pointer for caller
    *pp_edy_program = 0;

    // Free the program source code
    (void)realloc(p_edy_program->p_program_text, 0);

    // Free the program struct
    (void)realloc(p_edy_program, 0);

    // Success
    return 1;

    // Error handling
    {
        no_program:
            #ifndef NDEBUG
                log_error("[edy] Null pointer provided for parameter \"pp_edy_program\" in call to function \"%s\"\n", __FUNCTION__);
            #endif

            // Error
            return 0;
    }
}