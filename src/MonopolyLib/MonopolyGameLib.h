#ifndef MONOPOLYGAME_H
#define MONOPOLYGAME_H

#include "Result.h"

typedef void* MonopolyGameLib;

result MonopolyGameLibCreate( MonopolyGameLib* api );
result MonopolyGameLibFree( MonopolyGameLib* api );

#endif // MONOPOLYGAME_H
