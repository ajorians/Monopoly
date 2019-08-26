#ifndef MONOPOLYGAMEFACTORY_H
#define MONOPOLYGAMEFACTORY_H

#include "Result.h"
#include "MonopolyCallbacks.h"

struct MonopolyGame;

struct MonopolyGameFactory
{
   int m_nNumberOfPlayers;

   //Player callbacks
   struct MonopolyPlayerCallbacks m_PlayerCallbacks;
};

result MonopolyGameFactoryCreate( struct MonopolyGameFactory** ppGameFactory );
result MonopolyGameFactoryFree( struct MonopolyGameFactory** ppGameFactory );

struct MonopolyGame* MonopolyGameFactoryCreateGame( struct MonopolyGameFactory* pGameFactory );

result MonopolyGameFactorySetNumberOfPlayers( struct MonopolyGameFactory* pGameFactory, int nNumPlayers );
result MonopolyGameFactorySetPlayerCallbacks( struct MonopolyGameFactory* pGameFactory, struct MonopolyPlayerCallbacks* pPlayerCallbacks );


#endif // MONOPOLYGAMEFACTORY_H
