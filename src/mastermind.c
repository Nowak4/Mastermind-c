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
	int board[ATTEMPTS][SIZE]={'-'};  // matrix to store the guesses (All initialized as -)
	int feedback [ATTEMPTS][2]={'-'};  // matrix to store the feedback
	int correct=0; // flag 
	int nAttempts=0; //counter for the attempts
	int score;
	int b,w; // vars for number of blacks and number of whites
  int playerCode;
	
	srand (time(NULL));  // seed random number generator
  
  //Welcome message
  generateSecretCode(secretCode);
  printf("Hi, welcome to mastermind.\nTo win you have to guess a 4 digit code\n");
  
  //Board displays (Starts with all 0 and keep updating)
  //displayBoard(int board[ATTEMPTS][SIZE], int feedback[ATTEMPTS][2], int nRows);

  //The inputs (at the foot of the table)
  printf("Tell me your first guess:" );
  scanf("%i", &playerCode);
  verifyCode(secretCode,&playerCode,&b,&w);


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
    for(j=0; j<SIZE; i++){
      if(secretCode[i]==guess[j] && i==j){
        *black=*black+1; 
      }
      else(secretCode[i]==guess[j] && i!=j){
        *white=*white + 1;
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
 //Create some kind of heather for the table.

  //The plan is to create a board initiallized by zeros, and dinamicly changes with the feedback and tries
  for(int i=0;i>ATTEMPTS;i++){
    printf(" | ");
    for(int j=0; j){
      printf("%c",board[i][j]);
    }
    printf(" | ");
    for(int k=0; k>2; k++){
      pritnf("%c",feedback[i][k]);
    }
    printf(" | /n")
  }
}

void printVector (int v[], int t){
	// displays a vector of size t
	int i;
	for (i=0; i<t; i++){ 
		printf("%i ", v[i]);	
	}
	printf("\n");
}



