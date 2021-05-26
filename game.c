#include "game.h"

void init_heros(Game game){
    set_hero(game.board, 1, 'b', create_hero(BLUE, ARCHER));
    set_hero(game.board, 2, 'b', create_hero(BLUE, SOLDIER));
    set_hero(game.board, 1, 'd', create_hero(BLUE, ARCHER));
    set_hero(game.board, 2, 'd', create_hero(BLUE, TRICKSTER));
    set_hero(game.board, 6, 'b', create_hero(RED, TRICKSTER));
    set_hero(game.board, 7, 'b', create_hero(RED, ARCHER));
    set_hero(game.board, 6, 'd', create_hero(RED, SOLDIER));
    set_hero(game.board, 7, 'd', create_hero(RED, ARCHER));  
}

Game init_game() {
    Box** board = init_board();
    Player* player1 = malloc(sizeof(Player));
    Player* player2 = malloc(sizeof(Player));
    Game game =(Game) {board, player1, player2};
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


void free_game(Game g){
    free_board(g.board);
    free_player(g.player1);
    free_player(g.player2);
}