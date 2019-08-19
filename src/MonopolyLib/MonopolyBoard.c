#include "MonopolyBoardLib.h"
#include "MonopolyLocationLib.h"

#ifdef _TINSPIRE
#else
#include <stdlib.h>
#endif

struct MonopolyBoardSide
{
   MonopolyLocationLib* m_pLocations;
   int m_nNumLocations;
};

struct MonopolyBoard
{
   struct MonopolyBoardSide* m_pBoardSides;
   int m_nNumSides;
};

result MonopolyBoardLibCreate( MonopolyBoardLib* api )
{
   struct MonopolyBoard* pB;

   pB = malloc( sizeof( struct MonopolyBoard ) );
   if ( pB == NULL )
   {//Out of memory
      return RESULT_OUT_OF_MEMORY;
   }

   const int NumSides = 4;
   const int NumPlacesPerSide = 10;

   pB->m_pBoardSides = NULL;
   struct MonopolyBoardSide* pSides = malloc( NumSides * sizeof( struct MonopolyBoard ) );

   for ( int nSide = 0; nSide < NumSides; nSide++ )
   {
      struct MonopolyBoardSide* pSide = &pSides[nSide];
      pSide->m_pLocations = malloc( NumPlacesPerSide * sizeof( MonopolyLocationLib ) );
      for ( int nLocation = 0; nLocation < NumPlacesPerSide; nLocation++ )
      {
         MonopolyLocationLib* pLocation = &pSide->m_pLocations[nLocation];
         if ( RESULT_OK != MonopolyLocationLibCreate( pLocation, "Mediterranean Avenue", 100 ) )
         {
            //Rollback: TODO
         }
      }
      pSide->m_nNumLocations = NumPlacesPerSide;
   }
   pB->m_pBoardSides = pSides;
   pB->m_nNumSides = NumSides;

   *api = pB;

   return RESULT_OK;
}

result MonopolyBoardLibFree( MonopolyBoardLib* api )
{
   struct MonopolyBoard* pB;

   pB = *api;

   struct MonopolyBoardSide* pSides = pB->m_pBoardSides;
   for( int nSide = 0; nSide < pB->m_nNumSides; nSide++ )
   {
      struct MonopolyBoardSide* pSide = &pSides[nSide];

      for( int nLocation = 0; nLocation < pSide->m_nNumLocations; nLocation++ )
      {
         MonopolyLocationLib* pLocation = &pSide->m_pLocations[nLocation];

         MonopolyLocationLibFree( pLocation );
      }
      free( pSide->m_pLocations );
      pSide->m_pLocations = NULL;
   }
   free( pB->m_pBoardSides );
   pB->m_pBoardSides = NULL;

   free( pB );
   *api = NULL;
   return RESULT_OK;
}

MonopolyLocationLib MonopolyBoardGetSpot( MonopolyBoardLib* api, int nIndex )
{
   struct MonopolyBoard* pB = ( struct MonopolyBoard* )api;

   int nSpotIndex = 0;
   struct MonopolyBoardSide* pSides = pB->m_pBoardSides;
   for ( int nSide = 0; nSide < pB->m_nNumSides; nSide++ )
   {
      struct MonopolyBoardSide* pSide = &pSides[nSide];

      for ( int nLocation = 0; nLocation < pSide->m_nNumLocations; nLocation++ )
      {
         MonopolyLocationLib* pLocation = &pSide->m_pLocations[nLocation];

         if ( nSpotIndex == nIndex )
         {
            return *pLocation;
         }

         nSpotIndex++;
      }
   }

   return NULL;
}
