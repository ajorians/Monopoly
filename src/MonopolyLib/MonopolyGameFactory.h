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

   //Location callbacks
   struct MonopolyLocationCallbacks m_LocationCallbacks;

   //Board callbacks
   struct MonopolyBoardCallbacks m_BoardCallbacks;

   //Dice callbacks
   struct MonopolyDiceCallbacks m_DiceCallbacks;
};

result MonopolyGameFactoryCreate( struct MonopolyGameFactory** ppGameFactory );
result MonopolyGameFactoryFree( struct MonopolyGameFactory** ppGameFactory );

struct MonopolyGame* MonopolyGameFactoryCreateGame( struct MonopolyGameFactory* pGameFactory );

result MonopolyGameFactorySetNumberOfPlayers( struct MonopolyGameFactory* pGameFactory, int nNumPlayers );
result MonopolyGameFactorySetPlayerCallbacks( struct MonopolyGameFactory* pGameFactory, struct MonopolyPlayerCallbacks* pPlayerCallbacks );


#endif // MONOPOLYGAMEFACTORY_H
