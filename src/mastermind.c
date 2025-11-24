#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NCOLORS 6 
#define SIZE 4 		// size of the secret code
#define ATTEMPTS 10 //10
#define MAX_SCORE 100

// **************Prototypes ************************
void generateSecretCode  (int secretCode[]);
int verifyCode(int secretCode[], int guess[], int *black, int *white);	
void scanVector (int v[], int t);
void printVector (int v[], int t);
void displayBoard (int board[ATTEMPTS][SIZE], int feedback[ATTEMPTS][2], int nRows);


int main (void){
	int secretCode[SIZE];
	int board[ATTEMPTS][SIZE];  // matrix to store the guesses
	int feedback[ATTEMPTS][2];  // matrix to store the feedback
	int correct=0; // flag 
	int nAttempts=0; //counter for the attempts
	int score;
	int b=0,w=0; // vars for number of blacks and number of whites
  int playerCode;
  int v;
	
	srand (time(NULL));  // seed random number generator
  
  generateSecretCode(secretCode);
  printf("Hi, welcome to mastermind.\n");
  printf("To win you have to guess a 4 digit code\n");


  while(nAttempts<ATTEMPTS){
    printf("Tell me your nº %i guess:\n", nAttempts+1);
    scanVector(board[nAttempts], SIZE);
    verifyCode(secretCode,board[nAttempts],&b,&w);
    feedback[nAttempts][0]=b;
    b=0;
    feedback[nAttempts][1]=w;
    w=0;
    if((feedback[nAttempts][0]=SIZE)){
      break;
    }
    nAttempts++;
  }
  // printVector(secretCode, SIZE); for debugging purposes
  // printVector(feedback[nAttempts], 2);
	return 0;
}

void generateSecretCode  (int secretCode[]){
	// returns a vector of four elements containing a random secret code
  int colorPegs[NCOLORS]={1, 2, 3, 4, 5, 6};  //vector containing available pegs
  int t=NCOLORS; //number of available pegs, initially 8
  int num;
  int i, j;
  
  for (i=0; i<SIZE; i++){
      num=rand()%t;     //generate random number from 0 to t-1
      secretCode[i]=colorPegs[num];
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

void displayBoard (int board[ATTEMPTS][SIZE], int feedback[ATTEMPTS][2], int nRows){

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
