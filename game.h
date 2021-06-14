#include "main.h"
#include "screen.h"
#include "ia.h"

typedef struct
{
    Box** board;
    Player* player1;
    Player* player2;
    int config_height;
    int config_width;
}Game;

//Initialisation partie
Game* init_game(int config_height, int config_width);

Player* run(Game* game);

void ask_player_name(Game* g, int id);

void display_game(Game* game, int selected_height, int selected_width, char* message);

void set_player(Game* g, char* username, PlayerType type, int id);
