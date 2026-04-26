#include <condefs.h>
#include "define.h"
#include "extern.h"
#include "global.h"
#include "agents.h"
#include "forecast.h"
#include "history.h"


/************************************************************************************
*					©  W. Brian Arthur. Santa Fe Institute. 
*					Code for the El Farol problem. Version 31.8.94.
*
*  	For a description of the problem, see my article: Inductive Behavior and 
*	Bounded Rationality, Amer. Econ. Review, 84, May 1994.
*					 
*	The program was written on a Symantec Think C compiler (and runs on the new 
*	Symantec C++ compiler). Program was originally written in August 1992 as a 
*	programming exercise in learning C. Hence it might be usefully streamlined.
*	Note that many inbuilt diagnostic printouts and plots are commented out.
*
*	 
*************************************************************************************/


/*------------------------------------------------------------------------------------*/

//USEUNIT("agents.c");
//USEUNIT("forecast.c");
//USEUNIT("history.c");
//---------------------------------------------------------------------------
main()	{	int i, agent; int x;

			srand(time(NULL));

			day = 1;
			ofp = fopen("log", "w"); 		/* log file logs predictors used */
 			ofplot = fopen("plot", "w");    /* plot file logs daily attendance */ 
 			
Initiate_history(pastdays);					/* read in the initial history	*/ 
	
Initiate_predictors(forecast);				/* set up the predictors */
	sort(forecast);

Initiate_agents(person);					/* set up agents with their predictors 	*/
	/*	print_agent_predictors(person); */

	/*	fprint_history(pastdays); 	*/


						/* -------start of main loop -----------*/
							
 while (day <= EXPT_LENGTH)	{				
 
	Make_new(forecast);				/* All predictions updated	*/
	
	Make_choice(forecast, person, predictor_use);	/* Agents forecast and decide	*/
	/*	print_choices(forecast,person);		*/
							
	todays_number = Calculate_number(person); 	/* Fetch the new attendance	*/
		fprintf(ofplot, "%d \n",todays_number);		
	
	/* Make_Report(day, pastdays, todays_number, forecast, person, predictor_use);	*/

	Update_accuracy(todays_number,forecast);	/* Reassess accuracy and ranks	*/
		sort(forecast);
	/*	print_forecasts(forecast);		*/

	Update_history(pastdays,todays_number);		/* Update attendance history	*/
	/*	print_history(pastdays);  */		
			
				
	++day; 						/*  Loop to next day 		*/
 
 
 
 } 
                                                                                                    	
}
/*-------------------------- End of main file  ------------------------------------------*/	


