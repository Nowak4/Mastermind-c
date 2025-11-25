#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "players.h"

#define NCOLORS 6 
#define SIZE 4 		// size of the secret code
#define ATTEMPTS 10 //10
#define MAX_SCORE 100

// **************Prototypes ************************
void generateSecretCode  (struct typeGame *game);
int verifyCode(struct typeGame game, int *black, int *white);	
void scanVector (struct typeGame game);
void printVector (struct typeGame game);
void displayBoard (struct typeGame game, int nRows);
void scanGuess (struct typeGame game);

int main (void){
  setbuf(stdout, NULL); //for debugging purposes
	int correct=0; // flag 
	int b=0,w=0; // vars for number of blacks and number of whites
  int playerCode;
  int v;
  struct typeGame game[ATTEMPTS];
	
	srand (time(NULL));  // seed random number generator
  
  // generateSecretCode(struct typeGame game[nAttempts]);
  printf("Hi, welcome to mastermind.\n");
  printf("To win you have to guess a 4 digit code\n");



  // while(game.nAttempts<ATTEMPTS){
  //   displayBoard(game.board,game.feedback,10);
  //
  //   printf("Tell me your nº %i guess:\n", game.nAttempts+1);
  //   scanGuess(struct typeGame *game);
  //   verifyCode(game.secretCode,game.board[game.nAttempts],&b,&w);
  //
  //   game.feedback[game.nAttempts][0]=b;
  //   b=0;
  //   game.feedback[game.nAttempts][1]=w;
  //   w=0;
  //
  //   if(game.feedback[game.nAttempts][0]==SIZE){
  //     break;
  //   }
  //   game.nAttempts++;
  // }
  // // printVector(secretCode, SIZE); for debugging purposes
  // printVector(feedback[nAttempts], 2);
	return 0;
}

void generateSecretCode (struct typeGame *game){
	// returns a vector of four elements containing a random secret code
  int colorPegs[NCOLORS]={1, 2, 3, 4, 5, 6};  //vector containing available pegs
  int t=NCOLORS; //number of available pegs, initially 8
  int num;
  int i, j;
  
  for (i=0; i<SIZE; i++){
      num=rand()%t;     //generate random number from 0 to t-1
      game->secretCode[i]=colorPegs[num];
      //we remove that colour from the vector containing available pegs
      // we move them all one position forward 
      for (j=num; j<t; j++){
          colorPegs[j]=colorPegs[j+1];
      }
      t=t-1; //number of available pegs is updated
  }
  return;
}


int verifyCode(int secretCode[], int guess[], int *blacks, int *whites){
	// secretCode: secretCode to verify (input) 1x4
	// guess: colors entered by the user (input) 1x4
	// feedback = number of white and black pegs (output, by reference)
	// return; 1 if valid, 0 if not valid
  int i=0;
  int j=0;
  int check=0;

  for(i=0;i<SIZE;i++){
    for(j=0; j<SIZE; j++){
      if(secretCode[i]==guess[j] && i==j){
        (*blacks)++;
      }
      if(secretCode[i]==guess[j] && i!=j){
        (*whites)++;
      }
    }
  }

 return 1;
}

void scanVector (int v[], int t){
	// reads values for a vector of size t	
	int i;
	for (i=0; i<t; i++)
		scanf("%i", &v[i]);
	return;
}

void scanGuess (int v[], int t){
	// reads values for a vector of size t	
	int i;
	for (i=0; i<t; i++){
    printf("Position %i: ", i+1);
    scanf("%i", &v[i]);
  }
	return;
}

void displayBoard (int board[ATTEMPTS][SIZE], int feedback[ATTEMPTS][2], int nRows){
 //Create some kind of header for the table.
  printf("| YOUR GUESS | Black White|\n");
  printf("---------------------------\n");

  //The plan is to create a board initiallized by zeros, and dinamicly changes with the feedback and tries
  for(int i=0;i<ATTEMPTS;i++){
    printf("|");
    for(int j=0; j<SIZE; j++){
      printf(" %d ",board[i][j]);
    }
    printf("|");
    for(int k=0; k<2; k++){
      printf("   %d  ",feedback[i][k]);
    }
    printf("|\n");
  }
  return;
}

void printVector (int v[], int t){
	// displays a vector of size t
	int i;
	for (i=0; i<t; i++){ 
		printf("%i ", v[i]);	
	}
	printf("\n");
}

//asdf

//asdfdsafasdft
