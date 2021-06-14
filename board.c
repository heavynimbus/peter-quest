#include "board.h"
#include "screen.h"
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


void get_const_lines(char* number_line, char* top_line, char* filling_line, char* bottom_line, int width)
{
	strcat(number_line, WHITE_COLOR);
	char* tmp = calloc(30, sizeof(char));
	for (int j = 0; j < width; j++)
	{
		sprintf(tmp, "%lc%lc%lc%lc", (j == 0)? TOP_LEFT_CORNER : TOP_MIDDLE,
									 DOUBLE_HORIZONTAL,
									 DOUBLE_HORIZONTAL, 
									 DOUBLE_HORIZONTAL);
		strcat(top_line, tmp);
		sprintf(tmp, "%lc%lc%lc%lc", (j == 0)? BOTTOM_LEFT_CORNER : BOTTOM_MIDDLE,
									 DOUBLE_HORIZONTAL,
									 DOUBLE_HORIZONTAL, 
									 DOUBLE_HORIZONTAL);
		strcat(bottom_line, tmp);
		sprintf(tmp, "%lc%lc%lc%lc", (j == 0)? FILLING_LEFT : FILLING_MIDDLE,
									 SIMPLE_HORIZONTAL,
									 SIMPLE_HORIZONTAL, 
									 SIMPLE_HORIZONTAL);
		strcat(filling_line, tmp);
		sprintf(tmp, " %2d ", j+1);
		strcat(number_line, tmp);
	}
	sprintf(tmp, "%lc", TOP_RIGHT_CORNER);
	strcat(top_line, tmp);
	sprintf(tmp, "%lc", BOTTOM_RIGHT_CORNER);
	strcat(bottom_line, tmp);
	sprintf(tmp, "%lc", FILLING_RIGHT);
	strcat(filling_line, tmp);
}

char* get_variable_line(Box* line, int width, int selected)
{
 	char* result = calloc(255, sizeof(char));
 	char* tmp = calloc(255, sizeof(char));
 	char* color;
 	for(int i = 0; i < width; i++)
 	{
 		Box box = line[i];
 		switch(box.hero->type)
 		{
 			case BLUE: color = BLUE_COLOR;
 				break;
 			case RED: color = RED_COLOR;
 				break;
 			case NONE_HERO: color = WHITE_COLOR;
 				break;
 		}
 		if(i == selected) color = UNDERLINE;

		sprintf(tmp, "%lc %s%c%s ", (i==0)?DOUBLE_VERTICAL:SIMPLE_VERTICAL,
								color,
								get_char(box.hero->race->type),
								WHITE_COLOR);
		strcat(result, tmp);
 	}
 	sprintf(tmp, "%lc", DOUBLE_VERTICAL);
 	strcat(result, tmp);
	return result;
}

char** board_to_string(Box** board,int config_height, int config_width, int selected_height, int selected_width, int* size)
{
	char* top_line = calloc(255, sizeof(char));
	char* bottom_line = calloc(255, sizeof(char));
	char* filling_line = calloc(255, sizeof(char));
	char* number_line = calloc(255, sizeof(char));
 	get_const_lines(number_line, top_line, filling_line, bottom_line, config_width);

 	int cpt = 0;
 	char* variable_lines[config_height];
 	for(int i = 0; i < config_height; i++)
 	{
 		if(i == selected_height) variable_lines[i] = get_variable_line(board[i], config_width, selected_width);
 		else variable_lines[i] = get_variable_line(board[i], config_width, -1);

 	}


 	*size = (config_height * 2)+2;
 	char** result = calloc(*size, sizeof(char*));
 	for(int i = 0; i < *size; i++)
 	{
 		if(i == 0) result[i] = number_line;
 		else if(i == 1) result[i] = top_line;
 		else if((i % 2) == 1)
 		{
 			if(i == (*size - 1)) result[i] = bottom_line;
 			else result[i] = filling_line;	
 		} 
 		else
 		{
 			result[i] = variable_lines[cpt++];
 		}
 	}
 	return result;
}

void init_heros(Box** board, int height, int width)
{
	int middle = height/2;
	printf("height:%d, width:%d -> middle %d\n",height, width, middle );
	switch(height%2)
	{
		case 0:
			board[middle+1][0].hero = create_hero(BLUE, ARCHER);
			board[middle+1][width-1].hero = create_hero(RED, TRICKSTER);

			board[middle+1][1].hero = create_hero(BLUE, SOLDIER);
			board[middle+1][width-2].hero = create_hero(RED, SOLDIER);

			board[middle-2][0].hero = create_hero(BLUE, TRICKSTER);
			board[middle-2][width-1].hero = create_hero(RED, ARCHER);

			board[middle-2][1].hero = create_hero(BLUE, SOLDIER);
			board[middle-2][width-2].hero = create_hero(RED, SOLDIER);
			break;
		case 1:
			board[middle+1][0].hero = create_hero(BLUE, ARCHER);
			board[middle+1][width-1].hero = create_hero(RED, TRICKSTER);

			board[middle+1][1].hero = create_hero(BLUE, SOLDIER);
			board[middle+1][width-2].hero = create_hero(RED, SOLDIER);

			board[middle-1][0].hero = create_hero(BLUE, TRICKSTER);
			board[middle-1][width-1].hero = create_hero(RED, ARCHER);

			board[middle-1][1].hero = create_hero(BLUE, SOLDIER);
			board[middle-1][width-2].hero = create_hero(RED, SOLDIER);
			break;
	}
}

void display_board_center(Box** board, int config_height, int config_width, int selected_height, int selected_width)
{
	int size;
	char** to_display = board_to_string(board, config_height, config_width, selected_height, selected_width, &size);
	int screen_height, screen_width, cpt = 0;
	get_screen_dimensions(&screen_height, &screen_width);
	int x = (screen_width - (4 * config_width) )/2;
	int y = (screen_height - (2 * config_height) +2)/2;
 	for(int j = 0; j < size; j++)
 	{
 		set_pos(x,y++);
 		printf("%c\t%s\n",(j%2 != 1 && j > 1)?'A'+cpt++:' ', to_display[j]);
	}	
}

void display_board(Box** board, int config_height, int config_width)
{
	int size = 0;
	char** to_display = board_to_string(board, config_height, config_width, -1, -1, &size);
	for(int i = 0; i < size; i++) printf("%s\n", to_display[i]);
}

void moove(Box** board, int initial_line, int initial_column, int moove_line, int moove_column)
{
	Hero* tmp = board[initial_line][initial_column].hero;
	board[initial_line][initial_column].hero = board[moove_line][moove_column].hero;
	board[moove_line][moove_column].hero = tmp;
}

void kill(Box** board, int line, int column)
{
	Hero* to_free = board[line][column].hero;
	board[line][column].hero = create_hero(NONE_HERO, NONE_RACE);
	free_hero(to_free);
}

Box* get_neighbours(Box** board, int line, int column, int* nb_neighbours, int config_height, int config_width)
{
    int cpt = 0;
    Box* neighbours = calloc(4, sizeof(Box));
    if(line-1 >= 0) neighbours[cpt++] = board[line-1][column];
    if(line+1 < config_height) neighbours[cpt++] = board[line+1][column];
    if(column-1 >= 0) neighbours[cpt++] = board[line][column-1];
    if(column+1 < config_width) neighbours[cpt++] = board[line][column+1];
    *nb_neighbours = cpt;
    return neighbours;
}

int** get_scope_count(Box** board, int line, int column, int config_height, int config_width)
{
    int** result = calloc(config_height, sizeof(int*));
    for(int i = 0; i < config_height; i++)
    {
        result[i] = calloc(config_width, sizeof(int));
        for(int j = 0; j < config_width; j++)
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
            Box* neighbours = get_neighbours(board, list[i].line, list[i].column, &nb_neighbours, config_height, config_width);
        
            for(int j = 0; j < nb_neighbours; j ++)
            {
                if (result[neighbours[j].line][neighbours[j].column] == -2)
                {
                	result[neighbours[j].line][neighbours[j].column] = count;
                	next_list[cpt++] = neighbours[j];         
                }
            }
        }
        list = next_list;
        nb_elements = cpt;
    }while(nb_elements>0);
    return result;
}

Box** copy_board(Box** board,int config_height, int config_width) {
	
	Box** copy = calloc(config_height, sizeof(Box*));
	for(int i=0; i<config_height; i++) {
		copy[i] = calloc(config_width, sizeof(Box));
		for(int j=0; j<config_width; j++) {
			copy[i][j] = copy_box(board[i][j]);
		}
	}
	return copy;
}