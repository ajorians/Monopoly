#ifndef MONOPOLYGAME_H
#define MONOPOLYGAME_H

#include "Result.h"
#include "MonopolyLibTypes.h"

result MonopolyGameLibCreate( MonopolyGameLib* api );
result MonopolyGameLibFree( MonopolyGameLib* api );

MonopolyBoardLib MonopolyGameGetBoard( MonopolyGameLib api );

#endif // MONOPOLYGAME_H
