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
    
    printf("%c \n", get_value(resHero));

    if(get_value(resHero) != ' ') {
        return TRUE;
    }
    return FALSE;
}

void choose_move(Box** board, int column, char line, Hero* hero) {
    set_hero(board, column, line, hero);
}

void playGame(Game game) {
    char response1;
    char response2;
    Box** board = game.board;
    printf("Le joueur indique les coordonnées d'une de ses unités : \n");
	scanf(" %c%c", &response1, &response2);
    while (have_unit(board, response1, response2) == FALSE) {
        printf("Mauvaises coordonnées, veuillez renseigner de bonnes coordonnées.\n");
        printf("Le joueur indique les coordonnées d'une de ses unités : \n");
	    scanf(" %c%c", &response1, &response2);
    }
    char l=response1;
    int c=(int)response2-'0';
    //choose_move(board, c+1, l, get_hero(board, c, l));    
    display_board(board);
}