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
void deplace(Box** board, Hero* hero, int column, char line);

//Test si le héro peut se deplacer
int can_deplace(Box** board, Hero* hero, int column, char line);

//Attaque avec un hero
void attack(Hero hero);

//Test si le hero peut attaquer
int can_attack(Hero hero);

//Test la présence d'un héro dans une case 
int have_unit(Box** board, int column, char line);

//Choisir le mouvement d'un héro
Box* choose_move(Box** board, int column, char line, Hero* hero);

//Lance une partie
void play_game(Game game);

//Lance une partie avec 2 joueurs
void play_game_2p(Game game);

//Modifier les valeurs d'un joueur
void set_player(Game g, char* username, PlayerType type, int id);

//Retourne la distance entre 2 unités
int check_distance(int columnBox, int lineBox, int columnUnity, int lineUnity);