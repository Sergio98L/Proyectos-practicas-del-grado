#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "types.h"

/**
 * Calculates the coordinate of the cell at the top of the current cell.
 * 
 * @param c Cell's coordinate
 * @return Coordinate of the cell at the top of the current cell.
 */
tCoordinate* getCellUp (tCoordinate* c);

/**
 * Calculates the coordinate of the cell at the bottom of the current cell.
 * 
 * @param c Cell's coordinate
 * @return Coordinate of the cell at the bottom of the current cell.
 */
tCoordinate* getCellDown (tCoordinate* c);


/**
 * Calculates the coordinate of the cell at the left of the current cell.
 * 
 * @param c Cell's coordinate
 * @param worldWidth Width of the world (in number of cells).
 * @return Coordinate of the cell at the left of the current cell.
 */
tCoordinate* getCellLeft (tCoordinate* c, int worldWidth);

/**
 * Calculates the coordinate of the cell at the right of the current cell.
 * 
 * @param c Cell's coordinate
 * @param worldWidth Width of the world (in number of cells).
 * @return Coordinate of the cell at the right of the current cell.
 */
tCoordinate* getCellRight (tCoordinate* c, int worldWidth);

/**
 * Gets the cell at coordinate c located in a world.
 * 
 * @param c Cell's coordinate
 * @param world World where the requested cell is placed.
 * @param worldWidth Width of the world (in number of cells).
 * @return State of the cell at coordinate c.
 */
unsigned short int getCellAtWorld (tCoordinate* c, 
							   	   unsigned short* world,
								   int worldWidth);

/**
 * Sets the cell at coordinate c.
 * 
 * @param c Cell's coordinate
 * @param world World where is plced the requested cell.
 * @param worldWidth Width of the world (in number of cells).
 * @param value New state of the cell. 
 */
void setCellAt (tCoordinate* c, 
			   unsigned short* world,
			   int worldWidth,
			   unsigned short int type);


/** 
 * Inits the world (randomly)
 * 
 * @param w World to be initialized.
 * @param worldWidth Width of the world (in number of cells).
 * @param worldHeight Height of the world (in number of cells).
 */
void initRandomWorld (unsigned short *w, 
					int worldWidth, 
					int worldHeight);

/**
 * Clears the world.
 * 
 * @param w World to be cleared (all cells are set to CELL_EMPTY).
 * @param worldWidth Width of the world (in number of cells).
 * @param worldHeight Height of the world (in number of cells).
 * 
 */
void clearWorld (unsigned short *w, 
				int worldWidth, 
				int worldHeight);

/**
 * 
 * Calculations performed when a cell is dead and has no neighbours.
 * 
 */
void calculateLonelyCell ();

void updateCell (tCoordinate *cell, unsigned short* currentWorld, unsigned short* newWorld, int worldWidth, int worldHeight);

#endif



