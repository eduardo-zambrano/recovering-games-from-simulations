/*  File contains the predictors. The function Make_new (prediction) updates all 
	the predictors. It feeds them a new history, collects their predictions, and
	puts the new predictions in the global struct array "forecast."
*/

//#include "define.h"
//#include "extern.h"
				
prediction predictor0 (int *, prediction);
prediction predictor1 (int *, prediction);		/* 	Local function prototypes	*/
prediction predictor2 (int *, prediction);
prediction predictor3 (int *, prediction);
prediction predictor4 (int *, prediction);
prediction predictor5 (int *, prediction);
prediction predictor6 (int *, prediction);
prediction predictor7 (int *, prediction);
prediction predictor8 (int *, prediction);
prediction predictor9 (int *, prediction);
prediction predictor10 (int *, prediction);
prediction predictor11 (int *, prediction);
prediction predictor12 (int *, prediction);
prediction predictor13 (int *, prediction);
prediction predictor14 (int *, prediction);
prediction predictor15 (int *, prediction);
prediction predictor16 (int *, prediction);
prediction predictor17 (int *, prediction);
prediction predictor18 (int *, prediction);
prediction predictor19 (int *, prediction);
prediction predictor20 (int *, prediction);
/*------------------------------------------------------------------------------------*/
void Initiate_predictors (prediction forecast[])	{
			int i;
	for (i = 0; i < TOTPREDICTORS; ++i)	{
		forecast[i].numbers = 0;
		forecast[i].accuracy = (0.25 * TOTPERSONS);
		forecast[i].rank	= i;
	} 
}
/*------------------------------------------------------------------------------------*/
void Update_accuracy (int newobs, prediction forecast[])	{
			int i; int temp;
	for (i = 0; i < TOTPREDICTORS; ++i) {
				temp = abs(newobs - forecast[i].numbers);
		forecast[i].accuracy =  (1- ETA)*forecast[i].accuracy + ETA*temp;
	}  
}
/*------------------------------------------------------------------------------------*/
void sort(prediction forecast[])	{ 	/* sort for rank based on accuracy  */
  int i, j, best; float upper;			/* rank 0 is the most accurate			*/
  
  	for (i = 0; i < TOTPREDICTORS; ++i)
  		forecast[i].flag = 0;			/* flag becomes 1 when sorted */
  
  		
  	/* Now sort out lowest member each pass and tag it with the next rank number */
  	
  	for (i = 0; i < TOTPREDICTORS; ++i)	{
  					upper = TOTPERSONS * 2;
  	  for (j = 0; j < TOTPREDICTORS; ++j)
		if (forecast[j].accuracy <= upper && forecast[j].flag == 0)	{
							best = j;
							upper = forecast[j].accuracy;
		}
				forecast[best].rank = i;
				forecast[best].flag = 1;
	}  
}
/*------------------------------------------------------------------------------------*/


void Make_new (prediction forecast[])	{	
		
	/* Runs all the prediction functions and puts the results in 
	the forecast array under forecast[i].number and forecast[i].accuracy */
	
		
if (0 < TOTPREDICTORS)	forecast[0] = predictor0(pastdays, forecast[0]);
if (1 < TOTPREDICTORS)	forecast[1] = predictor1(pastdays, forecast[1]);
if (2 < TOTPREDICTORS)	forecast[2] = predictor2(pastdays, forecast[2]);
if (3 < TOTPREDICTORS)	forecast[3] = predictor3(pastdays, forecast[3]);
if (4 < TOTPREDICTORS)	forecast[4] = predictor4(pastdays, forecast[4]);
if (5 < TOTPREDICTORS)	forecast[5] = predictor5(pastdays, forecast[5]);
if (6 < TOTPREDICTORS)	forecast[6] = predictor6(pastdays, forecast[6]);
if (7 < TOTPREDICTORS)	forecast[7] = predictor7(pastdays, forecast[7]);
if (8 < TOTPREDICTORS)	forecast[8] = predictor8(pastdays, forecast[8]);	
if (9 < TOTPREDICTORS)	forecast[9] = predictor9(pastdays, forecast[9]);
if (10< TOTPREDICTORS)	forecast[10] = predictor10(pastdays, forecast[10]);
if (11< TOTPREDICTORS)	forecast[11] = predictor11(pastdays, forecast[11]);
if (12 < TOTPREDICTORS)	forecast[12] = predictor12(pastdays, forecast[12]);
if (13 < TOTPREDICTORS)	forecast[13] = predictor13(pastdays, forecast[13]);
if (14 < TOTPREDICTORS)	forecast[14] = predictor14(pastdays, forecast[14]);
if (15 < TOTPREDICTORS)	forecast[15] = predictor15(pastdays, forecast[15]);
if (16 < TOTPREDICTORS)	forecast[16] = predictor16(pastdays, forecast[16]);
if (17 < TOTPREDICTORS)	forecast[17] = predictor17(pastdays, forecast[17]);
if (18 < TOTPREDICTORS)	forecast[18] = predictor18(pastdays, forecast[18]);	
if (19 < TOTPREDICTORS)	forecast[19] = predictor19(pastdays, forecast[19]);
if (20< TOTPREDICTORS)	forecast[20] = predictor20(pastdays, forecast[20]);
}
	
/*------------------------------------------------------------------------------------*/

void print_forecasts (prediction forecast[])  {
		int i;	
	 	printf("\n	*	*	*	 Forecasts Were		*	*	*	");
	 	printf("\n   Predictor      Forecast    Accuracy    Rank  ");	
	for (i = 0; i < TOTPREDICTORS; ++i)
		printf("\n% d %s:     % 4d        %2.2f      % d",
				i, pred[i], forecast[i].numbers, forecast[i].accuracy, forecast[i].rank);

}
/*------------------------------------------------------------------------------------*/

void Make_Report(int day,int hist[],int todays_number,prediction forecast[],hombre guy[],
					int use[])	{
				int i;
	
	i = HISTORY_LENGTH -1;
	fprintf(ofp,"\n\n Day % 2d      History: ",day);
	for (; i >=0 ; i--)	{
		if ((HISTORY_LENGTH -i) % 25 ==24)	fprintf(ofp, "\n");	
		fprintf(ofp, " %4d", pastdays[i]);
	}
					
	fprintf(ofp, "\n   Predictor       Forecast     Accuracy     Rank     Use");	
	for (i = 0; i < TOTPREDICTORS; ++i)
		fprintf(ofp, "\n%-3d  % s:     % 4d        %5.2f      % 3d    % 3d",
			i, pred[i], forecast[i].numbers, forecast[i].accuracy, forecast[i].rank, use[i]);
	
	fprintf(ofp, "\nNumber attending: %d", todays_number);
	
}	
/*------------------------------------------------------------------------------------*/
prediction predictor0 (int *hist, prediction forecast) {		
											/* rational expectations predictor	*/
											
	forecast.numbers 	= CRITNUM;
	
/*		(rand() % TOTPERSONS > CRITNUM)? (CRITNUM + 1): CRITNUM; /* forecast 60 w. prob 60% otherwise 61   */			
			return forecast;
}
/*------------------------------------------------------------------------------------*/
prediction predictor1 (int *hist, prediction forecast) {		
											/* close to ree indicator	*/
											
forecast.numbers 	=   (CRITNUM + 1);			
			return forecast;	
}
/*------------------------------------------------------------------------------------*/
prediction predictor2 (int *hist, prediction forecast) {		
											/* extrapolates the past two times  */ 
		int temp;
		temp		=	(hist[0] + (hist[0] - hist[1]));
		if (temp > TOTPERSONS) 	forecast.numbers 	=  TOTPERSONS;
		else if (temp < 0)	forecast.numbers 	=    0;
		else 				forecast.numbers 	=   temp;
		return forecast;
}
/*------------------------------------------------------------------------------------*/
prediction predictor3 (int *hist, prediction forecast) {		
												/*	 reflects the number around half		*/
		forecast.numbers 	=    (TOTPERSONS - hist[0]);
		return forecast;
}
/*------------------------------------------------------------------------------------*/
prediction predictor4 (int *hist, prediction forecast) {		
							/* if too many or too few expect reversal	*/
			if (hist[0] > (0.8 * TOTPERSONS)) 	forecast.numbers = (0.3 * TOTPERSONS);
			else if (hist[0] < (0.2 * TOTPERSONS))	forecast.numbers = (0.7 * TOTPERSONS);
			else 					forecast.numbers =  hist[0];
			return forecast;
}
/*------------------------------------------------------------------------------------*/
prediction predictor5 (int *hist, prediction forecast) {		
							/* if too many or too few expect reversal	*/
			if (hist[0] > (0.7 * TOTPERSONS)) forecast.numbers = (0.4 * TOTPERSONS);
			else if (hist[0] < (0.3 * TOTPERSONS))	forecast.numbers = (0.6 * TOTPERSONS);
			else 					forecast.numbers = hist[0];
			return forecast;
}
/*------------------------------------------------------------------------------------*/
prediction predictor6 (int *hist, prediction forecast) {		
										/* if too many or too few expect reversal	*/
			if (hist[0] > (0.9 * TOTPERSONS)) 	forecast.numbers = (0.1 * TOTPERSONS);
			else if (hist[0] < (0.1 * TOTPERSONS))	forecast.numbers = (0.9 * TOTPERSONS);
			else 					forecast.numbers = hist[0];
			return forecast;
}
/*------------------------------------------------------------------------------------*/
prediction predictor7 (int *hist, prediction forecast) {		
													/* just forecast 50 every time	*/
	 		forecast.numbers =  (0.5 * TOTPERSONS);
			return forecast;
}
/*------------------------------------------------------------------------------------*/
prediction predictor8 (int *hist, prediction forecast) {		
											/* extrapolate and reverse if extreme	*/
	int temp;
			temp = hist[0] + (hist[0] - hist[4]);
			if (temp > (0.8 * TOTPERSONS)) 		forecast.numbers = (0.3 * TOTPERSONS);
			else if (temp < (0.2 * TOTPERSONS))	forecast.numbers = (0.7 * TOTPERSONS);
			else 				forecast.numbers 	=   temp;
			return forecast;
}
/*------------------------------------------------------------------------------------*/
prediction predictor9 (int *hist, prediction forecast) {		
											/* extrapolate and reverse if extreme	*/
	int temp;
			temp = hist[0] + (hist[0] - hist[2]);
			if (temp > (0.9 * TOTPERSONS)) 		forecast.numbers = (0.2 * TOTPERSONS);
			else if (temp < (0.1 * TOTPERSONS))	forecast.numbers = (0.8 * TOTPERSONS);
			else 				forecast.numbers 	=   temp;			
			return forecast;
}

/*------------------------------------------------------------------------------------*/

prediction predictor10 (int *hist, prediction forecast) {			
														/* average of last three	*/
														
			forecast.numbers 		=    (hist[0] + hist[1] + hist[2]) / 3;
			return forecast;
}

/*------------------------------------------------------------------------------------*/
prediction predictor11 (int *hist, prediction forecast) {			
															/* same as last time	*/
			forecast.numbers 		=    hist[0];
			return forecast;
}
/*------------------------------------------------------------------------------------*/
prediction predictor12 (int *hist, prediction forecast) {			
															/* detects cycle of period 2 */
			forecast.numbers 		=    hist[1];
			return forecast;
}/*------------------------------------------------------------------------------------*/
prediction predictor13 (int *hist, prediction forecast) {			
															/* detects cycle of period 3 */
			forecast.numbers 		=    hist[2];
			return forecast;
}/*------------------------------------------------------------------------------------*/
prediction predictor14 (int *hist, prediction forecast) {			
															/* detects cycle of period 4 */
			forecast.numbers 		=    hist[3];
			return forecast;
}/*------------------------------------------------------------------------------------*/
prediction predictor15 (int *hist, prediction forecast) {			
															/* detects cycle of period 5 */
			forecast.numbers 		=    hist[4];
			return forecast;
}/*------------------------------------------------------------------------------------*/
prediction predictor16 (int *hist, prediction forecast) {			
															/* detects cycle of period 6 */
			forecast.numbers 		=    hist[5];
			return forecast;
}/*------------------------------------------------------------------------------------*/
prediction predictor17 (int *hist, prediction forecast) {			
															/* detects cycle of period 7 */
			forecast.numbers 		=    hist[6];
			return forecast;
}/*------------------------------------------------------------------------------------*/
prediction predictor18 (int *hist, prediction forecast) {			
															/* detects cycle of period 8 */
			forecast.numbers 		=    hist[7];
			return forecast;
}/*------------------------------------------------------------------------------------*/
prediction predictor19 (int *hist, prediction forecast) {			
															/* detects cycle of period 9 */
			forecast.numbers 		=    hist[8];
			return forecast;
}/*------------------------------------------------------------------------------------*/
prediction predictor20 (int *hist, prediction forecast) {			
															/* detects cycle of period 10 */
			forecast.numbers 		=    hist[9];
			return forecast;
}


