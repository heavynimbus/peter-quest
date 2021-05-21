#include "main.h"
#include "box.h"

#define WIDTH 7
#define HEIGHT 5

// create and initialize a board
Box** init_board();

// display used for the game
void display_board(Box** board);

void set_hero(Box** board, int column, char line, Hero* hero);

Hero* get_hero(Box** board, int column, char line);

char get_value(Hero* hero);