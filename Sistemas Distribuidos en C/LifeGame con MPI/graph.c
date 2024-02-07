#include "graph.h"

void drawCell (tCoordinate *cell, unsigned short type, SDL_Renderer* renderer){

	SDL_Rect fillRect = {cell->col*CELL_SIZE, cell->row*CELL_SIZE, CELL_SIZE, CELL_SIZE};

		// Set color for this cell
		switch(type){
	
			case CELL_NEW:
				SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
			break;
	
			case CELL_LIVE: 
				SDL_SetRenderDrawColor(renderer, 0x00, 0x99, 0x00, 0x00);
			break;
		
			case CELL_DEAD: 
				SDL_SetRenderDrawColor(renderer, 0xCC, 0x00, 0x00, 0x00);
			break;
		
			case CELL_EMPTY: 
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
			break;
			
			case CELL_CATACLYSM: 
				SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0x00);
			break;
		}

		// Render cell (point or rectangle)
		if (CELL_SIZE == 1)
			SDL_RenderDrawPoint(renderer, cell->col, cell->row);
		else
			SDL_RenderFillRect (renderer, &fillRect);
}

void drawWorld (unsigned short *currentWorld, 
			    unsigned short *newWorld, 
				SDL_Renderer* renderer,
				int firstRow,
				int lastRow,
				int worldWidth, 
				int worldHeight){
	
	tCoordinate cell;

		for (int col=0; col<worldWidth; col++)
			for (int row=firstRow; row<=lastRow; row++){
			
				cell.row = row;
				cell.col = col;			
				
				// New cell
				if (getCellAtWorld(&cell, currentWorld, worldWidth) == CELL_EMPTY && getCellAtWorld(&cell, newWorld, worldWidth) == CELL_LIVE)
					drawCell (&cell, CELL_NEW, renderer);
				
				// Current cell remains alive
				else if (getCellAtWorld(&cell, currentWorld, worldWidth) == CELL_LIVE && getCellAtWorld(&cell, newWorld, worldWidth) == CELL_LIVE)				
					drawCell (&cell, CELL_LIVE, renderer);
					
				// Current cell dies
				else if (getCellAtWorld(&cell, currentWorld, worldWidth) == CELL_LIVE && getCellAtWorld(&cell, newWorld, worldWidth) == CELL_EMPTY)					
					drawCell (&cell, CELL_DEAD, renderer);
					
				// Cataclysm cell
				else if (getCellAtWorld(&cell, currentWorld, worldWidth) == CELL_CATACLYSM && getCellAtWorld(&cell, newWorld, worldWidth) == CELL_EMPTY)					
					drawCell (&cell, CELL_CATACLYSM, renderer);
		}	
	
}

void saveImage (SDL_Renderer* renderer, 
				char* fileName, 
				int screenWidth, 
				int screenHeight){

	const Uint32 format = SDL_PIXELFORMAT_RGB24;

		SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(SDL_SWSURFACE, screenWidth, screenHeight, 24, format);		
		SDL_RenderReadPixels(renderer, NULL, format, surface->pixels, surface->pitch);
		SDL_LockSurface (surface);
		SDL_SaveBMP(surface, fileName);		
		SDL_UnlockSurface (surface);
		SDL_FreeSurface(surface);
}
