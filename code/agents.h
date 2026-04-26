//#include "define.h"
//#include "extern.h"

/*------------------------------------------------------------------------------------*/
void Initiate_agents(hombre agent[])	{	/* Assigns predictors to be monitored by
						each agent. Other functions will later
						fill in predictor chosen and decision	*/
											
	int i,j,k, index, count; int flag[TOTPREDICTORS];
	
	for (i = 0; i < TOTPERSONS ; ++i)	{		/* for each agent 		*/
		for (k = 0; k < TOTPREDICTORS ; ++k)  {	/* reset predictor and heed flags	*/
				flag[k] = 0;
				agent[i].heed[k] = 0;
		}
			count = 1;					/* Choose predictors	*/
		while (count <= MAXHEED) {		
			index = ( rand() % 21);				/* fetch a random index	*/
			if (flag[index] == 0) 				/* if not yet chosen	*/
						++count;		/* choose it and	*/ 
			agent[i].heed[index] =	1;			/* set heed-flag to 1. 	*/
			flag[index] = 1;					
		}						/* Repeat until MAXHEED is reached */
			
	}
}
/*------------------------------------------------------------------------------------*/
void print_agent_predictors (hombre *agent) {
		int i,j;
		
		for (i = 0; i < TOTPERSONS ; ++i)	{	
				fprintf(ofp,"\n Agent % 2d	predictors:", i);
					for (j = 0; j< TOTPREDICTORS; ++j)
						if (agent[i].heed[j] == 1) fprintf(ofp, "  % 4d", j );	
		}
}
/*------------------------------------------------------------------------------------*/
void Make_choice(prediction *forecast,hombre *guy, int *use)	{

	/* Takes in updated forecasts and for each guy chooses best forecaster 
		and makes decision. */
	
	int i,j, rank,  best, index;
	float av, expect, sd, sumEx, sumSq, var;

		for (j=0; j < TOTPREDICTORS; ++j) use[j] = 0;		/* reset predictor use counter	*/
	
	
	for (i=0; i < TOTPERSONS; ++i)	{				/* 		for each agent	*/
		 		
		best = TOTPREDICTORS +1;				/* 		reset best indicator	*/
	 		for (j=0; j <TOTPREDICTORS; ++j)	{	/* 		choose best predictor	*/
		 		if (forecast[j].rank < best && guy[i].heed[j] == 1)
		 		best = forecast[j].rank, index = j;
		 	}
		guy[i].forecaster = index;				/* record index of best predictor		*/
		expect = forecast[index].numbers;			/* make best forecast				*/
		use[index]++;						/* count one more user for used predictor	*/ 
/*		fprintf(ofp,"\nagent % 3d:  index % 3d", i, index);		*/
																					
/* 		Agents decide: 
		stay if expecting more than CRITNUM to attend go if expecting fewer		*/
					
		if (expect > CRITNUM)		guy[i].decision =  stay;
		else if (expect <= CRITNUM)	guy[i].decision =  go;
	} 
	sumEx = 0;
	sumSq = 0;
	for (i=0; i < TOTPERSONS; ++i)	{
		expect = forecast[guy[i].forecaster].numbers;
		sumEx += expect;
		sumSq += (expect * expect);
	}
	av = (sumEx / TOTPERSONS);
	var = ((sumSq / TOTPERSONS) - (av * av));

	fprintf(ofplot, "%5.5f %5.5f ", av, var); 
}
/*------------------------------------------------------------------------------------*/
void print_choices(prediction *forecast,hombre *guy)	{	
			int i;
	for (i=0; i < TOTPERSONS; ++i)	{
		printf("\nAgent %d predictor %d forecast % d decision %s",
		i, guy[i].forecaster, forecast[guy[i].forecaster].numbers, decide[guy[i].decision]);
	}  
}
/*------------------------------------------------------------------------------------*/

int Calculate_number(hombre *guy)	{		/* totals numbers who decide to go	*/
	int i, count = 0;
	for (i=0; i < TOTPERSONS; ++i)	{
		count += guy[i].decision; 
	}
		return count;
}  
/*------------------------------------------------------------------------------------*/
void print_decisions(hombre *guy)	{
	int i;
		printf("Agents:\n");
	for (i = 0;i<TOTPERSONS;++i)	{
			printf(" % d: % s \t", i, decide[guy[i].decision]); 	
	}
}


