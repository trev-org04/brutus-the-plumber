/* Trevor Gerald */

#include <stdio.h>
#include <math.h>

#include "structs.h"
#include "sim.h"
#include "libll.h"
#include "lists.h"
#include "debug.h"
#include "constants.h"
#include "physics.h"
#include "output.h"
#include "memory.h"

#define CLOSE_ENOUGH (0.5)

// Determine whether the mascot is at the pole
static bool game_on(void *data, void *helper)
{
    struct Buckeye *brutus = data;
    if (brutus->x_position < FLAGPOLE) return true;
    return false;
}

// Determine whether a mascot has a greater y-position value than the next
static bool sort_by_y_value(void *obj, void *obj2) 
{
    struct Buckeye *brutus = obj;
    struct Buckeye *brutus2 = obj2;
    return brutus->y_position > brutus2->y_position;
}

// Determine whether a mascot has a greater score than the next
static bool sort_by_point_value(void *obj, void *obj2) 
{
    struct Buckeye *brutus = obj;
    struct Buckeye *brutus2 = obj2;
    int score = (int) brutus->x_position + brutus->y_position + brutus->loot;
    int score2 = (int) brutus2->x_position + brutus2->y_position + brutus2->loot;
    return score > score2;
}

// Determines whether a coin is the correct coin for a mascot
static bool is_my_coin(void *coin_data, void *mascot_data)
{
    struct Coin *coin = coin_data;
    struct Buckeye *brutus = mascot_data;
    double x_distance = coin->x_position - brutus->x_position;
    double y_distance = coin->y_position - brutus->y_position;
    double distance = sqrt((x_distance * x_distance) + (y_distance * y_distance));
    return (coin->color == brutus->color) && (distance <= CLOSE_ENOUGH);
}

// Frees a coin object from memory
static void delete_coin(void *data)
{
    struct Coin *coin = data;
    free_memory(coin);
}

// Function used to determine whether coins are collected by mascots
static void sweep_coins(void *data)
{
    struct Buckeye *brutus = data;
    int coins_collected = deleteSome(&(brutus->world->coins), is_my_coin, brutus, delete_coin, TEXT);
    if (coins_collected > 0) print_brutus_loot_text(brutus), brutus->loot += coins_collected;
}

// Starts a fresh run for the simulation
void run_sim(void *data)
{    
    struct Sim *world = data;
    while(any(world->mascots, game_on, world->mascots)) 
    {
        sort(world->mascots, sort_by_y_value);
        master_output(world);
        world->elapsed_time += DELTA_TIME;
        iterate(world->mascots, move_brutus);
        iterate(world->mascots, sweep_coins);
    }
    sort(world->mascots, sort_by_point_value);
    final_output(world);
    clear_lists(world);
}
