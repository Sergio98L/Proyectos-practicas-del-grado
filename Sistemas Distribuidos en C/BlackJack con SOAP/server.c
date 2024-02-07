#include "server.h"
#include <pthread.h>

/** Shared array that contains all the games. */
tGame games[MAX_GAMES];

void initGame (tGame *game){

	// Init players' name
	memset (game->player1Name, 0, STRING_LENGTH);	
	memset (game->player2Name, 0, STRING_LENGTH);

	// Alloc memory for the decks		
	clearDeck (&(game->player1Deck));	
	clearDeck (&(game->player2Deck));	
	initDeck (&(game->gameDeck));
	
	// Bet and stack
	game->player1Bet = 0;
	game->player2Bet = 0;
	game->player1Stack = INITIAL_STACK;
	game->player2Stack = INITIAL_STACK;
	
	// Game status variables
	game->endOfGame = FALSE;
	game->status = gameEmpty;
}

void initServerStructures (struct soap *soap){

	if (DEBUG_SERVER)
		printf ("Initializing structures...\n");

	// Init seed
	srand (time(NULL));

	// Init each game (alloc memory and init)
	for (int i=0; i<MAX_GAMES; i++){
		games[i].player1Name = (xsd__string) soap_malloc (soap, STRING_LENGTH);
		games[i].player2Name = (xsd__string) soap_malloc (soap, STRING_LENGTH);

		if ((rand()%2)==0)
			games[i].currentPlayer = player1;
		else
			games[i].currentPlayer = player2;

		allocDeck(soap, &(games[i].player1Deck));	
		allocDeck(soap, &(games[i].player2Deck));	
		allocDeck(soap, &(games[i].gameDeck));
		initGame (&(games[i]));

		pthread_mutex_init(&games[i].mutexPlayers,NULL);
		pthread_cond_init(&games[i].cond,NULL);
	}	
}

void initDeck (blackJackns__tDeck *deck){

	deck->__size = DECK_SIZE;

	for (int i=0; i<DECK_SIZE; i++)
		deck->cards[i] = i;
}

void clearDeck (blackJackns__tDeck *deck){

	// Set number of cards
	deck->__size = 0;

	for (int i=0; i<DECK_SIZE; i++)
		deck->cards[i] = UNSET_CARD;
}

tPlayer calculateNextPlayer (tPlayer currentPlayer){
	return ((currentPlayer == player1) ? player2 : player1);
}

unsigned int getRandomCard (blackJackns__tDeck* deck){

	unsigned int card, cardIndex, i;

		// Get a random card
		cardIndex = rand() % deck->__size;
		card = deck->cards[cardIndex];

		// Remove the gap
		for (i=cardIndex; i<deck->__size-1; i++)
			deck->cards[i] = deck->cards[i+1];

		// Update the number of cards in the deck
		deck->__size--;
		deck->cards[deck->__size] = UNSET_CARD;

	return card;
}

void copyGameStatusStructure (blackJackns__tBlock* status, char* message, blackJackns__tDeck *newDeck, int newCode){

	// Copy the message
	memset((status->msgStruct).msg, 0, STRING_LENGTH);
	strcpy ((status->msgStruct).msg, message);
	(status->msgStruct).__size = strlen ((status->msgStruct).msg);

	// Copy the deck, only if it is not NULL
	if (newDeck->__size > 0)
		memcpy ((status->deck).cards, newDeck->cards, DECK_SIZE*sizeof (unsigned int));	
	else
		(status->deck).cards = NULL;

	(status->deck).__size = newDeck->__size;

	// Set the new code
	status->code = newCode;	
}

unsigned int calculatePoints (blackJackns__tDeck *deck){

	unsigned int points = 0;
		
		for (int i=0; i<deck->__size; i++){

			if (deck->cards[i] % SUIT_SIZE < 9)
				points += (deck->cards[i] % SUIT_SIZE) + 1;
			else
				points += FIGURE_VALUE;
		}

	return points;
}


void *processRequest(void *soap){

	pthread_detach(pthread_self());

	
	//printf ("Processing a new request...");

	soap_serve((struct soap*)soap);
	soap_destroy((struct soap*)soap);
	soap_end((struct soap*)soap);
	soap_done((struct soap*)soap);
	free(soap);

	return NULL;
}

int buscarGameDisponible (){

	int i=0, encontrado=FALSE, result=-1;
	
	// Buscamos una partida que no este completa
	while ((!encontrado) && (i<MAX_GAMES)){

		if ((games[i].status == gameEmpty) ||
			(games[i].status == gameWaitingPlayer)){
			encontrado = TRUE;
		}
		else
			i++;
	}
	if (encontrado){
		result = i;
	}
	else{
		result = ERROR_SERVER_FULL;
	}

	return result;
}

int buscarJugador (xsd__string name, int idPartida){
	
	int result = ERROR_PLAYER_NOT_FOUND;
	
	//Va buscando por el array Games si existe ya un jugador con el mismo nombre
		if((strcmp(name, games[idPartida].player1Name) == 0) || (strcmp(name, games[idPartida].player2Name) == 0)){
			result = ERROR_NAME_REPEATED;
		}		
				
	return result;
}

int blackJackns__register (struct soap *soap, blackJackns__tMessage playerName, int* result){
		
	int gameIndex;

	// Set \0 at the end of the string
	playerName.msg[playerName.__size] = 0;

	if (DEBUG_SERVER)
		printf ("[Register] Registering new player -> %s\n", playerName.msg);


	if((gameIndex = buscarGameDisponible()) == ERROR_SERVER_FULL){
		*result = ERROR_SERVER_FULL;
	}
	//If server is not full
	else{	
		pthread_mutex_lock(&games[gameIndex].mutexPlayers);
		//Check if playername given is already registered
		if(buscarJugador(playerName.msg,gameIndex) == ERROR_PLAYER_NOT_FOUND){
			
			//The game in the gameIndex position is waitingPlayer
			if(games[gameIndex].status == gameWaitingPlayer){
				strcpy(games[gameIndex].player2Name, playerName.msg);
				games[gameIndex].status = gameReady;
				//Hay que devolver un número entero positivo con el identificador de la partida
				*result = gameIndex;
			}
			//The game in the gameIndex position is empty.
			else{
				strcpy(games[gameIndex].player1Name, playerName.msg);
				games[gameIndex].status = gameWaitingPlayer;
				//Hay que devolver un número entero positivo con el identificador de la partida
				*result = gameIndex;

			}	
		}
		//Name registered
		else{
			*result = ERROR_NAME_REPEATED;
		}
		pthread_cond_signal(&games[gameIndex].cond);
		pthread_mutex_unlock(&games[gameIndex].mutexPlayers);
	}
	
  	return SOAP_OK;
}
int blackJackns__getStatus (struct soap *soap, blackJackns__tMessage playerName,int idPartida, blackJackns__tBlock* gameStatus){

	//CUANDO NO SEA EL TURNO DEL JUGADOR ACTUAL LE TIENE QUE DEJAR WAITING (PHTHREAD_COND_WAIT())
	//Recordar que wait desbloquea el mutex para que otros hilos puedan ejecutarse, cuando deja de estar en espera hace un lock

	int code=idPartida;

	xsd__string message;
	message = (xsd__string) malloc (STRING_LENGTH);
	memset (message, 0, STRING_LENGTH);


	playerName.msg[playerName.__size] = 0;

	allocClearBlock(soap,gameStatus);
	

	
	//Hay que comprobar que playerName este registrado en la partida
	int encontrado = FALSE;
	if((strcmp(playerName.msg, games[idPartida].player1Name) == 0) || (strcmp(playerName.msg, games[idPartida].player2Name) == 0)){
				encontrado=TRUE;
	}	
	if(!encontrado)
		code = ERROR_PLAYER_NOT_FOUND;


	if(code != ERROR_PLAYER_NOT_FOUND){
	
		//--------------------Si ha empezado la partida--------------------//
		pthread_mutex_lock(&games[idPartida].mutexPlayers);

		if(games[idPartida].status != gameWaitingPlayer){

			//Si no es el turno del jugador actual ponemos en espera el thread

			while((games[idPartida].currentPlayer != player1 && strcmp(games[idPartida].player1Name,playerName.msg)==0)||
				(games[idPartida].currentPlayer != player2 && strcmp(games[idPartida].player2Name,playerName.msg)==0)){				
					
					pthread_cond_wait(&games[idPartida].cond,&games[idPartida].mutexPlayers);
			}

			//--------------------Si termina la partida--------------------//
			if(games[idPartida].endOfGame){ 	

				//--------------------Jugador Actual player1--------------------//
				if(games[idPartida].currentPlayer == player1){
					//Soy yo el jugador1?	
					if(strcmp(playerName.msg, games[idPartida].player1Name) == 0){			
						if(games[idPartida].player1Stack == 0) {
							code = GAME_LOSE;
							message = "FIN!! HAS PERDIDO LA PARTIDA!!";		
						}else if(games[idPartida].player2Stack == 0){
							code = GAME_WIN;
							message = "FIN!! HAS GANADO LA PARTIDA!!";	
						}						
					}else{
						if(games[idPartida].player1Stack == 0) {
							code = GAME_WIN;
							message = "FIN!! HAS GANADO LA PARTIDA!!";	
						}else if(games[idPartida].player2Stack == 0){
							code = GAME_LOSE;
							message = "FIN!! HAS PERDIDO LA PARTIDA!!";	
						}
					}
					//Enviamos el mensaje de Win/Lose
					copyGameStatusStructure(gameStatus,message,&games[idPartida].player1Deck,code);
				}//--------------------Jugador Actual player2--------------------//
				else{
					//Soy yo el jugador2?
					if(strcmp(playerName.msg, games[idPartida].player2Name) == 0){	
						if(games[idPartida].player2Stack == 0) {
							code = GAME_LOSE;
							message = "FIN!! HAS PERDIDO LA PARTIDA!!";	

						}else if(games[idPartida].player1Stack == 0){
							code = GAME_WIN;
							message = "FIN!! HAS GANADO LA PARTIDA!!";	
							
						}						
					}else{
						if(games[idPartida].player1Stack == 0) {
							code = GAME_WIN;
							message = "FIN!! HAS PERDIDO LA PARTIDA!!";		
						}else if(games[idPartida].player2Stack == 0){
							code = GAME_LOSE;
							message = "FIN!! HAS GANADO LA PARTIDA!!";	
						}
					}
					//Enviamos el mensaje de Win/Lose
					copyGameStatusStructure(gameStatus,message,&games[idPartida].player2Deck,code);
				}				
				//Como evitamos que el jugador que acabe la partida ganando/perdiendo vuelva a llamar a getStatus
				//solo el ultimo jugador accede a esta parte de getStatus por lo que es seguro volver a inicializar la partida aqui
				initGame(&games[idPartida]);

			pthread_mutex_unlock(&games[idPartida].mutexPlayers);
			}//--------------------Si no hay ganador--------------------//
			else{
			
				games[idPartida].player1Bet =DEFAULT_BET;
				games[idPartida].player2Bet =DEFAULT_BET;

				//--------------------Jugador actual Player1--------------------//
				if(games[idPartida].currentPlayer == player1){					
					if(strcmp(playerName.msg, games[idPartida].player1Name) == 0){

					//--------------------Repartimos las cartas iniciales--------------------//
					if(games[idPartida].player1Deck.__size == 0){
						for(int i = 0; i < 2; i++){
							unsigned int carta = getRandomCard(&games[idPartida].gameDeck);
							unsigned int nCarta = games[idPartida].player1Deck.__size;
							games[idPartida].player1Deck.cards[nCarta] = carta;
							games[idPartida].player1Deck.__size++;
						}
					}
						code = TURN_PLAY;

						unsigned int puntosJug1 = calculatePoints(&games[idPartida].player1Deck);
						unsigned int puntosJug2 = calculatePoints(&games[idPartida].player2Deck);

						if(puntosJug2>0){
							sprintf(message,"Es tu turno, actualmente tienes %d puntos, el rival tiene %d puntos",puntosJug1,puntosJug2);								
						}else{
							sprintf(message,"Es tu turno, actualmente tienes %d puntos",puntosJug1);								
						}
						
					}
				else{
					code = TURN_WAIT;	
					message = "Turno del rival, porfavor espere";			
				}
				//Como el jugador actual es el player1 queremos ver su deck en ambos jugadores(Como usamos wait, no se muestra en el jugador en espera)
				copyGameStatusStructure(gameStatus,message,&games[idPartida].player1Deck,code);
				}//--------------------Jugador actual Player2--------------------//	
				else{						
					if(strcmp(playerName.msg, games[idPartida].player1Name) == 0){
						code = TURN_WAIT;					
						message = "Turno del rival, porfavor espere";		
					}
					else{						
						if(games[idPartida].player2Deck.__size == 0){
							for(int i = 0; i < 2; i++){
								unsigned int carta = getRandomCard(&games[idPartida].gameDeck);
								unsigned int nCarta = games[idPartida].player2Deck.__size;
								games[idPartida].player2Deck.cards[nCarta] = carta;
								games[idPartida].player2Deck.__size++;
							}
						}
						code = TURN_PLAY;
						unsigned int puntosJug1 = calculatePoints(&games[idPartida].player1Deck);
						unsigned int puntosJug2 = calculatePoints(&games[idPartida].player2Deck);

						if(puntosJug2>0){
							sprintf(message,"Es tu turno, actualmente tienes %d puntos, el rival tiene %d puntos",puntosJug2,puntosJug1);								
						}else{
							sprintf(message,"Es tu turno, actualmente tienes %d puntos",puntosJug2);								
						}}


				//Como el jugador actual es el player2 queremos ver su deck en ambos jugadores
				copyGameStatusStructure(gameStatus,message,&games[idPartida].player2Deck,code);
				}
			}	
		}//--------------------Si aun falta algun jugador para empezar la partida--------------------//
		else if(games[idPartida].status == gameWaitingPlayer){			
			code = gameWaitingPlayer;

			if(strcmp(playerName.msg, games[idPartida].player1Name) == 0){
				if(games[idPartida].currentPlayer  == player1){
					message = "Empiezas tu la partida";
				}else{
					message = "Empieza el rival, porfavor espere";				}									
					
			}else{
				if(games[idPartida].currentPlayer  == player1){
					message = "Empieza el rival, porfavor espere";
				}else{
					message = "Empiezas tu la partida";
				}		
			}

			copyGameStatusStructure(gameStatus,message,&games[idPartida].player1Deck,code);		

			while(games[idPartida].status == gameWaitingPlayer){
				
				pthread_cond_wait(&games[idPartida].cond,&games[idPartida].mutexPlayers);

				//Despues de este wait se ejecuta el turno del segundo jugador aqui se pueden hacer comprobaciones para ver si ha ganado la partida?
			}
			
		}
		pthread_mutex_unlock(&games[idPartida].mutexPlayers);
	}//Si no ha encontrado el nombre del jugador
	else{
		code = ERROR_PLAYER_NOT_FOUND;	
		strcpy(message,"Player is not registered, impossible obtain match state");
		copyGameStatusStructure(gameStatus,message,&games[idPartida].gameDeck,code);
	}
	
	return SOAP_OK;
}

int blackJackns__playerMove (struct soap *soap, blackJackns__tMessage playerName, int playerMove, int idPartida, blackJackns__tBlock* gameStatus){

	//TODO FALTA QUE CUANDO UN JUGADOR PIERDA UNA RONDA EN VEZ DE PERDER SE LE DESCUENTE EL STACK
	
	/*
	Cuando un jugador realiza un movimiento en el juego (servicio playerMove), es posible que
	éste provoque el fin de la partida, bien porque haya ganado, bien porque se haya pasado y gane
	el rival. En este caso, es posible devolver el código de fin de partida en la estructura
	blackJackns__tBlock, además del mensaje correspondiente. De esta forma, este jugador no
	tendrá que volver a invocar el servicio getStatus para comprobar si la partida ha finalizado
	*/


	playerName.msg[playerName.__size] = 0;
	allocClearBlock (soap, gameStatus);
	int code = idPartida;
	int nuevaRonda = FALSE;
	int empate = FALSE;
	xsd__string message;
	message = (xsd__string) malloc (STRING_LENGTH);
	memset (message, 0, STRING_LENGTH);

	int encontrado = FALSE;
	if((strcmp(playerName.msg, games[idPartida].player1Name) == 0) || (strcmp(playerName.msg, games[idPartida].player2Name) == 0)){
				encontrado=TRUE;
	}	
	if(!encontrado)
		code = ERROR_PLAYER_NOT_FOUND;


	if(code != ERROR_PLAYER_NOT_FOUND){

		//Miramos que jugador tiene turno actualmente
		pthread_mutex_lock(&games[idPartida].mutexPlayers);
		
		blackJackns__tDeck* deckJugActual;
		blackJackns__tDeck* deckJugRival;
		int* stackJugActual;
		int* stackJugRival;


		//--------------------Jugador actual Player1--------------------//
			if(strcmp(playerName.msg, games[idPartida].player1Name) == 0){


			deckJugActual = &games[idPartida].player1Deck;
			deckJugRival = &games[idPartida].player2Deck;

			stackJugActual = &games[idPartida].player1Stack;
			stackJugRival = &games[idPartida].player2Stack;
			}else{
			deckJugActual = &games[idPartida].player2Deck;
			deckJugRival = &games[idPartida].player1Deck;

			stackJugActual = &games[idPartida].player2Stack;
			stackJugRival = &games[idPartida].player1Stack;
			}

			

			//Distinguimos entre PLAYER_STAND y PLAYER_HIT_CARD
			if(playerMove == PLAYER_HIT_CARD){
				//Le repartimos una carta
				unsigned int carta = getRandomCard(&games[idPartida].gameDeck);
				unsigned int nCarta = deckJugActual->__size;
				deckJugActual->cards[nCarta] = carta;
				deckJugActual->__size++;
				code= TURN_PLAY;
			}else{
				code = TURN_WAIT;
				
			}
			//Calculamos los puntos
			unsigned int puntosActuales = calculatePoints(deckJugActual);
			unsigned int puntosRival = calculatePoints(deckJugRival);
			//Empate: if(puntosActuales >21 && puntosRival > 21){cleardeck}
			sprintf(message,"Turno del jugador 1, tienes %d puntos",puntosActuales);	
			if(puntosActuales>21){
				//Pierde su turno
				code = TURN_WAIT;
			}

			//Comprobamos el resultado de la ronda, comprobamos el tamaño del deck del jugador rival para ver si el ya ha jugado su turno
			//Si el jugador rival tiene mas de 0 cartas significa que ya ha jugado su turno y podemos calcular quien ha ganado la ronda
			if(code == TURN_WAIT && deckJugRival->__size >0){
				//Primero vemos si han empatado
				if(puntosActuales>21 && puntosRival>21 ||puntosActuales == puntosRival){
					//Ninguno pierde stacks y se resetea la ronda
					nuevaRonda = TRUE;	
					empate = TRUE;				
				}
				else{//Si no hay empate

					//Calculamos si hemos perdido la ronda
					if((puntosRival <= 21 && puntosActuales<puntosRival) || puntosActuales>21){				
						*stackJugActual -= DEFAULT_BET;
						*stackJugRival += DEFAULT_BET;

						//Vemos si hemos perdido la partida
						if(*stackJugActual ==0){
							code = GAME_LOSE;
							games[idPartida].endOfGame = TRUE;
						}
						else{//Empieza nueva ronda porque aun no ha terminado la partida
							nuevaRonda = TRUE;
						}
					}else{
						*stackJugRival -= DEFAULT_BET;
						*stackJugActual += DEFAULT_BET;

						//Vemos si hemos perdido la partida
						if(*stackJugRival ==0){
							code = GAME_WIN;
							games[idPartida].endOfGame = TRUE;
						}
						else{//Empieza nueva ronda porque aun no ha terminado la partida
							nuevaRonda = TRUE;
						}
					}
				}							
			}
			//Jugador actual pierde el turno
			if(playerMove == PLAYER_STAND || code == GAME_LOSE ||code == TURN_WAIT){
				//Cambiamos de jugador actual
				games[idPartida].currentPlayer = calculateNextPlayer (games[idPartida].currentPlayer);
				if(code == GAME_LOSE){
					message = "FIN!! HAS PERDIDO LA PARTIDA!!";	
				}else if(nuevaRonda){
					if(empate){
						sprintf(message,"Finaliza la ronda en empate, ambos jugadores recuperan su apuesta,el rival tiene %d stack, tu tienes %d stack y tus cartas son:",DEFAULT_BET,stackJugRival, stackJugActual);
					}else{
						sprintf(message,"Finaliza la ronda, has ganado %d stacks,el rival tiene %d stack, tu tienes %d stack y tus cartas son:",DEFAULT_BET,stackJugActual,stackJugRival);					
					}
				}else if( code == GAME_WIN){
					message = "FIN!! HAS GANADO LA PARTIDA!!";
				}else{
					if(puntosActuales <= 21){
						if(puntosRival >0){
							sprintf(message,"Finalizas tu turno,el rival tiene %d puntos, tu tienes %d puntos y tus cartas son:",puntosRival, puntosActuales);				
						}else{
							sprintf(message,"Finalizas tu turno,tienes %d puntos y tus cartas son:",puntosActuales);			
						}
					}
					else{
					sprintf(message,"Has superado los 21 puntos pierdes tu turno, tienes %d puntos y tus cartas son:",puntosActuales);
					}
				}
				//Desbloquea el pthread asociado a esa variable de condicion
				pthread_cond_signal(&games[idPartida].cond);					
			}
				copyGameStatusStructure(gameStatus,message,deckJugActual,code);

				if(nuevaRonda){
					clearDeck(&games[idPartida].player1Deck);
					clearDeck(&games[idPartida].player2Deck);
				}
				pthread_mutex_unlock(&games[idPartida].mutexPlayers);					
	}else{
		code = ERROR_PLAYER_NOT_FOUND;	
		message = "Player is not registered, impossible obtain match state";
	}
	
	
	return SOAP_OK;
}

int main(int argc, char **argv){ 

	struct soap soap;
	struct soap *tsoap;
	pthread_t tid;
	int port;
	SOAP_SOCKET m, s;

		// Check arguments
		if (argc !=2) {
			printf("Usage: %s port\n",argv[0]);
			exit(0);
		}

	soap_init(&soap);
	initServerStructures(&soap);

	soap.send_timeout = 60; // 60 seconds
	soap.recv_timeout = 60; // 60 seconds
	soap.accept_timeout = 3600; // server stops after 1 hour of inactivity
	soap.max_keep_alive = 100; // max keep-alive sequence

	// Get listening port
	port = atoi(argv[1]);

	m = soap_bind(&soap, NULL, port, 100);

	// Bind to the specified port
	if (!soap_valid_socket(m)){
		exit(1);
	}

		printf ("Server is ON! waiting for requests...\n");

	// Listen to next connection
			while (TRUE){

			// Accept a new connection
			s = soap_accept(&soap);

			// Socket is not valid :(
			if (!soap_valid_socket(s)){

				if (soap.errnum){
					soap_print_fault(&soap, stderr);
					exit(1);
				}

				fprintf(stderr, "Time out!\n");
				break;
			}

			// Copy the SOAP environment
			tsoap = soap_copy(&soap);

			if (!tsoap){
				printf ("SOAP copy error!\n");
				break;
			}

			// Create a new thread to process the request
			pthread_create(&tid, NULL, (void*(*)(void*))processRequest, (void*)tsoap);
		}
	// Free mutex and condition variables
for (int i=0; i<MAX_GAMES; i++){
	pthread_mutex_destroy(&games[i].mutexPlayers);
	pthread_cond_destroy(&games[i].cond);
}
	// Detach SOAP environment
	soap_done(&soap);
	return 0;
}