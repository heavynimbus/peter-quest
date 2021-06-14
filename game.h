#include "main.h"
#include "screen.h"
#include "ia.h"

typedef struct
{
    Box** board;
    Player* player1;
    Player* player2;
}Game;

//Initialisation partie
Game* init_game();

void set_player(Game g, char* username, PlayerType type, int id);

void free_game(Game* g);

Player* run(Game* game);