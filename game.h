#include "main.h"
#include "board.h"
#include "player.h"

#define BOX_WIDTH 7
#define BOX_HEIGHT 5

typedef struct
{
    Box** board;
    Player* player1;
    Player* player2;
}Game;

//Initialisation partie
Game init_game();

//Deplace un héro
void deplace(Hero hero);

//Test si le héro peut se deplacer
int can_deplace(Hero hero);

//Attaque avec un hero
void attack(Hero hero);

//Test si le hero peut attaquer
int can_attack(Hero hero);

//Test la présence d'un héro dans une case 
int have_unit(Box** board, int column, char line);

//Choisir le mouvement d'un héro
void choose_move(Box** board, int column, char line, Hero* hero);

//Lance une partie
void play_game(Game game);

void set_player(Game g, char* username, PlayerType type, int id);

void free_game(Game g);