#include "MonopolyGame.h"

#include "MonopolyBoard.h"
#include "MonopolyPlayer.h"
#include "MonopolyLocation.h"
#include "MonopolyDice.h"

#ifdef _TINSPIRE
#else
#include <stdlib.h>
#include <assert.h>
#endif

struct MonopolyPlayer* GetPlayer( struct MonopolyGame* pGame, int nIndex );
int GetPlayerIndex( struct MonopolyGame* pGame, struct MonopolyPlayer* pPlayer );

result MonopolyGameCreate( struct MonopolyGame** ppGame,
                           int numPlayers,
                           struct MonopolyPlayerCallbacks* pPlayerCallbacks,
                           struct MonopolyBoardCallbacks* pBoardCallbacks,
                           struct MonopolyDiceCallbacks* pDiceCallbacks )
{
   struct MonopolyGame* pG;

   pG = malloc( sizeof( struct MonopolyGame ) );
   if ( pG == NULL )
   {//Out of memory
      return RESULT_OUT_OF_MEMORY;
   }

   pG->m_nTurnNumber = 0;
   MonopolyBoardCreate( &pG->m_pBoard, pBoardCallbacks );

   pG->m_ppPlayers = NULL;
   struct MonopolyPlayer** ppPlayers = malloc( numPlayers * sizeof( struct MonopolyPlayer* ) );

   for ( int nPlayer = 0; nPlayer < numPlayers; nPlayer++ )
   {
      if ( RESULT_OK != MonopolyPlayerCreate( &ppPlayers[nPlayer], pPlayerCallbacks ) )
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

   MonopolyDiceCreate( &pG->m_pDice, pDiceCallbacks );

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
   MonopolyDiceFree( &pG->m_pDice );

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

void MonopolyGamePlayerRollsForTurn( struct MonopolyGame* pGame, struct MonopolyPlayer* pPlayerRolling )
{
   if ( MonopolyGameWhosTurn( pGame ) != pPlayerRolling )
   {
      assert( 0 );
      return;
   }

   MonopolyDiceRoll( pGame->m_pDice );

   //TODO: Add to roll history

   //TODO Check for doubles

   int total = MonopolyDiceGetTotal( pGame->m_pDice );

   struct MonopolyLocation* pCurrentLocation = MonopolyPlayerGetLocation( pPlayerRolling );
   struct MonopolyLocation* pNewLocation = MonopolyBoardRelativeLocation( pGame->m_pBoard, pCurrentLocation, total );

   MonopolyLocationSetPlayerPosition( pPlayerRolling, pNewLocation );
}

void MonopolyGameEndCurrentTurn( struct MonopolyGame* pGame, struct MonopolyPlayer* pPlayerEndingTurn )
{
   if ( MonopolyGameWhosTurn( pGame ) != pPlayerEndingTurn )
   {
      assert( 0 );
      return;
   }

   int nPlayerIndex = GetPlayerIndex( pGame, pPlayerEndingTurn );

   //TODO: Skip over bankrupted players

   nPlayerIndex++;
   if ( nPlayerIndex >= pGame->m_nNumPlayers )
   {
      pGame->m_nTurnNumber++;
   }
   nPlayerIndex %= pGame->m_nNumPlayers;

   pGame->m_pPlayersTurn = GetPlayer( pGame, nPlayerIndex );
}

void MonopolyGamePlayerPurchacesProperty( struct MonopolyGame* pGame, struct MonopolyPlayer* pPlayer, struct MonopolyLocation* pLocation, int howMuch )
{
   //Somebody has to be on this property in order to purchase it; even for auction
   int nSomebodyOnSpot = 0;
   for ( int i = 0; i < pGame->m_nNumPlayers; i++ )
   {
      if ( MonopolyPlayerGetLocation( GetPlayer( pGame, i ) ) == pLocation )
      {
         nSomebodyOnSpot = 1;
         break;
      }
   }

   if ( nSomebodyOnSpot == 0 )
   {
      assert( 0 );
      return;
   }

   pLocation->m_pOwner = pPlayer;
   pPlayer->m_nMoney -= howMuch;
}

struct MonopolyPlayer* GetPlayer( struct MonopolyGame* pGame, int nIndex )
{
   assert( GetPlayerIndex( pGame, pGame->m_ppPlayers[nIndex] ) == nIndex );
   return pGame->m_ppPlayers[nIndex];
}

int GetPlayerIndex( struct MonopolyGame* pGame, struct MonopolyPlayer* pPlayer )
{
   for ( int i = 0; i < pGame->m_nNumPlayers; i++ )
   {
      if ( pGame->m_ppPlayers[i] == pPlayer )
      {
         return i;
      }
   }
   assert( 0 );
   return -1;
}

