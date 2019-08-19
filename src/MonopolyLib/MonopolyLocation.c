#include "MonopolyLocationLib.h"

#ifdef _TINSPIRE
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

struct MonopolyLocation
{
   char m_strName[64];
   int m_nCost;
};

result MonopolyLocationLibCreate( MonopolyLocationLib* api, const char* pstrName, int nCost )
{
   struct MonopolyLocation* pL;

   pL = malloc( sizeof( struct MonopolyLocation ) );
   if ( pL == NULL )
   {//Out of memory
      return RESULT_OUT_OF_MEMORY;
   }
   strcpy( pL->m_strName, pstrName );
   pL->m_nCost = nCost;

   *api = pL;

   return RESULT_OK;
}

result MonopolyLocationLibFree( MonopolyLocationLib* api )
{
   struct MonopolyLocation* pL;

   pL = *api;

   free( pL );
   *api = NULL;
   return RESULT_OK;
}

const char* MonopolyLocationGetName( MonopolyLocationLib api )
{
   struct MonopolyLocation* pL = ( struct MonopolyLocation* )api;

   return pL->m_strName;
}
