//#include "define.h"
//#include "extern.h"

/* ------------------------------------------------------------------------------------*/	
void Initiate_history(int * past){	/* Sets up the historical attendance figures
										and, when called, puts in pastdays array.
										Note:		0 is the most recent day.	 	*/
										
	int i;																			
	for ( i = HISTORY_LENGTH - 1; i >= 0; i--)		
		past[i] =  rand() % TOTPERSONS;
}
/* ------------------------------------------------------------------------------------*/	

void Update_history(int *past,int newnumber){
 
	/* Updates history array (past by adding latest attendance (newnumber) to end
		 and dropping earliest day. Note: 0 is most recent day						*/
		
	int i;

	for ( i = HISTORY_LENGTH - 1; i >= 0; i--)		
		past[i] = past[i-1];	
	past[0] = newnumber;
}
/* ------------------------------------------------------------------------------------*/	

void fprint_history(int *past)	{
	int i = HISTORY_LENGTH -1;
	fprintf(ofp,"\n History: ");
	for (; i >=0 ; i--)	{
		if ((HISTORY_LENGTH -i) % 25 ==24)	fprintf(ofp,"\n");	
		fprintf(ofp," %4d", pastdays[i]);
	}
	fprintf(ofp,"\n");
}
/* ------------------------------------------------------------------------------------*/	

void print_history(int *past)	{
	int i = HISTORY_LENGTH -1;
	printf("\n History: ");
	for (; i >=0 ; i--)	{
		if ((HISTORY_LENGTH -i) % 25 ==24)	printf("\n");	
		printf(" %4d", pastdays[i]);
	}
	printf("\n");
}

/* ------------------------------------------------------------------------------------*/	


