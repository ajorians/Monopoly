#ifndef MONOPOLYPLAYER_H
#define MONOPOLYPLAYER_H

#include "Result.h"
#include "MonopolyCallbacks.h"

struct MonopolyLocation;

struct MonopolyPlayer
{
   int m_nMoney;//TODO: Move to different class?
   struct MonopolyLocation* m_pLocation;

   PlayerMovedFunc m_callbackPlayerMoved;
};

result MonopolyPlayerCreate( struct MonopolyPlayer** ppPlayer, struct MonopolyPlayerCallbacks* pPlayerCallbacks );
result MonopolyPlayerFree( struct MonopolyPlayer** ppPlayer );

void MonopolyLocationSetPlayerPosition( struct MonopolyPlayer* pPlayer, struct MonopolyLocation* pLocation );

//Note this can return null if player is bankrupt
struct MonopolyLocation* MonopolyPlayerGetLocation( struct MonopolyPlayer* pPlayer );

#endif // MONOPOLYLOCATION_H
