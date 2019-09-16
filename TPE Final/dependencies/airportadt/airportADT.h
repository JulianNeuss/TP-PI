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
* airportADT.h
* Contract of ADT Lineal lists
* Simply chainly ordered, without repetitions nor header
*/

#ifndef AIRPORTADT_H_
#define AIRPORTADT_H_

//Limit tokenChars
#define MAXFIELDS_AIRPORT 23
#define MAX_aLOCAL 4
#define MAX_aICAO 5
#define MAX_aIATA 4
#define MAX_aTYPE 11
#define MAX_aDESCR 70
#define MAX_aCOND 8
#define MAX_aTRAFFIC 14

/*
* Theese are the fields of the line from the file.
* The enum is to put a name to every field possible.
*/
enum categoriesAirport{ aLOCAL = 0, aICAO, aIATA, aTYPE, aNAME, aCOORDINATES, aLATITUDE, aLONGITUDE, aELEV, aUOM_ELEV, aREF, aDISTANCE_REF, aDIRECTION_REF, aCONDITION, aCONTROL, aREGION, aFIR, aUSO, aTRAFFIC, aSNA, aCONSESIONATE, aSTATE, aINHAB };


/* Data storage: struct apData
* These are the fields important to the user. They can be edited as pleased,
* having into acount that the icao field MUST NOT BE ERRASED, because that
* field provides the order of the list. The other fields are
* disposable/changeable. Its a char* so the data stored needs to be freed
*/

typedef struct apData
{
  char local[MAX_aLOCAL];
  char icao[MAX_aICAO];
  char iata[MAX_aIATA];
  char type[MAX_aTYPE];
  char descr[MAX_aDESCR];
  char cond[MAX_aCOND];
  char traffic[MAX_aTRAFFIC];
}airportDataType;


typedef struct airportCDT* airportADT;


/* Function: defineAirportField
* Use: char* structField  = defineAirportField( organizedVector[CATEGORY_PLACEMENT] );
* -----------------------------------------------------------------------------------
* Description: Stores the data that the user needs in that field. It then needs
*                      to be freed in order to avoid errors.
* ------------------------------------------------------------------------------------
* Pre-condition: airportDataType toAirportDataType( char* ) called
* Post-condition: airport data created
*/
char* defineAirportField( char* data );

/* Function: newAirport
* Use: airportADT ap = newAirport(added);
*-------------------------------------------------------------------------------
* Description: Initializes the airport.
*-------------------------------------------------------------------------------
* Pre-condition:  -
* Post-condition: Airport created.
*/
airportADT newAirport();

/* Function: insertAirport
* Use: res == insertAirport( ap, line );
*-------------------------------------------------------------------------------
* Description: Inserts an element into the ordered list, using the functions
                defineField and putAirportData, having into account the
                    alphabetical order of the icao.
*-------------------------------------------------------------------------------
* Pre-condition: Valid airport, previously created.
* Post-condition: Airport with the new element.
*/
int insertAirport( airportADT ap, char* data,int * added);

/* Function: freeAirport
* Use: freeAirport( ap );
*-------------------------------------------------------------------------------
* Description: Destroys the airport, freeing all the reosurces allocated.
*-------------------------------------------------------------------------------
* Pre-condition: Valid airport
* Post-condition: -
*/
void freeAirport( airportADT ap );

/* Function: toAirportDataType
* Use:  airportDataType data = toAirportDataType( line );
*-------------------------------------------------------------------------------
* Description: Passes a line from the reader into organized data of the airport
*-------------------------------------------------------------------------------
* Pre-condition: A chain of char*
* Post-condition: struct with the airport data separated in fields
*/
airportDataType toAirportDataType( char* formattedText );

/*
* Functions to be able to iterate over the airport
*/
void toBeginAirport( airportADT ap );

int hasNextAirport( airportADT ap );

airportDataType nextAirport( airportADT ap );

#endif /* _AIRPORT_H_ */
