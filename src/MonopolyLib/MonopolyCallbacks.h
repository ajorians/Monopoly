#ifndef MONOPOLYCALLBACKS_H
#define MONOPOLYCALLBACKS_H

struct MonopolyPlayer;
struct MonopolyLocation;
enum BuildType;

//Player callbacks
typedef void( *PlayerMovedFunc )( struct MonopolyPlayer* pPlayer, struct MonopolyLocation* pLocationOld, struct MonopolyLocation* pLocationNew );

//Location callbacks
typedef void( *LocationBuildingChangedFunc )( struct MonopolyLocation* pLocation, enum BuildType eOldBuildings, enum BuildType eNewBuildings );

//Board callbacks
typedef void( *BoardUnknownFunc )( struct MonopolyBoard* pBoard, int nTODONotYes );

//Game callbacks

//
struct MonopolyPlayerCallbacks
{
   PlayerMovedFunc m_PlayerMovedCallback;
};

struct MonopolyLocationCallbacks
{
   LocationBuildingChangedFunc m_BuildingsChangedCallback;
};

struct MonopolyBoardCallbacks
{
   BoardUnknownFunc m_SomethingChangedCallback;

   struct MonopolyLocationCallbacks* m_pLocationCallbacks;
};

#endif // MONOPOLYCALLBACKS_H
