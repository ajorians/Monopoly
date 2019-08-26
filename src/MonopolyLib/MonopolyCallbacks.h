#ifndef MONOPOLYCALLBACKS_H
#define MONOPOLYCALLBACKS_H

struct MonopolyPlayer;
struct MonopolyLocation;

//Player callbacks
typedef void( *PlayerMovedFunc )( struct MonopolyPlayer* pPlayer, struct MonopolyLocation* pLocationOld, struct MonopolyLocation* pLocationNew );

struct MonopolyPlayerCallbacks
{
   PlayerMovedFunc m_PlayerMovedCallback;
};


#endif // MONOPOLYCALLBACKS_H
