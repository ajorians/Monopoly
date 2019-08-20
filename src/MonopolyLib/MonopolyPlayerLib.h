#ifndef MONOPOLYPLAYER_H
#define MONOPOLYPLAYER_H

#include "Result.h"
#include "MonopolyLibTypes.h"

result MonopolyPlayerLibCreate( MonopolyPlayerLib* api );
result MonopolyPlayerLibFree( MonopolyPlayerLib* api );

const char* MonopolyLocationGetName( MonopolyLocationLib api );

#endif // MONOPOLYLOCATION_H
