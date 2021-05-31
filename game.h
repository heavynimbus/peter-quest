#include "main.h"
#include "board.h"
#include "player.h"
#include "screen.h"

#define BOX_WIDTH 7
#define BOX_HEIGHT 5

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