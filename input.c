/* Trevor Gerald */

#include <stdio.h>
#include <stdbool.h>

#include "structs.h"
#include "input.h"
#include "bits.h"
#include "physics.h"
#include "lists.h"
#include "output.h"

// Reads in the hex input from a file and determines its validity, creating the appropriate objects if necessary
bool good_input_run(void *data) 
{
    unsigned short hex_input;
    int check_for_end;
    struct Sim *world = data;
    
    while (((check_for_end = scanf("%hX\n", &hex_input)) != EOF) && (check_for_end > 0)) 
    {
        if (is_mascot(hex_input) && validate_mascot(hex_input)) deal_with_mascot(hex_input, world);
        else if (is_coin(hex_input) && validate_coin(hex_input)) deal_with_coin(hex_input, world);
        else {
            output_bad_bits(hex_input);
            return false;
        }
    }
    output_scanf(check_for_end);
    if (check_for_end == 0) return false;
    return true;
}
