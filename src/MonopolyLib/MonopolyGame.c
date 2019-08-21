#include "MonopolyGame.h"

#include "MonopolyBoard.h"
#include "MonopolyPlayer.h"
#include "MonopolyLocation.h"

#ifdef _TINSPIRE
#else
#include <stdlib.h>
#include <assert.h>
#endif

struct MonopolyPlayer* GetPlayer( struct MonopolyGame* pGame, int nIndex );

result MonopolyGameCreate( struct MonopolyGame** ppGame, int numPlayers )
{
   struct MonopolyGame* pG;

   pG = malloc( sizeof( struct MonopolyGame ) );
   if ( pG == NULL )
   {//Out of memory
      return RESULT_OUT_OF_MEMORY;
   }

   pG->m_nTurnNumber = 0;
   MonopolyBoardCreate( &pG->m_pBoard );

   pG->m_ppPlayers = NULL;
   struct MonopolyPlayer** ppPlayers = malloc( numPlayers * sizeof( struct MonopolyPlayer* ) );

   for ( int nPlayer = 0; nPlayer < numPlayers; nPlayer++ )
   {
      if ( RESULT_OK != MonopolyPlayerCreate( &ppPlayers[nPlayer] ) )
      {
         //Rollback: TODO
      }
   }
   pG->m_ppPlayers = ppPlayers;
   pG->m_nNumPlayers = numPlayers;

   //Set all players on start position
   struct MonopolyLocation* pStartOnGo = MonopolyBoardGetSpot( pG->m_pBoard, 0 );
   assert( pStartOnGo->m_eLocationType == Go );
   for ( int nPlayer = 0; nPlayer < numPlayers; nPlayer++ )
   {
      MonopolyLocationSetPlayerPosition( GetPlayer( pG, nPlayer ), pStartOnGo );
   }

   pG->m_pPlayersTurn = pG->m_ppPlayers[0];

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

struct MonopolyPlayer* MonopolyGameWhosTurn( struct MonopolyGame* pGame )
{
   return pGame->m_pPlayersTurn;
}

void MonopolyGamePlayerRollsForTurn( struct MonopolyGame* pGame, struct MonopolyPlayer* pPlayerRolling, int* pDice1, int* pDice2 )
{
   if ( MonopolyGameWhosTurn( pGame ) != pPlayerRolling )
   {
      assert( 0 );
      return;
   }

   int dice1 = ( rand() % 6 ) + 1;
   if ( pDice1 )
      *pDice1 = dice1;

   int dice2 = ( rand() % 6 ) + 1;
   if ( pDice2 )
      *pDice2 = dice2;

   //TODO: Add to roll history

   //TODO Check for doubles

   int total = dice1 + dice2;

   struct MonopolyLocation* pCurrentLocation = MonopolyPlayerGetLocation( pPlayerRolling );
   struct MonopolyLocation* pNewLocation = MonopolyBoardRelativeLocation( pGame->m_pBoard, pCurrentLocation, total );

   MonopolyLocationSetPlayerPosition( pPlayerRolling, pNewLocation );
}

struct MonopolyPlayer* GetPlayer( struct MonopolyGame* pGame, int nIndex )
{
   return pGame->m_ppPlayers[nIndex];
}

