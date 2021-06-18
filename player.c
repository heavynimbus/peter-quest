#include "player.h"

void display_player(Player* player){
	printf("Player(%s, %s)\n", player->username, (player->type)?"IA":"HUMAN");
}

void free_player(Player* player){
	free(player->username);
	free(player);
}