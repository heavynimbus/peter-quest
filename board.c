#include "board.h"
#include "screen.h"

Hero* get_hero(Box** board, int column, char line){
	return board[(int)(line-'a')][column-1].hero;
}

int get_camp(Box** board, int column, char line){
	Hero* hero = get_hero(board, column, line);
	return hero->type;
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

char* get_value_with_color(Hero* hero)
{	
	char* result = calloc(255, sizeof(char));
	switch(hero->type){
		case BLUE: sprintf(result, "%s%c%s", BLUE_COLOR, get_char(hero->race->type), WHITE_COLOR);
			break;
		case RED: sprintf(result, "%s%c%s", RED_COLOR, get_char(hero->race->type), WHITE_COLOR);
			break;
		case NONE_HERO: sprintf(result, "%s%c%s", WHITE_COLOR, get_char(hero->race->type), WHITE_COLOR);
			break;
	}
	return result;
}

void display_board(Box** board)
{
	const char* numbers_line = "\t 1 2 3 4 5 6 7";
	const char* filling_line = "\t|-------------|";

	printf("%s%48s%s\n%48s%s\n", WHITE_COLOR, "", numbers_line,"", filling_line);

	for(int i = 0; i < HEIGHT; i++){
		
		char* line_to_print = (char*)calloc(16, sizeof(char));
		char** values = calloc(WIDTH, sizeof(char*)); // init all values to 0
		for(int j = 0; j < WIDTH; j++)
		{
			values[j] = get_value_with_color(board[i][j].hero);
		}
		sprintf(line_to_print, "%c\t|%s|%s|%s|%s|%s|%s|%s|", (char)('a'+ i) ,values[0], values[1], values[2], values[3], values[4], values[5], values[6]);
		printf("%48s%s\n%48s%s\n", "", line_to_print, "", filling_line);
	}
}

void display_board_underlined(Box** board, int height, int width)
{
	const char* numbers_line = "\t 1 2 3 4 5 6 7";
	const char* filling_line = "\t|-------------|";

	printf("%s%48s%s\n\t\t\t\t\t\t%s\n", WHITE_COLOR, "", numbers_line, filling_line);

	for(int i = 0; i < HEIGHT; i++){
		
		char* line_to_print = (char*)calloc(16, sizeof(char));
		char** values = calloc(WIDTH, sizeof(char*)); // init all values to 0
		for(int j = 0; j < WIDTH; j++)
		{	
			values[j] = calloc(255, sizeof(char));
			if (i == height && j == width){
				sprintf(values[j], "%s%c%s", UNDERLINE, get_char(board[i][j].hero->race->type), WHITE_COLOR);
			}else{
				values[j] = get_value_with_color(board[i][j].hero);
			}
		}
		sprintf(line_to_print, "%c\t|%s|%s|%s|%s|%s|%s|%s|", (char)('a'+ i) ,values[0], values[1], values[2], values[3], values[4], values[5], values[6]);
		printf("%48s%s\n%48s%s\n", "", line_to_print, "", filling_line);
	}
}

void free_board(Box** board){
	for(int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			free_box(board[i][j]);
		}
	}
}