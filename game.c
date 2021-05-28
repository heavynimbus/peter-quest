#include "game.h"

void init_heros(Game game){
    Hero* ally1 = create_hero(BLUE, ARCHER);
    Hero* ally2 = create_hero(BLUE, SOLDIER);
    Hero* ally3 = create_hero(BLUE, ARCHER);
    Hero* ally4 = create_hero(BLUE, TRICKSTER);
    set_hero(game.board, 1, 'b', ally1);
    set_hero(game.board, 2, 'b', ally2);
    set_hero(game.board, 1, 'd', ally3);
    set_hero(game.board, 2, 'd', ally4);
    Hero* enemy1 = create_hero(RED, TRICKSTER);
    Hero* enemy2 = create_hero(RED, ARCHER);
    Hero* enemy3 = create_hero(RED, SOLDIER);
    Hero* enemy4 = create_hero(RED, ARCHER);
    set_hero(game.board, 6, 'b', enemy1);
    set_hero(game.board, 7, 'b', enemy2);
    set_hero(game.board, 6, 'd', enemy3);
    set_hero(game.board, 7, 'd', enemy4);  
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


