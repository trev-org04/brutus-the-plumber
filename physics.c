/* Trevor Gerald */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "structs.h"
#include "physics.h"
#include "output.h"
#include "btp.h"
#include "constants.h"
#include "debug.h"

#define GRAVITY (-10.0)

// Move Brutus using the basic equations of motion
void basic_motion(struct Buckeye *brutus)
{
    brutus->x_position += (DELTA_TIME * brutus->x_velocity);
    brutus->y_position += (DELTA_TIME * brutus->y_velocity) + (0.5 * GRAVITY * DELTA_TIME * DELTA_TIME);
    brutus->y_velocity += (GRAVITY * DELTA_TIME);
}

// Handles hitting the ceiling/floor, jumping, and reaching the flag cases
void handle_edge_cases(struct Buckeye *brutus, double og_x_pos, double og_y_pos, double og_y_vel, double y_adj)
{
    if (y_adj != 0.0) brutus->y_velocity = 0.0;
    if (og_y_vel > 0.0 && brutus->y_velocity == 0.0) print_brutus_ceiling_text(brutus);
    if (og_y_vel < 0.0 && brutus->y_velocity == 0.0) print_brutus_floor_text(brutus);
    if (brutus->x_position == og_x_pos && brutus->y_position == og_y_pos) 
    {
        brutus->y_velocity = brutus->jump_velocity;
        print_brutus_jump_text(brutus);
    }
    if (brutus->x_position >= FLAGPOLE) print_brutus_flag_text();
}

// Moves Brutus while he is not at the flagpole
void move_brutus(void *data) 
{
    struct Buckeye *brutus = data;
    if (brutus->x_position < FLAGPOLE) {
        double og_x_pos = brutus->x_position, og_y_pos = brutus->y_position, og_y_vel = brutus->y_velocity, y_adj;
        basic_motion(brutus);
        brutus->x_position += btp_X_adjustment(brutus->x_position, brutus->y_position);
        brutus->y_position += (y_adj = btp_Y_adjustment(brutus->x_position, brutus->y_position));
        handle_edge_cases(brutus, og_x_pos, og_y_pos, og_y_vel, y_adj);
    }
}

// Gets the appropriate score for Brutus
int get_score(struct Buckeye *brutus) {
    if(brutus->x_position < FLAGPOLE)
	{
	    return (int) (brutus->x_position + brutus->loot);
	}
	else
	{
	    return (int) (brutus->x_position + brutus->y_position + brutus->loot);
	}
}
