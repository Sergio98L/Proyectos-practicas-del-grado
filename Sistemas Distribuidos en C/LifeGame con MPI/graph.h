#include "world.h"
#include <SDL.h>

/**
 * Draws a cell in a renderer.
 * 
 * @param cell Cell's coordinates. 
 * @param type Type of the cell.
 * @param renderer Rendered where the cell is drawn.
 */
void drawCell (tCoordinate *cell, 
				unsigned short type, 
				SDL_Renderer* renderer);

/**
 * Draws a world.
 * 
 * @param currentWorld Current state of the world. 
 * @param newWorld Next state of the world.
 * @param renderer Renderer where the cell is drawn.
 * @param firstRow First row to be drawn.
 * @param lastRow Last row to be drawn.
 * @param worldWidth Width of the world (in number of cells).
 * @param worldHeight Height of the world (in number of cells).
 */
void drawWorld (unsigned short *currentWorld, 
			    unsigned short *newWorld, 
				SDL_Renderer* renderer,
				int firstRow,
				int lastRow,
				int worldWidth, 
				int worldHeight);

/**
 * Saves the current state of the screen in a bmp image.
 * 
 * @param renderer Renderer that contais the world (in pixels).
 * @param fileName Name of the output bmp file.
 * @param screenWidth Width of the screen (in pixels).
 * @param screenHeight Height of the screen (in pixels).
 * 
 */
void saveImage (SDL_Renderer* renderer, 
				char* fileName, 
				int screenWidth, 
				int screenHeight);
