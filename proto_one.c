/* Trevor Gerald */

#include <stdio.h>
#include <stdbool.h>

#include "proto_one.h"

#define LOWER_ORDER_BIT_MASK 1

// Function to read in input from file and determine if it is a mascot
int main() 
{
    unsigned short hex_input;
    int check_for_end;

    while(((check_for_end = scanf("%hX\n", &hex_input)) != EOF) && (check_for_end > 0))
    {
        printf("proto_one.c: is_mascot: Input: %hX\n", hex_input);
        int lower_order_bit;
        lower_order_bit = hex_input & LOWER_ORDER_BIT_MASK;
        printf("proto_one.c: is_mascot: Lower Order Bit of Input: %d\n\n", lower_order_bit); 
    }
    return 1;
}
