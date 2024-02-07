#include "soapH.h"

/**
 * Shows an error message and ends the execution.
 *
 * @param msg Error message.
 */
void showError(const char *msg);

/**
 * Prints the received code.
 *
 * @param code Received code.
 */
void showCodeText (unsigned int code);

/**
 * Gets the suit of a given card.
 *
 * @param number Card.
 * @return Suit of the card.
 */
char suitToChar (unsigned int number);

/**
 * Gets the value of a given card.
 *
 * @param number Card.
 * @return Value of the card.
 */
char cardNumberToChar (unsigned int number);

/**
 * Prints a deck.
 *
 * @param deck Deck to be shown.
 */
void printDeck (blackJackns__tDeck *deck);

/**
 * Prints a deck in a fancy way :)
 *
 * @param deck Deck to be shown.
 */
void printFancyDeck (blackJackns__tDeck *deck);

/** 
 * Prints the current status of the game.
 * 
 * @param status Status of the game. 
 * @param debug This parameter indicates if the code is also displayed.
 */
void printStatus (blackJackns__tBlock *status, int debug);

/** 
 * Allocates memory for one deck.
 * 
 * @param soap Soap context.
 * @param Deck structure where the cards will be stored.
 */
void allocDeck (struct soap *soap, blackJackns__tDeck* deck);

/** 
 * Allocates and clears memory for one message structure.
 * 
 * @param soap Soap context.
 * @param Message structure where the message will be stored.
 */
void allocClearMessage (struct soap *soap, blackJackns__tMessage* msg);

/** 
 * Allocates memory for a blackJackns__tBlock structure.
 * 
 * @param soap Soap context.
 * @param Structure where the code, message and deck will be stored.
 */
void allocClearBlock (struct soap *soap, blackJackns__tBlock* block);
