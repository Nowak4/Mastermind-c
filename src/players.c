// prototypes of  functions not used outside the library, only local
#include <string.h> // Te deja usar strcpy 
#include <stdio.h>  // La clasica 
#include <stdlib.h> // Random stuff
#include <math.h>   // Deja usar pow
#include <time.h>

#include "players.h"

// prototypes of the functions that can be used in the program are available in players.h
void initFeedback(int board[ATTEMPTS][2]);
void initBoard(int board[ATTEMPTS][SIZE]);
void generate(int code[]);
int verify(int code[], int guess[], int *black, int *white);

// *****************************
// **** library functions   *****
// *****************************


// *****************************************************
// **** Funcionalidad basicas. Funcionalidad Juego *****
// *****************************************************

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

void scanGuess (int secretCode[], int board[][SIZE], int nAttempts){
	// reads values for a vector of size t	
	int i;
  int num=123; // Store the ibput
  int check=123;
	scanf("%d",&num);
  // &v[0]=(num/1000)%10;
  // &v[1]=(num/100)%10;   Thats the concept of the for, which decomposes the number
  // &v[2]=(num/10)%10;
  // &v[3]=num%10;
  if(num==6969){          //Codigo secreto para que se chive el juego
    while(check!=0){
      printf("You are a cheater...\nThe code is: ");
      for(i=0;i<SIZE;i++){
        printf("%d",secretCode[i]);
      }
      printf("\nType 0 to continue as nothing happened: ");
      scanf("%d",&check);
    }
  }
  for (i=0; i<SIZE; i++){ 
    board[nAttempts][i]=(int)(num/(pow(10,SIZE-i-1)))%10;
  }
	return;
}
 
struct typeGame play(struct typeGame game){
	int b=0,w=0; // vars for number of blacks and number of whites
	srand(time(NULL));   // seed random number generator
  system("cls");
  
  //Welcome message
  generateSecretCode(game.secretCode);

  printf("Hi, welcome to mastermind\n");
  printf("To win you have to guess a %d digit code\n", SIZE);

  while(game.nAttempts<ATTEMPTS){

    printVector(game.secretCode);
    displayGame(game);

    printf("\nGuess nº %i  (Up to %d numbers): ", game.nAttempts+1,SIZE);
    scanGuess(game.secretCode,game.board,game.nAttempts);
    verifyCode(game.secretCode, game.board[game.nAttempts],&b,&w);

    game.feedback[game.nAttempts][0]=b;
    b=0;
    game.feedback[game.nAttempts][1]=w;
    w=0;

    if(game.feedback[game.nAttempts][0]==SIZE){
      game.nAttempts++;
      system("cls");                          //Hay dos escores
      displayGame(game);
      game.score=(MAX_SCORE+10)-game.nAttempts*10; //Score de la partida (El +10 arregla el desfase para que 1º Attempt -> 100 puntos)
      printf("Congratulations!!! You broke the code with just %d attempts.\nThose are %d points",game.nAttempts,game.score);
      return game;  
    }

    
    system("cls");
    game.nAttempts++;
  }
    system("cls");
    displayGame(game);
    printf("Ohh you are such a bad decoder. The code was ");
    int i;  
    for(i=0; i<SIZE; i++){
        printf("%d",game.secretCode[i]);
      }
    printf("\nMaybe you are luckier next time.");

  system("cls");
  return game;
  
}




struct typeGame selectPlayer(struct typeGame *game, struct typePlayer list_players[],int nPlayers){    //Cambiamos el id del jugador para que se estoree ahí la info. Id=3 luegoal usar loadListOfPlayers[i] i=Id
  
  int input = 0;                             //Variable para ajustar el input a la posición natural de una lista array 1-> arr[0]
  do{
    system("cls");
    // displayListOfPlayers(struct typePlayer listP[],int nPlayers)   
    printf("Who is going to play?");
    MyDisplayListOfPlayers(list_players,nPlayers);
    printf("\nType the Id of the player: ");
    scanf("%d", &input);

  }while(input>nPlayers || input<=0 );
  game->playerId=input-1;
  return *game;
}

// ****************************************
// **** Funcionalidad para displayear *****
// ****************************************

void displayBoard (int board[ATTEMPTS][SIZE], int feedback[ATTEMPTS][2], int nRows){
 //Create some kind of header for the table.
  printf("| YOUR GUESS | Black White|\n");
  printf("---------------------------\n");

  //The plan is to create a board initiallized by zeros, and dinamicly changes with the feedback and tries
  int i,j,k;
  for(i=0;i<nRows;i++){
    printf("|");
    for(j=0; j<SIZE; j++){
      printf(" %d ",board[i][j]);
    }
    printf("|");
    for(k=0; k<2; k++){
      printf("   %d  ",feedback[i][k]);
    }
    printf("|\n");
  }
  for( i=0;i<ATTEMPTS-nRows;i++){
      printf("|");
      for(j=0; j<SIZE; j++){
        printf(" - ");
      }
        printf("|");  
      for(k=0; k<2; k++){
        printf("   -  ");
    }
    printf("|\n");
  }

  return;
}

void displayGame (struct typeGame game){

  printf("Attempt: %-6d Score: %d\n", game.nAttempts, MAX_SCORE-game.nAttempts*10);

  displayBoard(game.board,game.feedback,game.nAttempts);

  return;
}

void displayListOfGames(struct typeGame listG[],int nGame){
  system("cls");
  //header_game();
  printf("|  Game  |  Secret Code  |  Score  |  Attempts|\n");
  printf(" --------------------------------------------- \n");
  int i,j;
  for(j=0; j<nGame;j++){
  printf("     %d     ",j+1);
  printf("     ");
  for(i=0; i<SIZE; i++){
    printf("%d",listG[j].secretCode[i]);
  }
  printf("     ");
  printf("     %d          %d     \n", listG[j].score, listG[j].nAttempts);
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
// Modificacion de la del profe para usar en el programa
void MyDisplayListOfPlayers(struct typePlayer listP[],int nPlayers){
	int i;
	printf("\n\nid\tName       Surname\n");
	printf("--\t----       -------\n");
 	for (i=0;i<nPlayers;i++){ 
		printf("%i\t", listP[i].id);
		printf("%-10s %-10s\n", listP[i].name,listP[i].surname);
	}
}
// Otro mod del display del profe para ensñar el rank
void displayRankOfPlayers(struct typePlayer listP[],int nPlayers){
	int i;
	printf("\n\nRank\tName       Surname\tScore\tnGames\n");
	printf("--\t----       -------\t-----\t------\n");
 	for (i=0;i<nPlayers;i++){ 
		printf("%d\t",i+1 );
		printf("%-10s %-10s\t", listP[i].name,listP[i].surname);
		printf("%i\t", listP[i].score);
		printf("%i\n", listP[i].nGPlayed);
	}
}


// ****************************************
// ****   Funcionalidad para ordenar   ****
// ****************************************

void rankPlayers(struct typePlayer listPlayers[],int nPlayers){
  //Primero copiar los datos de estructura a estructura 
  system("cls");
  //header_rank();           //Cabecero ASCII 
  struct typePlayer sortedPlayers[nPlayers];
  int i=0;        //Valor para no perder posiciones
  int j=0;
  
  for(i=0;i<nPlayers;i++){
    sortedPlayers[i] = listPlayers[i];
      // printf("\nCopy points: %d\n", sortedPlayers[i].score); // debugging
  }


  for(j=0;j<nPlayers;j++){
    for(i=0;i<nPlayers-1;i++){
      if(sortedPlayers[i].score<sortedPlayers[i+1].score){
        //Primero cambia los rank y luego el pointer (posición)
        struct typePlayer copyStruct = sortedPlayers[i];
        sortedPlayers[i]=sortedPlayers[i+1];
        sortedPlayers[i+1]=copyStruct;
      }
    }
  }
  displayRankOfPlayers(sortedPlayers,nPlayers);
  return;
}

void showTop(struct typePlayer listPlayers[],int nPlayers){
  int top=0;
  system("cls");
  struct typePlayer sortedPlayers[nPlayers];
  //header_top();            //Cabecero ASCII
  printf("How many player do you want to show in the top: ");
  scanf("%d", &top);
  if(top>nPlayers){
    top=nPlayers;
  }
  else if(top<=0){
    return;
  }
  system("cls");
  //header_top(); 
  printf("How many player do you want to show in the top: %d",top); //Hace que si tipeas algo !=0 no te permita cambiar el top
  int i=0;        //Valor para no perder posiciones
  int j=0;

  for(i=0;i<nPlayers;i++){
    sortedPlayers[i] = listPlayers[i];
  }

  for(j=0;j<nPlayers;j++){
    for(i=0;i<nPlayers-1;i++){
      if(sortedPlayers[i].score<sortedPlayers[i+1].score){
        //Primero cambia los rank y luego el pointer (posición)
        struct typePlayer copyStruct = sortedPlayers[i];
        sortedPlayers[i]=sortedPlayers[i+1];
        sortedPlayers[i+1]=copyStruct;
      }
    }
  }

  displayRankOfPlayers(sortedPlayers,top);
  return;

}

// ****************************************
// ****     Funcionalidad arte ACII     ***
// ****************************************
void header_mastermind(){
  printf("\n███╗░░░███╗░█████╗░░██████╗████████╗███████╗██████╗░███╗░░░███╗██╗███╗░░██╗██████╗░\n");
  printf("████╗░████║██╔══██╗██╔════╝╚══██╔══╝██╔════╝██╔══██╗████╗░████║██║████╗░██║██╔══██╗\n");
  printf("██╔████╔██║███████║╚█████╗░░░░██║░░░█████╗░░██████╔╝██╔████╔██║██║██╔██╗██║██║░░██║\n");
  printf("██║╚██╔╝██║██╔══██║░╚═══██╗░░░██║░░░██╔══╝░░██╔══██╗██║╚██╔╝██║██║██║╚████║██║░░██║\n");
  printf("██║░╚═╝░██║██║░░██║██████╔╝░░░██║░░░███████╗██║░░██║██║░╚═╝░██║██║██║░╚███║██████╔╝\n");
  printf("╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═════╝░\n");
  return;
}
void header_players(){
printf("\n██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗ ███████╗\n");
printf("██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗██╔════╝\n");
printf("██████╔╝██║     ███████║ ╚████╔╝ ███████╗██████╔╝███████╗\n");
printf("██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██═════╝██╔══██╗╚════██║\n");
printf("██║     ███████╗██║  ██║   ██║   ███████║██║  ██║███████║\n");
printf("╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚══════╝\n");
}
void header_rank(){
printf("\n██████╗  █████╗ ███╗   ██╗██╗  ██╗\n");
printf("██╔══██╗██╔══██╗████╗  ██║██║ ██╔╝\n");
printf("██████╔╝███████║██╔██╗ ██║█████╔╝ \n");
printf("██╔══██╗██╔══██║██║╚██╗██║██╔═██╗ \n");
printf("██║  ██║██║  ██║██║ ╚████║██║  ██╗\n");
printf("╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝\n");
}
void header_top(){
printf("\n████████╗ ██████╗ ██████╗\n");
printf("╚══██╔══╝██╔═══██╗██╔══██╗\n");
printf("   ██║   ██║   ██║██████╔╝ \n");
printf("   ██║   ██║   ██║██╔═══╝ \n");
printf("   ██║   ╚██████╔╝██║     \n");
printf("   ╚═╝    ╚═════╝ ╚═╝     \n");

}
void header_game(){
printf("\n ██████╗  █████╗ ███╗   ███╗███████╗███████╗\n");
printf("██╔════╝ ██╔══██╗████╗ ████║██╔════╝██╔════╝\n");
printf("██║  ███╗███████║██╔████╔██║█████╗  ███████╗\n");
printf("██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ╚════██║\n");
printf("╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗███████║\n");
printf(" ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝╚══════╝\n\n");

}
// ********************************************
// **** Funciones para inicializar struct *****
// ********************************************

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

void mainMenu (){

  printf("\n");
  printf(" 1. Display games \n");
  printf(" 2. Play game \n");
  printf(" 3. List of players \n");  
  printf(" 4. Ranking of players \n"); 
  printf(" 5. Top ranking of players \n");
  printf(" 0. Exit \n");
  printf(" Select an option:");

  return;
}

void exitMenu(){
  int check=-1;

  while(check!=0){
    printf("Type 0 to return:\n");
    scanf("%d", &check);
  }
  system("cls");

  return;
}

void printVector(int v[]){
  int i;
  for(i=0;i<SIZE;i++){
    printf("%i", v[i]);
  }
  printf("\n");
}

void updatePlayersScores(struct typeGame listG[], struct typePlayer listP[], int nGames, int nPlayers){ 

  int i;
  int lastPlayerId = listG[nGames].playerId; // better readability
  // printf("Last score: %d \n LastId: %d", listG[nGames].score, listG[nGames].playerId); // debugging
  if(nGames==0){
    for(i=0;i<nPlayers;i++){
      listP[i].score = 0;
      listP[i].nGPlayed = 0; 
      // printf("\n %s initialized \n", listP[i].name);
    }
  }
  listP[lastPlayerId].score = listP[lastPlayerId].score + listG[nGames].score; //updating score


  return;
}


