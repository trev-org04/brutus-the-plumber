/* Trevor Gerald */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "structs.h"
#include "proto_three.h"
#include "bits.h"

// Function to read in file input and print color and X-Velocity from input
int main() 
{
    unsigned short hex_input;
    int check_for_end;
    while (((check_for_end = scanf("%hX\n", &hex_input)) != EOF) && (check_for_end > 0)) 
    {
        printf("proto_three.c: create_lists: %hX\n", hex_input);
        if (is_mascot(hex_input) && validate_mascot(hex_input))
        {
            printf("proto_three.c: Found mascot!\n");
            struct Buckeye *brutus = malloc(sizeof(struct Buckeye));
            if (brutus == NULL) {
                printf("proto_three.c: allocate_mem: Memory was not properly allocated!\n");
            }
            else {
                printf("proto_three.c: allocate_mem: Memory was properly allocated!\n");
                brutus->x_position = 0.5;
                brutus->y_position = 0.5;
                brutus->x_velocity = get_x_vel(hex_input);
                brutus->y_velocity = 0.0;
                brutus->jump_velocity = get_jump_vel(hex_input);
                brutus->color = get_color(hex_input);
                brutus->loot = 0;
                printf("proto_three.c: check_brutus_creation: Brutus Jump Velocity: %f\n", brutus->jump_velocity);
                printf("proto_three.c: check_brutus_creation: Brutus Color: %d\n\n", brutus->color);
                free(brutus);
            }
        }
        else if (is_coin(hex_input) && validate_coin(hex_input))
        {
            printf("proto_three.c: Found coin!\n");
            struct Coin *coin = malloc(sizeof(struct Coin));
            if (coin == NULL) {
                printf("proto_three.c: allocate_mem: Memory was not properly allocated!\n");
            }
            else {
                printf("proto_three.c: allocate_mem: Memory was properly allocated!\n");
                coin->color = get_color(hex_input);
                coin->x_position = get_coin_x_pos(hex_input) + 0.5;
                coin->y_position = get_coin_y_pos(hex_input) + 0.5;
                printf("proto_three.c: check_coin_creation: Coin X Position: %f\n", coin->x_position);
                printf("proto_three.c: check_coin_creation: Coin Color: %d\n\n", coin->color);
                free(coin);
            }
        }
        else
        {
            printf("Invalid input!");
        }
    }
    return 1;
}
