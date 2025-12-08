#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <math.h>
#include "players.h"

#define NCOLORS 6 
#define SIZE 4 		// size of the secret code
#define ATTEMPTS 10 //10
#define MAX_SCORE 100
#define MAX_GAMES 50

// **************Prototypes ************************

void generateSecretCode(struct typeGame *game);
int verifyCode(struct typeGame game, int *black, int *white);	
void scanVector (int v[], int t);
void printSecretCode (struct typeGame game, int t);
void printVector (int v[]);
void displayGame (struct typeGame game);
void displayBoard (struct typeGame game);
void mainMenu();
void exitMenu();
void scanGuess (struct typeGame *game, int t);
void displayListOfGames (struct typeGame listG [], int nGames);
void updatePlayersScores(struct typeGame listG[], struct typePlayer listP[], int nGames, int nPlayers); 
struct typeGame play(struct typeGame *game, int nGame);

int main (void){
	srand (time(NULL));  // seed random number generator
  setbuf(stdout, NULL); //for debugging purposes
  struct typeGame game[MAX_GAMES];
  struct typePlayer player[10];
  int nGame = 0;
  int nPlayer = 10;
  int i=-1;
  int id;

  loadListOfGames(game, &nGame);
  loadListOfPlayers(player, &nPlayer);
  for(i=0;i<nPlayer;i++){
    game[i].nAttempts = 0;
  }

  nGame = 0;
  printf("Welcome to mastermind \n");
  printf("Choose your option:");

  while(i!=0){

    mainMenu();
    scanf("%d",&i);

    switch(i) {

      case 0:
        printf(" Exiting");
        return 0;

      case 1:
        system("clear");       
        displayListOfGames(game, nGame);
        exitMenu();
        break;

      case 2:
        system("clear");       
        printf("Tell me your player id: ");
        displayListOfPlayers(player, nPlayer);
        scanf("%d", &id);
        game[nGame].playerId = id-1;
        if(nGame<MAX_GAMES){
          play(&game[nGame], nGame);
          printVector(game[nGame].secretCode);
          updatePlayersScores(game, player, nGame, nPlayer);
          // printf("\nnGAme: %d\n", nGame); for debugging
          // printf("Last id: %d\n", game[nGame].playerId);
          nGame++;
        }
        exitMenu();
        break;

      case 3:
        system("clear");
        // printf("\nLast nGame: %d (%d)", nGame, nGame-1); for debugging
        // printf("\nLast id: %d (%d)", game[nGame-1].playerId+1, game[nGame-1].playerId);
        // printf("\nLast player points: %d \n", game[nGame-1].score);
        displayListOfPlayers(player, nPlayer);
        exitMenu();
        break;

      case 4:
        system("clear");
        displayListOfPlayers(player, nPlayer);
        exitMenu();
        break;

      case 5:
        system("clear");
        displayListOfPlayers(player, nPlayer);
        exitMenu();
        break;
    }
  }

	return 0;
}
void updatePlayersScores(struct typeGame listG[], struct typePlayer listP[], int nGames, int nPlayers){ 

  int i;
  if(nGames==0){
    for(i=0;i<nPlayers;i++){
      listP[i].score = 0;
      listP[i].nGPlayed = 0; 
      // printf("\n %s initialized \n", listP[i].name);
    }
  }
  listP[listG[nGames].playerId].score = listP[listG[nGames].playerId].score + listG[nGames].score;


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

struct typeGame play(struct typeGame *game, int nGame){ //passed as pointer, so everything inside the funct with * is not a pointer

	int b=0,w=0; // vars for number of blacks and number of whites
	
  generateSecretCode(game);
  printf("\n");
  // printSecretCode(*game, SIZE); debugging
  // printf("Last id: %d", game[nGame].playerId);


  while(game->nAttempts<ATTEMPTS){

    displayGame(*game);   //Welcome message
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
      printf("Last id: %d", game[nGame].playerId);
      return *game;
    }
    system("clear");
    (game->nAttempts)++;
  }

  printf("Ohh you are such a bad decoder. The code was ");
  printSecretCode(*game, SIZE);
  printf("\nMaybe you are luckier next time.\n");
  printVector(game[0].secretCode);
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

void printVector(int v[]){
  int i;
  for(i=0;i<SIZE;i++){
    printf("%i", v[i]);
  }
  printf("\n");
}

//asdf


void exitMenu(){
  int i=0;

  while(i!=3){
    printf("Type 3 to return:\n");
    scanf("%d", &i);
  }
  system("clear");

  return;
}
void mainMenu (){

  printf("\n");
  printf(" 1. Display games \n");
  printf(" 2. Play game \n");
  printf(" 3. List of players \n");  
  printf(" 4. Ranking of players \n"); 
  printf(" 5. Top ranking of players \n");
  printf(" 0. Exit \n");
  printf(" ");

  return;
}



