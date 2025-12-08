#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <math.h>

#define NCOLORS 6 
#define SIZE 4 		// size of the secret code
#define ATTEMPTS 10 //10
#define MAX_SCORE 100
#define MAX_GAMES 50

// **************Prototypes ************************
struct typeGame {  
  int nAttempts;  
  int secretCode[4];  
  int board [10][4];  
  int feedback [10][4];  
  int score; 
}; 

void generateSecretCode(struct typeGame *game);
int verifyCode(struct typeGame game, int *black, int *white);	
void scanVector (int v[], int t);
void printSecretCode (struct typeGame game, int t);
void displayGame (struct typeGame game);
void displayBoard (struct typeGame game);
void welcomeScreen ();
void scanGuess (struct typeGame *game, int t);
void displayListOfGames (struct typeGame listG [], int nGames);
struct typeGame play(struct typeGame *game);

int main (void){
  setbuf(stdout, NULL); //for debugging purposes

  struct typeGame game[MAX_GAMES];
  int nGame=0;
  int i=-1;

  printf("Welcome to mastermind \n");
  printf("Choose your option:");

  while(i!=0){

    welcomeScreen();

    scanf("%d",&i);
     

    switch(i) {

      case 0:
        printf(" Exiting");
        return 0;

      case 1:
        system("clear");       
        displayListOfGames(game, nGame);
        while(i!=3){
          printf("Type 3 to return:\n");
          scanf("%d", &i);
        }
        system("clear");        
        break;

      case 2:
        system("clear");       
        if(nGame<50){
          play(&game[nGame]);
          nGame++;
        }
        while(i!=3){
        printf("Type 3 to return:\n");
        scanf("%d", &i);

        }
        system("clear");

        break;

    }
  }

	return 0;
}

void welcomeScreen (){

  printf("\n");
  printf(" 1. Diplay games \n");
  printf(" 2. Play game \n");
  printf(" 0. Exit \n");
  printf(" ");

  return;
}

void displayListOfGames (struct typeGame listG[], int nGames){

  int i;
  char sep[2]="-";
  printf("\nGame\t \tScore\t \tSecret Code\n");
  for(i=0;i<43;i++){
    printf("-");
  }
  printf("\n");
  for(i=0;i<nGames;i++){
    printf("%-15d %-16d", i+1, listG[i].score);
    printSecretCode(listG[i], SIZE);
    printf("\n");
  }
 
};

struct typeGame play(struct typeGame *game){

  int correct=0; // flag 
	int b=0,w=0; // vars for number of blacks and number of whites
  int playerCode;
  int v;
	
	srand (time(NULL));  // seed random number generator
  //Welcome message
  generateSecretCode(game);

  while(game->nAttempts<ATTEMPTS){

  displayGame(*game);
  displayBoard(*game);

    printf("\n Guess nº %i  (Up to %d numbers): ", (game->nAttempts)+1,SIZE);
    scanGuess(game, SIZE);
    verifyCode(*game,&b,&w);

    game->feedback[game->nAttempts][0]=b;
    b=0;
    game->feedback[game->nAttempts][1]=w;
    w=0;

    if(game->feedback[game->nAttempts][0]==SIZE){
      system("clear");
      game->score=MAX_SCORE-game->nAttempts*10;
      printf("Congratulations!!! You broke the code with just %d attempts.\nThose are %d points",game->nAttempts,game->score);
      return *game;
    }
    system("clear");
    (game->nAttempts)++;
  }
  printf("Ohh you are such a bad decoder. The code was ");
  printSecretCode(*game, SIZE);
  //   for(int i=0; i<SIZE; i++){
  //   printf("%d, ",game.secretCode[i]);
  // }
  printf("\nMaybe you are luckier next time.\n");
  return *game;
  
};

void generateSecretCode  (struct typeGame *game){
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


int verifyCode(struct typeGame game, int *black, int *white){
	// secretCode: secretCode to verify (input) 1x4
	// guess: colors entered by the user (input) 1x4
	// feedback = number of white and black pegs (output, by reference)
	// return; 1 if valid, 0 if not valid
  int i=0;
  int j=0;
  int check=0;

  for(i=0;i<SIZE;i++){
    for(j=0; j<SIZE; j++){
      if(game.secretCode[i]==game.board[game.nAttempts][j] && i==j){
        (*black)++;
      }
      if(game.secretCode[i]==game.board[game.nAttempts][j] && i!=j){
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

void scanGuess (struct typeGame *game, int t){
	// reads values for a vector of size t	
	int i;
  int num=0;            // Store te imput
	scanf("%d",&num);
  // &v[0]=(num/1000)%10;
  // &v[1]=(num/100)%10;   Thats the concept of the for, which decomposes the number
  // &v[2]=(num/10)%10;
  // &v[3]=num%10;

  for (i=0; i<t; i++){
   game->board[game->nAttempts][i]=(int)(num/(pow(10,t-i-1)))%10;
  }
	return;
}

void displayGame (struct typeGame game){

  printf("Hi, welcome to mastermind\n");
  printf("To win you have to guess a %d digit code\n", SIZE);
  printf("\n");

  printf("Attempt: %-6d Score: %d\n", game.nAttempts, MAX_SCORE-game.nAttempts*10);

  return;
}

void displayBoard (struct typeGame game){
 //Create some kind of header for the table.
  printf("| YOUR GUESS | Black White|\n");
  printf("---------------------------\n");
  int i,j;

  //The plan is to create a board initiallized by zeros, and dinamicly changes with the feedback and tries
  for(i=0;i<game.nAttempts;i++){
    printf("|");
    for(j=0; j<SIZE; j++){
      printf(" %d ",game.board[i][j]);
    }
    printf("|");
    for(j=0; j<2; j++){
      printf("   %d  ",game.feedback[i][j]);
    }
    printf("|\n");
  }
  for(i=game.nAttempts;i<ATTEMPTS;i++){
    printf("|"); 

    for(j=0;j<SIZE+2;j++){
      if(j<SIZE){
      printf(" - ");
      }

      if(j>=SIZE){
      printf("   -  ");
      }

      if(j==SIZE-1){
        printf("|");
      }

    }

    printf("|\n");
  }
  return;
}

void printSecretCode (struct typeGame game, int t){
	// displays a vector of size t
	int i;
	for (i=0; i<t; i++){ 
		printf("%i", game.secretCode[i]);	
	}
	printf("\n");
}

//asdf


