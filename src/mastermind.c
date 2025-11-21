#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
void scanGuess (int v[], int t);

int main (void){
  setbuf(stdout, NULL); //for debugging purposes
	int secretCode[SIZE];
	int board[ATTEMPTS][SIZE]={0};  // matrix to store the guesses
	int feedback[ATTEMPTS][2]={0};  // matrix to store the feedback
	int correct=0; // flag 
	int nAttempts=0; //counter for the attempts
	int score;
	int b=0,w=0; // vars for number of blacks and number of whites
  int playerCode;
  int v;
	
	srand (time(NULL));  // seed random number generator
  
  //Welcome message
  generateSecretCode(secretCode);

  printf("Hi, welcome to mastermind\n");
  printf("To win you have to guess a %d digit code\n", SIZE);

  while(nAttempts<ATTEMPTS){
    displayBoard(board,feedback,10);

    printf("\nTell me your nº %i guess (Up to %d numbers): ", nAttempts+1,SIZE);
    scanGuess(board[nAttempts], SIZE);
    verifyCode(secretCode,board[nAttempts],&b,&w);

    feedback[nAttempts][0]=b;
    b=0;
    feedback[nAttempts][1]=w;
    w=0;

    if(feedback[nAttempts][0]==SIZE){
      break;
    }
    system("clear");
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


int verifyCode(int secretCode[], int guess[], int *black, int *white){
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
        (*black)++;
      }
      if(secretCode[i]==guess[j] && i!=j){
        (*white)++;
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
  int num=0;            // Store te imput
	scanf("%d",&num);
  // &v[0]=(num/1000)%10;
  // &v[1]=(num/100)%10;   Thats the concept of the for, which decomposes the number
  // &v[2]=(num/10)%10;
  // &v[3]=num%10;

  for (i=0; i<t; i++){
   v[i]=(int)(num/(pow(10,t-i-1)))%10;
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


