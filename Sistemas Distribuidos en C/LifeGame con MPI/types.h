#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>


// Seed to create random numbers
#define SEED 123

// Size of the matrix (calculation for the lonely cells)
#define MATRIX_SIZE 10

// Percentage of initial cells
#define INITIAL_CELLS_PERCENTAGE 30

// Cell size (in pixels)
#define CELL_SIZE  5

// States of the cells
#define CELL_LIVE 1
#define CELL_NEW 2
#define CELL_DEAD 3
#define CELL_CATACLYSM 4
#define CELL_EMPTY 0

// Master process
#define MASTER 0

// End processing
#define END_PROCESSING -1

/** Matrix type */
typedef int* tMatrix;

// Structure to represent a coordinate
typedef struct coordinate{	
	int row;
	int col;	
}tCoordinate;

#endif

