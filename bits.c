/* Trevor Gerald */

#include <stdio.h>
#include <stdbool.h>

#include "bits.h"
#include "debug.h"

#define COLOR_BIT_MASK 7
#define LOWER_ORDER_BIT_MASK 1
#define COLOR_HEX_MASK 0xF000
#define JUMP_HEX_MASK 0x0F00
#define X_VEL_HEX_MASK 0x00F0
#define SHIFT_VALUE 4

// Returns the parity of the input
static int get_parity(unsigned short run_input) 
{
    if (DEBUG) printf("bits.c: get_parity: Input: %hX\n", run_input);
    int parity = 0;
    while (run_input)
    {
        parity ^= run_input & 1;
        run_input >>= 1;
    }
    if (DEBUG) printf("bits.c: get_parity: Parity of Input: %d\n\n", parity);
    return parity;
}

// Gets the color from the leftmost group of four bits
int get_color(unsigned short run_input)
{
    if (DEBUG) printf("bits.c: get_color: Input: %hX\n", run_input);
    int color;
    // Mask all other bits other than color bits (save first four bits)
    color = run_input & COLOR_HEX_MASK;
    // Right shift color bits to the start of the int
    color >>= (SHIFT_VALUE * 3);
    // Mask check bit
    color &= COLOR_BIT_MASK;
    if (DEBUG) printf("bits.c: get_color: Color of Input: %d\n\n", color);
    return color;
}

// Gets the jump velocity from the second leftmost group of four bits
int get_jump_vel(int run_input)
{
    if (DEBUG) printf("bits.c: get_jump_vel: Input: %hX\n", run_input);
    int jump_vel;
    // Mask all other bits other than jump bits (save second group of four bits)
    jump_vel = run_input & JUMP_HEX_MASK;
    // Right shift jump bits to the start of the int
    jump_vel >>= (SHIFT_VALUE * 2);
    if (DEBUG) printf("bits.c: get_jump_vel: Jump Velocity of Input: %d\n\n", jump_vel);
    return jump_vel;
}

// Gets the coin X-position from the second leftmost group of four bits
int get_coin_x_pos(int run_input)
{
    if (DEBUG) printf("bits.c: get_coin_x: Input: %hX\n", run_input);
    int coin_x_pos;
    // Mask all other bits other than jump bits (save second group of four bits)
    coin_x_pos = run_input & JUMP_HEX_MASK;
    // Right shift jump bits to the start of the int
    coin_x_pos >>= (SHIFT_VALUE * 2);
    if (DEBUG) printf("bits.c: get_coin_x: Coin X Position of Input: %d\n\n", coin_x_pos);
    return coin_x_pos;
}

// Gets the X-velocity from the third leftmost group of four bits
int get_x_vel(unsigned short run_input)
{
    if (DEBUG) printf("bits.c: get_x_vel: Input: %hX\n", run_input);
    int x_vel;
    // Mask all other bits other than x velocity bits (save third group of four bits)
    x_vel = run_input & X_VEL_HEX_MASK;
    // Right shift x velocity bits to the start of the int
    x_vel >>= SHIFT_VALUE;
    if (DEBUG) printf("bits.c: get_x_vel: X-Velocity of Input: %d\n\n", x_vel);
    return x_vel;
}


// Gets the coin Y-position from the third leftmost group of four bits
int get_coin_y_pos(unsigned short run_input)
{
    if (DEBUG) printf("bits.c: get_coin_y_pos: Input: %hX\n", run_input);
    int coin_y_pos;
    // Mask all other bits other than x velocity bits (save third group of four bits)
    coin_y_pos = run_input & X_VEL_HEX_MASK;
    // Right shift x velocity bits to the start of the int
    coin_y_pos >>= SHIFT_VALUE;
    if (DEBUG) printf("bits.c: get_coin_y_pos: X-Velocity of Input: %d\n\n", coin_y_pos);
    return coin_y_pos;
}

// Determines whether the given input is a mascot or not
bool is_mascot(unsigned short run_input) {
    if (DEBUG) printf("bits.c: is_mascot: Input: %hX\n", run_input);
    int lower_order_bit;
    lower_order_bit = run_input & LOWER_ORDER_BIT_MASK;
    if (DEBUG) printf("bits.c: is_mascot: Lower Order Bit of Input: %d\n\n", lower_order_bit);
    return lower_order_bit == 1;
}

// Determines whether the given input is a coin or not
bool is_coin(unsigned short run_input) {
    if (DEBUG) printf("bits.c: is_mascot: Input: %hX\n", run_input);
    int lower_order_bit;
    lower_order_bit = run_input & LOWER_ORDER_BIT_MASK;
    if (DEBUG) printf("bits.c: is_mascot: Lower Order Bit of Input: %d\n\n", lower_order_bit);
    return lower_order_bit == 0;
}

// Validates the provided input to see if it is a mascot and prints an error message if it is not
bool validate_mascot(unsigned short run_input) 
{
    if (DEBUG) printf("bits.c: validate_input: Input: %hX\n", run_input);
    int parity = get_parity(run_input), color = get_color(run_input), jump_vel = get_jump_vel(run_input), x_vel = get_x_vel(run_input);
    if (DEBUG) printf("bits.c: validate_input: Parity: %d, Color: %d, Jump Velocity: %d, X-Velocity: %d\n\n", parity, color, jump_vel, x_vel);
    if ((parity != 0) || (color > 7 || color < 1) || (jump_vel == 0) || (x_vel == 0)) return false;
    return true;
}

// Validates the provided input to see if it is a coin and prints an error message if it is not
bool validate_coin(unsigned short run_input) 
{
    if (DEBUG) printf("bits.c: validate_coin: Input: %hX\n", run_input);
    int parity = get_parity(run_input), color = get_color(run_input);
    if (DEBUG) printf("bits.c: validate_coin: Parity: %d, Color: %d\n\n", parity, color);
    if ((parity != 0) || (color > 7 || color < 1)) return false;
    return true;
}
