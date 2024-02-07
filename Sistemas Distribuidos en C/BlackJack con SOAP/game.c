#include "game.h"

void showError(const char *msg){
	perror(msg);
	exit(0);
}

void showCodeText (unsigned int code){

	xsd__string string;

		// Reset
		string = (xsd__string) malloc (STRING_LENGTH);
		memset (string, 0, STRING_LENGTH);

		switch(code){

			case TURN_PLAY:
				strcpy (string, "TURN_PLAY");
				break;

			case TURN_WAIT:
				strcpy (string, "TURN_WAIT");
				break;

			case PLAYER_HIT_CARD:
				strcpy (string, "PLAYER_HIT_CARD");
				break;

			case PLAYER_STAND:
				strcpy (string, "PLAYER_STAND");
				break;

			case GAME_WIN:
				strcpy (string, "GAME_WIN");
				break;

			case GAME_LOSE:
				strcpy (string, "GAME_LOSE");
				break;

			default:
				strcpy (string, "UNKNOWN CODE");
				break;
		}

		printf ("Received code: %s\n", string);
		free (string);	
}

char suitToChar (unsigned int number){

	char suit;

		if ((number/SUIT_SIZE) == 0)
			suit = 'c';
		else if ((number/SUIT_SIZE) == 1)
			suit = 's';
		else if ((number/SUIT_SIZE) == 2)
			suit = 'd';
		else
			suit = 'h';

	return suit;
}

char cardNumberToChar (unsigned int number){

	// init
	char numberChar = ' ';

		if ((number%SUIT_SIZE) == 0)
			numberChar = 'A';
		else if ((number%SUIT_SIZE) == 1)
			numberChar = '2';
		else if ((number%SUIT_SIZE) == 2)
			numberChar = '3';
		else if ((number%SUIT_SIZE) == 3)
			numberChar = '4';
		else if ((number%SUIT_SIZE) == 4)
			numberChar = '5';
		else if ((number%SUIT_SIZE) == 5)
			numberChar = '6';
		else if ((number%SUIT_SIZE) == 6)
			numberChar = '7';
		else if ((number%SUIT_SIZE) == 7)
			numberChar = '8';
		else if ((number%SUIT_SIZE) == 8)
			numberChar = '9';
		else if ((number%SUIT_SIZE) == 9)
			numberChar = 'T';
		else if ((number%SUIT_SIZE) == 10)
			numberChar = 'J';
		else if ((number%SUIT_SIZE) == 11)
			numberChar = 'Q';
		else if ((number%SUIT_SIZE) == 12)
			numberChar = 'K';

	return numberChar;
}

void printDeck (blackJackns__tDeck *deck){

	printf ("%d cards -> ", deck->__size);

	for (int i=0; i<deck->__size; i++)
		printf("%c%c ", cardNumberToChar (deck->cards[i]), suitToChar (deck->cards[i]));

	printf("\n");
}

void printFancyDeck (blackJackns__tDeck *deck){
	
	printf ("%d cards\n", deck->__size);

	// Print the first line
	for (int currentCard=0; currentCard<deck->__size; currentCard++)
		printf ("  ___ ");

	printf ("\n");

	// Print the second line
	for (int currentCard=0; currentCard<deck->__size; currentCard++)
		printf (" |%c  |", cardNumberToChar (deck->cards[currentCard]));

	printf ("\n");

	// Print the third line
	for (int currentCard=0; currentCard<deck->__size; currentCard++){
		if (suitToChar (deck->cards[currentCard]) == 'c')
			printf (" | \u2663 |");
		else if (suitToChar (deck->cards[currentCard]) == 'd')
			printf (" | \u25C6 |");
		else if (suitToChar (deck->cards[currentCard]) == 's')
			printf (" | \u2660 |");
		else if (suitToChar (deck->cards[currentCard]) == 'h')
			printf (" | \u2665 |");
	}
		
	printf ("\n");

	// Print the fourth line
	for (int currentCard=0; currentCard<deck->__size; currentCard++)
		printf (" |__%c|", cardNumberToChar (deck->cards[currentCard]));

	printf ("\n");
}

void printStatus (blackJackns__tBlock *status, int debug){

	if (debug)
		showCodeText (status->code);
	
	// Set end of message
	(status->msgStruct).msg[(status->msgStruct).__size] = 0;

	// Show message received from server
	printf ("%s\n", (status->msgStruct).msg);

	// Show deck
	printFancyDeck (&(status->deck));
}

void allocDeck (struct soap *soap, blackJackns__tDeck* deck){
	deck->cards = (unsigned int *) soap_malloc (soap, DECK_SIZE * sizeof (unsigned int));
	deck->__size = 0;
}

void allocClearMessage (struct soap *soap, blackJackns__tMessage* msg){
	msg->msg = (xsd__string) soap_malloc (soap, STRING_LENGTH);
	memset(msg->msg, 0, STRING_LENGTH);	
	msg->__size = STRING_LENGTH;
}

void allocClearBlock (struct soap *soap, blackJackns__tBlock* block){
	block->code = -1;
	allocClearMessage (soap, &(block->msgStruct));
	allocDeck (soap, &(block->deck));
}