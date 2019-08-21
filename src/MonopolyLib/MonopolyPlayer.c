#include "MonopolyPlayer.h"

#ifdef _TINSPIRE
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

result MonopolyPlayerCreate( struct MonopolyPlayer** ppPlayer )
{
   struct MonopolyPlayer* pP;

   pP = malloc( sizeof( struct MonopolyPlayer ) );
   if ( pP == NULL )
   {//Out of memory
      return RESULT_OUT_OF_MEMORY;
   }
   pP->m_nMoney = 1500;
   pP->m_pLocation = NULL;

   *ppPlayer = pP;

   return RESULT_OK;
}

result MonopolyPlayerFree( struct MonopolyPlayer** ppPlayer )
{
   struct MonopolyPlayer* pP;

   pP = *ppPlayer;

   free( pP );
   *ppPlayer = NULL;
   return RESULT_OK;
}

void MonopolyLocationSetPlayerPosition( struct MonopolyPlayer* pPlayer, struct MonopolyLocation* pLocation )
{
   pPlayer->m_pLocation = pLocation;
}

struct MonopolyLocation* MonopolyPlayerGetLocation( struct MonopolyPlayer* pPlayer )
{
   return pPlayer->m_pLocation;
}
