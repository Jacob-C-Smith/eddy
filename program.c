/** !
 *  Defines functions for working with eddy programs
 * 
 * @file program.c
 * 
 * @author Jacob Smith
*/

// Include 
#include <eddy/program.h>

dict *p_eddy_type_lut;

const char *in_regs[8] = { "rdi", "rsi", "rdx", "rcx", "r8", "r9", "r10", "r11" };
const char *out_regs[4] = { "r12", "r13", "r14", "r15" };

void init_type_lut (void)
{

    // Construct the type LUT
    dict_construct(&p_eddy_type_lut, 32, 0);

    // Populate the type LUT
    for (size_t i = 0; i < 9; i++) dict_add(p_eddy_type_lut, eddy_type_strings[i], (void *) i);

    // Done
    return;
}

int program_create ( eddy_program **const pp_eddy_program )
{

    // Argument check
    if ( pp_eddy_program == (void *) 0 ) goto no_eddy_program;

    // Initialized data
    eddy_program *p_eddy_program = realloc(0, sizeof(eddy_program));

    // Error check
    if ( p_eddy_program == (void *) 0 ) goto no_mem;

    // Zero set
    memset(p_eddy_program, 0, sizeof(eddy_program));

    // Return a pointer to the caller
    *pp_eddy_program = p_eddy_program;

    // Success
    return 1;

    // Error handling
    {
        
        // Argument check
        {
            no_eddy_program:
                #ifndef NDEBUG
                    log_error("[eddy] [program] Null pointer provided for parameter \"pp_eddy_program\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Standard library errors
        {
            no_mem:
                #ifndef NDEBUG
                    printf("[eddy] [program] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int program_load_as_json_value ( eddy_program **const pp_eddy_program, const json_value *const p_value )
{

    // Argument check
    if ( pp_eddy_program == (void *) 0        ) goto no_eddy_program;
    if ( p_value        == (void *) 0        ) goto wrong_type;
    if ( p_value->type  != JSON_VALUE_OBJECT ) goto wrong_type;

    // Initialized data
    eddy_program *p_eddy_program = 0;
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

    // Allocate memory for the eddy program
    if ( program_create(&p_eddy_program) == 0 ) goto failed_to_allocate_eddy_program;

    // Copy the program name
    strncpy(p_eddy_program->_name, p_name->string, 255);

    // Copy the source code
    {

        // Initialized data
        size_t len = strlen(p_source->string);

        // Allocate memory for the program text
        p_eddy_program->p_program_text = calloc(len + 1, 2);

        // Copy the program text
        //strncpy(p_eddy_program->p_program_text, p_source->string, len);

        // Decode the program text
        base64_decode(p_source->string, len*2, p_eddy_program->p_program_text);
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
                strncpy(p_eddy_program->input[i]._name, p_name->string, 255);

                // Store the type of the input
                p_eddy_program->input[i]._type = (enum eddy_type) dict_get(p_eddy_type_lut, p_type->string);
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
                strncpy(p_eddy_program->output[i]._name, p_name->string, 255);

                // Store the type of the output
                p_eddy_program->output[i]._type = (enum eddy_type) dict_get(p_eddy_type_lut, p_type->string);
            }
        }
    }

    // Construct a stack
    stack_construct(&p_eddy_program->p_stack, 32);

    // Parse the source code
    {

        // Initialized data
        size_t i = 0,
               j = 0;
        char   buf[64];
        char *p_text = p_eddy_program->p_program_text;

        // Walk the file
        while ( *p_text )
        {
            // Skip newlines and whitespaces
            if ( *p_text == ' ' || *p_text == '\n' || *p_text == '\t' || *p_text == '\r' ) { p_text++; continue; };

            switch (*p_text)
            {
            case '<':
            {
                p_eddy_program->operations[j].type = EDDY_OP_PUSH;
                p_text++;
                p_text++;
                
                char *old_p = p_text;
                size_t l = 0;
                while(*p_text!='\n' && *p_text!='\0') { p_text++; };
                l = (p_text - old_p);
                strncpy(buf, old_p, l);
                buf[l] = '\0';

                for (size_t k = 0; k < 8; k++)
                {
                    if ( strcmp(buf, &p_eddy_program->input[k]._name) == 0 ) 
                    {
                        p_eddy_program->operations[j].push.from = k;
                        break;
                    }
                }
                
                j++;

                if ( *p_text== '\0')
                    continue;


                break;
                }

            case '>':
            {
                p_eddy_program->operations[j].type = EDDY_OP_POP;
                
                p_text++;
                p_text++;
                char *old_p = p_text;
                size_t l = 0;
                while(*p_text!='\n' && *p_text!='\0') { p_text++; };
                l = (p_text - old_p);
                strncpy(buf, old_p, l);
                buf[l] = '\0';

                for (size_t k = 0; k < 4; k++)
                {
                    if ( strcmp(buf, p_eddy_program->output[k]._name) == 0 ) 
                    {
                        p_eddy_program->operations[j].pop.to = k;
                        break;
                    }
                }
                
                j++;

                if ( *p_text== '\0')
                    continue;


                break;
            }

            case '+':
                p_eddy_program->operations[j].type = EDDY_OP_ADD;

                while(*p_text!='\n' && *p_text!='\0') { p_text++; };
                j++;

                continue;

            case '-':
                p_eddy_program->operations[j].type = EDDY_OP_SUB;

                while(*p_text!='\n' && *p_text!='\0') { p_text++; };
                j++;

                continue;

            case '*':
                p_eddy_program->operations[j].type = EDDY_OP_MUL;

                while(*p_text!='\n' && *p_text!='\0') { p_text++; };
                j++;

                continue;

            case '/':
                p_eddy_program->operations[j].type = EDDY_OP_DIV;

                while(*p_text!='\n' && *p_text!='\0') { p_text++; };
                j++;

                continue;

            default:
                while(*p_text!='\n' && *p_text!='\0') { p_text++; };

                continue;
            }
        }
        
        p_text++;
    }

    // Return a pointer to the caller
    *pp_eddy_program = p_eddy_program;

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
            no_eddy_program:
                #ifndef NDEBUG
                    log_error("[eddy] [program] Null pointer provided for parameter \"pp_eddy_program\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // eddy errors
        {
            failed_to_allocate_eddy_program:
                #ifndef NDEBUG
                    log_error("[eddy] [program] Failed to allocate memory for eddy program in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // json errors
        {
            missing_properties:
                #ifndef NDEBUG
                    log_error("[eddy] Not enough properties to construct program in call to function \"%s\"\nRefer to eddyschema: https://eddy.g10.app/program.json \n", __FUNCTION__);
                #endif

                // Error
                return EXIT_FAILURE;

            missing_input_properties:
                #ifndef NDEBUG
                    log_error("[eddy] Not enough properties to construct program input in call to function \"%s\"\nRefer to eddyschema: https://eddy.g10.app/program.json \n", __FUNCTION__);
                #endif

                // Error
                return EXIT_FAILURE;

            wrong_type:
                #ifndef NDEBUG
                    log_error("[eddy] Expected json value to be of type [ object ] in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return EXIT_FAILURE;

        }

        // Standard library errors
        {
            no_mem:
                #ifndef NDEBUG
                    log_error("[eddy] [program] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

void program_info ( const eddy_program *const p_eddy_program )
{

    // Argument check
    if ( p_eddy_program == (void *) 0 ) goto no_eddy_program;

    // Log the name
    log_info(" - %s - \n", p_eddy_program->_name);

    log_info("input: \n", p_eddy_program->_name);

    // Log the inputs
    for (size_t i = 0; i < 8; i++)
        if ( p_eddy_program->input[i]._type != EDDY_TYPE_INV )
            log_info("\t[%d] %s: %s\n", i, p_eddy_program->input[i]._name, eddy_type_strings[p_eddy_program->input[i]._type]);
    
    log_info("output: \n", p_eddy_program->_name);

    // Log the outputs
    for (size_t i = 0; i < 4; i++)
        if ( p_eddy_program->output[i]._type != EDDY_TYPE_INV )
            log_info("\t[%d] %s: %s\n", i, p_eddy_program->output[i]._name, eddy_type_strings[p_eddy_program->output[i]._type]);
    
    putchar('\n');
    log_info("source code\n------------------------------\n");

    printf("%s\n\n", p_eddy_program->p_program_text);

    // Log the source code
    log_info("stack pointer | IR\n------------------------------\n");
    
    size_t stack_pointer = 0;

    for (size_t i = 0; p_eddy_program->operations[i].type != EDDY_OP_INVALID; i++)
    {
        
        switch (p_eddy_program->operations[i].type)
        {
        case EDDY_OP_POP:
            printf("%-13d | POP %d\n", stack_pointer, p_eddy_program->operations[i].pop.to);
            stack_pointer--;
            break;
        case EDDY_OP_PUSH:
            printf("%-13d | PUSH %d\n", stack_pointer, p_eddy_program->operations[i].push.from);
            stack_pointer++;
            break;
        case EDDY_OP_ADD:
            stack_pointer--;
            printf("%-13d | ADD\n", stack_pointer);
            break;
        case EDDY_OP_SUB:
            stack_pointer--;
            printf("%-13d | SUB\n", stack_pointer);
            break;
        case EDDY_OP_MUL:
            stack_pointer--;
            printf("%-13d | MUL\n", stack_pointer);
            break;
        case EDDY_OP_DIV:
            stack_pointer--;
            printf("%-13d | DIV\n", stack_pointer);
            break;
        default:
            printf("%-13d | \n", stack_pointer);
            break;
        }
    }
    
    putchar('\n');

    stack_pointer = 0;

    log_info("asm:\n------------------------------\n");

    printf("\n");

    printf("[BITS 64]\n");
    printf("main:\n");
    for (size_t i = 0; p_eddy_program->operations[i].type != EDDY_OP_INVALID; i++)
    {
        
        switch (p_eddy_program->operations[i].type)
        {
        case EDDY_OP_POP:
            stack_pointer--;
            printf("vmovaps zword [%s], zmm%d\n", out_regs[p_eddy_program->operations[i].pop.to], stack_pointer);
            break;
        case EDDY_OP_PUSH:
            printf("vmovaps zmm%d, zword[%s]\n", stack_pointer, in_regs[p_eddy_program->operations[i].push.from]);
            stack_pointer++;
            break;
        case EDDY_OP_ADD:
            stack_pointer--;
            printf("vaddps zmm%d, zmm%d, zmm%d\n", stack_pointer - 1, stack_pointer - 1, stack_pointer);
            break;
        case EDDY_OP_SUB:
            stack_pointer--;
            printf("vsubps zmm%d, zmm%d, zmm%d\n", stack_pointer - 1, stack_pointer - 1, stack_pointer);
            break;
        case EDDY_OP_MUL:
            stack_pointer--;
            printf("vmulps zmm%d, zmm%d, zmm%d\n", stack_pointer - 1, stack_pointer - 1, stack_pointer);
            break;
        case EDDY_OP_DIV:
            stack_pointer--;
            printf("vdivps zmm%d, zmm%d, zmm%d\n", stack_pointer - 1, stack_pointer - 1, stack_pointer);
            break;
        default:
            break;
        }
    }
    

    no_eddy_program:

    // Done
    return;
}

int program_destroy ( eddy_program **const pp_eddy_program )
{

    // Argument check
    if ( pp_eddy_program == (void *) 0 ) goto no_program;

    // Initialized data
    eddy_program *p_eddy_program = *pp_eddy_program;

    // No more pointer for caller
    *pp_eddy_program = 0;

    // Free the program source code
    (void)realloc(p_eddy_program->p_program_text, 0);

    // Free the program struct
    (void)realloc(p_eddy_program, 0);

    // Success
    return 1;

    // Error handling
    {
        no_program:
            #ifndef NDEBUG
                log_error("[eddy] Null pointer provided for parameter \"pp_eddy_program\" in call to function \"%s\"\n", __FUNCTION__);
            #endif

            // Error
            return 0;
    }
}
