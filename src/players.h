#define ATTEMPTS 10  // max number of attempts
#define SIZE 4 		 // size of the secret code
#define NCOLORS 6    // number of possible color	
#define MAX_GAMES 50   // max number of games
#define MAX_PLAYERS 20 // max number of players
#define MAX_SCORE 10 
// structure to store player information
struct typePlayer{
   int id;			// player id
   char name[256];
   char surname[256];
   int score;			// score
   int nGPlayed;		// number of games played
};

// structure to store game information
struct typeGame {
	int nAttempts;
	int secretCode[SIZE];
	int board [ATTEMPTS][SIZE];
	int feedback [ATTEMPTS][2];
	int score;
	int playerId;

};


void displayListOfPlayers(struct typePlayer listP[],int nPlayers);
void loadListOfGames(struct typeGame listG[], int *nGames);
void loadListOfPlayers(struct typePlayer listP[],int *nPlayers);



