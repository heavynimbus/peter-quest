#include "main.h"

typedef enum{
		HUMAN, IA 
}PlayerType;

typedef struct{
	PlayerType type;
	char* username;
	int level;
}Player;

void display_player(Player* player);

void free_player(Player* player);