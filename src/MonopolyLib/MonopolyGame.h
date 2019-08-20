#ifndef MONOPOLYGAME_H
#define MONOPOLYGAME_H

#include "Result.h"

struct MonopolyGame
{
   int m_nTurnNumber;

   struct MonopolyBoard* m_pBoard;
};

result MonopolyGameCreate( struct MonopolyGame** ppGame );
result MonopolyGameFree( struct MonopolyGame** ppGame );

struct MonopolyBoard* MonopolyGameGetBoard( struct MonopolyGame* pGame );

#endif // MONOPOLYGAME_H
