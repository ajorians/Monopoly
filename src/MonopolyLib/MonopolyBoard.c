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

struct DefaultLocations
{
   const char* pstrName;
   enum LocationType eType;
   int nCost;
   int nRent;
   int naRentWithHousesHotel[5];
   int nMortgage;
} g_DefaultLocations[] = 
{
   //Name                   Type            Cost Rent Rent with houuses and hotel    Mortgage
   { "Go",                   Go,             -1, -1,  { -1,  -1,  -1,   -1,   -1   },  -1 },
   { "Mediterranean Avenue", Property,       60,  2,  { 10,  30,  90,   160,  250  },  30 },
   { "Community Chest",      CommunityChest, -1, -1,  { -1,  -1,  -1,   -1,   -1   },  -1 },
   { "Baltic Avenue",        Property,       60,  4,  { 20,  60,  180,  320,  450  },  30},
   { "Income Tax",           IncomeTax,      -1, -1,  { -1,  -1,  -1,   -1,   -1   },  -1 },
   { "Reading Railroad",     Railroad,       200, -1, { -1,  -1,  -1,   -1,   -1   }, 100 },
   { "Oriental Avenue",      Property,       100, 6,  { 30,  90,  270,  400,  550  },  50 },
   { "Chance",               Chance,         -1, -1,  { -1,  -1,  -1,   -1,   -1   },  -1 },
   { "Vermont Avenue",       Property,       100, 6,  { 30,  90,  270,  400,  550  },  50 },
   { "Connecticut Avenue",   Property,       120, 8,  { 40,  100, 300,  450,  600  },  60 },
   { "Jail/Just Visiting",   Jail,           -1, -1,  { -1,  -1,  -1,   -1,   -1   },  -1 },
   { "St.Charles Place",     Property,       140, 10, { 50,  150, 450,  625,  750  },  70 },
   { "Electric Company",     Utility,        150, -1, { -1,  -1,  -1,   -1,   -1   },  75 },
   { "States Avenue",        Property,       140, 10, { 50,  150, 450,  625,  750  },  70 },
   { "Virginia Avenue",      Property,       160, 12, { 60,  180, 500,  700,  900  },  80 },
   { "Pennsylvania Railroad",Railroad,       200, -1, { -1,  -1,  -1,   -1,   -1   }, 100 },
   { "St.James Place",       Property,       180, 14, { 70,  200, 550,  750,  950  },  90 },
   { "Community Chest",      CommunityChest, -1, -1,  { -1,  -1,  -1,   -1,   -1   },  -1 },
   { "Tennessee Avenue",     Property,       180, 14, { 70,  200, 550,  750,  950  },  90 },
   { "New York Avenue",      Property,       200, 16, { 80,  220, 600,  800,  1000 }, 100 },
   { "Free Parking",         FreeParking,    -1, -1,  { -1,  -1,  -1,   -1,   -1   },  -1 },
   { "Kentucky Avenue",      Property,       220, 18, { 90,  250, 700,  875,  1050 }, 110 },
   { "Chance",               Chance,         -1, -1,  { -1,  -1,  -1,   -1,   -1   },  -1 },
   { "Indiana Avenue",       Property,       220, 18, { 90,  250, 700,  875,  1050 }, 110 },
   { "Illinois Avenue",      Property,       240, 20, { 100, 300, 750,  925,  1100 }, 120 },
   { "B. & O. Railroad",     Railroad,       200, -1, { -1,  -1,  -1,   -1,   -1   }, 100 },
   { "Atlantic Avenue",      Property,       260, 22, { 110, 330, 800,  975,  1150 }, 130 },
   { "Ventnor Avenue",       Property,       260, 22, { 110, 330, 800,  975,  1150 }, 130 },
   { "Water Works",          Utility,        150, -1, { -1,  -1,  -1,   -1,   -1   },  75 },
   { "Marvin Gardens",       Property,       280, 24, { 120, 360, 850,  1025, 1200 }, 140 },
   { "Go to Jail",           GotoJail,        -1, -1, { -1,  -1,  -1,   -1,   -1   },  75 },
   { "Pacific Avenue",       Property,       300, 26, { 130, 390, 900,  1100, 1275 }, 150 },
   { "North Carolina Avenue",Property,       300, 26, { 130, 390, 900,  1100, 1275 }, 150 },
   { "Community Chest",      CommunityChest, -1, -1,  { -1,  -1,  -1,   -1,   -1   },  -1 },
   { "Pennsylvania Avenue",  Property,       320, 28, { 150, 450, 1000, 1200, 1400 }, 160 },
   { "Short Line Railroad",  Railroad,       200, -1, { -1,  -1,  -1,   -1,   -1   }, 100 },
   { "Chance",               Chance,         -1, -1,  { -1,  -1,  -1,   -1,   -1   },  -1 },
   { "Park Place",           Property,       350, 35, { 175, 500, 1100, 1300, 1500 }, 175 },
   { "Luxury Tax",           LuxuryTax,      -1, -1,  { -1,  -1,  -1,   -1,   -1   },  -1 },
   { "Boardwalk",            Property,       400, 50, { 200, 600, 1400, 1700, 2000 }, 200 }
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
         if ( RESULT_OK != MonopolyLocationLibCreate( pLocation, 
                                                      g_DefaultLocations[nLocation].pstrName,
                                                      g_DefaultLocations[nLocation].eType,
                                                      g_DefaultLocations[nLocation].nCost,
                                                      g_DefaultLocations[nLocation].nRent,
                                                      g_DefaultLocations[nLocation].naRentWithHousesHotel,
                                                      g_DefaultLocations[nLocation].nMortgage ) )
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
