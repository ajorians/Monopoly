#include "MonopolyGameLib.h"

#ifdef _TINSPIRE
#else
#include <stdlib.h>
#endif

struct MonopolyGame
{
   int m_nTurnNumber;
};

result MonopolyGameLibCreate( MonopolyGameLib* api )
{
   struct MonopolyGame* pM;

   pM = malloc( sizeof( struct MonopolyGame ) );
   if ( pM == NULL )
   {//Out of memory
      return RESULT_OUT_OF_MEMORY;
   }

   pM->m_nTurnNumber = 0;

   *api = pM;

   return RESULT_OK;
}

result MonopolyGameLibFree( MonopolyGameLib* api )
{
   struct MonopolyGame* pM;

   pM = *api;

   //if ( pS->m_pBoard != NULL )
   //{
   //   free( pS->m_pBoard );
   //   pS->m_pBoard = NULL;
   //}

   free( pM );
   *api = NULL;
   return RESULT_OK;
}
