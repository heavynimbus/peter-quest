#include "main.h"

typedef enum{
		HUMAN, IA 
}PlayerType;

typedef struct{
	PlayerType type;
	char* username;
}Player;

void display_player(Player* player);