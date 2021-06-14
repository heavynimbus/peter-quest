#include "main.h"
#include "box.h"



// create and initialize a board
Box** init_board(int config_height, int config_width);

// display used for the game
char** board_to_string(Box** board,int config_height, int config_width, int selected_height, int selected_width, int* size);


void init_heros(Box** board, int height, int width);

void display_board_center(Box** board, int config_height, int config_width, int selected_height, int selected_width);

void display_board(Box** board, int config_height, int config_width);

void moove(Box** board, int initial_line, int initial_column, int moove_line, int moove_column);

void kill(Box** board, int line, int column);
