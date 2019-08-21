#include "MonopolyDice.h"

#ifdef _TINSPIRE
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

result MonopolyDiceCreate( struct MonopolyDice** ppDice )
{
   struct MonopolyDice* pD;

   pD = malloc( sizeof( struct MonopolyDice ) );
   if ( pD == NULL )
   {//Out of memory
      return RESULT_OUT_OF_MEMORY;
   }
   pD->m_nDice1 = 0;
   pD->m_nDice2 = 0;

   *ppDice = pD;

   return RESULT_OK;
}

result MonopolyDiceFree( struct MonopolyDice** ppDice )
{
   struct MonopolyDice* pD;

   pD = *ppDice;

   free( pD );
   *ppDice = NULL;
   return RESULT_OK;
}

void MonopolyDiceRoll( struct MonopolyDice* pDice )
{
   int dice1 = ( rand() % 6 ) + 1;
   pDice->m_nDice1 = dice1;

   int dice2 = ( rand() % 6 ) + 1;
   pDice->m_nDice2 = dice2;
}

int MonopolyDiceGetTotal( struct MonopolyDice* pDice )
{
   return pDice->m_nDice1 + pDice->m_nDice2;
}

int MonopolyDiceIsDoubles( struct MonopolyDice* pDice )
{
   return pDice->m_nDice1 == pDice->m_nDice2;
}

void MonopolyDiceGetLastRoll( struct MonopolyDice* pDice, int* pDice1, int* pDice2 )
{
   *pDice1 = pDice->m_nDice1;
   *pDice2 = pDice->m_nDice2;
}
