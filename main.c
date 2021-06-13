#include "config.h"
#include "game.h"

void between(int* value, int min, int max)
{
	if (*value < min) *value = max-1;
	if (*value >= max) *value = min;
}

int main()
{
	setlocale(LC_CTYPE, ""); // for unicode chars


	char* config_file_path = "peter.config"; // default path	

	int config_height, config_width;
	get_config(config_file_path, &config_height, &config_width);
	

	/*
	int selected_width, selected_height;
	Game* game = init_game(config_height, config_width);
	select_a_box(game,1,1, &selected_height, &selected_width);
	printf("height : %d\twidth : %d\n", selected_height, selected_width);*/

	switch(menu(4, "Jouer", "Regles du jeu", "Options", "Quitter"))
	{
		case 0:
			switch(menu(3, "1 Joueur", "2 Joueurs", "Retour"))
			{
				case 0:
					return main();
				case 1:
				{
					Game* game = init_game(config_height, config_width);
					ask_player_name(game, 0);
					ask_player_name(game, 1);

					run(game);
					break;
				}
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
	}


	//printf("Config width :%d\tConfig height: %d\n", config_width, config_height);

	//display_board_center(board, config_height, config_width, 115, 16);
	
	return 0;
}