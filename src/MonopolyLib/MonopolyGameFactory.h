#ifndef MONOPOLYGAMEFACTORY_H
#define MONOPOLYGAMEFACTORY_H

#include "Result.h"

struct MonopolyGame;

struct MonopolyGameFactory
{
   int m_nNumberOfPlayers;
};

result MonopolyGameFactoryCreate( struct MonopolyGameFactory** ppGameFactory );
result MonopolyGameFactoryFree( struct MonopolyGameFactory** ppGameFactory );

struct MonopolyGame* MonopolyGameFactoryCreateGame( struct MonopolyGameFactory* pGameFactory );

result MonopolyGameFactorySetNumberOfPlayers( struct MonopolyGameFactory* pGameFactory, int nNumPlayers );


#endif // MONOPOLYGAMEFACTORY_H
