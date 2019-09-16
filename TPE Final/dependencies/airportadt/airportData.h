/* Additional changeable function to airportADT */

/* Function: putAirportData
* Use: airportDataType dataType = putAirportData( organizedVector );
*-------------------------------------------------------------------------------
* Description: Organizes the data of a line on a vector that is sub-categorized,
*              and then, puts it in the corresponding field
*-------------------------------------------------------------------------------
* Pre-condition: Data on an organized vector
* Post-condition: Data on airportDataType
*/
static airportDataType putAirportData( char organizedVector[][MAX_LENGHT] )
{
  airportDataType data;
 strncpy( data.local, organizedVector[aLOCAL], MAX_aLOCAL);
 strncpy( data.icao, organizedVector[aICAO], MAX_aICAO);
 strncpy( data.iata, organizedVector[aIATA], MAX_aIATA);
 strncpy( data.type, organizedVector[aTYPE], MAX_aTYPE);
 strncpy( data.descr, organizedVector[aNAME], MAX_aDESCR);
 strncpy( data.cond, organizedVector[aCONDITION], MAX_aCOND);
 strncpy( data.traffic, organizedVector[aTRAFFIC], MAX_aTRAFFIC);

  return data;
}

