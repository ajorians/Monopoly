#include "MonopolyGameFactory.h"

#include "MonopolyGame.h"

#ifdef _TINSPIRE
#else
#include <stdlib.h>
#include <assert.h>
#endif

result MonopolyGameFactoryCreate( struct MonopolyGameFactory** ppGameFactory )
{
   struct MonopolyGameFactory* pF;

   pF = malloc( sizeof( struct MonopolyGameFactory ) );
   if ( pF == NULL )
   {//Out of memory
      return RESULT_OUT_OF_MEMORY;
   }

   pF->m_nNumberOfPlayers = 0;
   pF->m_PlayerCallbacks.m_PlayerMovedCallback = NULL;
   pF->m_LocationCallbacks.m_BuildingsChangedCallback = NULL;
   pF->m_BoardCallbacks.m_pLocationCallbacks = &pF->m_LocationCallbacks;
   pF->m_BoardCallbacks.m_SomethingChangedCallback = NULL;
   pF->m_DiceCallbacks.m_DiceRolledCallback = NULL;

   *ppGameFactory = pF;

   return RESULT_OK;
}

result MonopolyGameFactoryFree( struct MonopolyGameFactory** ppGameFactory )
{
   struct MonopolyGameFactory* pF;

   pF = *ppGameFactory;

   free( pF );
   *ppGameFactory = NULL;
   return RESULT_OK;
}

struct MonopolyGame* MonopolyGameFactoryCreateGame( struct MonopolyGameFactory* pGameFactory )
{
   struct MonopolyGame* pGame = NULL;
   MonopolyGameCreate( &pGame,
                       pGameFactory->m_nNumberOfPlayers,
                       &pGameFactory->m_PlayerCallbacks,
                       &pGameFactory->m_BoardCallbacks,
                       &pGameFactory->m_DiceCallbacks );//TODO: Check result

   return pGame;
}

result MonopolyGameFactorySetNumberOfPlayers( struct MonopolyGameFactory* pGameFactory, int nNumPlayers )
{
   pGameFactory->m_nNumberOfPlayers = nNumPlayers;
   return RESULT_OK;
}

result MonopolyGameFactorySetPlayerCallbacks( struct MonopolyGameFactory* pGameFactory, struct MonopolyPlayerCallbacks* pPlayerCallbacks )
{
   pGameFactory->m_PlayerCallbacks.m_PlayerMovedCallback = pPlayerCallbacks->m_PlayerMovedCallback;
   return RESULT_OK;
}


