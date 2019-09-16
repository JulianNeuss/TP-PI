#include <stdlib.h>
#include <stdio.h>
#include "../dependencies/flightadt/flightADT.h"
#include "../dependencies/airportadt/airportADT.h"

static void Error( char* filename )
{
  fprintf(stderr,"Error when trying to read %s, look README.txt \n", filename);
  exit(0);
}

airportADT processAirports( char *filename)
{
  int error = FALSE;
  FILE *reader = fopen(filename, "r");
  if(!reader)
    Error( filename );


  int added;
  airportADT ap = newAirport();
  if(!ap)
  {
     fprintf(stderr,"Error while trying to create new airport. Aborting \n");
    exit(0);
  }

  char line[MAX_LENGHT];
  fgets(line, MAX_LENGHT, reader);      //this one is to skip the name of the fields.

  while(fgets(line, MAX_LENGHT, reader))
    if( insertAirport( ap, line, &added ) && added == FALSE )
      error++;


  if(error)
    fprintf(stderr,"Some of the lines of %s weren't able to be copied\n", filename );

  fclose(reader);
  return ap;
}

flightADT processFlights(char *filename, unsigned year)
{

  FILE *reader = fopen(filename, "r");
  if(!reader)
    Error( filename );

  flightADT fl = newFlight( year );
  if(!fl)
  {
    fprintf(stderr,"Error while trying to create new flight. Aborting \n");
    exit(0);
  }

  int error = FALSE , added;

  char line[MAX_LENGHT];

  fgets(line, MAX_LENGHT, reader);      //this one is to skip the name of the fields.

  while(fgets(line, MAX_LENGHT, reader))
    if( insertFlight( fl, line, &added ) && added == FALSE )
      error++;


  if(error)
      fprintf(stderr,"Some of the lines of %s weren't able to be copied\n", filename );

  fclose( reader );
  return fl;
}
