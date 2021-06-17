#include "main.h"
#include "screen.h"
#include "board.h"
#include "player.h"
#include "node.h"

typedef struct
{
    Box** board;
    Player* player1;
    Player* player2;
    int config_height;
    int config_width;
}Game;
/*
struct node
{
    Game* game;
    struct node* children;
    int score;
    int nb_children;
};

typedef struct node Node;*/




//Initialisation partie
Game* init_game(int config_height, int config_width);

Player* run(Game* game);

void ask_player_name(Game* g, int id);

void display_game(Game* game, int selected_height, int selected_width, char* message);

void set_player(Game* g, char* username, PlayerType type, int id);

Game* copy_game(Game* game);
