/* Trevor Gerald */
/* Parts of this code are adapted from the Lab 3 output.c file */

#include <stdio.h>
#include <stdbool.h>

#include "structs.h"
#include "output.h"
#include "n2.h"
#include "btp.h"
#include "debug.h"
#include "physics.h"
#include "constants.h"
#include "libll.h"

// Prints the jump message for Brutus depending on the mode
void print_brutus_jump_text(struct Buckeye *brutus)
{
    if(TEXT)printf("Brutus jumps at %8.5lf, %8.5lf\n", brutus->x_position, brutus->y_position);
	if(GRAPHICS)btp_status("Brutus jumps");
}

// Prints the ceiling message for Brutus depending on the mode
void print_brutus_ceiling_text(struct Buckeye *brutus)
{
	if(TEXT)printf("Brutus hits the ceiling at %8.5lf, %8.5lf\n", brutus->x_position, brutus->y_position);
	if(GRAPHICS)btp_status("Brutus hits the ceiling");}

// Prints the floor message for Brutus depending on the mode
void print_brutus_floor_text(struct Buckeye *brutus)
{
	if(TEXT)printf("Brutus hits the floor at %8.5lf, %8.5lf\n", brutus->x_position, brutus->y_position);
	if(GRAPHICS)btp_status("Brutus hits the floor");
}

// Prints the loot message for Brutus depending on the mode
void print_brutus_loot_text(struct Buckeye *brutus)
{
	if(TEXT)printf("Brutus finds loot at %8.5lf, %8.5lf\n", brutus->x_position, brutus->y_position);
	if(GRAPHICS)btp_status("Brutus finds some loot");
}

// Prints the flag message for Brutus depending on the mode
void print_brutus_flag_text()
{
	if(GRAPHICS) btp_status("Brutus makes it to the flag");
	if(TEXT) printf("\nBrutus makes it to the flag!\n");
}

// Prints the appropriate text for a coin for text mode
// Adapted from the Lab 3 output.c reference file
static void print_coin(void * data)
{
	struct Coin *cash = data;
	printf("%d    (%8.5lf, %8.5lf)\n", cash->color, cash->x_position, cash->y_position);
}

// Print the appropriate text for Brutus for text mode
// Adapted from the Lab 3 output.c reference file
static void print_brutus(void * data)
{
	struct Buckeye *brutus = data;
	printf("%3d    %d    (%8.5lf, %8.5lf)    (%9.5lf, %9.5lf)\n", get_score(brutus), brutus->color, brutus->x_position, brutus->y_position, brutus->x_velocity, brutus->y_velocity);
}

// Prints the appropriate text for text mode
static void text_output(struct Sim *world)
{
    printf("\nPts    C    (__X_____, __Y_____)    (__VX_____, __VY_____) ET=%8.5lf\n", world->elapsed_time);
    iterate(world->mascots, print_brutus);
    printf( "\nC    (__X_____, __Y_____)\n" );
    iterate(world->coins, print_coin);
}

// Draws a coin based on the color and position
// Adapted from the Lab 3 output.c reference file
static void draw_coin(void * data)
{
	struct Coin *cash = data;
	btp_coin( cash->color, cash->x_position, cash->y_position);
}

// Draws Brutus based on the color and position
// Adapted from the Lab 3 output.c reference file
static void draw_brutus(void * data)
{
	struct Buckeye *brutus = data;
	btp_brutus(get_score(brutus), brutus->color, brutus->x_position, brutus->y_position, true);
}

// Updates graphics appropriately for graphics mode
static void master_draw(struct Sim *world)
{
	btp_clear();
	btp_time((int) (1000 * world->elapsed_time));
	iterate(world->mascots, draw_brutus);
	iterate(world->coins, draw_coin);
	btp_refresh();
	microsleep((unsigned int) (DELTA_TIME * 1000000));
}

// Controls all output for a given run based on the current mode
void master_output(void *data)
{
    struct Sim *world = data;
    if (TEXT) text_output(world);
    if (GRAPHICS) master_draw(world);
}

// Displays the approprate final output when a run is complete based on the current mode
void final_output(struct Sim *world) 
{
    if (TEXT)
    {
        text_output(world);
    }
    if (GRAPHICS) 
    {
        double time_between_runs = 0.0;
        while (time_between_runs < 4.0) 
        {
            time_between_runs += DELTA_TIME;
            master_draw(world);
        }
    }
}

// Output message if hex input is invalid
// Adapted from the Lab 3 output.c reference file
void output_bad_bits(unsigned short code)
{
	if(TEXT) printf("ERROR: invalid input: hex %X\n", code);
}

// Output the number of tokens that scanf read
// Adapted from the Lab 3 output.c reference file
void output_scanf(int tokens)
{
	if(TEXT) printf("scanf returned %d\n", tokens);
}

