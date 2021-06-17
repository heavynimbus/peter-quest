#include "config.h"
#include "game.h"

void between(int* value, int min, int max)
{
	if (*value < min) *value = max-1;
	if (*value >= max) *value = min;
}

void display_winner(Player* winner) {
    system("clear");
    printf("%s à gagné\n", winner->username);
    getchar();
}


int main()
{
	setlocale(LC_CTYPE, ""); // for unicode chars


	char* config_file_path = "peter.config"; // default path	

	int config_height, config_width;
	get_config(config_file_path, &config_height, &config_width);

	switch(menu(4, "Jouer", "Regles du jeu", "Options", "Quitter"))
	{
		case 0:
			switch(menu(3, "1 Joueur", "2 Joueurs", "Retour"))
			{
				case 0:
				{
					Game* game = init_game(config_height, config_width);
					ask_player_name(game, 0);
					set_player(game, "IA", IA, 1);

					Player* winner = run(game);
					display_winner(winner);

					break;
				}
				case 1:
				{
					Game* game = init_game(config_height, config_width);
					ask_player_name(game, 0);
					ask_player_name(game, 1);

					Player* winner = run(game);
					display_winner(winner);
					return main();
				}
				case 2:
					return main();
			}
			break;
		case 1:
			show_about();
			getchar();
			return main();
		case 2:
			option_menu(&config_height, &config_width);
			set_config(config_file_path, config_height, config_width);
			return main();
		case 3:
			return 0;
	}
	return 0;
}