#ifndef MONOPOLYLOCATION_H
#define MONOPOLYLOCATION_H

#include "Result.h"
#include "MonopolyLibTypes.h"

result MonopolyLocationLibCreate( MonopolyLocationLib* api, const char* pstrName, int nCost );
result MonopolyLocationLibFree( MonopolyLocationLib* api );

const char* MonopolyLocationGetName( MonopolyLocationLib api );

#endif // MONOPOLYLOCATION_H
