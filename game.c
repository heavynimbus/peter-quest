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

void deplace(Box** board, Hero* hero, int column, char line){
    if (can_deplace(board, hero, column, line) == TRUE) {
        Box* newBox = choose_move(board, column, line, hero);
        Box* replaceBox = malloc(sizeof(Box));

        board[newBox->x][(int)newBox->y -'a'] = *newBox;

        // init replace box
        replaceBox->hero = (Hero*)create_hero(NONE_HERO, NONE_RACE);
        replaceBox->x = column;
        replaceBox->y = line;

        //le hero se déplace donc plus présent sur l'ancienne box
        board[(int)line-'a'][column] = *replaceBox;
        
        //display_hero(hero);
    }
}

int can_deplace(Box** board, Hero* hero, int column, char line){
    // check la race, on a le range a la fin
    int range = hero->race->shifting;

    for (int c=0; c<range; c++) {
        for (int l=0; l<range; l++) {
            if (check_distance(c, l, column, (int)line-'a') <= range) {
                if (have_unit(board, c, l) == FALSE) {
                    return TRUE;
                }
            }
        }
    }
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
    if(get_char(resHero->race->type) == get_char(NONE_RACE)) {
        return FALSE;
    }
    return TRUE;
}

int check_distance(int columnBox, int lineBox, int columnUnity, int lineUnity) {
    // calcul distance (yb-ya) + (xb-xa)
    return (lineUnity - lineBox) + (columnUnity - columnBox);
}

// TODO: change return to list of possibilities
Box* choose_move(Box** board, int column, char line, Hero* hero) {    
    int range = hero->race->shifting;
    
    Box* mouvementPossible = calloc(200, sizeof(Box));
    int cpt = 0;

    for (int c=0; c<range; c++) {
        for (int l=0; l<range; l++) {
            if (check_distance(c, l, column, (int)line-'a') <= range) {
                if (have_unit(board, c, l) == FALSE) {
                    mouvementPossible[cpt] = board[l][c];
                    cpt++;
                } else {
                    //Il y a une unité, contournement
                    
                }
            }
        }
    }

    // show all posibilities
    for (int e=0; e<cpt; e++) {
        printf("possibilité %d : %d%d%c", e, mouvementPossible->hero->type, mouvementPossible->x, mouvementPossible->y);
    }

    // choose mouvement
    int* choice1 = malloc(sizeof(int));
    char* choice2 = malloc(sizeof(char));

    printf("Le joueur indique les coordonnées : \n");
    scanf(" %c%d", choice1, choice2);

    int r = 0;
    int indiceTrouve = FALSE;
    while (r<cpt && indiceTrouve==FALSE) {
        if (mouvementPossible[r].x==*choice1 && mouvementPossible[r].y==*choice2){
            mouvementPossible->hero = hero;
            indiceTrouve=TRUE;
        } else {
            r++;
        }
    }
    
    printf("Emplacements trouvés : %d", cpt);
    return mouvementPossible[r];

}


void play_game(Game game) {
    char* response1 = malloc(sizeof(char));
    char *response2 = malloc(sizeof(char));
    Box **board = game.board;
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
    
void play_game_2p(Game game) {

    char* response1 = malloc(sizeof(char));
    char* response2 = malloc(sizeof(char));
    Box** board = game.board;
    Player* player1 = game.player1;
    //Player* player2 = game.player2;

    printf("%s indique les coordonnées d'une de ses unités : \n", player1->username);
	scanf(" %c%c", response1, response2);
    
    //test if unit exist
    while (have_unit(board, (int)*response2-48, *response1) == FALSE) {
        printf("Mauvaises coordonnées, veuillez renseigner de bonnes coordonnées.\n");
        printf("Le joueur indique les coordonnées d'une de ses unités : \n");
	    scanf(" %c%c", response1, response2);
    }
    
    Hero* heroTmp = get_hero(board, (int)*response2-48, *response1);


    // deplacement du hero du joueur 1
    deplace(board, heroTmp, (int)*response2-48, *response1);
    
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


