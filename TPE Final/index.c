#include <stdlib.h>
#include <stdio.h>

#include "config/config.h"
#include "dependencies/airportadt/airportADT.h"
#include "dependencies/flightadt/flightADT.h"
#include "dependencies/processfile/processFile.h"
#include "dependencies/queries/queries.h"


#define YEAR_POS 1


int yearIsValid( char* yearString )
{
  int year = atoi( yearString );
  if( year >= 2014 && year <= 2018 )
    return TRUE;
  return FALSE;
}


int main( int argq, char *argv[] )
{
  if( argq == 2 &&  yearIsValid( argv[YEAR_POS] ))
  {

    printf("Starting files processing... \n");
    airportADT ap = processAirports( AIRPORTS);
    flightADT fl = processFlights( FLIGHTS, atoi( argv[YEAR_POS] ));
    printf("Processing: Ready\n");

    printf("Starting Querys...\n");

    movsPerAirport( QUERY1, ap, fl);
    printf("Query #1 STATUS: Ready.\n");

    intMovsPerAirport( QUERY2, ap, fl);
    printf("Query #2 STATUS: Ready.\n");

    flightsPerWeekDay( QUERY3, fl);
    printf("Query #3 STATUS: Ready.\n");

    movesAtoA( QUERY4, ap, fl);
    printf("Query #4 STATUS: Ready.\n");

    freeAirport( ap );
    freeFlight( fl );

    printf("Program ended succesfully\n");

    return 0;
  }
  fprintf(stderr,"Error with the parameters. Aborting\n" );
  return 1;
}
