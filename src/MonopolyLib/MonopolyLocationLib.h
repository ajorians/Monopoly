#ifndef MONOPOLYLOCATION_H
#define MONOPOLYLOCATION_H

#include "Result.h"
#include "MonopolyLibTypes.h"

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

result MonopolyLocationLibCreate( MonopolyLocationLib* api, const char* pstrName, enum LocationType eLocationType, int nCost, int nRent, int naRentWithHouseHotel[5], int nMortgate );
result MonopolyLocationLibFree( MonopolyLocationLib* api );

const char* MonopolyLocationGetName( MonopolyLocationLib api );

#endif // MONOPOLYLOCATION_H
