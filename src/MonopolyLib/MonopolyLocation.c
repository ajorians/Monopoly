#include "MonopolyLocationLib.h"

#ifdef _TINSPIRE
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

struct MonopolyLocation
{
   char m_strName[64];
   enum LocationType m_eLocationType;
   int m_nCost;
   int m_nRent;
   int m_naRentWithHouseHotel[5];
   int m_nMortgage;
};

result MonopolyLocationLibCreate( MonopolyLocationLib* api, const char* pstrName, enum LocationType eLocationType, int nCost, int nRent, int naRentWithHouseHotel[5], int nMortgate )
{
   struct MonopolyLocation* pL;

   pL = malloc( sizeof( struct MonopolyLocation ) );
   if ( pL == NULL )
   {//Out of memory
      return RESULT_OUT_OF_MEMORY;
   }
   strcpy( pL->m_strName, pstrName );
   pL->m_eLocationType = eLocationType;
   pL->m_nCost = nCost;
   pL->m_nRent = nRent;
   memcpy( pL->m_naRentWithHouseHotel, naRentWithHouseHotel, 5 * sizeof( int ) );
   pL->m_nMortgage = nMortgate;

   *api = pL;

   return RESULT_OK;
}

result MonopolyLocationLibFree( MonopolyLocationLib* api )
{
   struct MonopolyLocation* pL;

   pL = *api;

   free( pL );
   *api = NULL;
   return RESULT_OK;
}

const char* MonopolyLocationGetName( MonopolyLocationLib api )
{
   struct MonopolyLocation* pL = ( struct MonopolyLocation* )api;

   return pL->m_strName;
}
