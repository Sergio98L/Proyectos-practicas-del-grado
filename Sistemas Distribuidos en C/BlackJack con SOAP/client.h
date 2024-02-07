#include "soapH.h"
#include "blackJack.nsmap"
#include "game.h"

/** Debug mode? */
#define DEBUG_CLIENT FALSE

/**
 * Reads a bet entered by the player.
 *
 * @return A number that represents the bet for the current hand.
 */
unsigned int readBet ();

/**
 * Reads the action taken by the player (stand or hit).
 *
 * @return A number that represents the action taken by the player.
 */
unsigned int readOption ();

