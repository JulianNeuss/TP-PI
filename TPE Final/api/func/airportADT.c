#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../dependencies/airportadt/airportADT.h"
#include "../../dependencies/airportadt/airportData.h"


typedef struct airportNode* tAirportNode;
typedef struct airportNode
{
  airportDataType data;
  tAirportNode tail;
}airportNode;


typedef struct airportCDT
{
  tAirportNode first;
  tAirportNode iter;
}airportCDT;



airportDataType toAirportDataType( char* formattedText )
{
  char data[MAXFIELDS_AIRPORT][MAX_LENGHT];
  char* token;
  char* aux;
  int i = 0;
  aux = formattedText;

  while( i < MAXFIELDS_AIRPORT )
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

  return putAirportData( data );
}



airportADT newAirport()
{
  airportADT aux =  calloc( 1, sizeof( airportCDT ));
  return aux;
}




static tAirportNode insertAirportRecc( tAirportNode n, airportDataType data, int* added )
{
  if( n == NULL || strcmp( data.icao, n->data.icao )  < 0 )
  {
      tAirportNode newNode = malloc( sizeof( airportNode));
      if( newNode == NULL )
      {
        *added = FALSE;
        return n;
      }
      newNode->data = data;
      newNode->tail = n;
      *added = TRUE;
      return newNode;
  }

  n->tail = insertAirportRecc( n->tail, data, added );
  return n;
}



int insertAirport( airportADT ap, char* data, int* added)
{
  airportDataType newData = toAirportDataType( data);

  if( *(newData.icao) != 0 )
  {
    ap->first = insertAirportRecc( ap->first, newData, added );
    return TRUE;
  }
  return FALSE;
}



void freeAirport( airportADT ap )
{
  tAirportNode nodeAux;
  toBeginAirport( ap );

  while( hasNextAirport( ap ))
  {
    nodeAux = ap->iter;
    nextAirport( ap );
    free( nodeAux );
  }
  free( ap );
}



void toBeginAirport( airportADT ap )
{
  ap->iter = ap->first;
}



int hasNextAirport( airportADT ap )
{
  return ap->iter != NULL;
}



airportDataType nextAirport( airportADT ap )
{
  airportDataType data = ap->iter->data;
  ap->iter = ap->iter->tail;
  return data;
}
