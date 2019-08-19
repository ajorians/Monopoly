#ifdef _TINSPIRE
#include <nspireio/nspireio.h>
#else
#include <stdio.h>
#include <stdlib.h>
#endif

#include <MonopolyGameLib.h>

#ifdef _TINSPIRE
#define PRINT  nio_printf
#else
#define PRINT  printf
#endif

#ifdef _TINSPIRE
#define PRINT_FUNC PRINT("%s", __func__);
#else
#define PRINT_FUNC PRINT("%s", __FUNCTION__);
#endif

#define TEST_SUCCEEDED  (0)
#define TEST_FAILED     (1)

int TestConstruction()
{
   MonopolyGameLib api;
   PRINT_FUNC;
   if ( RESULT_OK != MonopolyGameLibCreate( &api ) )
      return TEST_FAILED;

   if ( RESULT_OK != MonopolyGameLibFree( &api ) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}


//=====================================================================
typedef int( *testfunc )( );
testfunc g_Tests[] =
{
   TestConstruction
};

void RunTests()
{
   unsigned i;
   for ( i = 0; i < sizeof( g_Tests ) / sizeof( testfunc ); i++ )
   {

      int nRet = g_Tests[i]();
      if ( nRet == TEST_SUCCEEDED )
      {
         PRINT( "........OK\n" );
      }
      else
      {
         PRINT( "........FAIL\n" );
      }
   }
}

