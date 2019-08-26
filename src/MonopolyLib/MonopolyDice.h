#ifndef MONOPOLYDICE_H
#define MONOPOLYDICE_H

#include "Result.h"

struct MonopolyDice
{
   int m_nDice1;
   int m_nDice2;
};

result MonopolyDiceCreate( struct MonopolyDice** ppDice );
result MonopolyDiceFree( struct MonopolyDice** ppDice );

void MonopolyDiceRoll( struct MonopolyDice* pDice );
int MonopolyDiceGetTotal( struct MonopolyDice* pDice );
int MonopolyDiceIsDoubles( struct MonopolyDice* pDice );
void MonopolyDiceGetLastRoll( struct MonopolyDice* pDice, int* pDice1, int* pDice2 );


#endif // MONOPOLYDICE_H
