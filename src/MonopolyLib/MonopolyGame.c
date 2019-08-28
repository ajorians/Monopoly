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
                           struct MonopolyGameCallbacks* pGameCallbacks,
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
   pG->m_callbackPropertyPurchased = pGameCallbacks->m_PropertyPurchasedCallback;
   pG->m_callbackPropertyDeclinedPurchase = pGameCallbacks->m_PropertyDeclinedPurchaseCallback;

   pG->m_pResponseHead = NULL;

   //Set all players on start position
   struct MonopolyLocation* pStartOnGo = MonopolyBoardGetSpot( pG->m_pBoard, 0 );
   assert( pStartOnGo->m_eLocationType == Go );
   for ( int nPlayer = 0; nPlayer < numPlayers; nPlayer++ )
   {
      MonopolyLocationSetPlayerPosition( GetPlayer( pG, nPlayer ), pStartOnGo );
   }

   pG->m_pPlayersTurn = pG->m_ppPlayers[0];
   struct MonopolyGameAwaitingResponse* pResponse = malloc( sizeof( struct MonopolyGameAwaitingResponse ) );
   pResponse->m_eResponseWaitingOn = RollForTurn;
   pResponse->m_pPlayerWaitingOn = pG->m_pPlayersTurn;
   pResponse->m_pNext = pG->m_pResponseHead;

   pG->m_pResponseHead = pResponse;

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

   struct MonopolyGameAwaitingResponse* pResponse = pGame->m_pResponseHead;
   if ( pResponse->m_eResponseWaitingOn != RollForTurn || pResponse->m_pPlayerWaitingOn != pPlayerRolling )
   {
      return;//TODO: Add error code
   }

   pGame->m_pResponseHead = pResponse->m_pNext;
   free( pResponse );

   MonopolyDiceRoll( pGame->m_pDice );

   //TODO: Add to roll history

   //TODO Check for doubles

   int total = MonopolyDiceGetTotal( pGame->m_pDice );

   struct MonopolyLocation* pCurrentLocation = MonopolyPlayerGetLocation( pPlayerRolling );
   struct MonopolyLocation* pNewLocation = MonopolyBoardRelativeLocation( pGame->m_pBoard, pCurrentLocation, total );

   MonopolyLocationSetPlayerPosition( pPlayerRolling, pNewLocation );

   if ( MonopolyLocationIsPurchasableLocation( pNewLocation ) && pNewLocation->m_pOwner == NULL )
   {
      //Do you want to buy this property?
      struct MonopolyGameAwaitingResponse* pResponseWantToBuy = malloc( sizeof( struct MonopolyGameAwaitingResponse ) );
      pResponseWantToBuy->m_eResponseWaitingOn = PropertyForPurchase;
      pResponseWantToBuy->m_pPlayerWaitingOn = pPlayerRolling;
      pResponseWantToBuy->m_pNext = pGame->m_pResponseHead;

      pGame->m_pResponseHead = pResponseWantToBuy;
   }
}

void MonopolyGameEndCurrentTurn( struct MonopolyGame* pGame, struct MonopolyPlayer* pPlayerEndingTurn )
{
   if ( MonopolyGameWhosTurn( pGame ) != pPlayerEndingTurn )
   {
      assert( 0 );
      return;
   }

   struct MonopolyGameAwaitingResponse* pResponse = pGame->m_pResponseHead;
   if ( pResponse != NULL )
   {
      //Something wasn't finished yet.  Perhaps a player must mortgage or something.  Cannot end turn.
      return;//TODO: Add error code
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

   //TODO check for game over

   struct MonopolyGameAwaitingResponse* pResponseRollForTurn = malloc( sizeof( struct MonopolyGameAwaitingResponse ) );
   pResponseRollForTurn->m_eResponseWaitingOn = RollForTurn;
   pResponseRollForTurn->m_pPlayerWaitingOn = pGame->m_pPlayersTurn;
   pResponseRollForTurn->m_pNext = pGame->m_pResponseHead;

   pGame->m_pResponseHead = pResponse;
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

   if ( pGame->m_callbackPropertyPurchased != NULL )
   {
      ( pGame->m_callbackPropertyPurchased )( pGame, pPlayer, pLocation, howMuch );
   }
}

void MonopolyGamePlayerDeclinesPropertyPurchase( struct MonopolyGame* pGame, struct MonopolyPlayer* pPlayer, struct MonopolyLocation* pLocation )
{
   if ( pGame->m_callbackPropertyDeclinedPurchase != NULL )
   {
      ( pGame->m_callbackPropertyDeclinedPurchase )( pGame, pPlayer, pLocation );
   }
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

