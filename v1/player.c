#include "player.h"

Player* create_player(PlayerType type, char* username){
	Player* result = malloc(sizeof(Player));
	result->type = type;
	result->username = username;
	return result;
}

void display_player(Player* player){
	printf("Player(%s, %s)\n", player->username, (player->type)?"IA":"HUMAN");
}

void free_player(Player* player){
	free(player->username);
	free(player);
}