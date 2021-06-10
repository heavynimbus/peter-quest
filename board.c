#include "board.h"
// create and initialize a board
Box** init_board(int config_height, int config_width){
	Box** board = calloc(config_height, sizeof(Box*));
	for(int i = 0; i < config_height; i++) {
		board[i] = calloc(config_width, sizeof(Box));
		for(int j = 0; j < config_width; j++)
			board[i][j] = create_box(i, j, create_hero(NONE_HERO, NONE_RACE));
	}
	return board;
}

