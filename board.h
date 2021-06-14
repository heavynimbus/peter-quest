#include "main.h"
#include "box.h"



// create and initialize a board
Box** init_board();

// display used for the game
void display_board(Box** board);

void display_board_underlined(Box** board, int line, int column);

void set_hero(Box** board, int column, char line, Hero* hero);

void free_board(Box** board);

int kill(Box** board, int line, int column);

Box** copy_board(Box** board);

int** get_scope_count(Box** board, int line, int column);

Box* get_neighbours(Box** board, int line, int column, int* nb_neighbours);