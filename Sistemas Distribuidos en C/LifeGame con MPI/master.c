#include "master.h"
void master(int totalIterations, unsigned short *worldA, unsigned short *worldB,SDL_Renderer* renderer,SDL_Window* window,int worldWidth, int worldHeight,int nProcesos,int distModeStatic,int tamGrano, int autoMode){
			
		double iterStartTime,iterEndTime;
		int contIterCataclismo = ITER_CATACLYSM;

		for(int i = 1; i<= totalIterations;++i){
			
			iterStartTime = MPI_Wtime();

			if(i%2 == 0){
				if(distModeStatic){
					staticMaster(worldB,worldA,renderer,window,worldWidth,worldHeight, nProcesos,&contIterCataclismo);
				}
				else{
					dynamicMaster(worldB,worldA,renderer,window,worldWidth,worldHeight, tamGrano, nProcesos,&contIterCataclismo);
				}
				clearWorld(worldB, worldWidth,worldHeight);
			}
			else{

				if(distModeStatic){
					staticMaster(worldA,worldB,renderer,window,worldWidth,worldHeight, nProcesos,&contIterCataclismo);
				}
				else{
					dynamicMaster(worldA,worldB,renderer,window,worldWidth,worldHeight, tamGrano, nProcesos,&contIterCataclismo);
				}
				clearWorld(worldA, worldWidth,worldHeight);
			}
			
			iterEndTime = MPI_Wtime();

			printf("Iteration: %d, Time: %f...\n",i,iterEndTime-iterStartTime);

			if(autoMode == 0){
				getchar();
			}
		}
		endWorkers(nProcesos);
}
void staticMaster(unsigned short *currentWorld, unsigned short *newWorld, SDL_Renderer* renderer,SDL_Window* window,int worldWidth, int worldHeight,int nProcesos,int* contIterCataclismo){

	int isquit = 0;
	SDL_Event event;
	MPI_Status status;

	//Cada iteracion se limpia
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);	
		
	//En esta tabla vamos a guardar las filas donde empiezan el procesamiento cada worker
	int *tablaOrdenacion = (int*) malloc(nProcesos*sizeof(int));

	int numElemsWorker=0;
	int nEnv =0,nRecv =0;
	int count=0;
	int tag =0;
	
	//Como es estatico vamos a dividir a partes iguales el vector entre los workers
	//nProcesos -1 porque tenemos nProcesos -1 workers
	//Es el numero de filas que procesa cada worker
	numElemsWorker = worldHeight/(nProcesos-1);

	int filasAReservar = numElemsWorker+4;
	MPI_Bcast(&filasAReservar, 1, MPI_INT, 0, MPI_COMM_WORLD);

	//Punteros de cada parte del vector
	unsigned short* top =  currentWorld+(worldWidth * (worldHeight-1));
 	unsigned short* area = currentWorld;
	unsigned short* bottom = currentWorld + (worldWidth*numElemsWorker);

	int filasRestantes;
	//Empezamos en i=1 porque el proceso 0 es el master
	for(int i =1; i< nProcesos;i++){
		//En caso del primer worker indicamos que empieza en la fila 0, el segundo worker en la fila 0 + numElemsWorker, etc
		tablaOrdenacion[i] = nEnv;

		//Si es el ultimo worker le enviamos todas las filas que falten por computar
		if(i == (nProcesos-1)){
			bottom = currentWorld;			
			numElemsWorker = worldHeight - nEnv;			
		}

		MPI_Send(&numElemsWorker, 1,MPI_INT,i,tag,MPI_COMM_WORLD);
		MPI_Send(top, worldWidth,MPI_SHORT,i,tag,MPI_COMM_WORLD);
		MPI_Send(area, numElemsWorker*worldWidth,MPI_SHORT,i,tag,MPI_COMM_WORLD);		    
        MPI_Send(bottom, worldWidth,MPI_SHORT,i,tag,MPI_COMM_WORLD);	
		nEnv += numElemsWorker;	 

        area = bottom;
        top = currentWorld+(worldWidth*(nEnv-1));
        bottom = currentWorld+(worldWidth*(nEnv+numElemsWorker));			
	}

    while(nRecv < worldHeight){
        MPI_Recv(&count, 1, MPI_INT, MPI_ANY_SOURCE,tag,MPI_COMM_WORLD,&status);
        MPI_Recv(newWorld + (tablaOrdenacion[status.MPI_SOURCE]*worldWidth),count*worldWidth,MPI_SHORT,status.MPI_SOURCE,tag,MPI_COMM_WORLD,&status);
        nRecv+=count;
    }


	comprobarCataclismo(contIterCataclismo,currentWorld, newWorld, worldWidth, worldHeight);
   	drawWorld(currentWorld,newWorld,renderer,0, worldHeight, worldWidth, worldHeight);
	free(tablaOrdenacion);

		
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
        
}
void dynamicMaster(unsigned short *currentWorld, unsigned short *newWorld, SDL_Renderer* renderer,SDL_Window* window,int worldWidth, int worldHeight, int grano,int nProcesos,int* contIterCataclismo){

	int numElems=0,tag;
	int nEnv =0,nRecv =0;
	int n=0;
	MPI_Status status;
	tag =0;

	int *tablaOrdenacion = (int*) malloc(nProcesos*sizeof(int));

	//Cada iteracion se limpia
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);	
		
	//Top es la fila contigua superior
	unsigned short* top =  currentWorld+(worldWidth * (worldHeight-1));
	//Area es la zona que le enviamos al worker para que procese
 	unsigned short* area = currentWorld;
	//Bottom es la fila contigua inferior
	unsigned short* bottom = currentWorld + (worldWidth*grano);

	numElems = grano;
	int filasAReservar = numElems+2;
	MPI_Bcast(&filasAReservar, 1, MPI_INT, 0, MPI_COMM_WORLD);

	for(int i=1; i<nProcesos && nEnv < worldHeight;i++){
		
		tablaOrdenacion[i] = nEnv;

		//Comprobamos si quedan suficientes filas sin worker como para pasarle el grano entero
		if((worldHeight - nEnv) <= grano){
			numElems = worldHeight - nEnv;
			bottom = currentWorld;
		}

		MPI_Send(&numElems, 1,MPI_INT,i,tag,MPI_COMM_WORLD);
		MPI_Send(top, worldWidth,MPI_SHORT,i,tag,MPI_COMM_WORLD);
		MPI_Send(area, numElems*worldWidth,MPI_SHORT,i,tag,MPI_COMM_WORLD);		    
        MPI_Send(bottom, worldWidth,MPI_SHORT,i,tag,MPI_COMM_WORLD);

		nEnv +=numElems;

		area = bottom;
        top = currentWorld+(worldWidth*(nEnv-1));
        bottom = currentWorld+(worldWidth*(nEnv+grano));
	}

	while(nRecv < worldHeight){

		MPI_Recv(&numElems, 1, MPI_INT, MPI_ANY_SOURCE,tag,MPI_COMM_WORLD,&status);
		MPI_Recv(newWorld + (tablaOrdenacion[status.MPI_SOURCE]*worldWidth),numElems*worldWidth,MPI_SHORT,status.MPI_SOURCE,tag,MPI_COMM_WORLD,&status);
		//drawWorld(currentWorld,newWorld,renderer, tablaOrdenacion[status.MPI_SOURCE], tablaOrdenacion[status.MPI_SOURCE]+numElems, worldWidth, worldHeight);
		nRecv += numElems;
		//Comparamos con el numero de filas porque nEnv contiene el numero de filas enviadas
		if(nEnv <worldHeight){			

			tablaOrdenacion[status.MPI_SOURCE] =nEnv;
			numElems = (worldHeight-nEnv)>= grano ? grano :  worldHeight - nEnv;

			if(numElems == (worldHeight - nEnv)){
				 bottom = currentWorld;
			}

			MPI_Send(&numElems, 1,MPI_INT,status.MPI_SOURCE,tag,MPI_COMM_WORLD);
			MPI_Send(top, worldWidth,MPI_SHORT,status.MPI_SOURCE,tag,MPI_COMM_WORLD);
			MPI_Send(area, numElems*worldWidth,MPI_SHORT,status.MPI_SOURCE,tag,MPI_COMM_WORLD);
			MPI_Send(bottom, worldWidth,MPI_SHORT,status.MPI_SOURCE,tag,MPI_COMM_WORLD);
			nEnv += numElems;
			area = bottom;
			top = currentWorld+(worldWidth*(nEnv-1));
			bottom = currentWorld+(worldWidth*(nEnv+numElems));
		}
	}


	comprobarCataclismo(contIterCataclismo,currentWorld, newWorld, worldWidth, worldHeight);
	
	drawWorld(currentWorld,newWorld,renderer,0, worldHeight, worldWidth, worldHeight);
	free(tablaOrdenacion);

	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
}

void comprobarCataclismo(int* contIterCataclismo,unsigned short *currentWorld, unsigned short *newWorld,int worldWidth, int worldHeight){
	(*contIterCataclismo)++;
	// Lógica del cataclismo
	if ((double)rand() / RAND_MAX < (PROB_CATACLYSM/100) && *contIterCataclismo >= ITER_CATACLYSM) {
		// Se produjo un cataclismo, poner la última columna y la primera a cero
		for (int i = 0; i < worldHeight; i++) {

			currentWorld[i * worldWidth] = CELL_CATACLYSM;                // Primera columna
			currentWorld[(i + 1) * worldWidth - 1] = CELL_CATACLYSM;      // Última columna

			newWorld[i * worldWidth] = CELL_EMPTY;                // Primera columna
			newWorld[(i + 1) * worldWidth - 1] = CELL_EMPTY;      // Última columna

		}
		*contIterCataclismo =0;
		
    	printf("Se produjo un cataclismo. Esperando %d iteraciones hasta el próximo cataclismo...\n", ITER_CATACLYSM);
	}
}
void endWorkers(int size){
    int fin = END_PROCESSING;
    for(int i = 1; i<size; ++i)
    	MPI_Send(&fin, 1,MPI_INT,i,0,MPI_COMM_WORLD);
}