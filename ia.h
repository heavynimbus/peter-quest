#include "main.h"
#include "board.h"
#include "player.h"

#define NB_ALLY 1000
#define NB_ENEMY 500
#define HP_ALLY 20
#define HP_ENEMY 10
#define PROXIMITY_ALLY 1
#define PROXIMITY_ENEMY 0

//return the score board
int score_board(Box** board, Player* player, int column, int line);

