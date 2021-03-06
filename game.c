#include "game.h"

/**
    Print the hero informations at x,y index 
*/
void display_hero_informations(Box box, int x, int y)
{   
    char* infos = get_hero_informations(box);
    set_pos(x, y);
    switch(box.hero->type){
        case NONE_HERO:
            return;
        case RED:
            printf("%s%s", RED_COLOR, infos);
            break;
        case BLUE:
            printf("%s%s", BLUE_COLOR, infos);
            break;
    }
}

/**
    print all the informations about the game
*/
void display_player_informations(Game* game){

	int screen_height, screen_width;    
	get_screen_dimensions(&screen_height, &screen_width);

	int x = (screen_width - (4 * game->config_width) )/2;
	int y = (screen_height - (2 * game->config_height) +2)/2;

    int x1 = x/3, y1 = y;
    int x2 = x + 4 * game->config_width + x/2, y2 = y;

    set_pos(x1, y1);
    printf("%s%s", BLUE_BACKGROUND, game->player1->username);
    x1 -= 5; y1 += 2;

    set_pos(x2, y2);
    printf("%s%s", RED_BACKGROUND, game->player2->username);
    x2 -=5; y2 += 2;

    for(int i = 0; i < game->config_height; i++)
    {
        for(int j = 0; j < game->config_width; j++)
        {
            switch(game->board[i][j].hero->type)
            {
                case BLUE:
                {
                    display_hero_informations(game->board[i][j], x1, y1);
                    y1 += 2;
                    break;
                }
                case RED:
                {
                    display_hero_informations(game->board[i][j], x2, y2);
                    y2 += 2;
                    break;
                }
                case NONE_HERO:
                {
                    break;
                }
            }
        }
    }
}

/**
    Set the player to the game
*/
void set_player(Game g, char* username, PlayerType type, int id){
    switch(id){
        case 0:
            g.player1->username = username;
            g.player1->type = type;
            break;
        case 1:
            g.player2->username = username;
            g.player2->type = type;
            break;
    }
}

/**
	Ask the player's name
*/
void ask_player_name(Game* g, int id){
	show_logo();
	char* result = calloc(30, sizeof(char));
	printf("Joueur %d\nEntrez votre nom:\t", id+1);
	fgets(result, 30, stdin);
	if(result[strlen(result)-1]=='\n')result[strlen(result)-1]=0;
	if(strlen(result) == 0) sprintf(result, "Joueur %d", id+1);
	set_player(*g, result, HUMAN, id);
}


void display_game(Game* game, int selected_height, int selected_width, char* message)
{
	system("clear");
	display_board_center(game->board, game->config_height, game->config_width, selected_height, selected_width);
	display_player_informations(game);
	if(message != NULL && strlen(message) > 0) display_messages(1, message);
}

//Initialisation partie
Game* init_game(int config_height, int config_width)
{
	Box** board = init_board(config_height, config_width);
	init_heros(board, config_height, config_width);
	Player* player1 = malloc(sizeof(Player));
	Player* player2 = malloc(sizeof(Player));
	Game* game = malloc(sizeof(Game));
	game->board = board;
	game->player1 = player1;
	game->player2 = player2; 

	game->config_height = config_height;
	game->config_width = config_width;
	return game;
}

void update_tired(Game* game, HeroType type)
{
	for(int i = 0; i < game->config_height; i++)
        for (int j = 0; j < game->config_width; j++)
        	if(game->board[i][j].hero->type == type) game->board[i][j].hero->is_tired = 0;
}

int update_game_state(Game* game, int* who_is_playing, int* is_game_finished){
    
	int tired_count1 = 0, tired_count2 = 0;
    int count1=0, count2=0;
    for(int i = 0; i < game->config_height; i++)
    {
        for (int j = 0; j < game->config_width; j++)
        {
            switch(game->board[i][j].hero->type)
            {
                case BLUE:
                    if (game->board[i][j].hero->hp > 0) count1++;
                    if (game->board[i][j].hero->is_tired) tired_count1++; 
                    break;
                case RED:
                    if (game->board[i][j].hero->hp > 0) count2++;
                    if (game->board[i][j].hero->is_tired) tired_count2++;
                    break;
                case NONE_HERO:
                    continue;
            }
        }
    }
    if(count1 == tired_count1) update_tired(game, BLUE);
    if(count2 == tired_count2) update_tired(game, RED);

    *is_game_finished = (count1 == 0 || count2 == 0 )? 1:0; 

    *who_is_playing = (*who_is_playing)?0:1;
    if(*is_game_finished) return (count1)? 0:1;
    return -1;
}



void select_a_box(Game* game, int height, int width, int* selected_height, int* selected_width, char* message, int can_pass)
{
    int selected = 0;
   	do
   	{
   		display_game(game, height, width, message);
   		switch(getchar())
   		{
   			case 0x41: height--;// up key
				break;
			case 0x42: height++;// down key
				break;
			case 0x43: width++;// right key
				break;
			case 0x44: width--;// left key
				break;
			case '\n': selected++;
				break;
			case 'q':
				if (can_pass) return;
   		}
   		between(&height, 0, game->config_height);
   		between(&width, 0, game->config_width);
   	}while(!selected);
   	
   	*selected_height = height;
   	*selected_width = width;
}


Box* get_neighbours(Game* game, int line, int column, int* nb_neighbours)
{
    int cpt = 0;
    Box* neighbours = calloc(4, sizeof(Box));
    if(line-1 >= 0) neighbours[cpt++] = game->board[line-1][column];
    if(line+1 < game->config_height) neighbours[cpt++] = game->board[line+1][column];
    if(column-1 >= 0) neighbours[cpt++] = game->board[line][column-1];
    if(column+1 < game->config_width) neighbours[cpt++] = game->board[line][column+1];
    *nb_neighbours = cpt;
    return neighbours;
}


void display_debug(int** tab, int height, int width)
{
    for(int i = 0; i < height; i++){
        printf("[");
        for(int j = 0; j < width; j++)
            printf("%d\t", tab[i][j]);
        printf("]\n");
    }
}

int** get_moove_count(Game* game, int line, int column)
{
    int** result = calloc(game->config_height, sizeof(int*));
    for(int i = 0; i < game->config_height; i++)
    {
        result[i] = calloc(game->config_width, sizeof(int));
        for(int j = 0; j < game->config_width; j++)
            result[i][j] = -2;
    }


    Box* list = malloc(sizeof(Box));
    *list = game->board[line][column];
    int nb_elements = 1, count = 0;

    result[line][column] = count;
    do{

        count++;
        int nb_elements_next_list = 4 * nb_elements, cpt = 0;
        Box* next_list = calloc(nb_elements_next_list, sizeof(Box));
        
        for(int i = 0; i < nb_elements; i++)
        {
        
            int nb_neighbours;
            Box* neighbours = get_neighbours(game, list[i].line, list[i].column, &nb_neighbours);
        
            for(int j = 0; j < nb_neighbours; j ++)
            {
                if (result[neighbours[j].line][neighbours[j].column] == -2)
                {
                    if (game->board[neighbours[j].line][neighbours[j].column].hero->type == NONE_HERO)
                    {
                    	result[neighbours[j].line][neighbours[j].column] = count;
                    	next_list[cpt++] = neighbours[j];
                    }
                	else result[neighbours[j].line][neighbours[j].column] = -1;                    
                }
            }
        }
        list = next_list;
        nb_elements = cpt;
    }while(nb_elements>0);
    return result;
}

int** get_scope_count(Game* game, int line, int column)
{
    int** result = calloc(game->config_height, sizeof(int*));
    for(int i = 0; i < game->config_height; i++)
    {
        result[i] = calloc(game->config_width, sizeof(int));
        for(int j = 0; j < game->config_width; j++)
            result[i][j] = -2;
    }


    Box* list = malloc(sizeof(Box));
    *list = game->board[line][column];
    int nb_elements = 1, count = 0;

    result[line][column] = count;
    do{

        count++;
        int nb_elements_next_list = 4 * nb_elements, cpt = 0;
        Box* next_list = calloc(nb_elements_next_list, sizeof(Box));
        
        for(int i = 0; i < nb_elements; i++)
        {
        
            int nb_neighbours;
            Box* neighbours = get_neighbours(game, list[i].line, list[i].column, &nb_neighbours);
        
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

int can_attack(Game* game, int line, int column)
{
	if(game->board[line][column].hero->type == NONE_HERO) return FALSE;
	int scope = game->board[line][column].hero->race->scope;
	int** scope_count = get_scope_count(game, line, column);
	HeroType enemyType = (game->board[line][column].hero->type == BLUE)?RED:BLUE;
	for(int i = 0; i < game->config_height; i++)
	{
		for(int j = 0; j < game->config_width; j++)
		{
			if ((game->board[i][j].hero->type == enemyType) &&
							(scope_count[i][j] <= scope))
			{	
				return TRUE;
			}
		}
	}
	return FALSE;
}


void attack_and_response(Game* game, int allyLine, int allyColumn, int enemyLine, int enemyColumn)
{
	Hero* ally = game->board[allyLine][allyColumn].hero;
	Hero* enemy = game->board[enemyLine][enemyColumn].hero;

	if((ally->type == NONE_HERO) ||
		(enemy->type == NONE_HERO)) return;

	attack(ally, enemy);

	if(enemy->hp > 0)
	{
		int** enemy_scope_count = get_scope_count(game, enemyLine, enemyColumn);
		if(enemy_scope_count[allyLine][allyColumn] <= enemy->race->scope)
		{
			attack(enemy, ally);
			if(ally->hp <= 0)
				kill(game->board, allyLine, allyColumn);
		}
	}
	else
		kill(game->board, enemyLine, enemyColumn);
}



Player* run(Game* game)
{	
	static struct termios oldMask, newMask;
	tcgetattr ( STDIN_FILENO, &oldMask );
    newMask = oldMask;
    newMask.c_lflag &= ~(ICANON); // avoid <enter>
    newMask.c_lflag &= ~(ECHO); // hide text typed
    tcsetattr( STDIN_FILENO, TCSANOW, &newMask);
	
	
	
	int is_player2_winner;
	int who_is_playing = 0, is_game_finished = 0;
	Player* player;

	char* message = calloc(255, sizeof(char));
	char* message_color;

	do
	{
		if(who_is_playing)
        {
            message_color = RED_COLOR;
            player = game->player2;
        }else{
            message_color = BLUE_COLOR;
            player = game->player1;
        }

        switch(player->type)
        {
        	case HUMAN:
        	{
        		sprintf(message, "%s%s pr??parez vous !", message_color, player->username);
				display_game(game, -1, -1, message);
				getchar();
		        

		        int initial_line = -1, initial_column = -1;
		        int move_line = -1, move_column = -1;
				int move_done = 0;
				do
				{
					do
					{
						sprintf(message, "%sSelectionnez une de vos unit??s pour un deplacement",message_color);
						select_a_box(game, 0, 0, &initial_line, &initial_column, message, 0);
					}while(game->board[initial_line][initial_column].hero->type != ((who_is_playing)?RED:BLUE));

					if (game->board[initial_line][initial_column].hero->is_tired)
					{
						sprintf(message, "%sCette unit?? est trop fatigu??e..", message_color);
						display_game(game, -1, -1, message);
						getchar();
						continue;
					}

					int** moove_count = get_moove_count(game, initial_line, initial_column);
					do
					{
						sprintf(message, "%sChoisissez votre deplacement",message_color);
						select_a_box(game, initial_line, initial_column, &move_line, &move_column, message, 0);
					}while(game->board[move_line][move_column].hero->type != NONE_HERO);

					if(moove_count[move_line][move_column] <= game->board[initial_line][initial_column].hero->race->shifting)
					{
						moove(game->board, initial_line, initial_column, move_line, move_column);
						move_done++;
					}
					else
					{
						sprintf(message, "%sCette unit?? ne peut pas de deplacer de plus de %d cases ...", message_color, game->board[initial_line][initial_column].hero->race->shifting);
						display_game(game, -1, -1, message);
						getchar();
					}
				}while(!move_done);

				if(can_attack(game, move_line, move_column))
				{	
					int** scope_count = get_scope_count(game, move_line, move_column);
					int attack_line = -1, attack_column = -1;
					int attack_done = 0;
					do
					{
						do
						{
							sprintf(message, "%sChoisissez l'unit?? que vous voulez attaquer. Appuyez sur 'q' pour passer", message_color);
							select_a_box(game, move_line, move_column, &attack_line, &attack_column, message, 1);
							if(attack_line < 0 && attack_column < 0) break;
						}while(game->board[attack_line][attack_column].hero->type != ((who_is_playing)?BLUE:RED));

						if(attack_line < 0 && attack_column < 0) break;
						if (scope_count[attack_line][attack_column] <= game->board[move_line][move_column].hero->race->scope)
						{
							attack_and_response(game, move_line, move_column, attack_line, attack_column);
							attack_done++;
						}
						else 
						{
							sprintf(message, "%sVotre unit?? a une port??e d'attaque de %d cases", message_color, game->board[initial_line][initial_column].hero->race->shifting);
							display_game(game, -1, -1, message);
							getchar();
						}
					}while(!attack_done);
				}
				game->board[move_line][move_column].hero->is_tired = 1;
        		break;
        	}
        	case IA:
        	{
        		break;
        	}
        }
        is_player2_winner = update_game_state(game, &who_is_playing, &is_game_finished);
	}while(!is_game_finished);


    tcsetattr( STDIN_FILENO, TCSANOW, &oldMask);

	if(is_player2_winner) return game->player2;
	return game->player1;
}