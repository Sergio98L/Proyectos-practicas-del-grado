#include "client.h"

unsigned int readBet (){

	int isValid, bet=0;
	xsd__string enteredMove;

		// While player does not enter a correct bet...
		do{

			// Init...
			enteredMove = (xsd__string) malloc (STRING_LENGTH);
			bzero (enteredMove, STRING_LENGTH);
			isValid = TRUE;

			printf ("Enter a value:");
			fgets(enteredMove, STRING_LENGTH-1, stdin);
			enteredMove[strlen(enteredMove)-1] = 0;

			// Check if each character is a digit
			for (int i=0; i<strlen(enteredMove) && isValid; i++)
				if (!isdigit(enteredMove[i]))
					isValid = FALSE;

			// Entered move is not a number
			if (!isValid)
				printf ("Entered value is not correct. It must be a number greater than 0\n");
			else
				bet = atoi (enteredMove);

		}while (!isValid);

		printf ("\n");
		free (enteredMove);

	return ((unsigned int) bet);
}

unsigned int readOption (){

	unsigned int bet;

		do{
			printf ("What is your move? Press %d to hit a card and %d to stand\n", PLAYER_HIT_CARD, PLAYER_STAND);
			bet = readBet();
			if ((bet != PLAYER_HIT_CARD) && (bet != PLAYER_STAND))
				printf ("Wrong option!\n");			
		} while ((bet != PLAYER_HIT_CARD) && (bet != PLAYER_STAND));

	return bet;
}

int main(int argc, char **argv){

	struct soap soap;					/** Soap struct */
	char *serverURL;					/** Server URL */
	blackJackns__tMessage playerName;	/** Player name */
	blackJackns__tBlock gameStatus;		/** Game status */
	unsigned int playerMove;			/** Player's move */
	int resCode, gameId;				/** Result and gameId */
	unsigned int finJuego;
	
		// Init gSOAP environment
		soap_init(&soap);

		// Obtain server address
		serverURL = argv[1];

		// Allocate memory
		allocClearMessage (&soap, &(playerName));
		allocClearBlock (&soap, &gameStatus);
				
		// Check arguments
		if (argc !=2) {
			printf("Usage: %s http://server:port\n",argv[0]);
			exit(0);
		}

		//Lo inicializamos a -1 porque si el registro es correcto resCode pasa a ser positivo
		resCode = -1;
		finJuego = FALSE;
		
		
		while (resCode < 0){

			//Le pedimos que introduzca su nombre
			printf("Introduzca su nombre: ");
			memset(playerName.msg, 0, STRING_LENGTH);
			fgets(playerName.msg, STRING_LENGTH-1, stdin);

			//Guardamos la longitud del nombre introducido
			playerName.__size = strlen(playerName.msg);

			//Llamamos a soap_call_blackJackns__register de soapCLient.c para registrar el jugador
			soap_call_blackJackns__register(&soap, serverURL, " ",  playerName, &resCode);
			
			//Comprobamos el codigo que devuelve

			if (soap.error) {
				soap_print_fault(&soap, stderr);
				exit(1);
			}
			else if(resCode == ERROR_NAME_REPEATED){
				printf("Ya existe un jugador con el mismo nombre regitrado, no se ha podido realizar el registro\n");
			}
			else if(resCode == ERROR_SERVER_FULL){
				printf("Servidor lleno, no se puede registrar ningun jugador nuevo,, no se ha podido realizar el registro \n");
			}

		}
		//Para revisar el nombre del nuevo jugador
			printf ("Registrado con exito con identificador -> %s\n", playerName.msg);


		while (!finJuego && resCode != ERROR_PLAYER_NOT_FOUND ){	
				/*
				getStatus (nombreJugador,idPartida, …);
				Imprimir estado del juego
				Mientras (jugador tiene el turno)
					jugada = Leer opción del jugador
					playerMove (nombreJugador,idPartida, jugada, …)
					Imprimir estado del juego
				*/

				//Llamamos a getStatus
				soap_call_blackJackns__getStatus(&soap, serverURL, "", playerName,resCode, &gameStatus);

				gameStatus.msgStruct.msg[gameStatus.msgStruct.__size] = 0;
				printf ("%s\n", gameStatus.msgStruct.msg);
				
			
				if(gameStatus.code != 1){ //while the code is not gameWaitingPlayer
					//Imprimir el estado del juego:
					// Remove '\n'
					gameStatus.msgStruct.msg[gameStatus.msgStruct.__size] = 0;

					//Imprimir estado del juego
					printFancyDeck(&gameStatus.deck);

					//Mientras (jugador tiene el turno)
					while(gameStatus.code ==TURN_PLAY){
						playerMove = readOption();

						//Llamamos al servicio playerMove
						soap_call_blackJackns__playerMove(&soap, serverURL, "", playerName, playerMove,resCode, &gameStatus);

						// Remove '\n'
						gameStatus.msgStruct.msg[gameStatus.msgStruct.__size] = 0;

						//Imprimir el estado del juego
						printf ("%s\n", gameStatus.msgStruct.msg);
						printFancyDeck(&gameStatus.deck);
					}
					if(gameStatus.code == GAME_WIN || gameStatus.code == GAME_LOSE ){	
						//playerMove puede finalizar la partida	y asi evitamos volver a entrar en getStatus												
						finJuego = TRUE;
					}
				}
			}
		// Clean the environment
		soap_destroy(&soap);
		soap_end(&soap);
		soap_done(&soap);

  return 0;
}