#include "joueur.h"

Joueur* create_joueur(JoueurType type, char* username){
	printf("%d %s\n", type, username);

	char buffer[60];
	printf("Please enter your username: ");	
	fgets(buffer, 60, stdin);
	return malloc(sizeof(Joueur));
}