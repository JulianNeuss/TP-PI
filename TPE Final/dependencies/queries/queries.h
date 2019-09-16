
/*
* queries.h
* Contract of requested queries
*/


/* Function: movsPerAirport
* Use: movsPerAirport( filename, ap, fl );
*-------------------------------------------------------------------------------
* Description: Does the first query, of movements per airport, from the
                                airports list
*-------------------------------------------------------------------------------
* Pre-condition: Airports and flights with data
* Post-condition: A file with the name filename
*/
void movsPerAirport( char* filename, airportADT ap, flightADT fl);

/* Function: intMovsPerAirport
* Use: intMovsPerAirport( filename, ap, fl );
*-------------------------------------------------------------------------------
* Description: Does the second query, of international movements per airport,
                        from the airports list
*-------------------------------------------------------------------------------
* Pre-condition: Airports and flights with data
* Post-condition: A file with the name filename
*/
void intMovsPerAirport( char* filename, airportADT ap, flightADT fl);

/* Function: flightsPerWeekDay
* Use: flightsPerWeekDay( filename, fl );
*-------------------------------------------------------------------------------
* Description: Does the third query, of flights per week day, from the
                                flights list
*-------------------------------------------------------------------------------
* Pre-condition: Flights with data
* Post-condition: A file with the name filename
*/
void flightsPerWeekDay(char *filename, flightADT fl);

/* Function: movesAtoA
* Use: movesAtoA( filename, ap, fl );
*-------------------------------------------------------------------------------
* Description:  Does the fourth query, of movements from/to airports
                        from the airports list
*-------------------------------------------------------------------------------
* Pre-condition: Airports and flights with data
* Post-condition: A file with the name filename
*/
void movesAtoA( char* filename, airportADT ap, flightADT f);
