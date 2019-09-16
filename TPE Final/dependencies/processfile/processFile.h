
/* Data files processors */

/* Function: processAirports
* Use: ap = processAirports( filename );
*-------------------------------------------------------------------------------
* Description: It processes the data of the file into an airport list
*-------------------------------------------------------------------------------
* Pre-condition: A file with data of airports
* Post-condition: An airport list with that data
*/
airportADT processAirports( char *filename);

/* Function: processFlights
* Use:  f = processFlights( filename, year );
*-------------------------------------------------------------------------------
* Description: It processes the data of the file and the year selected
                            into a flights pile
*-------------------------------------------------------------------------------
* Pre-condition: A file with data of flights
* Post-condition: A flights pile with that data
*/
flightADT processFlights(char *filename, unsigned year);
