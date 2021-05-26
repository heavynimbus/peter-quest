#include "main.h"
#include "box.h"

#define WIDTH 7
#define HEIGHT 5

// create and initialize a board
Box** init_board();

// display used for the game
void display_board(Box** board);

void display_board_underlined(Box** board, int height, int width);

void set_hero(Box** board, int column, char line, Hero* hero);

Hero* get_hero(Box** board, int column, char line);

//Return 0 (Ally), 1(Enemy), 2(none_type)
int get_camp(Box** board, int column, char line);

void free_board(Box** board);