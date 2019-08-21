#ifndef MONOPOLYGAME_H
#define MONOPOLYGAME_H

#include "Result.h"

struct MonopolyBoard;
struct MonopolyPlayer;

struct MonopolyGame
{
   int m_nTurnNumber;

   struct MonopolyBoard* m_pBoard;
   struct MonopolyPlayer** m_ppPlayers;
   int m_nNumPlayers;

   struct MonopolyPlayer* m_pPlayersTurn;
};

result MonopolyGameCreate( struct MonopolyGame** ppGame, int numPlayers );
result MonopolyGameFree( struct MonopolyGame** ppGame );

struct MonopolyBoard* MonopolyGameGetBoard( struct MonopolyGame* pGame );

//Note it could be player 1's turn but player 2 might need to settle debt, accept trade, or other action first
struct MonopolyPlayer* MonopolyGameWhosTurn( struct MonopolyGame* pGame );

void MonopolyGamePlayerRollsForTurn( struct MonopolyGame* pGame, struct MonopolyPlayer* pPlayerRolling, int* pDice1, int* pDice2 );

#endif // MONOPOLYGAME_H
