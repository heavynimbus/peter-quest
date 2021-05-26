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


//TODO : add la fatigue + gestion de la portée.
int attack(Box** board, int x1, int y1, int x2, int y2)
{

    Hero* hero1 = get_hero(board, y1, x1);
    Hero* hero2 = get_hero(board, y2, x2);
    int damage = hero1->race->attack;
    int scope = hero1->race->scope;
    int len = x1 - x2 + y1 - y2;
    printf("attack : %d\n", damage);
    printf("pv du hero2 : %d\n", hero2->hp);

    if (len > scope) {
        return -1;
    } else {
        if (hero2->race->defense < damage) {
        hero2->hp = hero2->hp - damage + hero2->race->defense;
        } else {
            printf("La défense de la cible est trop élevée\n");
        }
        return 0;
    }
    
    
    display_hero(hero2);

    return 0;

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
    set_hero(board, column, line, hero);
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