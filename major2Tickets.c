#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


// generate random ticket prices between $200 - $400
int *createTickets(int *ranArr, int *boolArr)
{
	// variables to hold min and max $ amount for tickets
	int min = 200, max = 400; 
	 
	// seed rand()
	srand(time(NULL));
	
	// generate random number between min and max and put it in the array[i]
	int i; 
	for (i = 0; i < 25; i++) 
	{
            int ranNum = (rand() % (max - min + 1)) + min;
            ranArr[i] = ranNum;
	} 
	
	for (i = 0; i < 25; i++)
	{
		boolArr[i] = 1;
	}
}


// main function
int main()
{	
	int ranArr[25];		// array to hold randomly generated ticket prices
	int boolArr[25];	// array to hold ticket status | 0 = SOLD | 1 = AVAIL
	
	// create tickets function
	createTickets(ranArr, boolArr);
	
	printf("[<> SERVER ]: Database Table:\n");
	printf("TICKET NUMBER  PRICE  STATUS\n----------------------------\n");
	int i;
	for (i = 0; i < 25; i++)
	{
		// check ticket status
		char status[5];
		if (boolArr[i] == 0)
		{
			char status[] = "SOLD";
		}
		else
		{
			char status[] = "AVAIL";
		}
		
		// print tickets
		int ticketNum = i;
		printf("[Tkt # %d]: $ %d %s\n", 10000 + ticketNum, ranArr[i], status);
	}
	printf("----------------------------\n");
	
	return 0;
}