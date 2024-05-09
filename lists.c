/* Trevor Gerald */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "lists.h"
#include "bits.h"
#include "debug.h"
#include "memory.h"
#include "libll.h"

// Determines whether a coin has a greater color value than the next one
static bool coin_sort_by_color(void *val, void *val2) 
{
    struct Coin *coin = val;
    struct Coin *coin2 = val2;
    return coin->color > coin2->color;
}

// Fills a coin struct with the appropriate data
static void *fill_coin_data(struct Coin *coin, int color, int x_pos, int y_pos)
{
    coin->color = color;
    coin->x_position = x_pos + 0.5;
    coin->y_position = y_pos + 0.5;
    return coin;
}

// Creates coin struct object and inserts into world list
void deal_with_coin(unsigned short hex_input, void *world_data)
{
    struct Sim *world = world_data;
    struct Coin *coin = allocate_memory(sizeof(struct Coin));
    if (coin != NULL)
    {
        coin = fill_coin_data(coin, get_color(hex_input), get_coin_x_pos(hex_input), get_coin_y_pos(hex_input));
        if(!insert(&(world->coins), coin, coin_sort_by_color, TEXT)) free_memory(coin);
    }
}

// Determines whether a mascot has a greater y-position value than the next one
static bool mascot_sort_by_y_order(void *val, void *val2) 
{
    struct Buckeye *brutus = val;
    struct Buckeye *brutus2 = val2;
    return brutus->y_position > brutus2->y_position;
}

// Fills a mascot struct with the appropriate data
static void *fill_mascot_data(struct Buckeye *brutus, int color, int x_vel, int jump_vel, void *data)
{
    brutus->x_position = 0.5;
    brutus->y_position = 0.5;
    brutus->x_velocity = x_vel;
    brutus->y_velocity = 0;
    brutus->jump_velocity = jump_vel;
    brutus->color = color;
    brutus->loot = 0;
    brutus->world = data;
    return brutus;
}

// Creates mascot struct object and inserts into world list
void deal_with_mascot(unsigned short hex_input, void *world_data)
{
    struct Sim *world = world_data;
    struct Buckeye *brutus = allocate_memory(sizeof(struct Buckeye));
    if (brutus != NULL)
    {
        brutus = fill_mascot_data(brutus, get_color(hex_input), get_x_vel(hex_input), get_jump_vel(hex_input), world);
        if(!insert(&(world->mascots), brutus, mascot_sort_by_y_order, TEXT)) free_memory(brutus);
    }
}
