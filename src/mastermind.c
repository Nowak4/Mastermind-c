#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "players.h"
 
// **************Prototypes ************************
void generateSecretCode  (struct typeGame *game);
int verifyCode(struct typeGame game, int *black, int *white);	
void displayBoard (struct typeGame game); // nRows es ATTEMPTS
void scanGuess (struct typeGame *game);
struct typeGame play(struct typeGame *game);
void displayGame(struct typeGame listG[],int nGame); // La cambio de struc a void porque solo displayea los games, no hace falta ningun return
void mastermind();
struct typeGame selectPlayer(struct typeGame *game);

int main (void){
int index=100;
int nGame=0;
int nPlayer=0;
struct typeGame games[MAX_GAMES];
struct typePlayer players[MAX_PLAYERS];
loadListOfGames(games, &nGame);
loadListOfPlayers(players, &nPlayer);

while(index!=0){
    system("clear");
    mastermind();
    printf("\nWelcome, what do you want to do:\n1. Display all games\n2. Play game\n3.Display list of players\n4.Display ranking of players\nDisplay top players\n0. Exit\n");
    printf("Your option (Just Numeric): ");
    scanf("%d", &index);
    if(index==1){ 
      displayGame(games, nGame);      //El problema estaba en que se evaluaba mal en display game XD

    }

    else if(index==2){

      selectPlayer(&game[nGame]);
      play(&games[nGame]);
      nGame++;
    
    }
    else if(index==3){
      //Lista de jugadores

    }
    else if(index==4){
      //Ranking de jugadores
    }
    else if(index==5){
      //Top jugadores
    }
    else{
      system("clear");
    }
}
    system("exit;");

}
struct typeGame play(struct typeGame *game){
  setbuf(stdout, NULL); //for debugging purposes
	int score;
	int b=0,w=0; // vars for number of blacks and number of whites
  int playerCode;
  int v;
  int check=123;
	srand (time(NULL));   // seed random number generator
  system("clear");
  
  //Welcome message
  generateSecretCode(game);

  printf("Hi, welcome to mastermind\n");
  printf("To win you have to guess a %d digit code\n", SIZE);

  while(game->nAttempts<ATTEMPTS){

    displayBoard(*game);

    printf("\nGuess nº %i  (Up to %d numbers): ", game->nAttempts+1,SIZE);
    scanGuess(game);
    verifyCode(*game,&b,&w);

    game->feedback[game->nAttempts][0]=b;
    b=0;
    game->feedback[game->nAttempts][1]=w;
    w=0;

    if(game->feedback[game->nAttempts][0]==SIZE){
      int check=1;
      while(check!=0){
      system("clear");
      game->score=MAX_SCORE-game->nAttempts*10;
      printf("Congratulations!!! You broke the code with just %d attempts.\nThose are %d points",game->nAttempts,game->score);
      printf("\n\nType 0 to exit: ");
      scanf("%d",&check);
      }
      return *game;

    }
    system("clear");
    game->nAttempts++;
  }
  while(check!=0){
    printf("Ohh you are such a bad decoder. The code was ");
    for(int i=0; i<SIZE; i++){
    printf("%d",game->secretCode[i]);
  }
  printf("\nMaybe you are luckier next time.");
  printf("\nType 0 to exit: ");
  scanf("%d",&check);
	}
  system("clear");
  return *game;
  
}


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
void displayGame(struct typeGame listG[],int nGame){
  int check=123;
  system("clear");
  while(check!=0){
  printf("|  Game  |  Secret Code  |  Score  |  Attempts|\n");
  printf(" --------------------------------------------- \n");
  for(int j=0; j<nGame;j++){
  printf("     %d     ",j+1);
  printf("     ");
  for(int i=0; i<SIZE; i++){
    printf("%d",listG[j].secretCode[i]);
  }
  printf("     ");
  printf("     %d          %d     \n", listG[j].score, listG[j].nAttempts);
  }
  printf("\n\n\nInsert 0 to exit: ");
  scanf("%d",&check);
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

void scanGuess (struct typeGame *game){
	// reads values for a vector of size t	
	int i;
  int num=0;            // Store te imput
	scanf("%d",&num);
  // &v[0]=(num/1000)%10;
  // &v[1]=(num/100)%10;   Thats the concept of the for, which decomposes the number
  // &v[2]=(num/10)%10;
  // &v[3]=num%10;

  for (i=0; i<SIZE; i++){
   game->board[game->nAttempts][i]=(int)(num/(pow(10,SIZE-i-1)))%10;
  }
	return;
}
  
void displayBoard (struct typeGame game){
 //Create some kind of header for the table.
  printf("| YOUR GUESS | Black White|\n");
  printf("---------------------------\n");

  //The plan is to create a board initiallized by zeros, and dinamicly changes with the feedback and tries
   
  for(int i=0;i<game.nAttempts;i++){
    printf("|");
    for(int j=0; j<SIZE; j++){
      printf(" %d ",game.board[i][j]);
    }
    printf("|");
    for(int k=0; k<2; k++){
      printf("   %d  ",game.feedback[i][k]);
    }
    printf("|\n");
  }
  for(int i=0;i<ATTEMPTS-game.nAttempts;i++){
      printf("|");
      for(int j=0; j<SIZE; j++){
        printf(" - ");
      }
        printf("|");
      for(int k=0; k<2; k++){
        printf("   -  ");
    }
    printf("|\n");
  }

  return;
}
void mastermind(){
  printf("\n███╗░░░███╗░█████╗░░██████╗████████╗███████╗██████╗░███╗░░░███╗██╗███╗░░██╗██████╗░\n");
  printf("████╗░████║██╔══██╗██╔════╝╚══██╔══╝██╔════╝██╔══██╗████╗░████║██║████╗░██║██╔══██╗\n");
  printf("██╔████╔██║███████║╚█████╗░░░░██║░░░█████╗░░██████╔╝██╔████╔██║██║██╔██╗██║██║░░██║\n");
  printf("██║╚██╔╝██║██╔══██║░╚═══██╗░░░██║░░░██╔══╝░░██╔══██╗██║╚██╔╝██║██║██║╚████║██║░░██║\n");
  printf("██║░╚═╝░██║██║░░██║██████╔╝░░░██║░░░███████╗██║░░██║██║░╚═╝░██║██║██║░╚███║██████╔╝\n");
  printf("╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═════╝░\n");
  return;
}
struct typeGame selectPlayer(struct typeGame *game, nGame){    //Cambiamos el id del jugador para que se estoree ahí la info. Id=3 luegoal usar loadListOfPlayers[i] i=Id

    // displayListOfPlayers(struct typePlayer listP[],int nPlayers)
  printf("Who is going to play?");
  displayListOfPlayers(players,10);

  printf("Type the Id of the player: ");
  scanf("%d", game[nGame]->playerId)
}

