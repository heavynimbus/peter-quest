#include "ia.h"

int score_board(Box** board, Player* player, int column, int line) {
    int score = 0;
    int count_red = 0;
    int count_blue = 0;
    int count_hp_r = 0;
    int count_hp_b = 0;
    int count_shifting_b = 0;
    int count_shifting_r = 0;

    int** scope_count = get_scope_count(board, line, column);

    for (int i=0; i < HEIGHT; i++) {
        for (int j=0; j < WIDTH; j++) {
            switch (board[i][j].hero->type)
            {
                case RED:
                    count_red++;
                    count_hp_r = count_hp_r + board[i][j].hero->hp;
                    count_shifting_r = count_shifting_r + scope_count[i][j];
                    break;
                
                case BLUE:
                    count_blue++;
                    count_hp_b = count_hp_b + board[i][j].hero->hp;
                    count_shifting_b = count_shifting_b + scope_count[i][j];
                    break;
                default:
                    break;
            }

        }
        // printf("\n\n\n");
        // display_debug(get_scope_count(board, line, column));
        // printf("\n%d\n%d", count_shifting_b, count_shifting_r);
        // getchar();
    }

    
    if (player->type == HUMAN) {
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

    printf("\n%d : %d\n", count_shifting_b, count_shifting_r);
    getchar();

    return score;
}