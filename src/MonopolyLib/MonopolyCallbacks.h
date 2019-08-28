#ifndef MONOPOLYCALLBACKS_H
#define MONOPOLYCALLBACKS_H

struct MonopolyPlayer;
struct MonopolyBoard;
struct MonopolyLocation;
struct MonopolyDice;
enum BuildType;

//Player callbacks
typedef void( *PlayerMovedFunc )( struct MonopolyPlayer* pPlayer, struct MonopolyLocation* pLocationOld, struct MonopolyLocation* pLocationNew );

//Location callbacks
typedef void( *LocationBuildingChangedFunc )( struct MonopolyLocation* pLocation, enum BuildType eOldBuildings, enum BuildType eNewBuildings );

//Board callbacks
typedef void( *BoardUnknownFunc )( struct MonopolyBoard* pBoard, int nTODONotYes );

//Game callbacks
typedef void( *GamePropertyPurchasedFunc )( struct MonopolyGame* pGame, struct MonopolyPlayer* pPlayerPurchasingProperty, struct MonopolyLocation* pLocationPurchased );
typedef void( *GamePropertyDeclinedPurchasedFunc )( struct MonopolyGame* pGame, struct MonopolyPlayer* pPlayerPurchasingProperty, struct MonopolyLocation* pLocationPurchased );


//Dice callbacks
typedef void( *DiceRolledFunc )( struct MonopolyDice* pDice, int nNumDice, int arrDiceValues[] );

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

struct MonopolyGameCallbacks
{
   GamePropertyPurchasedFunc m_PropertyPurchasedCallback;
   GamePropertyDeclinedPurchasedFunc m_PropertyDeclinedPurchaseCallback;
};

struct MonopolyDiceCallbacks
{
   DiceRolledFunc m_DiceRolledCallback;
};

#endif // MONOPOLYCALLBACKS_H
