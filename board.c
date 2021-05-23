#include "board.h"

Hero* get_hero(Box** board, int column, char line){
	return board[(int)(line-'a')][column-1].hero;
}


void  set_hero(Box** board, int column, char line, Hero* hero)
{
  	board[(int)(line-'a')][column-1].hero = hero;
}

Box** init_board()
{
	Box** result = (Box**) calloc(HEIGHT, sizeof(Box*));
	for(int i = 0; i < HEIGHT; i++)
	{
		Box* line = (Box*) calloc(WIDTH, sizeof(Box));
		for(int j = 0; j < WIDTH; j++)
		{
			line[j] = create_box( (j + 1), ('a' + i), create_hero(NONE_HERO, NONE_RACE));
		}
		result[i] = line;
	}
	

	return result;
}


void display_board(Box** board)
{
	const char* numbers_line = "\t 1 2 3 4 5 6 7";
	const char* filling_line = "\t|-------------|";

	printf("\t\t\t\t\t\t%s\n\t\t\t\t\t\t%s\n", numbers_line, filling_line);

	for(int i = 0; i < HEIGHT; i++){
		
		char* line_to_print = (char*)calloc(16, sizeof(char));
		char values[WIDTH] = {0}; // init all values to 0
		for(int j = 0; j < WIDTH; j++)
		{
			values[j] = get_char(board[i][j].hero->race->type);
		}
		sprintf(line_to_print, "%c\t|%c|%c|%c|%c|%c|%c|%c|", (char)('a'+ i) , values[0], values[1], values[2], values[3], values[4], values[5], values[6]);
		printf("\t\t\t\t\t\t%s\n\t\t\t\t\t\t%s\n", line_to_print, filling_line);
	}
}