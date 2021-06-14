#include "board.h"
#include "screen.h"


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
			line[j] = create_box(i, j, create_hero(NONE_HERO, NONE_RACE));
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

void display_board_underlined(Box** board, int line, int column)
{
	const char* numbers_line = "\t 1 2 3 4 5 6 7";
	const char* filling_line = "\t|-------------|";

	printf("%s%48s%s\n%48s%s\n", WHITE_COLOR, "", numbers_line,"", filling_line);

	for(int i = 0; i < HEIGHT; i++){
		
		char* line_to_print = (char*)calloc(16, sizeof(char));
		char** values = calloc(WIDTH, sizeof(char*)); // init all values to 0
		for(int j = 0; j < WIDTH; j++)
		{	
			values[j] = calloc(255, sizeof(char));
			if (i == line && j == column){
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

int kill(Box** board, int line, int column)
{
	if(board[line][column].hero->type == NONE_HERO) return 0;
	board[line][column].hero = create_hero(NONE_HERO, NONE_RACE);
	return 1;
}

Box** copy_board(Box** board) {
    Box** board_copied = init_board();
    board_copied = board;
    return board_copied;
}

int** get_scope_count(Box** board, int line, int column)
{
    int** result = calloc(HEIGHT, sizeof(int*));
    for(int i = 0; i < HEIGHT; i++)
    {
        result[i] = calloc(WIDTH, sizeof(int));
        for(int j = 0; j < WIDTH; j++)
            result[i][j] = -2;
    }

    Box* list = malloc(sizeof(Box));
    *list = board[line][column];
    int nb_elements = 1, count = 0;

    result[line][column] = count;
    do{

        count++;
        int nb_elements_next_list = 4 * nb_elements, cpt = 0;
        Box* next_list = calloc(nb_elements_next_list, sizeof(Box));
        
        for(int i = 0; i < nb_elements; i++)
        {
        
            int nb_neighbours;
            Box* neighbours = get_neighbours(board, list[i].line, list[i].column, &nb_neighbours);
        
            for(int j = 0; j < nb_neighbours; j ++)
            {
                if ((result[neighbours[j].line][neighbours[j].column] == -2))
                {
                    result[neighbours[j].line][neighbours[j].column] = count;
                    next_list[cpt++] = neighbours[j];
                }
            }
        }
        free(list);
        list = next_list;
        nb_elements = cpt;
    }while(nb_elements>0);
    return result;
}

Box* get_neighbours(Box** board, int line, int column, int* nb_neighbours)
{
    int cpt = 0;
    Box* neighbours = calloc(4, sizeof(Box));
    if(line-1 >= 0) neighbours[cpt++] = board[line-1][column];
    if(line+1 < HEIGHT) neighbours[cpt++] = board[line+1][column];
    if(column-1 >= 0) neighbours[cpt++] = board[line][column-1];
    if(column+1 < WIDTH) neighbours[cpt++] = board[line][column+1];
    *nb_neighbours = cpt;
    return neighbours;
}