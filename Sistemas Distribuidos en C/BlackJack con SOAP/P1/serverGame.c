#include "serverGame.h"
#include <pthread.h>

tPlayer getNextPlayer (tPlayer currentPlayer){

	tPlayer next;

		if (currentPlayer == player1)
			next = player2;
		else
			next = player1;

	return next;
}

void initDeck (tDeck *deck){

	deck->numCards = DECK_SIZE;

	for (int i=0; i<DECK_SIZE; i++){
		deck->cards[i] = i;
	}
}

void clearDeck (tDeck *deck){

	// Set number of cards
	deck->numCards = 0;

	for (int i=0; i<DECK_SIZE; i++){
		deck->cards[i] = UNSET_CARD;
	}
}

void printSession (tSession *session){

		printf ("\n ------ Session state ------\n");

		// Player 1
		printf ("%s [bet:%d; %d chips] Deck:", session->player1Name, session->player1Bet, session->player1Stack);
		printDeck (&(session->player1Deck));

		// Player 2
		printf ("%s [bet:%d; %d chips] Deck:", session->player2Name, session->player2Bet, session->player2Stack);
		printDeck (&(session->player2Deck));

		// Current game deck
		if (DEBUG_PRINT_GAMEDECK){
			printf ("Game deck: ");
			printDeck (&(session->gameDeck));
		}
}

void initSession (tSession *session){

	clearDeck (&(session->player1Deck));
	session->player1Bet = 0;
	session->player1Stack = INITIAL_STACK;

	clearDeck (&(session->player2Deck));
	session->player2Bet = 0;
	session->player2Stack = INITIAL_STACK;

	initDeck (&(session->gameDeck));
}

unsigned int calculatePoints (tDeck *deck){

	unsigned int points;

		// Init...
		points = 0;

		for (int i=0; i<deck->numCards; i++){

			if (deck->cards[i] % SUIT_SIZE < 9)
				points += (deck->cards[i] % SUIT_SIZE) + 1;
			else
				points += FIGURE_VALUE;
		}

	return points;
}

unsigned int getRandomCard (tDeck* deck){

	unsigned int card, cardIndex, i;

		// Get a random card
		cardIndex = rand() % deck->numCards;
		card = deck->cards[cardIndex];

		// Remove the gap
		for (i=cardIndex; i<deck->numCards-1; i++)
			deck->cards[i] = deck->cards[i+1];

		// Update the number of cards in the deck
		deck->numCards--;
		deck->cards[deck->numCards] = UNSET_CARD;

	return card;
}
void actualizarFichas(tSession *sesionJuego){

		unsigned int puntosJug1, puntosJug2;

		//Probar a cambiar apuesta por player2Bet o player1Bet en los ifs
		puntosJug1 = calculatePoints (&(sesionJuego->player1Deck));
		puntosJug2 = calculatePoints (&(sesionJuego->player2Deck));


		//Empate
		if (((puntosJug1 > GOAL_GAME) && (puntosJug2 > GOAL_GAME)) || (puntosJug1 == puntosJug2)){
			sesionJuego->player1Stack += sesionJuego->player1Bet;
			sesionJuego->player2Stack += sesionJuego->player2Bet;
			printf ("\nEmpate\n");
		}

		//Jugador 1 se pasa de 21 puntos, jug2 gana la apuesta además recupera sus fichas apostadas
		else if (puntosJug1 > GOAL_GAME){
			sesionJuego->player2Stack += sesionJuego->player2Bet + sesionJuego->player1Bet;
			printf ("\n Turno ganado por %s ",sesionJuego->player2Name);
		}

		//Jugador 2 se pasa de 21 puntos, jug1 gana la apuesta además recupera sus fichas apostadas
		else if (puntosJug2 > GOAL_GAME){
			sesionJuego->player1Stack += sesionJuego->player2Bet + sesionJuego->player1Bet;
			printf ("\n Turno ganado por %s ",sesionJuego->player1Name);
		}

		// Gana el jugador 1
		else if ((GOAL_GAME-puntosJug1) < (GOAL_GAME-puntosJug2)){
			sesionJuego->player1Stack += sesionJuego->player2Bet + sesionJuego->player1Bet;
			printf ("\n Turno ganado por %s ",sesionJuego->player1Name);
		}

		// Gana el jugador 2
		else{
			sesionJuego->player2Stack += sesionJuego->player2Bet + sesionJuego->player1Bet;
			printf ("\n Turno ganado por %s ",sesionJuego->player2Name);
		}
}
void gestionar_apuesta (int socketJugador, unsigned int *stack, unsigned int *apuesta){

			//El servidor envia al jug1 el codigo TURN_BET y su stack
			//Recordar que TURN_BET es un numero, esta definido en game.h
			unsigned int codigoJug = TURN_BET;
			int msgJugLength= send(socketJugador,&codigoJug,sizeof(codigoJug),0);
			if(msgJugLength <0)
				showError("Error al enviar el codigo TURN_BET");

			//Enviamos el stack al jug1
			msgJugLength= send(socketJugador,stack,sizeof(*stack),0);
			if(msgJugLength <0)
				showError("Error al enviar el stack");

			//El jugador jugA introducirá por teclado una apuesta, es decir el servidor tiene que recibir un mensaje del jugador 1
			while(codigoJug != TURN_BET_OK){

				//Usamos sizeof porque la apuesta es un entero
				msgJugLength = recv(socketJugador,apuesta,sizeof(apuesta),0);
				if(msgJugLength <0)
					showError("Error al recibir el mensaje");

				//Comprobamos que la apuesta sea correcta, debe ser menor o igual que el stack del jugador y de la apuesta maxima permitida (MAX_BET) y ser de almenos una ficha
				if(*apuesta> 0 && *apuesta <= MAX_BET && *apuesta <= *stack){
					codigoJug =TURN_BET_OK;
				}else{
					codigoJug =TURN_BET;
				}

				//Enviamos el codigo al cliente para que este sepa si su apuesta es correcta o no y pueda volver a enviarla
				msgJugLength= send(socketJugador,&codigoJug,sizeof(codigoJug),0);
				if(msgJugLength <0)
					showError("Error al enviar el mensaje");
			}
			*stack -= *apuesta;
}
void enviar_cod_pts_deck (int socketPlayer,unsigned int *codigo,unsigned int *puntos,tDeck *deck){
	int msgJugLength= send(socketPlayer,codigo,sizeof(*codigo),0);
		if(msgJugLength <0)
			showError("Error al enviarle el codigo TURN_PLAY al jugador");
		msgJugLength= send(socketPlayer,puntos,sizeof(*puntos),0);
		if(msgJugLength <0)
			showError("Error al enviarle los puntos al jugador");	
		//Si hacemos sizeOf(Deck) estamos enviando todo el deck esto se hace teniendo en cuenta el numero de las cartas que vamos a enviar
		msgJugLength = send(socketPlayer,deck,sizeof(*deck),0);
		if(msgJugLength <0)
			showError("Error al enviarle el deck al jugador");
}

void turno (int jugadorActivo, int jugadorPasivo, tSession *sesionJuego, tDeck *deckJugActivo, unsigned int *stackJugActivo){
	for(int i = 0; i < 2; i++){
		//Repartimos carta al jugador activo, es decir el deck que pasamos es el del jugador Activ
		unsigned int carta = getRandomCard(&sesionJuego->gameDeck);
		unsigned int numero = deckJugActivo->numCards;
		deckJugActivo->cards[numero] = carta;
		deckJugActivo->numCards++;
	}
	//Calculamos los puntos
		unsigned int puntosActuales = calculatePoints(deckJugActivo);
		
		//Enviamos a jugA el codigo TURN_PLAY ,sus puntos,su deck y el stack	
		unsigned int codigoJugActivo = TURN_PLAY;
		enviar_cod_pts_deck(jugadorActivo,&codigoJugActivo,&puntosActuales,deckJugActivo);

		//JugB
		//Enviamos a jugB TURN_PLAY_WAIT,los puntos de A y el deck del jugA
		unsigned int codigoJugPasivo = TURN_PLAY_WAIT;
		enviar_cod_pts_deck(jugadorPasivo,&codigoJugPasivo,&puntosActuales,deckJugActivo);

		//Una vez enviada toda la informacion el servidor recibe TURN_PLAY_STAND o TURN_PLAY_HIT del jugadorActivo
		int msgJugLength = recv(jugadorActivo,&codigoJugActivo,sizeof(codigoJugActivo),0);
		if(msgJugLength <0)
			showError("Error al recibir el codigo del jugA");
	
		//Empieza a jugarse la partida, jugA activo, jugB pasivo
		//TURN_PLAY_STAND el jugA se planta
		//TURN_PLAY_HIT el jugA si pide una carta nueva
		//TURN_PLAY_OUT el jugA ha superado los 21 puntos

		//Necesitamos una variable para guardar otro codigo para TURN_PLAY y TURN_PLAY_OUT
		unsigned int codigoAux=TURN_PLAY;
		unsigned int carta =100;
		unsigned int numero =0;
		while(codigoJugActivo == TURN_PLAY_HIT && codigoAux == TURN_PLAY){		

			//Repartimos carta al jugA
			carta = getRandomCard(&sesionJuego->gameDeck);
			numero = deckJugActivo->numCards;
			deckJugActivo->cards[numero] = carta;
			deckJugActivo->numCards++;

			//Calculamos los puntos del jugA
			puntosActuales = calculatePoints(deckJugActivo);
			//Si tiene mas de 21 el codigo pasa a ser TURN_PLAY_OUT
			if(puntosActuales >21){
				codigoAux = TURN_PLAY_OUT;
			}else{
				codigoAux=TURN_PLAY;
			}

			//Enviamos la informacion a ambos jugadores
			//La parte de envio de informacion alomejor se puede meter en una funcion para no estar constantemente copiando y pegando
			
			//Jug A
			enviar_cod_pts_deck(jugadorActivo,&codigoAux,&puntosActuales,deckJugActivo);

			//Jug B
			enviar_cod_pts_deck(jugadorPasivo,&codigoJugPasivo,&puntosActuales,deckJugActivo);

		
			//Si no ha llegado a 21 puntos seguimos escuchando el codigo que nos envie el jugadorA
			if(codigoAux != TURN_PLAY_OUT){
				//Recibimos del jugA su codigo
				msgJugLength = recv(jugadorActivo,&codigoJugActivo,sizeof(codigoAux),0);
				if(msgJugLength <0)
					showError("Error al recibir el codigo del jugA");
			}
		}
		codigoJugPasivo = TURN_PLAY_RIVAL_DONE;
		msgJugLength= send(jugadorPasivo,&codigoJugPasivo,sizeof(codigoJugPasivo),0);
		if(msgJugLength <0)
			showError("Error al enviarle el codigo TURN_PLAY_HIT/STAND al jug2");
}

void *threadProcessing(void *threadArgs){
//Variables del servidor
	tSession sesionJuego;
	tPlayer jugadorActual = player1;
	int socketJug1;					/** Socket descriptor for player 1 */
	int socketJug2;					/** Socket descriptor for player 2 */
	unsigned int finPartida = FALSE; //El valor 1 equivale a false en C
	unsigned int codigoJug1,codigoJug2;


	//Obtenemos los sockets de los jugadores
 	socketJug1 = ((tThreadArgs *) threadArgs)->socketPlayer1;
 	socketJug2 = ((tThreadArgs *) threadArgs)->socketPlayer2;



	//Recibimos el nombre del jugador 1
	//Aqui tenemos que poner el socket del jugador1 ya que es el que nos envia la informacion, poner el socket del servidor (socketfd) es incorrecto
	int msgJugLength = recv(socketJug1,sesionJuego.player1Name,STRING_LENGTH-1,0);

	if(msgJugLength <0)
		showError("Error al recibir el mensaje");

	printf("Nombre jugador 1: %s\n",sesionJuego.player1Name);


	//Recibimos el nombre del jugador 2
	msgJugLength = recv(socketJug2,sesionJuego.player2Name,STRING_LENGTH-1,0);

	if(msgJugLength <0)
		showError("Error while binding");

	printf("Nombre jugador 2: %s\n",sesionJuego.player2Name);

	//Prueba de respuesta del servidor a jugador 1
	//Aqui tenemos que poner el socket del jugador1 ya que es el que nos envia la informacion, poner el socket del servidor (socketfd) es incorrecto
	msgJugLength= send(socketJug1,sesionJuego.player1Name,STRING_LENGTH-1,0);

	//Prueba de respuesta del servidor a jugador 2
	//Aqui tenemos que poner el socket del jugador1 ya que es el que nos envia la informacion, poner el socket del servidor (socketfd) es incorrecto
	msgJugLength= send(socketJug2,sesionJuego.player2Name,STRING_LENGTH-1,0);

	//Inicializamos la sesion para que se inicie la partida
	//Le pasamos la direccion de la variable de sesion para que los valores queden bien guardados
	initSession(&sesionJuego);

	//Comenzamos la partida
	while(!finPartida){
		printSession(&sesionJuego);

		//Primero recibimos las apuestas de los jugadores
		if(jugadorActual == player1){
			//Tenemos que obtener la apuesta de ambos jugadores
			//Es mejor usar una funcion a parte ya que es lo mismo para ambos jugadores y evitamos repetir codigo
			gestionar_apuesta(socketJug1,&sesionJuego.player1Stack,&sesionJuego.player1Bet);
			gestionar_apuesta(socketJug2,&sesionJuego.player2Stack,&sesionJuego.player2Bet);
		}else{
			//Tenemos que obtener la apuesta de ambos jugadores
			gestionar_apuesta(socketJug2,&sesionJuego.player2Stack,&sesionJuego.player2Bet);
			gestionar_apuesta(socketJug1,&sesionJuego.player1Stack,&sesionJuego.player1Bet);
		}

		//Ahora se juegan los turnos
		if(jugadorActual == player1){
			//Apartir de aqui ambos jugadores ya tienen TURN_BET_OK y empieza el juego siendo jugA activo y jugB pasivo
			//Aqui pasa lo mismo en vez de copiar y pegar el codigo 200 veces es mejor hacer una funcion
			turno (socketJug1, socketJug2,&sesionJuego,&sesionJuego.player1Deck, &sesionJuego.player1Stack);
			turno (socketJug2, socketJug1,&sesionJuego,&sesionJuego.player2Deck, &sesionJuego.player2Stack);
			//Imprimimos		
			printSession (&sesionJuego);
		}else{
			//Apartir de aqui ambos jugadores ya tienen TURN_BET_OK y empieza el juego siendo jugB activo y jugA pasivo
			turno (socketJug2, socketJug1,&sesionJuego,&sesionJuego.player2Deck, &sesionJuego.player2Stack);
			turno (socketJug1, socketJug2,&sesionJuego,&sesionJuego.player1Deck, &sesionJuego.player1Stack);
			printSession (&sesionJuego);
		}
		
		actualizarFichas(&sesionJuego);

		//Si pierde jugA
		if(sesionJuego.player1Stack == 0) {
			codigoJug1 = TURN_GAME_LOSE;
			codigoJug2 = TURN_GAME_WIN;
			finPartida = TRUE;

		}
		//Si pierde jugB
		else if(sesionJuego.player2Stack == 0) {
			codigoJug1 = TURN_GAME_WIN;
			codigoJug2 = TURN_GAME_LOSE;
			finPartida = TRUE;
		}
		//Si sigue el juego
		else{
			jugadorActual = getNextPlayer(jugadorActual);
			clearDeck (&(sesionJuego.player1Deck));
			clearDeck (&(sesionJuego.player2Deck));
			clearDeck (&(sesionJuego.gameDeck));
			initDeck  (&(sesionJuego.gameDeck));
			sesionJuego.player1Bet = 0;
			sesionJuego.player2Bet = 0;
		}

		if(finPartida){
			//Enviamos los codigos actualizados
			msgJugLength= send(socketJug1,&codigoJug1,sizeof(codigoJug1),0);
			if(msgJugLength <0)
				showError("Error al enviarle el codigo al jug1");
			msgJugLength= send(socketJug2,&codigoJug2,sizeof(codigoJug2),0);
			if(msgJugLength <0)
				showError("Error al enviarle el codigo al jug2");
			close(socketJug1);
			close(socketJug2);	
		}
	}
	return (NULL) ;
}


int main(int argc, char *argv[]){

	int socketfd;						/** Socket descriptor */
	struct sockaddr_in serverAddress;	/** Server address structure */
	unsigned int port;					/** Listening port */
	struct sockaddr_in player1Address;	/** Client address structure for player 1 */
	struct sockaddr_in player2Address;	/** Client address structure for player 2 */
	unsigned int clientLength;			/** Length of client structure */
	tThreadArgs *threadArgs; 			/** Thread parameters */
	pthread_t threadID;					/** Thread ID */


		// Seed
		srand(time(0));

		// Check arguments
		if (argc != 2) {
			fprintf(stderr,"ERROR wrong number of arguments\n");
			fprintf(stderr,"Usage:\n$>%s port\n", argv[0]);
			exit(1);
		}

	socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(socketfd < 0)
		showError("Error while opening socket");

	port = atoi(argv[1]);

	memset(&serverAddress,0,sizeof(serverAddress));

	//Rellenamos la estructura del servidor
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port =htons(port);
	
	//Asocia el puerto al socket del servidor
	if(bind(socketfd,(struct sockaddr *)&serverAddress,sizeof(serverAddress))<0)
		showError("Error al asociar el puerto (bind)");
	

	if (listen(socketfd, 10) < 0)
		showError("Error while listening") ;

		while (1){

			//Establecemos la conexion con los 2 clientes	
			//Jugador 1
			clientLength = sizeof(player1Address);
			//Aceptamos la conexion del jug1
			int socketJug1= accept(socketfd, (struct sockaddr *) &player1Address, &clientLength);
			if (socketJug1 < 0)
			  showError("ERROR while accepting");
	

			clientLength = sizeof(player2Address);
			//Aceptamos la conexion del jug1
			int socketJug2= accept(socketfd, (struct sockaddr *) &player2Address, &clientLength);
			if (socketJug2 < 0)
			  showError("ERROR while accepting");

			// Reservamos memoria
			if ((threadArgs = (struct tThreadArgs *) malloc(sizeof( struct tThreadArgs *))) == NULL)
				showError("Error while allocating memory");

			//Asignamos los sockets
			threadArgs->socketPlayer1 = socketJug1;
			threadArgs->socketPlayer2 = socketJug2;

			//Creamos el nuevo hilo
			if (pthread_create(&threadID, NULL, threadProcessing, (void *) threadArgs) != 0)
				showError("pthread_create() failed");
		}
	close (socketfd);
	return 0;
}
