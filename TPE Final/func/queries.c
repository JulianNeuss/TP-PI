
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../dependencies/flightadt/flightADT.h"
#include "../dependencies/airportadt/airportADT.h"
#include "../dependencies/queries/queries.h"
#include "../config/config.h"

#define DAYINAWEEK 7
#define ARRIVAL 'a'
#define TAKEOFF 't'

static void Error( char* filename )
{
  fprintf(stderr,"Error when trying to create or open %s file\n",filename);
  exit(0);
}

///QUERY 1/////////////////////////////////////////////////////////////////////////////////////////
void printMovsPerAirport( FILE* writer, airportDataType data, int flights )
{
  if( flights > 0 )
  {
    fprintf( writer, "%s;%s;%s;%d\n", data.icao, data.local, data.descr, flights );
  }
}

unsigned runThroughFlights( char* icao, flightADT f )
{
  unsigned flights = 0;
  toBeginFlight( f );
  flightDataType dataAux;

  while( hasNextFlight( f ))
  {
    dataAux = nextFlight( f );
    if(( (strcmp( dataAux.icaoOrig, icao ) == 0 && strcmp(dataAux.movType, MOVTYPE_TAKEOFF) == 0) ||
      (strcmp( dataAux.icaoDest, icao ) == 0 && strcmp(dataAux.movType, MOVTYPE_LANDING) == 0)  ) )
      flights++;
  }

  return flights;
}

void movsPerAirport( char* filename, airportADT ap, flightADT f)
{

  int flights;
  airportDataType dataAux;

  FILE* writer = fopen( filename, "w" );
  if(!writer)
  {
    Error( filename );
  }

  toBeginAirport( ap );
  while( hasNextAirport( ap ))
  {
    dataAux = nextAirport( ap );
    flights = runThroughFlights( dataAux.icao, f );
    printMovsPerAirport( writer, dataAux, flights );
  }
  fclose( writer );
}
///QUERY 2////////////////////////////////////////////////////////////////////////////////////////////
void printIntMovsPerAirport( FILE* writer, airportDataType data, int arrivals, int takeOffs )
{
  if( arrivals > 0 || takeOffs > 0 )
  {
    fprintf( writer, "%s;%s;%d;%d;%d\n", data.icao, data.iata, takeOffs, arrivals, takeOffs + arrivals );
  }
}

void runThroughFlightsInt( char* icao, flightADT f, int* arrivals, int* takeOffs )
{
  toBeginFlight( f );
  flightDataType data;

  while( hasNextFlight( f ))
  {
    data = nextFlight( f );

    if(  ( (strcmp( data.icaoOrig, icao ) == 0 && strcmp(data.movType, MOVTYPE_TAKEOFF) == 0) ||
      (strcmp( data.icaoDest, icao ) == 0 && strcmp(data.movType, MOVTYPE_LANDING) == 0)  )
     && strcmp( data.clasification, CLASIFICATION ) == 0 )
    {
      if( strcmp( data.movType, MOVTYPE_TAKEOFF ) == 0 )
        (*takeOffs)++;
      else
        (*arrivals)++;
    }
  }
}

void intMovsPerAirport( char* filename, airportADT ap, flightADT f)
{
  int arrivals, takeOffs;
  toBeginAirport( ap );
  airportDataType data;
  FILE* writer = fopen( filename, "w" );
  if(!writer)
    Error( filename );

  while( hasNextAirport( ap ))
  {
    data = nextAirport( ap );
    arrivals = takeOffs = 0;

    runThroughFlightsInt( data.icao, f, &arrivals, &takeOffs );
    printIntMovsPerAirport( writer, data, arrivals, takeOffs );

  }

  fclose( writer );
}

///QUERY 3//////////////////////////////////////////////////////////////////////////////////////////
typedef struct week{
	char* dayName;
	long int dayCounter;
}tWeek;

void printsFlightsPerWeek(char *filename, tWeek weekDays[])
{
	FILE *writer = fopen(filename, "w");
  if(!writer)
    Error( filename );

  int i;

  for(i=1; i <= DAYINAWEEK ; i++)
    fprintf(writer, "%s;%ld\n", weekDays[i%7].dayName, weekDays[i%7].dayCounter);

  fclose(writer);
}

void flightsPerWeekDay(char *filename, flightADT fl)
{
  tWeek weekDays[] = {{NONEDAY, 0},{ONEDAY, 0}, {TWOSDAY, 0}, {TREBLESDAY, 0}, {FOURSDAY, 0}, {FIVEDAY, 0}, {SIXADAY, 0}};
  flightDataType flData;
  toBeginFlight(fl);

  int i=0;
  while(hasNextFlight(fl))
  {
    flData = nextFlight(fl);
    weekDays[flData.weekDay].dayCounter++;
    i++;
  }
  printsFlightsPerWeek(filename, weekDays);
}
///QUERY 4//////////////////////////////////////////////////////////////////////////////////////
typedef struct apChild
{
  struct apChild* nextChild;
  char* childIcao;
  unsigned arrivals;
  unsigned takeOffs;
}apChild;
typedef apChild* childNode;

childNode insertChild( childNode n, char* childIcao, char movType, int * error)
{
  int cmp;

  if( n == NULL || ( cmp = strcmp( childIcao, n->childIcao )) < 0 )
  {
    childNode newChild = calloc( 1, sizeof( apChild ));
    if(!newChild)
      (*error) = TRUE;
    else
    {
      (*error) = FALSE;

      newChild->childIcao = childIcao;

      if( movType == ARRIVAL )
        (newChild->arrivals)++;
      else
        (newChild->takeOffs)++;
      newChild->nextChild = n;
      return newChild;
    }
  }
  else if( cmp == 0 )
  {
    if( movType == ARRIVAL )
      (n->arrivals)++;
    else
      (n->takeOffs)++;
  }
  else
    n->nextChild = insertChild( n->nextChild, childIcao, movType, error );
  return n;
}



void printMovesAtoA( char* icaoAp, childNode n, FILE* writer )
{
  if( n != NULL )
  {
    fprintf( writer, "%s;%s;%d;%d\n", icaoAp, n->childIcao, n->takeOffs, n->arrivals );
    printMovesAtoA( icaoAp, n->nextChild, writer );
    free( n );
  }
}




void lookAtoA( FILE* writer, char* icaoAp, flightADT f )
{
  toBeginFlight( f );
  flightDataType data;
  childNode first = NULL;
  int error = FALSE;
  while( hasNextFlight( f ))
  {
    data = nextFlight( f );
    if( strcmp( icaoAp, data.icaoOrig ) == 0 && strcmp( data.movType, MOVTYPE_TAKEOFF) == 0 )
      first = insertChild( first, data.icaoDest, TAKEOFF, &error );
    else if( strcmp( icaoAp, data.icaoDest ) == 0  && strcmp( data.movType, MOVTYPE_LANDING ) == 0 )
      first = insertChild( first, data.icaoOrig, ARRIVAL, &error);

    if(error){
      fprintf(stderr,"Error, there's no more space. Aborting\n");
      exit(0);
    }
  }

  printMovesAtoA( icaoAp, first, writer );
}


void movesAtoA( char* filename, airportADT ap, flightADT f)
{
  toBeginAirport( ap );
  airportDataType data;
  FILE* writer = fopen( filename, "w" );
  if(!writer)
    Error( filename);

  while( hasNextAirport( ap ))
  {
    data = nextAirport( ap );
    lookAtoA( writer, data.icao, f );
  }

  fclose( writer );
}
