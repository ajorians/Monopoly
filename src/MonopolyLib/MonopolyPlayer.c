#include "MonopolyPlayer.h"

#ifdef _TINSPIRE
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

result MonopolyPlayerCreate( struct MonopolyPlayer** ppPlayer, struct MonopolyPlayerCallbacks* pPlayerCallbacks )
{
   struct MonopolyPlayer* pP;

   pP = malloc( sizeof( struct MonopolyPlayer ) );
   if ( pP == NULL )
   {//Out of memory
      return RESULT_OUT_OF_MEMORY;
   }
   pP->m_nMoney = 1500;
   pP->m_pLocation = NULL;
   pP->m_callbackPlayerMoved = pPlayerCallbacks->m_PlayerMovedCallback;

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
   struct MonopolyLocation* pOldLocation = pPlayer->m_pLocation;
   pPlayer->m_pLocation = pLocation;

   if ( pPlayer->m_callbackPlayerMoved )
      ( pPlayer->m_callbackPlayerMoved )( pPlayer, pOldLocation, pLocation );
}

struct MonopolyLocation* MonopolyPlayerGetLocation( struct MonopolyPlayer* pPlayer )
{
   return pPlayer->m_pLocation;
}
