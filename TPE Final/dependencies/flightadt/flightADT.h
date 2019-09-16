#ifndef MACROS

#define MACROS
#define DELIM ';'
#define MAX_LENGHT 500
#define SEPARATOR ";"
#define SEPARATOR_DATE "/"
#define VOID_VECTOR ""
#define FALSE 0
#define TRUE !FALSE
#define suc( elem ) elem + 1

#endif


/*
* flightADT.h
* Contract of ADT Lineal Pile
* simple chained, without repetitions nor header
*/


#ifndef _FLIGHTADT_H_
#define _FLIGHTADT_H_

/*
* Theese are the fields of the line from the file.
* The enum is to put a name to every field possible.
*/
enum categoriesFlights{ fDATE = 0, fTIME, fCLASS, fCLASIFICATION, fMOV_TYPE, fICAOORIG, fICAODEST, fAIRLINE, fAIRSHIP, fAPC_AIRSHIP };
#define MAXFIELDS_FLIGHT 10
#define MAXLENGHT_MOVTYPE 11

/* Data storage:  . struct date
                  . struct flightData
* These are the fields important to the user. They can be edited as pleased. The
* date field in flightData MUST NOT be modified because its a pre-requisite to know
* the year of every flifht. The other fields are disposable/changeable.
* The char* fields need to allocate memory so the data stored needs to be freed.
*/

typedef struct date
{
  unsigned day;
  unsigned month;
  unsigned year;
}dateType;

typedef struct flightData
{
  dateType date;
  char *clasification;
  char *movType;
  char *icaoOrig;
  char *icaoDest;
  int weekDay;
}flightDataType;


////////////////////////////////////////////

typedef struct flightCDT* flightADT;

/* Function: determineDayByG_S
* Use: dayOfWeek = determineDayByG_S( date );
*-------------------------------------------------------------------------------
* Description: An algorithm based on a paper that gives conceptual proof on
*  Gauss' formula for calculating the day of the week by Berndt Schwerdtfeger.
*-------------------------------------------------------------------------------
* Pre-condition: A date in the dateType format
* Post-condition: The day of the week of the date
*/
int determineDayByG_S(dateType date);

/* Function: defineDate
* Use: dateType date = defineDate( line );
*-------------------------------------------------------------------------------
* Description:  It pases a line of char* with the format dd/mm/yyyy into
                                  separate fields
*-------------------------------------------------------------------------------
* Pre-condition:  A line with the format dd/mm/yyyy
* Post-condition: A datetype to that date
*/
dateType defineDate( char* date );

/* Function: defineFlightField
* Use: var = defineFlightField( data, &error );
*-------------------------------------------------------------------------------
* Description: It allocates memory for some * variables
*-------------------------------------------------------------------------------
* Pre-condition:  A line of data
* Post-condition: The data in the allocated space OR an error flag turned on
*/
char* defineFlightField( char* data, int * error);

/* Function: newFlight
* Use: fl = newFlight( year );
*-------------------------------------------------------------------------------
* Description: It allocates space for a new flights list
*-------------------------------------------------------------------------------
* Pre-condition:  A year selected
* Post-condition: A new flight
*/
flightADT newFlight(int year);

/* Function: insertFlight
* Use: ans = insertFlight( f, data, &error );
*-------------------------------------------------------------------------------
* Description:  Tells you if the flight could have been added to the list
*-------------------------------------------------------------------------------
* Pre-condition:  A flights list and a line of data
* Post-condition: A new flight into the list f OR an error flag turned on
*/
int insertFlight( flightADT f, char * data, int* error );

/* Function: freeFlight
* Use:  freeFlight( f );
*-------------------------------------------------------------------------------
* Description:  It frees the space allocated by function newFlight
*-------------------------------------------------------------------------------
* Pre-condition: A flight list
* Post-condition: -
*/
void freeFlight( flightADT f );

/*
* Functions to be able to iterate over the flights
*/
void toBeginFlight( flightADT f );

int hasNextFlight( flightADT f );

flightDataType nextFlight( flightADT f );

#endif /* _FLIGHTADT_H_ */
