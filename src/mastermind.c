/*

Group 5

Kevin D. Tejada Colmenero 100582890
Tanvir Md. Mahtab 100582052 

*/

#include <stdio.h>
#include <stdlib.h>
#include "players.h"
#include <time.h>
 
//prototypes

int main (void){
  srand (time(NULL));  // seed random number generator
  struct typeGame games[MAX_GAMES];
  struct typePlayer players[MAX_PLAYERS];
  int index=-1;
  int nGame=0;
  int nPlayers=N_PLAYERS;               
  
  loadListOfGames(games, &nGame);// inicialización
  loadListOfPlayers(players, &nPlayers); // inicialización

  while(index!=0){

    system("cls");

    //header_mastermind();
    mainMenu();
    scanf("%d",&index);

    switch(index) {

      case 0:
        printf(" Exiting");
        return 0;

      case 1:
        system("cls");       
        displayListOfGames(games, nGame);
        exitMenu();
        break;

      case 2:
        system("cls");       
        selectPlayer(&games[nGame],players,nPlayers);
        if(nGame<MAX_GAMES){
          games[nGame]=play(games[nGame]);
          updatePlayersScores(games, players, nGame, nPlayers);
          players[games[nGame].playerId].nGPlayed++;  
          nGame++;
        }
        printf("\n");
        exitMenu();
        break;

      case 3:
        system("cls");
        displayListOfPlayers(players, nPlayers);
        exitMenu();
        break;

      case 4:
        system("cls");
        rankPlayers(players,nPlayers);
        exitMenu();
        break;

      case 5:
        system("cls");
        showTop(players,nPlayers);
        exitMenu();
        break;
    }
  }
  return 0;
}


