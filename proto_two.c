/* Trevor Gerald */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "structs.h"
#include "proto_two.h"
#include "bits.h"

// Function to read in input from file and determine its validity
int main() 
{
    struct Sim *world = malloc(sizeof(struct Sim));
    if (world == NULL) {
        printf("proto_two.c: allocate_mem: Memory was not properly allocated!\n");
    }
    else {
        printf("proto_two.c: allocate_mem: Memory was properly allocated!\n");
        world->elapsed_time = 0;
        world->mascots = NULL;
        world->coins = NULL;
        printf("proto_two.c: check_world_creation: World Elapsed Time: %f\n", world->elapsed_time);
    }
    return 1;
}
