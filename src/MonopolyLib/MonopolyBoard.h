#ifndef MONOPOLYBOARD_H
#define MONOPOLYBOARD_H

#include "Result.h"
#include "MonopolyCallbacks.h"

struct MonopolyLocation;

struct MonopolyBoard
{
   struct MonopolyLocation** m_ppLocations;
   int m_nNumLocations;
};

result MonopolyBoardCreate( struct MonopolyBoard** ppBoard, struct MonopolyBoardCallbacks* pCallbacks );
result MonopolyBoardFree( struct MonopolyBoard** ppBoard );

struct MonopolyLocation* MonopolyBoardGetSpot( struct MonopolyBoard* pBoard, int nIndex );

struct MonopolyLocation* MonopolyBoardRelativeLocation( struct MonopolyBoard* pBoard, struct MonopolyLocation* pLocation, int offsetSpots );

#endif // MONOPOLYBOARD_H
