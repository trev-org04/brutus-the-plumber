
# Brutus the Plumber

This is the code repository of the Brutus the Plumber project I created in my Systems I: Introduction to Low-Level Programming and Computer Organization (CSE 2421) class at The Ohio State University. The application is made in C and uses a Makefile to compile all the relevant files into an executable. It makes use of a provided library for the graphics. This project was created as a way to get familiar with the C language in a variety of ways including static variables, arrays, linked lists, function pointers, and more.

## What Is It & How It Works
This code will simulate Brutus in motion with different starting conditions, which will be read in and 
decoded. He can have different colors. He has different velocities in X and in Y. He falls normally for an 
object in a gravity field. He runs along until he hits a wall and can’t move. If he can’t move, he jumps. 
In graphics mode on small screens, he will be rendered with just a few characters, but with ever larger 
screens, he will be rendered with his round shape more obvious.

The input data packs four values into a single number that gets read in and decoded. The decoded 
values are:
* the velocity in X for Brutus, in the range of 1-15
* the upward velocity that is used when Brutus jumps, also in the range of 1-15
* Color – an integer in the range 1-7
* A check bit for validation (0 is a coin and 1 is a mascot)

The program stores mascot data in a struct, which is dynamically allocated, with this format:
* X position
* Y position
* X velocity
* Y velocity
* Jump velocity
* Color
* Loot (the number of coins collected so far)
* A pointer that points to the simulation structure

The mascot input is valid if all of these are true:
* The color is not zero
* The X velocity value is not zero
* The jump velocity value is not zero
* The total number of 1 bits is even

The simulation structure has this format: 
* Elapsed time
* The head pointer for the linked list that stores mascots (a void pointer)
* The head pointer for the linked list that stores coins (another void pointer)

Coin data is also dynamically allocated and stored with this format:
* Color
* X position
* Y position

A coin is valid if it has good parity and the color is non-zero. Coins can have 0 values for x and y.


## Tech Stack
C, Make

## Test Files

There are a number of test files to choose from. Some have valid input and others do not. See the list below:

* x1.btp (valid)
* x1c.btp (valid)
* x2.btp (valid)
* x7.btp (valid)
* x7c.btp (valid)
* xE1.btp (valid)
* xE2.btp (invalid)
* xfast.btp (valid)
* xloot.btp (valid)

Use one of these test files when running the executable.

## Run Project Locally

This project has two modes: graphics and text mode. For graphics mode, edit the `GRAPHICS` variable to be 1 in the `debug.h` file. Similarly, text mode is activated by changing the `GRAPHICS` variable to 0 in `debug.h`.

Clone the repo: 

```bash
git clone https://github.com/trev-org04/brutus-the-plumber.git
```

Create the executable: 

```bash
make -r lab3
```

Run the executable!
```bash
lab3 < [test file name]
```
