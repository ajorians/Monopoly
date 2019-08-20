#ifndef MONOPOLYBOARD_H
#define MONOPOLYBOARD_H

#include "Result.h"

struct MonopolyLocation;

struct MonopolyBoard
{
   struct MonopolyLocation** m_ppLocations;
   int m_nNumLocations;
};

result MonopolyBoardCreate( struct MonopolyBoard** ppBoard );
result MonopolyBoardFree( struct MonopolyBoard** ppBoard );

struct MonopolyLocation* MonopolyBoardGetSpot( struct MonopolyBoard* pBoard, int nIndex );

#endif // MONOPOLYBOARD_H