#include "MonopolyPlayerLib.h"

#ifdef _TINSPIRE
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

struct MonopolyPlayer
{
   int m_nMoney;//TODO: Move
};

result MonopolyPlayerLibCreate( MonopolyPlayerLib* api )
{
   struct MonopolyPlayer* pP;

   pP = malloc( sizeof( struct MonopolyPlayer ) );
   if ( pP == NULL )
   {//Out of memory
      return RESULT_OUT_OF_MEMORY;
   }
   pP->m_nMoney = 1500;

   *api = pP;

   return RESULT_OK;
}

result MonopolyPlayerLibFree( MonopolyPlayerLib* api )
{
   struct MonopolyPlayer* pP;

   pP = *api;

   free( pP );
   *api = NULL;
   return RESULT_OK;
}

