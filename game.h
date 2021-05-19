#include "main.h"
#include "board.h"

typedef struct
{
    Box** board;
    char Payer1;
    char Player2;
}Game;

//Initialisation partie
Game init_game();

//Deplace un héro
void deplace(Hero hero);

//Test si le héro peut se deplacer
int can_deplace(Hero hero);

//Attaque avec un hero
void attack(Hero hero);

//test si le hero peut attaquer
int can_attack(Hero hero);