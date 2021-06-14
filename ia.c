#include "ia.h"

int score_board(Box** board, Player* player, int column, int line) {
    int score = 0;
    int countRed = 0;
    int countBlue = 0;
    int counthpRed = 0;
    int counthpBlue = 0;

    for (int i=0; i < HEIGHT; i++) {
        for (int j=0; j < WIDTH; j++) {

            switch (board[i][j].hero->type)
            {
                case RED:
                    countRed++;
                    counthpRed = counthpRed + board[i][j].hero->hp;
                    break;
                
                case BLUE:
                    countBlue++;
                    counthpBlue = counthpBlue + board[i][j].hero->hp;
                    break;
                default:
                    break;
            }            
        }
    }

    if (player->type == HUMAN) {
        score = score + countBlue*1000;
        score = score - countRed*500;
        score = score + counthpBlue*20;
        score = score - counthpRed*10;
    } else {
        score = score - countBlue*500;
        score = score + countRed*1000;
        score = score + counthpRed*20;
        score = score - counthpBlue*10;
    }

    return score;
}