#ifndef MONOPOLYGAME_H
#define MONOPOLYGAME_H

#include "Result.h"
#include "MonopolyCallbacks.h"

struct MonopolyBoard;
struct MonopolyPlayer;
struct MonopolyDice;

struct MonopolyGame
{
   int m_nTurnNumber;

   struct MonopolyBoard* m_pBoard;
   struct MonopolyPlayer** m_ppPlayers;
   int m_nNumPlayers;

   struct MonopolyPlayer* m_pPlayersTurn;
   struct MonopolyDice* m_pDice;

   GamePropertyPurchasedFunc m_callbackPropertyPurchased;
   GamePropertyDeclinedPurchasedFunc m_callbackPropertyDeclinedPurchase;
};

result MonopolyGameCreate( struct MonopolyGame** ppGame,
                           int numPlayers,
                           struct MonopolyGameCallbacks* pGameCallbacks,
                           struct MonopolyPlayerCallbacks* pPlayerCallbacks,
                           struct MonopolyBoardCallbacks* pBoardCallbacks,
                           struct MonopolyDiceCallbacks* pDiceCallbacks );
result MonopolyGameFree( struct MonopolyGame** ppGame );

struct MonopolyBoard* MonopolyGameGetBoard( struct MonopolyGame* pGame );

//Note it could be player 1's turn but player 2 might need to settle debt, accept trade, or other action first
struct MonopolyPlayer* MonopolyGameWhosTurn( struct MonopolyGame* pGame );

void MonopolyGamePlayerRollsForTurn( struct MonopolyGame* pGame, struct MonopolyPlayer* pPlayerRolling );
void MonopolyGameEndCurrentTurn( struct MonopolyGame* pGame, struct MonopolyPlayer* pPlayerEndingTurn );

//Used for Purchasing.  Trades don't use this
void MonopolyGamePlayerPurchacesProperty( struct MonopolyGame* pGame, struct MonopolyPlayer* pPlayer, struct MonopolyLocation* pLocation, int howMuch );

void MonopolyGamePlayerDeclinesPropertyPurchase( struct MonopolyGame* pGame, struct MonopolyPlayer* pPlayer, struct MonopolyLocation* pLocation );

#endif // MONOPOLYGAME_H
