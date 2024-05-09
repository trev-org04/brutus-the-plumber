/* Trevor Gerald */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "structs.h"
#include "memory.h"
#include "debug.h"
#include "bits.h"
#include "libll.h"

// Allocate memory for a given pointer based on its size
void *allocate_memory(int size)
{
    static int objects = 0;
    void *pointer;
    (size == 56) ? (pointer = malloc(sizeof(struct Buckeye))) : (pointer = malloc(sizeof(struct Sim)));
    if (pointer == NULL) {
        if (TEXT) printf("memory.c: allocate_brutus: Memory was not properly allocated!\n");
    }
    else {
        objects++;
        if (TEXT) printf("DIAGNOSTIC: allocation #%d allocated %d bytes\n", objects, size);
    }
    return pointer;
}

// Get the current value of how many objects have been freed
static int get_count_value(int val)
{
    static int count;
    if (val) count = val;
    return count;
}

// Free the memory for the pointer that is given to the function
void free_memory(void *pointer)
{
    static int count = 1;
    if (pointer){
        free(pointer);
        pointer = NULL;
    }
    else {
        if(TEXT) printf("ERROR: tried to free NULL pointer.\n");
    }
    if (TEXT) printf("DIAGNOSTIC: %d objects freed\n", count);
    get_count_value(count);
    count++;
}

// Determine whether a mascot should be deleted from the list
static bool should_delete_mascot(void *data, void *helper)
{
    return true;
}

// Determine whether a coin should be deleted from the list
static bool should_delete_coin(void *data, void *helper)
{
    return true;
}

// Clear the mascots and coins from their respective lists
void clear_lists(void *data)
{
    struct Sim *world = data;
    int prev_count = get_count_value(0);
    if (TEXT) printf("Clearing mascots list...\n");
    deleteSome(&(world->mascots), should_delete_mascot, world, free_memory, TEXT);
    if (TEXT) printf("     %d mascots deleted.\n", get_count_value(0) - prev_count), printf("Clearing coins list...\n");
    prev_count = get_count_value(0);
    deleteSome(&(world->coins), should_delete_coin, world, free_memory, TEXT);
    if (TEXT) printf("     %d coins deleted.\n", get_count_value(0) - prev_count);
}
