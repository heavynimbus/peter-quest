#include "game.h"

Game init_game() {

    Box** board = init_board();

    return (Game) {board, 'A', 'B'};
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

void playGame(Game game) {
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