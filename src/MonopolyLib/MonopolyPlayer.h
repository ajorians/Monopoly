#ifndef MONOPOLYPLAYER_H
#define MONOPOLYPLAYER_H

#include "Result.h"

struct MonopolyPlayer
{
   int m_nMoney;//TODO: Move
};

result MonopolyPlayerCreate( struct MonopolyPlayer** ppPlayer );
result MonopolyPlayerFree( struct MonopolyPlayer** ppPlayer );

const char* MonopolyLocationGetName( struct MonopolyPlayer* pPlayer );

#endif // MONOPOLYLOCATION_H
