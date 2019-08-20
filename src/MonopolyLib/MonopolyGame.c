#include "MonopolyGame.h"

#include "MonopolyBoard.h"

#ifdef _TINSPIRE
#else
#include <stdlib.h>
#endif

result MonopolyGameCreate( struct MonopolyGame** ppGame )
{
   struct MonopolyGame* pG;

   pG = malloc( sizeof( struct MonopolyGame ) );
   if ( pG == NULL )
   {//Out of memory
      return RESULT_OUT_OF_MEMORY;
   }

   pG->m_nTurnNumber = 0;
   MonopolyBoardCreate( &pG->m_pBoard );

   *ppGame = pG;

   return RESULT_OK;
}

result MonopolyGameFree( struct MonopolyGame** ppGame )
{
   struct MonopolyGame* pG;

   pG = *ppGame;

   //if ( pS->m_pBoard != NULL )
   //{
   //   free( pS->m_pBoard );
   //   pS->m_pBoard = NULL;
   //}
   MonopolyBoardFree( &pG->m_pBoard );

   free( pG );
   *ppGame = NULL;
   return RESULT_OK;
}

struct MonopolyBoard* MonopolyGameGetBoard( struct MonopolyGame* pGame )
{
   return pGame->m_pBoard;
}
