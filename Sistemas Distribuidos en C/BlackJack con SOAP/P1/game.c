#include "game.h"

void showError(const char *msg){
	perror(msg);
	exit(0);
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

void printDeck (tDeck* deck){

	// Print info for player 1
	printf ("%d cards -> ", deck->numCards);

	for (int i=0; i<deck->numCards; i++)
		printf("%c%c ", cardNumberToChar (deck->cards[i]), suitToChar (deck->cards[i]));

	printf("\n");
}

void printFancyDeck (tDeck* deck){

	// Print info for player 1
	printf ("%d cards\n", deck->numCards);

	// Print the first line
	for (int currentCard=0; currentCard<deck->numCards; currentCard++)
		printf ("  ___ ");

	printf ("\n");

	// Print the second line
	for (int currentCard=0; currentCard<deck->numCards; currentCard++)
		printf (" |%c  |", cardNumberToChar (deck->cards[currentCard]));

	printf ("\n");

	// Print the third line
	for (int currentCard=0; currentCard<deck->numCards; currentCard++){
		if (suitToChar (deck->cards[currentCard]) == 'c')
			printf (" | \u2663 |");
		else if (suitToChar (deck->cards[currentCard]) == 'd')
			printf (" | \u25C6 |");
		else if (suitToChar (deck->cards[currentCard]) == 's')
			printf (" | \u2660 |");
		else if (suitToChar (deck->cards[currentCard]) == 'h')
			printf (" | \u2665 |");
	}
		//printf (" | %c |", suitToChar (deck->cards[currentCard]));

	printf ("\n");

	// Print the fourth line
	for (int currentCard=0; currentCard<deck->numCards; currentCard++)
		printf (" |__%c|", cardNumberToChar (deck->cards[currentCard]));

	printf ("\n");
}

unsigned int min (unsigned int a, unsigned int b){
	return (a<b?a:b);
}
