#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <arpa/inet.h>


/** Bet */
#define TURN_BET 0

/** The bet is correct */
#define TURN_BET_OK 1

/** Play (player's turn) */
#define TURN_PLAY 2

/** Player hits */
#define TURN_PLAY_HIT 3

/** Player stands */
#define TURN_PLAY_STAND 4

/** Player exceeds 21 */
#define TURN_PLAY_OUT 5

/** Player must wait and see the rival's play */
#define TURN_PLAY_WAIT 6

/** Rival is done */
#define TURN_PLAY_RIVAL_DONE 7

/** Player wins */
#define TURN_GAME_WIN 8

/** Player loses */
#define TURN_GAME_LOSE 9

/** Deck's size */
#define DECK_SIZE 52

/** Number of suits in the deck */
#define SUIT_SIZE 13

/** Maximum bet */
#define MAX_BET 5

/** True value */
#define TRUE 1

/** False value */
#define FALSE 0

/** Length for tString */
#define STRING_LENGTH 128

/** Type for names, messages and this kind of variables */
typedef char tString [STRING_LENGTH];

/** Structure that represents a deck */
typedef struct{
	unsigned int cards [DECK_SIZE];
	unsigned int numCards;
}tDeck;


/**
 * Function that shows an error message.
 *
 * @param msg Error message.
 */
void showError(const char *msg);

/**
 * Gets the suit of a given card.
 *
 * @param number Given card.
 * @return Suit of the given card.
 */
char suitToChar (unsigned int number);

/**
 * Gets the number of a given card.
 *
 * @param number Given card.
 * @return Number of the given card in a char.
 */
char cardNumberToChar (unsigned int number);

/**
 * Prints a deck.
 *
 * @param deck Deck to be shown.
 */
void printDeck (tDeck* deck);

/**
 * Prints a deck in a fancy way :)
 *
 * @param deck Deck to be shown.
 */
void printFancyDeck (tDeck* deck);

/**
 * Calculates the minimum of two given numbers.
 *
 * @param a First number.
 * @param b Second number.
 * @return Minimun value of the two given numbers.
 */
unsigned int min (unsigned int a, unsigned int b);
