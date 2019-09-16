#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../../dependencies/flightadt/flightADT.h"
#include "../../dependencies/flightadt/flightData.h"

#define CENTURY 100
#define MAX_ICAO 4
#define NOT_APPLICABLE "N/A"


typedef struct flightNode* tFlightNode;
typedef struct flightNode
{
  flightDataType data;
  tFlightNode tail;
}flightNode;

typedef struct flightCDT
{
  int yearSelected;
  tFlightNode first;
  tFlightNode iter;
}flightCDT;


int determineDayByG_S(dateType date)
{
  int c, g, d=date.day, m=date.month, y=date.year;
  static int eLookUpTable[]={0,3,2,5,0,3,5,1,4,6,2,4};
  static int fLookUpTable[]={0,5,3,1};

  if(m<3)
    y--;

  c=y/CENTURY;
  g=y-CENTURY*c;

  return ((int)(d+eLookUpTable[m-1]+fLookUpTable[c%4]+g+(g/4)))%7;
}



void validateIcao( char s[] )
{
  int i;
  for( i = 0; s[i]; i++ )
    if( isdigit( s[i] ) || i >= MAX_ICAO )
    {
      strcpy( s, NOT_APPLICABLE );
      return;
    }
}


char* defineFlightField( char* data, int * error )
{
  char* aux = malloc( strlen( data ) + 1 );
  if(aux == NULL)
    (*error)=FALSE;
  else
     (*error)=TRUE;

  strcpy( aux, data );

  return aux;
}

dateType defineDate( char* date )
{
  dateType dateFormat;

  dateFormat.day = atoi( strtok( date, SEPARATOR_DATE ));
  dateFormat.month = atoi( strtok( NULL, SEPARATOR_DATE ));
  dateFormat.year = atoi( strtok( NULL, SEPARATOR_DATE ));

  return dateFormat;
}


flightDataType toflightDataType( char* formattedText, int * error )
{
  char data[MAXFIELDS_FLIGHT][MAX_LENGHT];
  char* token;
  char* aux;
  int i = 0;
  aux = formattedText;

  while( i < MAXFIELDS_FLIGHT )
  {
    if( *aux != DELIM )
    {
        token = strtok( aux, SEPARATOR );
        strcpy( data[i], token );
        aux = strtok( NULL, VOID_VECTOR );
    }
    else
    {
      data[i][0] = 0;
      aux = suc( aux );
    }
    i++;
  }
  validateIcao( data[fICAOORIG] );
  validateIcao( data[fICAODEST] );

  flightDataType newData = putFlightData( data,error );
  return newData;
}



flightADT newFlight( int year)
{
 flightADT aux = calloc( 1, sizeof( flightCDT ));
 if(aux)
  aux->yearSelected = year;
  return aux;
}



int insertFlight( flightADT f, char* data, int* added )
{
  flightDataType newData = toflightDataType(data,added);
  if((*added) == FALSE)
    return FALSE;
  if( newData.date.year == f->yearSelected)
  {
    tFlightNode newNode = malloc( sizeof( flightNode ));
    if( newNode == NULL )
    {
      *added = FALSE;
      freeFlightData( newData );
      return TRUE;
    }

      *added = TRUE;
      newNode->data = newData;
      newNode->tail = f->first;
      f->first = newNode;
      return TRUE;
  }

  *added = FALSE;
  freeFlightData( newData );

  return FALSE;
}



int flightIsEmpty( flightADT f )
{
  return f->first == NULL;
}



void freeFlight( flightADT f )
{
  toBeginFlight(f);
  tFlightNode nodeAux;
  flightDataType dataAux;

  while(hasNextFlight(f))
  {
    nodeAux = f->iter;
    dataAux = nextFlight( f );
    freeFlightData( dataAux );
    free( nodeAux );
  }
  free( f );
}

void toBeginFlight( flightADT f )
{
  f->iter = f->first;
}



int hasNextFlight( flightADT f )
{
  return f->iter != NULL;
}




flightDataType nextFlight( flightADT f )
{
  flightDataType data = f->iter->data;
  f->iter = f->iter->tail;
  return data;
}
