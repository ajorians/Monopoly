#ifndef MONOPOLYLOCATION_H
#define MONOPOLYLOCATION_H

#include "Result.h"
#include "MonopolyCallbacks.h"

struct MonopolyPlayer;

enum LocationType
{
   Go,
   Property,
   Railroad,
   Utility,
   Chance,
   CommunityChest,
   IncomeTax,
   Jail,//Just Visiting
   FreeParking,
   GotoJail,
   LuxuryTax
};

enum BuildType
{
   NothingBuilt,
   OneHouse,
   TwoHouse,
   ThreeHouse,
   FourHouse,
   Hotel
};

struct MonopolyLocation
{
   char m_strName[64];
   enum LocationType m_eLocationType;
   int m_nCost;
   int m_nRent;
   int m_naRentWithHouseHotel[5];
   int m_nMortgage;
   struct MonopolyPlayer* m_pOwner;

   enum BuildType m_eBuildings;

   LocationBuildingChangedFunc m_callbackBuildingsChanged;
};

result MonopolyLocationCreate( struct MonopolyLocation** ppLocation,
                               const char* pstrName,
                               enum LocationType eLocationType,
                               int nCost,
                               int nRent,
                               int naRentWithHouseHotel[5],
                               int nMortgate,
                               struct MonopolyLocationCallbacks* pLocationCallbacks );
result MonopolyLocationFree( struct MonopolyLocation** ppLocation );

const char* MonopolyLocationGetName( struct MonopolyLocation* pLocation );

#endif // MONOPOLYLOCATION_H
