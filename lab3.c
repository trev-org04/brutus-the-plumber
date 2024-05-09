/* Trevor Gerald */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "structs.h"
#include "lab3.h"
#include "debug.h"
#include "sim.h"
#include "input.h"
#include "btp.h"
#include "n2.h"

#define RVAL_BAD_INPUT 2;
#define RVAL_BAD_INIT 1;

// Creates a struct Sim object with the correct init values
static void *initialize_world()
{
    struct Sim *world = malloc(sizeof(struct Sim));
    world->elapsed_time = 0;
    world->mascots = NULL;
    world->coins = NULL;
    return world;
}

// Starts a run (if it can be started) and prints the return value and total runtime
int main()
{
    int rval = EXIT_SUCCESS;
    double start = now();
    struct Sim *world = initialize_world(world);
    
    if(TEXT || (GRAPHICS && btp_initialize(DEBUG))) 
    {
        if (good_input_run(world)) 
        {
            run_sim(world);
        }
        else
        {
            rval = RVAL_BAD_INPUT;
        }
        if(GRAPHICS) btp_teardown();   
    }
    else
    {
        rval = RVAL_BAD_INIT;
    }

    printf("Returning %d\n", rval);
    printf("Total runtime is %.9lf seconds\n", now() - start);
    return rval;
}
