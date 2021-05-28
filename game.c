#include "game.h"

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

void deplace(Hero hero){
    display_hero(&hero);
}

int can_deplace(Hero hero){
    display_hero(&hero);
    return FALSE;
}

void attack(Hero hero){
    display_hero(&hero);
}

int can_attack(Hero hero){
    display_hero(&hero);
    return FALSE;
}

int have_unit(Box** board, int column, char line) {
    Hero* resHero = get_hero(board, column, line);
    if(get_char(resHero->race->type) != ' ') {
        return TRUE;
    }
    return FALSE;
}

void choose_move(Box** board, int column, char line, Hero* hero) {
    /*
    int res = 0;
    // check la race, on a le range a la fin

    int range = 1;
    // deplacement possible
    // TODO: change range by hero.range hero->race->range
    for (int k=1; k<range; k++) {
        if (get_hero(board, column+k, line) == ' ') {
            printf("Un emplacement est trouvé");
            res++;
        }
        if (get_hero(board, column-k, line) == ' ') {
            printf("Un emplacement est trouvé");
            res++;
        }
        if (get_hero(board, column, line+k) == ' ') {
            printf("Un emplacement est trouvé");
            res++;
        }
        if (get_hero(board, column, line-k) == ' ') {
            printf("Un emplacement est trouvé");
            res++;
        }
    }
    printf("Emplacements trouvés : %d", res);
    */
    // choix du déplacement peut etre dans le deplace
    set_hero(board, column, line, hero);
}

void play_game(Game game) {
    char* response1 = malloc(sizeof(char));
    char* response2 = malloc(sizeof(char));
    Box** board = game.board;
    printf("Le joueur indique les coordonnées d'une de ses unités : \n");
	scanf(" %c%c", response1, response2);
    
    //test if unit exist
    while (have_unit(board, (int)*response2-48, *response1) == FALSE) {
        printf("Mauvaises coordonnées, veuillez renseigner de bonnes coordonnées.\n");
        printf("Le joueur indique les coordonnées d'une de ses unités : \n");
	    scanf(" %c%c", response1, response2);
    }
    //char l=response1;
    //int c=(int)response2-'0';
    //choose_move(board, c+1, l, get_hero(board, c, l));    
    display_board(board);
}

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

void select_a_box(Game* game, int* height, int* width){
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
        set_pos(1, 30);
        printf("\e[%dA", HEIGHT*2 + 2);
    }while(choix != '\n');

    *height = line;
    *width = column;
    tcsetattr( STDIN_FILENO, TCSANOW, &oldMask);
}


void run(Game* game){
    show_logo();
    display_board(game->board);
    // faire la suite du jeu
    printf("\n%50sJoueur 1 préparez vous !","");
    getchar();
    int w;
    int h;
    select_a_box(game, &h, &w);
    printf("Selected : %d %d\n", h, w);
}


void free_game(Game* g){
    free_board(g->board);
    free_player(g->player1);
    free_player(g->player2);
    free(g);
}