//#include "define.h"

/* ------------------------------------------------------------------------------------*/	

 prediction forecast[TOTPREDICTORS];		/*	The current predictors'forecasts 	*/
 hombre  person[TOTPERSONS];				/*	The population of agents			*/
 int pastdays[HISTORY_LENGTH];		 		/*	Array of past numbers attending		*/
 int predictor_use[TOTPREDICTORS];			/*  Counts no. of agents using predictor*/
 int todays_number;							/*  New attendance figure				*/
 
 char *decide[] = {"stay","go"};
 char *pred[] = {"R.e.e.    ", "Near r.e.e","Extrapol. ", "Reflect   ",
 	"Too many?1","Too many?2","Too many?3", "Fifty     ", "Trend/rev1","Trend/rev2",
 	"Av. prev 3", "Same  last", "2 cycle   ","3 cycle   ","4 cycle   ","5 cycle   ",
 	"6 cycle   ","7 cycle   ","8 cycle   ","9 cycle   ","10 cycle  "} ;
 FILE *ofp, *ofplot;
 long day;
 
/* ------------------------------------------------------------------------------------*/	
/*				**	The function prototypes follow	**								   */

void Initiate_agents(hombre *);
void Initiate_history(int *);
void Initiate_predictors(prediction *);
void print_forecasts(prediction *);
void sort( prediction *);
void Update_accuracy(int, prediction *);
float eval_accuracy(prediction function(void));
void Make_choice(prediction *, hombre *, int *);
int Calculate_number(hombre *);
void Update_history(int *, int);
void print_history( int *);
void fprint_history( int *);
void print_decisions(hombre *);
void print_agent_predictors(hombre *);
void print_choices(prediction *,hombre *);
void Make_new (prediction *);
void Make_Report(int,int *, int, prediction *, hombre *, int *);	


/* ------------------------------------------------------------------------------------*/	


