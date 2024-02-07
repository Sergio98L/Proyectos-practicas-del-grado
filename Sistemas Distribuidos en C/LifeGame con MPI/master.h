#include "graph.h"
#include "mpi.h"

// Enables/Disables the log messages from the master process
#define DEBUG_MASTER 0

// Probability that a cataclysm may occur [0-100] :(
#define PROB_CATACLYSM 10

// Number of iterations between two possible cataclysms
#define ITER_CATACLYSM 5


void staticMaster(unsigned short *currentWorld, unsigned short *newWorld, SDL_Renderer* renderer,SDL_Window* window,int worldWidth, int worldHeight,int nProcesos,int* contIterCataclismo);
void dynamicMaster(unsigned short *currentWorld, unsigned short *newWorld, SDL_Renderer* renderer,SDL_Window* window,int worldWidth, int worldHeight, int grano,int nProcesos,int* contIterCataclismo);
void master(int totalIterations, unsigned short *worldA, unsigned short *worldB,SDL_Renderer* renderer,SDL_Window* window,int worldWidth, int worldHeight,int nProcesos,int distModeStatic,int tamGrano, int autoMode);
void endWorkers(int size);
void comprobarCataclismo(int* contIterCataclismo,unsigned short *currentWorld, unsigned short *newWorld,int worldWidth, int worldHeight);