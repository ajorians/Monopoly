#ifndef MONOPOLYBOARD_H
#define MONOPOLYBOARD_H

#include "Result.h"
#include "MonopolyLibTypes.h"

result MonopolyBoardLibCreate( MonopolyBoardLib* api );
result MonopolyBoardLibFree( MonopolyBoardLib* api );

MonopolyLocationLib MonopolyBoardGetSpot( MonopolyBoardLib* api, int nIndex );

#endif // MONOPOLYBOARD_H
