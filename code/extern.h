

/*------------------	**	External arrays and variables	**	------------------------*/


extern prediction forecast[TOTPREDICTORS];	/*	The current predictors'forecasts 	*/
extern hombre person[TOTPERSONS];		/*	The population of agents		*/
extern int pastdays[HISTORY_LENGTH];		/*	Array of past numbers attending		*/
extern int predictor_use[TOTPREDICTORS];	/*  	No. of agents using predictor		*/
extern int todays_number;			/*  	New attendance figure			*/
extern char *decide[];
extern char *pred[];
extern FILE *ofp, *ofplot;
extern long int day; 	
/* ------------------------------------------------------------------------------------*/	


