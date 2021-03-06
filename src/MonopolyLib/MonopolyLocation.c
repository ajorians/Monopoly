#include "MonopolyLocation.h"

#ifdef _TINSPIRE
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

result MonopolyLocationCreate( struct MonopolyLocation** ppLocation,
                               const char* pstrName,
                               enum LocationType eLocationType,
                               int nCost,
                               int nRent,
                               int naRentWithHouseHotel[5],
                               int nMortgate,
                               struct MonopolyLocationCallbacks* pLocationCallbacks )
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

   pL->m_pOwner = NULL;

   pL->m_eBuildings = NothingBuilt;

   pL->m_callbackBuildingsChanged = pLocationCallbacks->m_BuildingsChangedCallback;

   *ppLocation = pL;

   return RESULT_OK;
}

result MonopolyLocationFree( struct MonopolyLocation** ppLocation )
{
   struct MonopolyLocation* pL;

   pL = *ppLocation;

   free( pL );
   *ppLocation = NULL;
   return RESULT_OK;
}

const char* MonopolyLocationGetName( struct MonopolyLocation* pLocation )
{
   return pLocation->m_strName;
}

enum LocationType MonopolyLocationGetLocationType( struct MonopolyLocation* pLocation )
{
   return pLocation->m_eLocationType;
}

int MonopolyLocationIsPurchasableLocation( struct MonopolyLocation* pLocation )
{
   if ( pLocation->m_eLocationType == Property ||
        pLocation->m_eLocationType == Railroad ||
        pLocation->m_eLocationType == Utility )
   {
      return 1;
   }

   return 0;
}
