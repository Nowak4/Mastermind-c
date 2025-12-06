#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

#include "players.h"
#define N_PLAYERS 10 

// prototypes of  functions not used outside the library, only local
// prototypes of the functions that can be used in the program are available in players.h
void initFeedback(int board[ATTEMPTS][2]);
void initBoard(int board[ATTEMPTS][SIZE]);
void generate(int code[]);
int verify(int code[], int guess[], int *black, int *white);

// *****************************
// **** library functions   *****
// *****************************


void displayListOfPlayers(struct typePlayer listP[],int nPlayers){
	int i;
	printf("\n\nid\tName       Surname\tScore\tnGames\n");
	printf("--\t----       -------\t-----\t------\n");
 	for (i=0;i<nPlayers;i++){ 
		printf("%i\t", listP[i].id);
		printf("%-10s %-10s\t", listP[i].name,listP[i].surname);
		printf("%i\t", listP[i].score);
		printf("%i\n", listP[i].nGPlayed);
	}
}

void loadListOfPlayers(struct typePlayer listP[],int *nPlayers){
/* assign initial values to the first N players 
       N_PLAYERS is a constant defined in this script- change constant to change number of players]
    Input data: 
          listOfPlayers: vector of players (parameter by reference)
    Output data: 
        listOfPlayers: vector of players (parameter by reference)
        nPlayers: number of players created - by reference 

   */
    char names[16][256]={"Carmen", "Antonio", "Isabel", "Jose", "Ana", "Manuel", "Pilar", "Francisco", "Dolores", "Juan", "Teresa", "David", "Laura", "Javier", "Cristina", "Jesus"};
    char surnames[16][256]={"Garcia", "Gonzalez", "Fernadez", "Rodriguez", "Lopez", "Martinez", "Sanchez", "Perez", "Gomez", "Martin", "Jimenez", "Ruiz", "Hernandez", "Diaz", "Moreno", "Alvarez"};
     
    int n=0;
    int i;
  
     
     *nPlayers =N_PLAYERS;
 
    // assign values to the fields in players
    for (i=0; i<*nPlayers; i++){
        listP[i].id=i+1;
        //Name, taking one random value from vector names
        n=(rand()%16);
        strcpy(listP[i].name, names[n]); // use strcpy to assign values to strings
        
        //Surname, taking one random value from vector surnames
        n=(rand()%16);
        strcpy(listP[i].surname, surnames[n]);
        
        // Games played and score initialized to 0
        listP[i].nGPlayed=0;
        listP[i].score=0;
        
    }
    return;
}


void loadListOfGames(struct typeGame listG[], int *nGames){
	int i,j,b,w;
	int r; // row in the board
	int n; // local var for nAttempts
	*nGames=rand()%6+6; //random number of games from 5 to 11
	
	for (i=0;i<*nGames;i++){ 
		initBoard(listG[i].board); //initialize Board to zeros
		initFeedback(listG[i].feedback); //initialize feedback to zeros
		
		// generate random number of attempts
		n=rand()%10+1; // nAttempts from 1 to 11

		// generate secret code
		generate(listG[i].secretCode);
				
		// copy secret code to last row according to number of attempts n, i.e. n-1
		for (j=0;j<4;j++){ 	// copy secret code last row
			listG[i].board[n-1][j]=listG[i].secretCode[j];
		}
		
		// fill in remaining rows with random values
		for  (r=0;r<n-1;r++){ 	
			generate(listG[i].board[r]); // use generateSecretCode to generate random guess -- it is not the secret code here
		}
				
		if (n == ATTEMPTS){ 
			// two options 10 and last row correct or 10 and last wrong
			if (rand()%2){
				// last row is wrong
				// change one value of last row -- for example, add one
				listG[i].board[n-1][1]=	listG[i].board[n-1][1]+1;
				// if adding one we get number 7, put it back to one
				if (listG[i].board[n-1][1]==7)
					listG[i].board[n-1][1]=1;
			}
		}
		
		// use verify code to populate feedback 
		for  (r=0;r<n;r++){ 
			verify(listG[i].secretCode, listG[i].board[r], &b, &w);
			listG[i].feedback[r][0]=b; //4 blacks
			listG[i].feedback[r][1]=w; //0 white
		}
			
		// set score and nAttempts	
		listG[i].nAttempts=n;
		listG[i].score=110-(listG[i].nAttempts*10);	
		if ((n == ATTEMPTS)&&(listG[i].feedback[ATTEMPTS][0]==4)) {//  code not guessed
			listG[i].score=0;
		}
		// assign random player
		listG[i].playerId=rand()%N_PLAYERS+1;	
	} 
}



// *****************************
// *** functions not available in the library, local	
// *****************************

void initBoard(int m[ATTEMPTS][SIZE]){
	int i,j;
	for (i=0;i<ATTEMPTS;i++){ 
	  for (j=0;j<SIZE;j++){  
	  	m[i][j]=0;
		}	
	}
}

void initFeedback(int m[ATTEMPTS][2]){
	int i,j;
	for (i=0;i<ATTEMPTS;i++){ 
		for (j=0;j<2;j++){  
			m[i][j]=0;
		}
	}
}

void generate  (int code[]){
  int colorPegs[NCOLORS]={1, 2, 3, 4, 5, 6}; 
  int t=NCOLORS; 
  int num;
  int i, j;
  
  for (i=0; i<SIZE; i++){
      num=rand()%t;     
      code[i]=colorPegs[num];
      for (j=num; j<t; j++){
          colorPegs[j]=colorPegs[j+1];
      }
      t=t-1; 
  }
  return;
}

int verify(int code[], int guess[], int *blacks, int *whites){
	*whites=0;  
	*blacks=0;
	int valid=0; 
	int i, j;
	for (i=0; i<SIZE; i++){
		for(j=0; j< SIZE; j++){
			if (code[i]==guess[j]){
				if (i==j)
					(*blacks)++;
				else
					(*whites)++;
			}
		}
	}
	if (*blacks==SIZE){
		valid=1;
	}
	return valid;
}



