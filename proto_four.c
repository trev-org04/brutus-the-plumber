/* Trevor Gerald */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "proto_four.h"
#include "libll.h"

// Determines whether a string comes before the next
static bool letter_comp(void *val, void *val2) 
{
    char *str = val;
    char *str2 = val2;
    return *str < *str2;
}

// Prints the given string
static void print_str(void *val) 
{
    char *str = val;
    printf("%s\n", str);
}

// Function to create strings and input them into the linked list
int main() 
{
    int rval;
    void *head_ptr = NULL;
    printf("head_ptr: %p\n", head_ptr);
    rval = insert(&head_ptr, "brutus", letter_comp, 1);
    printf("head_ptr: %p\n", head_ptr);
    if (rval) 
    {
        rval = insert(&head_ptr, "coin", letter_comp, 1);
        printf("head_ptr: %p\n", head_ptr);
    }
    if (rval) 
    {
        rval = insert(&head_ptr, "bottle", letter_comp, 1);
        printf("head_ptr: %p\n", head_ptr);
    }
    printf("head_ptr: %p\n", head_ptr);
    iterate(head_ptr, print_str);
    return rval;
}
