#include "game.h"

/**
    Set the heros positions for the beginning of the game
*/
void init_heros(Game* game){
    set_hero(game->board, 1, 'b', create_hero(BLUE, ARCHER));
    set_hero(game->board, 2, 'b', create_hero(BLUE, SOLDIER));
    set_hero(game->board, 1, 'd', create_hero(BLUE, ARCHER));
    set_hero(game->board, 2, 'd', create_hero(BLUE, TRICKSTER));
    set_hero(game->board, 6, 'b', create_hero(RED, TRICKSTER));
    set_hero(game->board, 7, 'b', create_hero(RED, ARCHER));
    set_hero(game->board, 6, 'd', create_hero(RED, SOLDIER));
    set_hero(game->board, 7, 'd', create_hero(RED, ARCHER));
}

/**
    Create a game and initialize it
*/
Game* init_game() {
    Box** board = init_board();
    Player* player1 = malloc(sizeof(Player));
    Player* player2 = malloc(sizeof(Player));
    Game* game = malloc(sizeof(Game));
    game->board = board;
    game->player1 = player1;
    game->player2 = player2;
    init_heros(game);
    return game;
}

/**
    Swap the two heros from the boxes

    ! warning ! 
    there is no verification, you have to do it before call this function
*/
void move(Box** board, int line1, int column1, int line2, int column2){
    Hero* save = board[line1][column1].hero;
    board[line1][column1].hero = board[line2][column2].hero;
    board[line2][column2].hero = save;
}

/**
    The first hero (at line1, column1) attack the second and deals damages
    reduced by the armor (min 1)

    ! warning ! 
    there is no verification, you have to do it before call this function  
*/
int attack(Box** board, int line1, int column1, int line2, int column2)
{
    Hero* hero1 = board[line1][column1].hero;
    Hero* hero2 = board[line2][column2].hero;
    int damage = hero1->race->attack;
    int scope = hero1->race->scope;
    int len = line1 - line2 + column1 - column2;
    len = (len < 0)? -len: len;
    if (len > scope) return -1;
    hero2->hp = (hero2->race->defense < damage)? hero2->hp - damage + hero2->race->defense: hero2->hp-1;   
    if(hero2->hp <= 0) kill(board, line2, column2);   
    return 0;
}

/**
    Predicate 
    return 1 (TRUE) if there is an enemy around him
    return 0 (FALSE) if not 
*/
int can_attack(Box** board, int line, int column)
{
    Hero* hero = board[line][column].hero;
    if(hero->type == NONE_HERO) return FALSE;

    int scope =  hero->race->scope;
    HeroType ennemy_type = (hero->type == RED)? BLUE: RED;
    for(int i = 0; i < BOX_HEIGHT; i++)
    {
        for(int j = 0; j < BOX_WIDTH; j++)
        {
            int len = line - i + column - j;
            len = (len < 0)? -len: len;
            if (len <= scope && board[i][j].hero->type == ennemy_type) return TRUE;
        }
    }
    return FALSE;
}

/**
    Set the player to the game
*/
void set_player(Game g, char* username, PlayerType type, int id){
    switch(id){
        case 1:
            g.player1->username = username;
            g.player1->type = type;
            break;
        case 2:
            g.player2->username = username;
            g.player2->type = type;
            break;
    }
}

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
    int x1 = 15, y1 = 18;
    int x2 = 100, y2 = 18;

    set_pos(x1, y1);
    printf("%s%s", BLUE_BACKGROUND, game->player1->username);
    x1 -= 5; y1 += 2;

    set_pos(x2, y2);
    printf("%s%s", RED_BACKGROUND, game->player2->username);
    x2 -=5; y2 += 2;

    for(int i = 0; i < BOX_HEIGHT; i++)
    {
        for(int j = 0; j < BOX_WIDTH; j++)
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
    print a message below the game
*/
void display_message(char* message)
{
    set_pos(1,30);
    printf("%50s%s", "", message);
}


/**
    This method is interactive the the user
    In height (int*) and width (int*) arguments will be stocked the position selected by the user
*/
void select_a_box(Game* game, int* height, int* width, char* message){
    static struct termios oldMask, newMask;
    show_logo();
    tcgetattr ( STDIN_FILENO, &oldMask );
    newMask = oldMask;
    newMask.c_lflag &= ~(ICANON); // avoid <enter>
    newMask.c_lflag &= ~(ECHO); // hide text typed
    tcsetattr( STDIN_FILENO, TCSANOW, &newMask);

    int column=0, line=0;
    int choix;
    do{
        display_board_underlined(game->board, line, column);
        display_player_informations(game);
        if(strlen(message) != 0) display_message(message);
        switch(choix = getchar()){
            case 0x41: // up key
                line--;
                break;
            case 0x42: // down key
                line++;
                break;
            case 0x43: // right key
                column++;
                break;
            case 0x44: // left key
                column--;
                break;
        }
        line = (line < 0)? line + BOX_HEIGHT: (line >= BOX_HEIGHT)? line - BOX_HEIGHT: line;
        column = (column < 0)? column + BOX_WIDTH: (column >= BOX_WIDTH)? column - BOX_WIDTH: column;
        column %= BOX_WIDTH;
        set_pos(1, 31);
        printf("\e[%dA", HEIGHT*2 + 3);
    }while(choix != '\n');

    *height = line;
    *width = column;
    tcsetattr( STDIN_FILENO, TCSANOW, &oldMask);
}

/*
    Check if the game is finished and change who is playing
*/
int update_game_state(Game* game, int* who_is_playing, int* is_game_finished){
    int count1=0, count2=0;
    for(int i = 0; i < BOX_HEIGHT; i++)
    {
        for (int j = 0; j < BOX_WIDTH; j++)
        {
            switch(game->board[i][j].hero->type)
            {
                case BLUE:
                    count1 = (game->board[i][j].hero->hp > 0)? count1+1: count1;
                    break;
                case RED:
                    count2 = (game->board[i][j].hero->hp > 0)? count2+1: count2;
                    break;
                case NONE_HERO:
                    continue;
            }
        }
    }
    *is_game_finished = (count1 == 0 || count2 == 0 )? 1:0; 

    *who_is_playing = (*who_is_playing)?0:1;
    return 0;
}

Player* run(Game* game){
    char* message = calloc(100, sizeof(char));
    char* message_color;
    int who_is_playing = 0, is_game_finished = 0;
    Player* player;

    do{
        if(who_is_playing)
        {
            message_color = RED_COLOR;
            player = game->player2;
        }else{
            message_color = BLUE_COLOR;
                player = game->player1;
        }

        show_logo();
        display_board(game->board);
        sprintf(message, "%s%s préparez vous !", message_color, (who_is_playing)?game->player2->username: game->player1->username);
        display_message(message);
        getchar();
        
        // TODO
        // demander son deplacement
        int initial_line = -1, initial_column = -1;
        int move_line = -1, move_column = -1;
        int attack_line = -1, attack_column = -1;
        int attack_res = -2, move_done = 0;
        do{
            do{ 
                sprintf(message, "%sVous devez choisir une de vos unités", message_color);
                select_a_box(game, &initial_line, &initial_column, message);
            }while(game->board[initial_line][initial_column].hero->type != ((who_is_playing)?RED:BLUE));

            do{
                sprintf(message, "%sVous devez choisir un deplacement", message_color);
                select_a_box(game, &move_line, &move_column, message);
            }while(game->board[move_line][move_column].hero->type != NONE_HERO);
            
            move(game->board, initial_line, initial_column, move_line, move_column);
            move_done = 1;

        }while(!move_done);
        // deplacer l'unite
        // si l'unite peut attaquer, attaquer

        //attaque
        if(can_attack(game->board, move_line, move_column))
        do
        {
            if(attack_res > -2)
            {
                show_logo();
                display_board(game->board);
                sprintf(message, "%sL'unité ennemi est trop loin, choisissez une autre unité", message_color);
                display_message(message);
                getchar();
            }
            
            do{ 
                sprintf(message, "%sVous devez choisir une unité ennemie", message_color);
                select_a_box(game, &attack_line, &attack_column, message);
            }while(game->board[attack_line][attack_column].hero->type != ((who_is_playing)?BLUE:RED)); 

            // recuperer les deplacements possible pour cette unité
            // int attack(Box** board, int x1, int y1, int x2, int y2)
            attack_res = attack(game->board, move_line, move_column, attack_line, attack_column);
            if(game->board[attack_line][attack_column].hero->hp > 0) attack(game->board, attack_line, attack_column, move_line, move_column);
        }while(attack_res < 0);

        update_game_state(game, &who_is_playing, &is_game_finished);
    }while(!is_game_finished);
    free(message);
    return player; // the winner
}


/**
    Safe free for a game
*/
void free_game(Game* g){
    free_board(g->board);
    free_player(g->player1);
    free_player(g->player2);
    free(g);
}