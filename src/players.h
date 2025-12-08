#define ATTEMPTS 10  // max number of attempts
#define SIZE 4 		 // size of the secret code
#define NCOLORS 6    // number of possible color	
#define MAX_GAMES 50   // max number of games
#define MAX_PLAYERS 20 // max number of players
#define MAX_SCORE 100
#define N_PLAYERS 10     
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
struct sortedPlayers{           //Nueva estructura para rankear
   int rank;			// player rank
   char name[256];
   char surname[256];
   int score;			// score
   int nGPlayed;		// number of games played
};


//FUNCIONES BÁSICAS FUNCIONALIDAD JUEGO
void generateSecretCode  (struct typeGame *game);
int verifyCode(struct typeGame game, int *black, int *white);	
void scanGuess (struct typeGame *game);
struct typeGame play(struct typeGame *game, struct typePlayer *player);
//
void displayListOfPlayers(struct typePlayer listP[],int nPlayers);
void MyDisplayListOfPlayers(struct typePlayer listP[],int nPlayers);
void loadListOfGames(struct typeGame listG[], int *nGames);
void loadListOfPlayers(struct typePlayer listP[],int *nPlayers);  
void displayRankOfPlayers(struct sortedPlayers listP[],int nPlayers);
void topPlayers(struct sortedPlayers listP[], int topPlayers);
