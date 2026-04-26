/* -------------------    Include Files and Definitions	--------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TOTPERSONS 	100    /*	Total agents 					*/

#define TOTPREDICTORS	21	/*	Total possible predictors			*/
#define MAXHEED		10	/*	Total predictors each agent notices		*/
#define HISTORY_LENGTH	12	/*	Total past days kept for predictors		*/
#define EXPT_LENGTH	500	/*	Desired number of days for program to run 	*/
#define ETA		0.05	/*	Rate for updating predictor accuracies		*/
#define CRITNUM		TOTPERSONS*0.6	/* critical target number of bargoers 		*/

/* -------------------	Type Definitions	----------------------------*/

typedef enum{stay,go} choice;

typedef struct	{			/* Each prediction contains a forecast and accuracy */
				int numbers;
				float accuracy;
				int rank;
				int flag;
} prediction;

typedef struct {					/* Each person heeds an array of predictors */
				int heed[TOTPREDICTORS];/* chooses a forecaster, decides to go or not */
				int forecaster;
				choice decision;
} hombre;

/* ------------------------------------------------------------------------------------*/



