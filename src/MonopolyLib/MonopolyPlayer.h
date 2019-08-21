#ifndef MONOPOLYPLAYER_H
#define MONOPOLYPLAYER_H

#include "Result.h"

struct MonopolyLocation;

struct MonopolyPlayer
{
   int m_nMoney;//TODO: Move to different class?
   struct MonopolyLocation* m_pLocation;
};

result MonopolyPlayerCreate( struct MonopolyPlayer** ppPlayer );
result MonopolyPlayerFree( struct MonopolyPlayer** ppPlayer );

void MonopolyLocationSetPlayerPosition( struct MonopolyPlayer* pPlayer, struct MonopolyLocation* pLocation );

//Note this can return null if player is bankrupt
struct MonopolyLocation* MonopolyPlayerGetLocation( struct MonopolyPlayer* pPlayer );

#endif // MONOPOLYLOCATION_H
