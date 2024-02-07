#include "soapH.h"
#include "blackJack.nsmap"
#include "game.h"
#include <pthread.h>


/** Flag to enable debugging */
#define DEBUG_SERVER 1

/** Maximum number of active games in the server */
#define MAX_GAMES 5

/** Initial stack for each player */
#define INITIAL_STACK 1

/** Default bet */
#define DEFAULT_BET 1

/** Number of points to win the game */
#define GOAL_GAME 21

/** Value of a figure */
#define FIGURE_VALUE 10

/** Code to represents an empty card (in the deck) */
#define UNSET_CARD 100



/** Type for game status */
typedef enum {gameEmpty, gameWaitingPlayer, gameReady} tGameState;

/** Players */
typedef enum players {player1, player2} tPlayer;

/**
 * Struct that contains a game for 2 players
 */
typedef struct game{
	
	tPlayer currentPlayer;					/** Current player */
	
	xsd__string player1Name;				/** Name of player 1 */
	blackJackns__tDeck player1Deck;			/** Player1's deck */
	unsigned int player1Bet;				/** Player1's bet */
	unsigned int player1Stack;				/** Player1's stack */
		
	xsd__string player2Name;				/** Name of player 2 */	
	blackJackns__tDeck player2Deck;			/** Player2's deck */
	unsigned int player2Bet;				/** Player2's bet */
	unsigned int player2Stack;				/** Player2's stack */
	
	blackJackns__tDeck gameDeck;			/** Main deck */
	int endOfGame;							/** Flag to control the end of the game */
	tGameState status;						/** Flag to indicate the status of this game */

	//Mutex y variable de condicion
	pthread_mutex_t mutexPlayers;
	pthread_cond_t cond;

}tGame;


/**
 * Initializes a game
 * 
 * @param game Game to be initialized.
 */
void initGame (tGame *game);

/**
 * Initialize server structures and alloc memory.
 *
 * @param soap Soap context.
 */
void initServerStructures (struct soap *soap);

/**
 * Inits the game deck with all the cards.
 *
 * @param deck Game deck.
 *
 */
void initDeck (blackJackns__tDeck *deck);

/**
 * Clears a deck (for players)
 *
 * @param deck Player deck.
 */
void clearDeck (blackJackns__tDeck *deck);

/**
 * Calculates the next player
 *
 * @param currentPlayer Current player.
 * @return Player that obtains the turn to play.
 */
tPlayer calculateNextPlayer (tPlayer currentPlayer);

/**
 * Gets a random card from the game deck. The obtained card is removed from the game deck.
 *
 * @param deck Deck where the card is removed from.
 * @return Randomly selected card from the deck.
 */
unsigned int getRandomCard (blackJackns__tDeck* deck);

/**
 * Copies the data to be sent in a blackJackns__tBlock structure.
 * 
 * @param status Structure where the data is copied.
 * @param message Message to be sent.
 * @param newDeck Deck to be sent.
 * @param newCode Code to be sent.
 */
void copyGameStatusStructure (blackJackns__tBlock* status, char* message, blackJackns__tDeck *newDeck, int newCode);

/**
 * Calculates the current points of a given deck.
 *
 * @param deck Given deck.
 * @return Points of the deck.
 */
unsigned int calculatePoints (blackJackns__tDeck *deck);

