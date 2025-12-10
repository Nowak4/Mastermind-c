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

    system("clear");

    header_mastermind();
    mainMenu();
    scanf("%d",&index);

    switch(index) {

      case 0:
        printf(" Exiting");
        return 0;

      case 1:
        system("clear");       
        displayListOfGames(games, nGame);
        exitMenu();
        break;

      case 2:
        system("clear");       
        printf("Tell me your players id: ");
        displayListOfPlayers(players, nPlayers);
        selectPlayer(&games[nGame],players,nPlayers);
        if(nGame<MAX_GAMES){
          games[nGame]=play(games[nGame]);
          // printf("\n nGame: %d\n", nGame); // debugging
          // printVector(games[nGame].secretCode);
          updatePlayersScores(games, players, nGame, nPlayers);
          // printf("\nnGAme: %d\n", nGame); // debugging
          // printf("Last id: %d\n", games[nGame].playerId);
          players[games[nGame].playerId].nGPlayed++;  
          nGame++;
        }
        printf("\n");
        exitMenu();
        break;

      case 3:
        system("clear");
        // printf("\nLast nGame: %d (%d)", nGame, nGame-1); // debugging
        // printf("\nLast id: %d (%d)", games[nGame-1].playerId+1, games[nGame-1].playerId);
        // printf("\nLast players points: %d \n", games[nGame-1].score);
        displayListOfPlayers(players, nPlayers);
        exitMenu();
        break;

      case 4:
        system("clear");
        rankPlayers(players,nPlayers);
        exitMenu();
        break;

      case 5:
        system("clear");
        showTop(players,nPlayers);
        exitMenu();
        break;
    }
  }
  //
  //     scanf("%d", &index);
  //     if(index==1){ 
  //       displayListOfGames(games, nGame);     
  //     }
  //
  //     else if(index==2){
  //
  //       selectPlayer(&games[nGame],players,nPlayers);
  //       play(games[nGame]);
  //       players[games[nGame].playerId].nGPlayed++;  
  //       nGame++;
  //
  //
  //     }
  //     else if(index==3){
  //       int check=123;      //While de control fuera de la función para no tocar lo que hizo el profe
  //       while(check!=0){
  //         system("clear");
  //         header_players();          //Cabecero ASCII
  //         displayListOfPlayers(players,nPlayers);
  //         printf("\nType 0 to exit: ");
  //         scanf("%d", &check);
  //       }
  //
  //     }
  //     else if(index==4){
  //       rankPlayers(players,nPlayers);    
  //     }
  //     else if(index==5){
  //       showTop(players,nPlayers);
  //     }
  //     else{
  //       system("clear");
  //     }
  // }
  //     system("exit");
  //
  return 0;
}


