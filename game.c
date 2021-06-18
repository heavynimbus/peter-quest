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
void set_player(Game* g, char* username, PlayerType type, int level, int id){
    switch(id){
        case 0:
            g->player1->username = username;
            g->player1->type = type;
            g->player1->level = level;
            break;
        case 1:
            g->player2->username = username;
            g->player2->type = type;
            g->player2->level = level;
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
	set_player(g, result, HUMAN, 0, id);
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
            Box* neighbours = get_neighbours(game->board, list[i].line, list[i].column, &nb_neighbours, game->config_height, game->config_width);
        
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


int can_attack(Game* game, int line, int column)
{
	if(game->board[line][column].hero->type == NONE_HERO) return FALSE;
	int scope = game->board[line][column].hero->race->scope;
	int** scope_count = get_scope_count(game->board, line, column, game->config_height, game->config_width);
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


int score_board(Game* game, int who_is_playing, int line, int column) {
    int score = 0;
    int count_red = 0;
    int count_blue = 0;
    int count_hp_r = 0;
    int count_hp_b = 0;
    int count_shifting_b = 0;
    int count_shifting_r = 0;

    int** scope_count = get_scope_count(game->board, line, column, game->config_height, game->config_width);


    for (int i=0; i < game->config_height; i++) {
        for (int j=0; j < game->config_width; j++) {
            switch (game->board[i][j].hero->type)
            {
                case RED:
                    count_red++;
                    count_hp_r = count_hp_r + game->board[i][j].hero->hp;
                    count_shifting_r = count_shifting_r + scope_count[i][j];
                    break;
                
                case BLUE:
                    count_blue++;
                    count_hp_b = count_hp_b + game->board[i][j].hero->hp;
                    count_shifting_b = count_shifting_b + scope_count[i][j];
                    break;
                default:
                    break;
            }

        }
    }


    if (!who_is_playing) {
        score = score + count_blue*NB_ALLY;
        score = score - count_red*NB_ENEMY;
        score = score + count_hp_b*HP_ALLY;
        score = score - count_hp_r*HP_ENEMY;
        score = score + count_shifting_b*PROXIMITY_ALLY;
        score = score - count_shifting_r*PROXIMITY_ENEMY;
    } else {
        score = score - count_blue*NB_ENEMY;
        score = score + count_red*NB_ALLY;
        score = score + count_hp_r*HP_ALLY;
        score = score - count_hp_b*HP_ENEMY;
        score = score + count_shifting_r*PROXIMITY_ALLY;
        score = score - count_shifting_b*PROXIMITY_ENEMY;
    }


    return score;
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
		int** enemy_scope_count = get_scope_count(game->board, enemyLine, enemyColumn, game->config_height, game->config_width);
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

Position* get_heroes_position(Game* game, HeroType type, int* nb_position) {
    Position* result = calloc(4, sizeof(Position));
    int count = 0;

    for(int i=0; i<game->config_height; i++) {
        for(int j=0; j<game->config_width; j++){            
            if (game->board[i][j].hero->type == type && !game->board[i][j].hero->is_tired) {
                result[count].line = i;
                result[count].column = j;
                count++;
            }
        }
    }

    *nb_position = count;

    return result;
}

Game* copy_game(Game* game) {
    Game* copy = malloc(sizeof(Game));
    copy->board = copy_board(game->board, game->config_height, game->config_width);
    copy->config_height = game->config_height;
    copy->config_width = game->config_width;
    copy->player1 = game->player1;
    copy->player2 = game->player2;
    return copy;
}

Position* get_posible_moves(Game* game, int line, int column, int* nb_position) {
    int** moove_count = get_moove_count(game, line, column);
    int shifting = game->board[line][column].hero->race->shifting;
    int count = 0;
    Position* result = calloc(game->config_height*game->config_width, sizeof(Position));
    for (int i=0; i<game->config_height; i++) {
        for(int j=0; j<game->config_width; j++) {
            if(moove_count[i][j]<=shifting && moove_count[i][j] >=0) {
                result[count].line = i;
                result[count].column = j;
                count++;
            }
        }
    }

    *nb_position = count;
    return result;
}

Position* get_posible_attack(Game* game, int line, int column, int* nb_position) {
    int** scope_count = get_scope_count(game->board, line, column, game->config_height, game->config_width);
    int scope = game->board[line][column].hero->race->scope;
    HeroType enemy = (game->board[line][column].hero->type == BLUE)? RED: BLUE;
    int count = 0;
    Position* result = calloc(game->config_height*game->config_width, sizeof(Position));
    for (int i=0; i<game->config_height; i++) {
        for(int j=0; j<game->config_width; j++) {
            if(scope_count[i][j] <= scope && game->board[i][j].hero->type == enemy) {
                result[count].line = i;
                result[count].column = j;
                count++;
            }
        }
    }
    Position* no_attack = create_position(-1, -1);
    result[count++] = *no_attack;
    *nb_position = count;
    return result;
    
}

Node* develop_node(Node* first, Game* game, int who_is_playing)
{
    int nb_position;
    Position* heroes = get_heroes_position(game, (who_is_playing)? RED : BLUE, &nb_position);
    
    Position* initial;
    Position* move;
    Position* attack;
    
    Game* copy;
    Game* copy_attack;
    
    for(int i=0; i<nb_position; i++) {
 //       printf("========================== HERO (%d, %d) ==========================\n", heroes[i].line, heroes[i].column);
        initial = malloc(sizeof(Position));
        *initial = heroes[i];
        int nb_possible_moves;
        Position* possible_moves = get_posible_moves(game, initial->line, initial->column, &nb_possible_moves);

        for(int j = 0; j < nb_possible_moves; j++)
        {
            copy = copy_game(game);
   //         printf("------------------------- deplacement (%d, %d) -------------------------\n", possible_moves[j].line, possible_moves[j].column);
            moove(copy->board, initial->line, initial->column, possible_moves[j].line, possible_moves[j].column);
     //       printf("reel:\n");
     //       display_board(game->board, game->config_height, game->config_width);
       //     printf("deplacement:\n");
        //    display_board(copy->board, copy->config_height, copy->config_width);
            move = malloc(sizeof(Position));
            *move = possible_moves[j];
            int nb_possible_attack;
            Position* possible_attacks = get_posible_attack(copy, move->line, move->column, &nb_possible_attack);

            for(int k = 0; k < nb_possible_attack; k++)
            {
                copy_attack = copy_game(copy);
          //      printf("debug:\n");
                if(possible_attacks[k].line >= 0 && possible_attacks[k].column >= 0)
                    attack_and_response(copy_attack, possible_moves[j].line, possible_moves[j].column, possible_attacks[k].line, possible_attacks[k].column);                                
                int score = score_board(copy_attack, who_is_playing, possible_moves[j].line, possible_moves[j].column);
            //    display_board(copy_attack->board, copy_attack->config_height, copy_attack->config_width);
             //   printf(">>>>>>>>> attaque possible (%d, %d) <<<<<<<<\n", possible_attacks[k].line, possible_attacks[k].column);
                attack = malloc(sizeof(Position));
                *attack = possible_attacks[k];
                NodeValue* value = create_node_value(score, initial, move, attack);
                Node* new_branch = create_node(value);
                add_element(first, new_branch);
            }
           // getchar();
        }
    }
    return first;
}

Game* copy_and_play_action(Game* game, NodeValue* value)
{
    Game* copy = copy_game(game);
    moove(copy->board, value->initial_position->line, value->initial_position->column, value->move_position->line, value->move_position->column);
    if(value->attack_position->line >= 0 && value->attack_position->column >= 0)
    {
        attack_and_response(copy, value->move_position->line, value->move_position->column, value->attack_position->line, value->attack_position->column);
    }
    return copy;
}

Node* get_min(Node* node)
{
    Node* result = node->node_list;
    for(int i = 1; i < node->nb_arg; i++)
    {
        if(node->node_list[i].value->score < result->value->score)
            result = node->node_list + i;
    }
    return result;
}

Node* get_max(Node* node)
{
    Node* result = node->node_list;
    for(int i = 1; i < node->nb_arg; i++)
    {
        if(node->node_list[i].value->score > result->value->score)
            result = node->node_list + i;
    }
    return result;
}

NodeValue* get_ia_decision(Game* game, int who_is_playing, int size_of_tree)
{
    Node* first = create_node(NULL);
    develop_node(first, game, who_is_playing);
    Game* copy;
    
    switch(size_of_tree)
    {
        case 1:
        {
            Node* max = get_max(first);
            return max->value;
        }
        case 2:
        {
            Node* second_final = NULL;
            Node* min_final = NULL;
            /*
                dans ce for un il y a un seg fault non résolu qui apparait rarement en fin de partie
            */
            for(int i = 0; i < first->nb_arg; i++)
            {
                Node* second = first->node_list+i;
                printf("ici");
                copy = copy_and_play_action(game, second->value);
                printf("ici");
                develop_node(second, copy, !who_is_playing);                
                printf("ici");
                Node* min = get_max(second);
                printf("ici");
                if(((second_final == NULL) || (min_final == NULL)) || (min_final->value->score > min->value->score))
                {
                    second_final = second;
                    min_final = min;
                }
            }
            return second_final->value;
        }
    }
    return NULL;
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
        		sprintf(message, "%s%s préparez vous !", message_color, player->username);
				display_game(game, -1, -1, message);
				getchar();
		        

		        int initial_line = -1, initial_column = -1;
		        int move_line = -1, move_column = -1;
				int move_done = 0;
				do
				{
					do
					{
						sprintf(message, "%sSelectionnez une de vos unités pour un deplacement",message_color);
						select_a_box(game, 0, 0, &initial_line, &initial_column, message, 0);
					}while(game->board[initial_line][initial_column].hero->type != ((who_is_playing)?RED:BLUE));

					if (game->board[initial_line][initial_column].hero->is_tired)
					{
						sprintf(message, "%sCette unité est trop fatiguée..", message_color);
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
						sprintf(message, "%sCette unité ne peut pas de deplacer de plus de %d cases ...", message_color, game->board[initial_line][initial_column].hero->race->shifting);
						display_game(game, -1, -1, message);
						getchar();
					}
				}while(!move_done);

				if(can_attack(game, move_line, move_column))
				{	
					int** scope_count = get_scope_count(game->board, move_line, move_column, game->config_height, game->config_width);
					int attack_line = -1, attack_column = -1;
					int attack_done = 0;
					do
					{
						do
						{
							sprintf(message, "%sChoisissez l'unité que vous voulez attaquer. Appuyez sur 'q' pour passer", message_color);
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
							sprintf(message, "%sVotre unité a une portée d'attaque de %d cases", message_color, game->board[initial_line][initial_column].hero->race->shifting);
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
                NodeValue* ia_decision = get_ia_decision(game, who_is_playing, player->level);
                if(ia_decision->initial_position->line == ia_decision->move_position->line &&
                    ia_decision->initial_position->column == ia_decision->move_position->column)
                    sprintf(message, "%s%s a passé son déplacement",message_color, player->username);
                else
                {
                    moove(game->board, ia_decision->initial_position->line, ia_decision->initial_position->column, ia_decision->move_position->line, ia_decision->move_position->column);
                    sprintf(message, "%s a deplacé son hero de %c%d à %c%d", player->username, ia_decision->initial_position->line + 'A', ia_decision->initial_position->column+1, ia_decision->move_position->line + 'A', ia_decision->move_position->column+1);
                }
                char* attack_message = calloc(255, sizeof(char));
                if(ia_decision->attack_position->line >= 0 && ia_decision->attack_position->column >= 0)
                {
                    attack_and_response(game, ia_decision->move_position->line, ia_decision->move_position->column, ia_decision->attack_position->line, ia_decision->attack_position->column);
                    sprintf(attack_message, " et a attaqué en %c%d\n", ia_decision->attack_position->line + 'A', ia_decision->attack_position->column + 1);
                }                    
                else
                    sprintf(attack_message, " et a passé l'attaque");
                strcat(message, attack_message);
                game->board[ia_decision->move_position->line][ia_decision->move_position->column].hero->is_tired = 1;
                display_game(game, -1, -1, message);
                getchar();

                /*system("clear");

                Node* first = create_node(NULL);

                Game* copy ;
                
                Node* list_node = first;
                int nb_element_list_node = 1;

                int size_new_list = 255;
                int nb_element_new_list = 0;
                Node* new_list = calloc(size_new_list, sizeof(Node));

                int who_is_playing_tmp = who_is_playing;

                int cpt = 0, limit = 2;
                while(cpt < limit)
                {
                    printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
                    for(int i = 0; i < nb_element_list_node; i++) // 1
                    {
                        // COPIE DE LA GAME ET ACTIONS
                        copy = copy_game(game);
                        if(list_node[i].value != NULL)
                        {
                            NodeValue* value = list_node[i].value;
                            moove(copy->board, value->initial_position->line, value->initial_position->column, value->move_position->line, value->move_position->column);
                            if(value->attack_position->line >= 0 && value->attack_position->column >= 0)
                            {
                                attack_and_response(copy, value->move_position->line, value->move_position->column, value->attack_position->line, value->attack_position->column);
                            }                            
                        }

                        // ON DEVELOPPE LE NODE
                        *(list_node + i) = *(develop_node(list_node+i, copy, who_is_playing_tmp));
                        display_node(list_node+i, 0);
                        printf("nb_arg: %d", list_node[i].nb_arg);
                        getchar();

                        // !! SEG FAULT
                        for(int j = 0; j < list_node[i].nb_arg; j++)
                        {
                            printf("j:%d\n", j);
                            new_list[nb_element_new_list++] = list_node[i].node_list[j];
                            printf("added:");
                            display_node(list_node[i].node_list + j, 0);
                            getchar();
                            //printf("nb elements new list %d\n", nb_element_new_list);

                            if(nb_element_new_list >= size_new_list)
                            {
                                size_new_list += 255;
                                new_list = reallocarray(new_list, size_new_list, sizeof(Node));
                            }
                        }


                        display_board(copy->board, copy->config_height, copy->config_width);
                        display_node(list_node+i, 0);
                        getchar();
                    }
                    list_node = new_list;

                    nb_element_list_node = nb_element_new_list;
                    nb_element_new_list = 0;
                    who_is_playing_tmp = (who_is_playing_tmp)?0:1;
                    cpt++;

                    printf("%d/%d\n", cpt, limit);
                    printf("nb_element_list_node:%d\n", nb_element_list_node);
                    for(int i = 0; i < nb_element_list_node; i++)
                    {
                        //printf("--------------------- New node --------------------\n");
                        display_node(list_node+i, 0);
                    }
                    getchar();
                }
                
                for(int i = 0; i < first->nb_arg; i++)
                {
                    NodeValue* value = (first->node_list+i)->value;
                    moove(copy->board, value->initial_position->line, value->initial_position->column, value->move_position->line, value->move_position->column);
                    develop_node(first->node_list+i, copy, who_is_playing);
                }
                display_node(first, 0);                          
                getchar();

        		break;*/

               
        	}
        }
        is_player2_winner = update_game_state(game, &who_is_playing, &is_game_finished);
	}while(!is_game_finished);


    tcsetattr( STDIN_FILENO, TCSANOW, &oldMask);

	if(is_player2_winner) return game->player2;
	return game->player1;
}