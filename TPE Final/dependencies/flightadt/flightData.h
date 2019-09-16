/* Function: putFlightData
* Use: data = putFlightData( organizedVector, &error );
*-------------------------------------------------------------------------------
* Description: It puts the organized vetor of data into the data you want
*-------------------------------------------------------------------------------
* Pre-condition: An organized vector of data
* Post-condition: A flight data type
*/
static flightDataType putFlightData( char organizedVector[][MAX_LENGHT],int * error )
{
  flightDataType data;
  int errorAns;

  (*error) = FALSE;

  data.date = defineDate( organizedVector[fDATE] );
  data.weekDay = determineDayByG_S(data.date);

  data.clasification= defineFlightField(organizedVector[fCLASIFICATION],&errorAns);
  if(errorAns)
  	(*error) = TRUE;

  data.movType = defineFlightField(organizedVector[fMOV_TYPE],&errorAns);
  if(errorAns)
  	(*error) = TRUE;

  data.icaoOrig= defineFlightField(organizedVector[fICAOORIG],&errorAns);
  if(errorAns)
  	(*error) = TRUE;

  data.icaoDest= defineFlightField(organizedVector[fICAODEST],&errorAns);
  if(errorAns)
  	(*error) = TRUE;

  return data;
}

/* Function: freeFlightData
* Use: freeFlightData( data );
*-------------------------------------------------------------------------------
* Description: It frees the space allocated by the previous function
*-------------------------------------------------------------------------------
* Pre-condition: A flight data type
* Post-condition: -
*/
static void freeFlightData( flightDataType data )
{
 free( data.clasification );
 free( data.movType );
 free( data.icaoOrig );
 free( data.icaoDest );
}
