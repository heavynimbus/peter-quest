#include "main.h"
#include "config.h"
#include "screen.h"
#include "board.h"

void get_const_lines(char* number_line, char* top_line, char* filling_line, char* bottom_line, int width)
{
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
	free(tmp);
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

int main()
{
	setlocale(LC_CTYPE, ""); // for unicode chars
	
	char* config_file_path = "peter.config"; // default path	

	int config_height, config_width;
	get_config(config_file_path, &config_height, &config_width);
	/**
	switch(menu(4, "Jouer", "Regles du jeu", "Options", "Quitter"))
	{
		case 0:
			switch(menu(3, "1 Joueur", "2 Joueurs", "Retour"))
			{
				case 0:
					return main();
				case 1:
					break;
				case 2:
					return main();
			}
			break;
		case 1:
			return main();
		case 2:
			option_menu(&config_height, &config_width);
			set_config(config_file_path, config_height, config_width);
			return main();
		case 3:
			return 0;
	}*/


	printf("Config width :%d\tConfig height: %d\n", config_width, config_height);
	Box** board = init_board(config_height, config_width);
	init_heros(board, config_height, config_width);
	int size;
	char** to_display = board_to_string(board, config_height, config_width, -1, -1, &size);

	int screen_height, screen_width, cpt = 0;
	get_screen_dimensions(&screen_height, &screen_width);
	int x = (screen_width - (4 * config_width) )/2;
	int y = (screen_height - (2 * config_height) +2)/2;
 	for(int j = 0; j < size; j++)
 	{
 		set_pos(x,y++);
 		printf("%c\t%s\n",(j%2 != 1 && j > 1)?'A'+cpt++:' ', to_display[j]);
	}
	
	printf("%d\n", 7%2);
	return 0;
}