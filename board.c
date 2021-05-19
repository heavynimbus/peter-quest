#include "board.h"

Box** init_board()
{
	Box** result = (Box**) calloc(HEIGHT, sizeof(Box*));
	for(int i = 0; i < HEIGHT; i++)
	{
		Box* line = (Box*) calloc(WIDTH, sizeof(Box));
		for(int j = 0; j < WIDTH; j++)
		{
			line[j] = create_box( (j + 1), ('a' + i), NULL);
		}
		result[i] = line;
	}
	return result;
}

char get_value(Hero* hero)
{
	if(hero == NULL) return ' ';
	
	printf("%c\n",hero->type );
	return 'A';
}

void display_board(Box** board)
{
	const char* numbers_line = "\t 1 2 3 4 5 6 7";
	const char* filling_line = "\t|-------------|";

	printf("%s\n%s\n", numbers_line, filling_line);

	for(int i = 0; i < HEIGHT; i++){
		
		char* line_to_print = (char*)calloc(16, sizeof(char));
		char values[WIDTH] = {0}; // init all values to 0
		for(int j = 0; j < WIDTH; j++)
		{
			values[j] = get_value(board[i][j].hero);
		}
		sprintf(line_to_print, "%c\t|%c|%c|%c|%c|%c|%c|%c|", (char)('a'+ i) , values[0], values[1], values[2], values[3], values[4], values[5], values[6]);
		printf("%s\n%s\n", line_to_print, filling_line);
	}
}