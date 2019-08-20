#ifdef _TINSPIRE
#include <nspireio/nspireio.h>
#else
#include <stdio.h>
#include <stdlib.h>
#endif

#include <MonopolyGame.h>
#include <MonopolyBoard.h>
#include <MonopolyLocation.h>
#include <Result.h>

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
   struct MonopolyGame* pGame;
   PRINT_FUNC;
   if ( RESULT_OK != MonopolyGameCreate( &pGame ) )
      return TEST_FAILED;

   if ( RESULT_OK != MonopolyGameFree( &pGame ) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}

int TestSomething()
{
   struct MonopolyGame* pGame;
   PRINT_FUNC;
   if ( RESULT_OK != MonopolyGameCreate( &pGame ) )
      return TEST_FAILED;

   struct MonopolyBoard* pBoard = MonopolyGameGetBoard( pGame );
   struct MonopolyLocation* pSpot = MonopolyBoardGetSpot( pBoard, 0 );
   const char* pstrName = MonopolyLocationGetName( pSpot );

   if ( RESULT_OK != MonopolyGameFree( &pGame ) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}


//=====================================================================
typedef int( *testfunc )( );
testfunc g_Tests[] =
{
   TestConstruction,
   TestSomething
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

